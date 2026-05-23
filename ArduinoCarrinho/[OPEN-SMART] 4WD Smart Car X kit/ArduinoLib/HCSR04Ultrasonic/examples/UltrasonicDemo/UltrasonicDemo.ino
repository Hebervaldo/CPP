/*
 // HCSR04Ultrasonic/examples/UltrasonicDemo/UltrasonicDemo.ino
 // for 4WD Bluetooth by catalex
 // Store: http://www.aliexpress.com/store/1199788
//      
 */

#include <Ultrasonic.h>


#define TRIGGER_PIN  A3//connect Trip of the Ultrasonic Sensor moudle to A3 of Arduino 
                      //and can be changed to other ports
#define ECHO_PIN     A2

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup()
  {
  Serial.begin(9600);
  }

void loop()
  {
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  Serial.print("MS: ");
  Serial.print(microsec);
  Serial.print(", CM: ");
  Serial.print(cmMsec);
  Serial.print(", IN: ");
  Serial.println(inMsec);
  delay(1000);
  }
