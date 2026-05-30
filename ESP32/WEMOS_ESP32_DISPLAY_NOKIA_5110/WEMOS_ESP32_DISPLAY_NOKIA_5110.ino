#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

/* Declare LCD object for SPI
 Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);*/
Adafruit_PCD8544 display = Adafruit_PCD8544(14, 13, 5, 15, 4); /*D5, D7, D1, D8, D2 */
int contrastValue = 60; /* Default Contrast Value */

void setup()
{
  /* Initialize the Display*/
  display.begin();

  /* Change the contrast using the following API*/
  display.setContrast(contrastValue);

  /* Clear the buffer */
  display.clearDisplay();
  display.display();
  delay(100);
  
  /* Now let us display some text */
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.setCursor(15,1);
  display.println("|ESP32|");
  display.setCursor(15,13);
  display.println("|NodeMCU|");
  //display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(22,25);
  display.println("|Nokia|");
  display.setCursor(25,37);
  display.println("|5110|");
  display.display();
  //delay(2000);
}

void loop()
{
  
}