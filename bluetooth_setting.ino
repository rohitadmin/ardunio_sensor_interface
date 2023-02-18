#include <SoftwareSerial.h>



SoftwareSerial BTserial(0, 1);

String BT_data;
String Arduino_Data;

void setup()
{
    Serial.begin(9600);  //Sets the data rate in bits per second (baud) for serial data transmission
    //pinMode(13, OUTPUT); //Sets digital pin 13 as output pin
    BTserial.begin(9600);
}

void loop()
{
    if(Serial.available())       // Send data only when you receive data:
    {
        Arduino_Data = Serial.readString();
        BTserial.println(Arduino_Data);
    }
    if(BTserial.available())       // Send data only when you receive data:
    {
        BT_data = BTserial.readString();
        Serial.println(BT_data);
    }                   
}
