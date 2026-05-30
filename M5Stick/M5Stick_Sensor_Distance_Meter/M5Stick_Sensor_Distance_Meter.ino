 /*
 * file: M5Stack_VL53L0X_advanced
 Measure distance using VL53L0X Laser Distance Sensor and dispaly on M5Stack Core 2 ESP3D IoT board
 * Written by Ahmad Shamshiri on April 03, 2021 in Ontario, Canada
 www.Robojax.com youTube http://youTube.com/robojaxTV
 
 using Pololu VL53L0X library https://github.com/pololu/vl53l0x-arduino
 * watch video instruction: https://youtu.be/6Js7CPe7Dwo
 * 
 * Must watch two videos
 * Introduction to M5Stack Core 2:https://youtu.be/zoDjT2_0M5g
 * Introduction to VL53L0X: https://youtu.be/S2jaAQEv3Yo
 * 

 * 
  * 
 * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.* 
 * This code has been download from Robojax.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
  
   URL: https://github.com/RobTillaart/HT16K33
  
*/
#include <M5Core2.h>

#include <Wire.h>

#include <VL53L0X.h>

VL53L0X sensor;
const uint8_t maximumDistance = 800;///mm 800mm=80cm
uint8_t type = 2;// 1=mm , 2= cm
char *unit[]={"mm","cm"};// variable for unit, mm or cm

float distanceCm;
uint8_t distance;

void printOnSerial();

//setup() runs only once. 
void setup() {
 
  M5.begin();
  M5.Lcd.fillScreen(YELLOW);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.print("Robojax");
  M5.Lcd.print("Distance");
  M5.Lcd.setTextSize(5);
  M5.Lcd.fillScreen(BLACK);

  Wire.begin();        // join i2c bus (address optional for master)
  Serial.println("VLX53LOX test started.");

  Serial.begin(9600);


  sensor.init();
  sensor.setTimeout(500);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();


delay(1000);


}

void loop() {
  M5.Lcd.fillScreen(BLACK);    
  M5.Lcd.setCursor(0,0);  
  M5.Lcd.print("Distance"); 

  M5.update();

  if(M5.BtnA.wasPressed())
  { 
    type=2;
  }
  if(M5.BtnB.wasPressed())
  {
   type=1;
  }
  if(M5.BtnC.wasPressed())
  {
    M5.Lcd.setCursor(0,0);  
    M5.Lcd.setTextSize(4);    
    M5.Lcd.fillScreen(BLACK);  
    M5.Lcd.print("Shutting down");
    M5.Lcd.setTextColor(YELLOW);    
    M5.Lcd.print("");    
    M5.Lcd.print("Use Power switch to turn it ON.");    
    delay(3000);     
    M5.shutdown();
  }  

 distance =sensor.readRangeContinuousMillimeters();//get the distance in mm

  if(type==2){
     M5.Lcd.setCursor(0, 60);      
    distanceCm =(float) (distance/10.0);//convert distance to cm
    M5.Lcd.printf("%.1f", distanceCm);
    //M5.Lcd.print(distanceCm);
    M5.Lcd.print(unit[type-1]);    
  }else{
    M5.Lcd.setCursor(0, 60);  
    M5.Lcd.print(distance);
    M5.Lcd.print(unit[type-1]);
  }
  



  
  delay(500);
  //printOnSerial();
}

void printOnSerial()
{
      Serial.print("Distance: ");  
        if(type==2){ 
           Serial.print(distanceCm);
        }else{
           Serial.print(distance);         
        }
      Serial.print(unit[type-1]);      
      Serial.println();  
}
 
