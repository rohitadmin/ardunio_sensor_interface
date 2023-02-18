#include <AltSoftSerial.h>
 
// RO to pin 8 & DI to pin 9 when using AltSoftSerial
#define RE 6
#define DE 7
 
const byte nitro[] = {0x01, 0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01, 0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01, 0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};
 
byte values[11];
AltSoftSerial mod;
 
void setup() {
  Serial.begin(9600);
  mod.begin(9600);
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
 
  // put RS-485 into receive mode
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
  //delay(3000);
}
 
void loop() {
  byte val1, val2, val3;
  Serial.print("Nitrogen: ");
  val1 = nitrogen();
  Serial.print(" = ");
  Serial.print(val1);
  Serial.println(" mg/kg");
  delay(250);
 
  Serial.print("Phosphorous: ");
  val2 = phosphorous();
  Serial.print(" = ");
  Serial.print(val2);
  Serial.println(" mg/kg");
  delay(250);
 
  Serial.print("Potassium: ");
  val3 = potassium();
  Serial.print(" = ");
  Serial.print(val3);
  Serial.println(" mg/kg");
  Serial.println();
  Serial.println();
  delay(3000);
}
 
byte nitrogen() {
  // clear the receive buffer
  mod.flushInput();
 
  // switch RS-485 to transmit mode
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
 
  // write out the message
  for (uint8_t i = 0; i < sizeof(nitro); i++ ) mod.write( nitro[i] );
 
  // wait for the transmission to complete
  mod.flush();
  
  // switching RS485 to receive mode
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
 
  // delay to allow response bytes to be received!
  delay(10);
 
  // read in the received bytes
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    Serial.print(values[i], HEX);
    Serial.print(' ');
  }
  return values[4];
}
 
byte phosphorous() {
  mod.flushInput();
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
  for (uint8_t i = 0; i < sizeof(phos); i++ ) mod.write( phos[i] );
  mod.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
// delay to allow response bytes to be received!
  delay(10);
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    Serial.print(values[i], HEX);
    Serial.print(' ');
  }
  return values[4];
}
 
byte potassium() {
  mod.flushInput();
  digitalWrite(DE, HIGH);
  digitalWrite(RE, HIGH);
  delay(1);
  for (uint8_t i = 0; i < sizeof(pota); i++ ) mod.write( pota[i] );
  mod.flush();
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
// delay to allow response bytes to be received!
  delay(10);
  for (byte i = 0; i < 7; i++) {
    values[i] = mod.read();
    Serial.print(values[i], HEX);
    Serial.print(' ');
  }
  return values[4];
}
