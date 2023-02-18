#include <Wire.h>
#include <SFE_BMP180.h>
#define seaLevelPressure_hPa 1013.25
#define ALTITUDE 943.7  //

SFE_BMP180 bmp_val;

void setup() {
  Serial.begin(9600);
  if (bmp_val.begin()){
    Serial.println("BMP180 init success");
  }
  else
  {
    Serial.println("BMP180 init fail");
    while(1); // Pause forever.
  }
}
  
void loop() {
      // Air pressure monitoring
    char cuurent_air_status;
    double air_temperature, air_pressure, air_attitude, air_seal_level;

    cuurent_air_status = bmp_val.startTemperature();

    if (cuurent_air_status != 0)
    {
    // Wait for the measurement to complete:
    delay(cuurent_air_status);
    cuurent_air_status = bmp_val.getTemperature(air_temperature);
    
    if(cuurent_air_status!= 0){
      
      //Serial.println(".........Air Pressure Monitoring........");
      Serial.print("temp:");
      Serial.print(air_temperature, 2);
      //Serial.println(" *C");
      Serial.print(",");

      cuurent_air_status = bmp_val.startPressure(3);
      if (cuurent_air_status != 0)
      {
        delay(cuurent_air_status);
        cuurent_air_status = bmp_val.getPressure(air_pressure, air_temperature);

        if (cuurent_air_status != 0)
        {
          Serial.print("pressure:");
          Serial.print(air_pressure, 2);
          Serial.print(",");
//          Serial.print("hpa:");
//          Serial.print(air_pressure * 100, 2);
//          Serial.print(",");
//          Serial.print("pa:");
//          Serial.print(air_pressure * 0.000986923, 2);
//          Serial.print(" atm = ");
//          Serial.print(air_pressure * 0.750063755, 2);
//          Serial.print(" mmHg = ");
//          Serial.print(air_pressure * 0.750061683, 2);
//          Serial.print(" torr = ");
//          Serial.print(air_pressure * 0.014503774, 2);
          //Serial.println(" psi");

          air_seal_level = bmp_val.sealevel(air_pressure, ALTITUDE);
//          Serial.print("relative (sea-level) pressure:");
//          Serial.print(air_seal_level, 2);
//          Serial.println(" hpa ");
          
          air_attitude = bmp_val.altitude(air_pressure, air_seal_level);
          Serial.print("altitude:");
          Serial.print(air_attitude, 0);
          //Serial.println(" meters ");
        }
        else {
          Serial.println("error retrieving pressure measurement\n");
        }
        }
        else {
          Serial.println("error starting pressure measurement\n");
        }
      }
      else {
        Serial.println("error retrieving temperature measurement\n");
      }
    }
    else 
    {
      Serial.println("error starting temperature measurement\n");
    }
    delay(1000);
}
