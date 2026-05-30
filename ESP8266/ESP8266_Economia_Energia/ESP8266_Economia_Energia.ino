//Include da lib de Wifi do ESP8266
#include <ESP8266WiFi.h>
// change next line to use with another board/shield
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <EEPROM.h>

//Define o quanto sera alocado entre 4 e 4096bytes
#define MEM_ALOC_SIZE 8
//Variavel com o numero de boots do ESP
uint8_t boot_num = 0;

uint32_t sleep_time_s = 60 * 1000;

ADC_MODE(ADC_VCC); //vcc read

//Definir o SSID da rede WiFi
const char* ssid = "GVT-B60C";
//Definir a senha da rede WiFi
const char* password = "8428503319";

WiFiUDP ntpUDP;

int16_t utc = -3; //UTC -3:00 Brazil
NTPClient timeClient(ntpUDP, "a.st1.ntp.br", utc*3600, 60000);

//Colocar a API Key para escrita neste campo
//Ela é fornecida no canal que foi criado na aba API Keys
String apiKey = "<<<API_KEY>>>";
const char* server = "api.thingspeak.com";

WiFiClient client;

void setup() {
  //Configuração da UART
  Serial.begin(115200);

  Serial.print("Conectando na rede ");
  Serial.println(ssid);

  //Inicia o WiFi
  WiFi.begin(ssid, password);

  //Loop até conectar no WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();
  timeClient.update();

  //Aloca o espaco definido na memoria
  EEPROM.begin(MEM_ALOC_SIZE);
  //Le o valor de numero de boots na EEPROM
  boot_num = EEPROM.read(0);
  //Imcrementa o valor do boot
  boot_num++;
  //Escreve a atualizacao do valor
  EEPROM.write(0,boot_num);
  //Finaliza para o valor salvar na memoria
  EEPROM.end();
  //Imprime o valor na serial
  Serial.printf("Boot num: %d\n", boot_num);

  //Logs na porta serial
  Serial.println("");
  Serial.println("WiFi conectado!");
  Serial.print("Conectado na rede ");
  Serial.println(ssid);
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void envia_dados(void){

  //Inicia um client TCP para o envio dos dados
  if (client.connect(server,80)) {

    float vdd = ESP.getVcc() / 1024.0;

    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(timeClient.getEpochTime());
           postStr +="&field2=";
           postStr += String(boot_num);
           postStr +="&field3=";
           postStr += String(vdd);
           postStr += "\r\n\r\n";

     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(postStr.length());
     client.print("\n\n");
     client.print(postStr);

  }
  client.stop();

}

void loop() {
    envia_dados();
    ESP.deepSleep(sleep_time_s);
}
