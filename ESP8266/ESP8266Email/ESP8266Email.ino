/*
   Email client sketch for IDE v1.0.5 and w5100/w5200
   Posted 7 May 2015 by SurferTim
*/
 
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Ethernet.h>
 
// this must be unique
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0x59, 0x67 };  
// change network settings to yours
IPAddress ip( 192, 168, 25, 3 );    
IPAddress gateway( 192, 168, 25, 1 );
IPAddress subnet( 255, 255, 255, 0 );

EthernetClient client;

WiFiClient client_;

const char* ssid = "Bijuu_Kurama"; // Change to the name of your network
const char* password = "4312543125"; // Change to your network password
int status = WL_IDLE_STATUS; // the Wifi radio's status

//change server to your email server ip or domain
//IPAddress server(n, n, n); use this or next line 1 or the other not both
char server[] = "smtp.gmail.com"; //Change to your smtp server
int port = 465; // this port for smtp2go

void setup()
{
  delay(2000);
  Serial.begin(115200);
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) 
  {
    Serial.println(F("WiFi shield not present")); 
    // don't continue:
    while(true);
  } 
  
  // check firmware version
  // Serial.print(F("Firmware version: ")); did not have firmmware function.
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) 
  { 
    Serial.print(F("Attempting to connect to open SSID: "));
    Serial.println(ssid);
    status = WiFi.begin(ssid,password);
    
    // wait 10 seconds for connection:
    delay(10000);
  }

  // you're connected now, so print out the data:
  Serial.print(F("You're connected to the network"));
  // printCurrentNet();
  // printWifiData();
  
  delay(2000);
  Serial.println(F("Ready. Press 'e' to send."));

  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  delay(2000);
  Serial.println(F("Ready. Press 'e' to send."));

}

void loop()
{
  byte inChar;
 
  inChar = Serial.read();
 
  // if(inChar == 'e')
  {
      if(sendEmail()) Serial.println(F("Email sent"));
      else Serial.println(F("Email failed"));
  }
}
 
byte sendEmail()
{
  byte thisByte = 0;
  byte respCode;
 
  if(client.connect(server,port) == 1) {
    Serial.println(F("connected"));
  } else {
    Serial.println(F("connection failed"));
    return 0;
  }
 
  if(!eRcv()) return 0;
 
  Serial.println(F("Sending hello"));
// replace 1.2.3.4 with your Arduino's ip
  client.println("EHLO 1.2.3.4");
  if(!eRcv()) return 0;
 
  Serial.println(F("Sending auth login"));
  client.println("auth login");
  if(!eRcv()) return 0;
 
  Serial.println(F("Sending User"));
// Change to your base64 encoded user
  client.println("ZXNwODI2NnVAZ21haWwuY29t");
 
  if(!eRcv()) return 0;
 
  Serial.println(F("Sending Password"));
// change to your base64 encoded password
  client.println("ZXNwODI2NnU=");
 
  if(!eRcv()) return 0;
 
// change to your email address (sender)
  Serial.println(F("Sending From"));
  client.println("MAIL From: <esp8266us@gmail.com>");
  if(!eRcv()) return 0;
 
// change to recipient address
  Serial.println(F("Sending To"));
  client.println("RCPT To: <hebervaldo@gmail.com>");
  if(!eRcv()) return 0;
 
  Serial.println(F("Sending DATA"));
  client.println("DATA");
  if(!eRcv()) return 0;
 
  Serial.println(F("Sending email"));
 
// change to recipient address
  client.println("To: You <hebervaldo@gmail.com>");
 
// change to your address
  client.println("From: Me <esp8266us@gmail.com>");
 
  client.println("Subject: Arduino email test\r\n");
 
  client.println("This is from my Arduino!");
 
  client.println(".");
 
  if(!eRcv()) return 0;
 
  Serial.println(F("Sending QUIT"));
  client.println("QUIT");
  if(!eRcv()) return 0;
 
  client.stop();
 
  Serial.println(F("disconnected"));
 
  return 1;
}
 
byte eRcv()
{
  byte respCode;
  byte thisByte;
  int loopCount = 0;
 
  while(!client.available()) {
    delay(1);
    loopCount++;
 
    // if nothing received for 10 seconds, timeout
    if(loopCount > 10000) {
      client.stop();
      Serial.println(F("\r\nTimeout"));
      return 0;
    }
  }
 
  respCode = client.peek();
 
  while(client.available())
  {  
    thisByte = client.read();    
    Serial.write(thisByte);
  }
 
  if(respCode >= '4')
  {
    efail();
    return 0;  
  }
 
  return 1;
}
 
 
void efail()
{
  byte thisByte = 0;
  int loopCount = 0;
 
  client.println(F("QUIT"));
 
  while(!client.available()) {
    delay(1);
    loopCount++;
 
    // if nothing received for 10 seconds, timeout
    if(loopCount > 10000) {
      client.stop();
      Serial.println(F("\r\nTimeout"));
      return;
    }
  }
 
  while(client.available())
  {  
    thisByte = client.read();    
    Serial.write(thisByte);
  }
 
  client.stop();
 
  Serial.println(F("disconnected"));
}
