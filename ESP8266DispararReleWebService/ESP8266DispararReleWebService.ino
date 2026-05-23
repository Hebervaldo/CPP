//****************************************************************************************
//                             ESP 8266 Disparador de Rele 
//                       Hebervaldo de Paula Carvalhedo, Julho 2017
//****************************************************************************************

// Build 1
//   r1 - Disparador de Rele, webserver, email, etc.

//*****************************************************************************************
#define bld  1
#define rev  1
//*****************************************************************************************

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <rBase64.h>
#include <RTClib.h> // RTC-Library
#include <WiFiManager.h>

#include "user_interface.h"

#define CycleThread1 250U
#define CycleThread2 250U
#define CycleThread3 250U
#define CycleThread4 250U

//Define o quanto sera alocado entre 4 e 4096bytes
#define MEM_ALOC_SIZE 512

unsigned long thread1LastMillis = 0; 
unsigned long thread2LastMillis = 0;
unsigned long thread3LastMillis = 0;
unsigned long thread4LastMillis = 0;

boolean thread1State = false;
boolean thread2State = false;
boolean thread3State = false;
boolean thread4State = false;

boolean modoAcionarRele = false;
unsigned int intervaloDuracaoAcionamentoRele = 500;
unsigned long quantidadeDisparoRele = 0;

WiFiClient client;
WiFiClientSecure client_;
WiFiServer server(80);
WiFiManager wifiManager; // WiFiManager: Local intialization. Once its business is done, there is no need to keep it around
WiFiUDP ntpUDP;

String req;

#define LED_ONBOARD LED_BUILTIN

#define PINO_GPIO0 0
#define PINO_GPIO1 1
#define PINO_GPIO2 2
#define PINO_GPIO3 3
#define PINO_GPIO4 4
#define PINO_GPIO5 5
#define PINO_GPIO6 6
#define PINO_GPIO7 7
#define PINO_GPIO8 8
#define PINO_GPIO9 9
#define PINO_GPIO10 10
#define PINO_GPIO11 11
#define PINO_GPIO12 12
#define PINO_GPIO13 13
#define PINO_GPIO14 14
#define PINO_GPIO15 15
#define PINO_GPIO16 16
#define PINO_IN PINO_GPIO4
#define PINO_RESET PINO_GPIO13

String numeroIP;
String numeroMAC;
String chipId;
String uptime;

const char *ssid = "ESP8266US";         // WIFI network name
const char *password = "";              // WIFI network password

const int cntintTimeout = 480;
const int cntintConnectTimeout = 60;

ADC_MODE(ADC_VCC); //vcc read

long ulngTempoRestanteEmailEnviado = 0;
long ulngTempoRestanteTempoLigado = 0;

long ulngDiferencaIntervaloEmailEnviado = 0;
long ulngDiferencaIntervaloTempoLigado = 0;

long ulngIntervaloEmailEnviado = 0 ;
long ulngIntervaloTempoLigado = 0;

const int cntintNumeroBoot = 0;
const int cntintAtivarModoDormir = 0;
const int cntintTempoMaximoDesligado = 71;
const int cntintTentativaAtualizarClienteDataHora = 3;
const int cntintTentativaEnviarEmail = 3;

const String cntstrEmailEmitente = "esp8266us@gmail.com";
const String cntstrEmailRecebedor = "esp8266us@gmail.com";
const String cntstrUsuario = "esp8266us@gmail.com";
const String cntstrSenha = "esp8266u";
const String cntstrServidor = "smtp.gmail.com";
const int cntintPorta = 465;
const int cntintEmailTempo = 600;
const int cntintTempoDesligado = cntintTempoMaximoDesligado;
const int cntintTempoLigado = -1;
const int cntintNumeroMaximoReinicio = 0;
const int cntintNumeroReinicio = 0;

String strEmailEmitente = cntstrEmailEmitente;
String strEmailRecebedor = cntstrEmailRecebedor;
String strUsuario = cntstrUsuario;
String strSenha = cntstrSenha;
String strServidor = cntstrServidor;
int intPorta = cntintPorta;
int intEmailTempo = cntintEmailTempo;
int intTempoDesligado = cntintTempoDesligado;
int intTempoLigado = cntintTempoLigado;
int intNumeroMaximoReinicio = cntintNumeroMaximoReinicio;
int intNumeroReinicio = cntintNumeroReinicio;

float vdd = 0;
uint8_t boot_num = cntintNumeroBoot;
int intAtivarModoDormir = cntintAtivarModoDormir;
bool blnPrimeiroEmail = true;
String Senha_base64 = "";

// int16_t utc = -3; //UTC -3:00 Brazil
int16_t utc = +3;

// const char* ntpServerName = "time.nist.gov";
// IPAddress timeServerIP(129, 6, 15, 28); // time.nist.gov NTP server
// unsigned int localPort = 2390; // local port to listen for UDP packets
const char* ntpServerName = "a.st1.ntp.br";
IPAddress timeServerIP(200, 160, 7, 186); // a.st1.ntp.br NTP server
unsigned int localPort = 2390; // local port to listen for UDP packets

#define NTP_PACKET_SIZE 48 // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets

// RTC handler
RTC_Millis RTC; // RTC (soft)
DateTime now; // current time
int ch, cm, cs, cdy, cmo, cyr, cdw; // current time & date variables

#define min(a,b) ((a)<(b)?(a):(b)) // recreate the min function

String assunto = "ESP 8266 - Disparador de Rele";
String mensagem = "";

// sendNTPpacket(): send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.begin(115200);
  Delay_(10);
  Serial.begin(115200);
  Delay_(10);

  Serial.println("Sending UDP NTP packet request");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE); // set all bytes in the buffer to 0
  // Initialize values needed to form NTP request
  packetBuffer[0] = 0b11100011; // LI, Version, Mode
  packetBuffer[1] = 0; // Stratum, or type of clock
  packetBuffer[2] = 6; // Polling Interval
  packetBuffer[3] = 0xEC; // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;

  ntpUDP.beginPacket(address, 123); // NTP requests are to port 123
  ntpUDP.write(packetBuffer, NTP_PACKET_SIZE); // all NTP fields have values, send UDP packet requesting a timestamp
  ntpUDP.endPacket();

  Delay_(10);
}

// getTime(): get current time from RTC (soft or hard)
void mtdObterDataHora()
{
  Serial.begin(115200);
  Delay_(10);
  Serial.begin(115200);
  Delay_(10);

  now = RTC.now();
  ch = min(23, now.hour());
  cm = min(59, now.minute());
  cs = min(59, now.second());
  cdy = min(31, now.day());
  cmo = min(12, now.month());
  cyr = min(9999, now.year());
  cdw = now.dayOfTheWeek();

  Delay_(10);
}

// IsDST(): returns true if during DST, false otherwise
boolean IsDST(int mo, int dy, int dw)
{
  Serial.begin(115200);
  Delay_(10);
  Serial.begin(115200);
  Delay_(10);

  if (mo < 3 || mo > 11) // January, February, and December are out.
  {
    return false;
  }
  if (mo > 3 && mo < 11) // April to October are in
  {
    return true;
  }
  int previousSunday = dy - dw;
  if (mo == 3) // In March, we are DST if our previous Sunday was on or after the 8th.
  {
    return previousSunday >= 8;
  }

  Delay_(10);
  
  return previousSunday <= 0; // In November we must be before the first Sunday to be DST. That means the previous Sunday must be before the 1st.
}

void mtdIniciarClienteDataHora()
{
  Serial.begin(115200);
  Delay_(10);
  Serial.begin(115200);
  Delay_(10);

  RTC.begin(DateTime(F(__DATE__), F(__TIME__))); // initially set to compile date & time
  ntpUDP.begin(localPort);
  Serial.print(F("Starting UDP with Local Port "));
  Serial.println(ntpUDP.localPort());
  
  Delay_(10);  
}

bool mtdAtualizarClienteDataHora(int tz)
{
  Serial.begin(115200);
  Delay_(10);
  Serial.begin(115200);
  Delay_(10);

  bool Retorno = false;

  //get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP); 

  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  // sendNTPpacket(NTP_ADDRESS);
  // wait to see if a reply is available
  Delay_(1000); // wait to see if a reply is available

  int cb = ntpUDP.parsePacket(); // get packet (if available)
  if (!cb)
  {
    Serial.println(F("... no packet yet"));

    Retorno = false;
  }
  else
  {
    Serial.print(F("... NTP packet received with "));
    Serial.print(cb);
    Serial.println(F(" bytes")); // We've received a packet, read the data from it
    ntpUDP.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]); // timestamp starts at byte 40 of packet. It is 2 words (4 bytes) long
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]); // Extract each word and...
    unsigned long secsSince1900 = highWord << 16 | lowWord; // ... combine into long: NTP time (seconds since Jan 1 1900):
  
    const unsigned long seventyYears = 2208988800UL; // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    unsigned long epoch = secsSince1900 - seventyYears; // subtract seventy years to get to 1 Jan. 1900:
  
    DateTime gt(epoch - (tz * 60 * 60)); // obtain date & time based on NTP-derived epoch...
    tz = IsDST(gt.month(), gt.day(), gt.dayOfTheWeek()) ? tz : tz + 1; // if in DST correct for GMT-(tz) hours else GMT-(tz + 1)
    DateTime ntime(epoch - (tz * 60 * 60)); // if in DST correct for GMT-(tz) hours else GMT-(tz + 1)
    RTC.adjust(ntime); // and set RTC to correct local time

    Retorno = true;
  }

  Delay_(10);

  return Retorno;
}

String mtdObterDataFormatada()
{
  Serial.begin(115200);
  Delay_(10);
  Serial.begin(115200);
  Delay_(10);

  String Retorno = "";
  mtdObterDataHora();

  Retorno = String(cdy < 10 ? "0" : "") + String(cdy) + "/" + String(cmo < 10 ? "0" : "") + String(cmo) + "/" + String(cyr);

  Delay_(10);

  return Retorno;
}

String mtdObterHoraFormatada()
{
  Serial.begin(115200);
  Delay_(10);
  Serial.begin(115200);
  Delay_(10);

  String Retorno = "";
  mtdObterDataHora();

  Retorno = String(ch < 10 ? "0" : "") + String(ch) + ":" + String(cm < 10 ? "0" : "") + String(cm) + ":" + String(cs < 10 ? "0" : "") + String(cs);

  Delay_(10);

  return Retorno;
}

String mtdObterDataHoraFormatada()
{
  Serial.begin(115200);
  Delay_(10);
  Serial.begin(115200);
  Delay_(10);

  String Retorno = "";
  mtdObterDataHora();

  Retorno = String(cdy < 10 ? "0" : "") + String(cdy) + "/" + String(cmo < 10 ? "0" : "") + String(cmo) + "/" + String(cyr) + " " + 
  String(ch < 10 ? "0" : "") + String(ch) + ":" + String(cm < 10 ? "0" : "") + String(cm) + ":" + String(cs < 10 ? "0" : "") + String(cs);

  Delay_(10);

  return Retorno;
}

boolean cycleCheck(unsigned long *lastMillis, unsigned int cycle)
{
  unsigned long currentMillis = millis();
  if(currentMillis - *lastMillis >= cycle)
  {
    *lastMillis = currentMillis;
    return true;
  }
  else
  {
    return false;
  }
}

String mtdConverterIpToString(IPAddress ip)
{
  String Retorno = "";

  for (int contador = 0; contador <= 4 - 1; contador++)
  {
    Retorno += (contador != 4 - 1) ? String(ip[contador]) + "." : String(ip[contador]);
  }

  return Retorno;
}

void mtdIniciarServidor()
{
  server.begin();
  Serial.println(F("Servidor iniciado."));
}

void mtdConectarGerenciadorWiFi()
{
  // WiFiManager wifiManager;
  // mtdResetarGerenciadorWiFi();
  // wifiManager.setTimeout(cntintTimeout);
  wifiManager.setConnectTimeout(cntintConnectTimeout);
  // wifiManager.setAPConfig(IPAddress(192,168,25,2), IPAddress(192,168,25,2), IPAddress(255,255,255,0)); //set custom ip for portal
  // wifiManager.autoConnect(); // use this for auto generated name ESP + ChipID       
  // wifiManager.autoConnect("NTP_SynClock_Connect"); // fetches ssid and pass from eeprom and tries to connect. 
  // If does not connect with stored information, start an access point with this name and stay in blocking loop awaiting configuration

  if(!wifiManager.autoConnect())
  {
    intAtivarModoDormir = 0;
    mtdEscreverEEPROM(String(intAtivarModoDormir), 0, 0);

    mtdResetarGerenciadorWiFi();
    mtdResetarHardwareESP();
  }
}

void mtdResetarGerenciadorWiFi()
{
  Serial.println(F("Resetando o ESP."));
  // Reset das definicoes de rede
  wifiManager.resetSettings(); // reset saved settings   
  Delay_(100);
}

void mtdResetarHardwareESP()
{
  //  ESP.restart();

  ESP.deepSleep(1, WAKE_RF_DEFAULT);
  
  Delay_(100);
}

void mtdExecutarModoDispararRele()
{
  if(modoAcionarRele)
  {
    digitalWrite(PINO_IN, LOW);
    Delay_(intervaloDuracaoAcionamentoRele);
    digitalWrite(PINO_IN, HIGH);
    modoAcionarRele = false;
    quantidadeDisparoRele++;
  }
}

String getValueSplitString(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if(data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void mtdObterIp()
{
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  IPAddress IP = WiFi.localIP();
  numeroIP = mtdConverterIpToString(IP);
}

void mtdObterUptime()
{
  int segundo = millis() / 1000;
  int minuto = segundo / 60;
  int hora = minuto / 60;

  char buffer[8] = "";
  sprintf(buffer, "%02d:%02d:%02d", hora, minuto % 60, segundo % 60);

  uptime = buffer;
}

String mtdObterValorCampo(String Nome)
{
  String Getdata;

  int _referans = Getdata.indexOf(Nome);
  int _field_num = Getdata.indexOf('=', _referans + 1);
  int _belirleyici = Getdata.indexOf('&');

  String _field = Getdata.substring(_field_num + 1, _belirleyici);

  return _field;
}

void Delay_(int Intervalo)
{
  int i;

  for(i = 1; i <= Intervalo; i++)
  {
    interrupts();
    delay(1);
    if(i % 100 == 0)
    {
      ESP.wdtFeed();
      yield();
    }
  }
}

String urldecode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  for (int i = 0; i < str.length(); i++)
  {
    c = str.charAt(i);
    if(c == '+')
    {
      encodedString += ' ';
    }
    else if(c == '%')
    {
      i++;
      code0 = str.charAt(i);
      i++;
      code1 = str.charAt(i);
      c = (h2int(code0) << 4) | h2int(code1);
      encodedString += c;
    }
    else
    {
      encodedString += c;
    }

    Delay_(10);
  }

  return encodedString;
}

String urlencode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++)
  {
    c = str.charAt(i);
    if(c == ' ')
    {
      encodedString += '+';
    }
    else if(isalnum(c))
    {
      encodedString += c;
    }
    else
    {
      code1 = (c & 0xf) + '0';
      if((c & 0xf) > 9)
      {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if(c > 9)
      {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      //encodedString+=code2;
    }

    Delay_(10);
  }
  return encodedString;
}

unsigned char h2int(char c)
{
  if(c >= '0' && c <= '9')
  {
    return ((unsigned char)c - '0');
  }
  if(c >= 'a' && c <= 'f')
  {
    return ((unsigned char)c - 'a' + 10);
  }
  if(c >= 'A' && c <= 'F')
  {
    return ((unsigned char)c - 'A' + 10);
  }

  return (0);
}

void mtdConexaoWiFi()
{
  int loop_client_available = 0;

  Delay_(10);

  client = server.available();
  if(!client)
  {
    return;
  }
  Serial.println(F("Nova conexao requisitada..."));

  while (!client.available())
  {
    Delay_(1);
  
    if(loop_client_available++ >= 32767)
    {
      mtdResetarHardwareESP();
    }
  }
  Serial.println(F("Nova conexao OK..."));

  Delay_(10);
}

void mtdGerarPaginaWebService()
{
  // Read the first line of the request
  req = client.readStringUntil('\r');

  // First line of HTTP request looks like "GET /path HTTP/1.1"
  // Retrieve the "/path" part by finding the spaces
  int addr_start = req.indexOf(' ');
  int addr_end = req.indexOf(' ', addr_start + 1);
  if(addr_start == -1 || addr_end == -1)
  {
    Serial.print(F("Invalid request: "));
    Serial.println(req);
    // return(20);
  }
  req = req.substring(addr_start + 1, addr_end);
  Serial.print(F("Request: "));
  Serial.println(req);

  String buf = "";

  buf += "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n";
  buf += "<html lang=\"en\"><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1, user-scalable=no\"/>\r\n";
  buf += "<title>ESP8266 Web Server</title>";
  buf += "<style>.c{text-align: center;} div,input{padding:5px;font-size:1em;} input{width:80%;} body{text-align: center;font-family:verdana;} button{border:0;border-radius:0.3rem;background-color:#808080;color:#fff;line-height:2.4rem;font-size:1.2rem;width:100%;} .q{float: right;width: 64px;text-align: right;}</style>";
  buf += "<script type='text/javascript'> function AutoRefresh(t) { setTimeout('location.reload(true);',t); } </script>";
  buf += "</head>";
  buf += "<body onload='JavaScript:AutoRefresh(600000);'>";
  buf += "<h3>ESP8266 Web Server - System Logs</h3>";
  buf += "<p>Disparar o Rele. <a href=\"?function=btnModoDispararRele_on\"><button>Pressionar</button></a></p>";
  buf += "<p>Resetar o gerenciador de WiFi. <a href=\"?function=btnResetWiFiManager\"><button>Reset</button></a></p>";
  buf += "Chip Id: ";
  buf += String(chipId);
  buf += "<br>";
  buf += "Numero IP: ";
  buf += String(numeroIP);
  buf += "<br>";
  buf += "Endereco MAC: ";
  buf += String(numeroMAC);
  buf += "<br>";
  buf += "Horario: ";
  buf += String(mtdObterDataHoraFormatada());
  buf += "<br>";
  buf += "Uptime: ";
  buf += uptime;
  buf += "<br>";
  buf += "Quantidade de Disparos do Rele: ";
  buf += String(quantidadeDisparoRele);
  buf += "<br>";
  buf += "Numero boot: ";
  buf += String(boot_num);
  buf += "<br>";
  buf += "Vdd (V): ";
  buf += String(vdd);
  buf += "<br>";
  buf += "Tempo desligado (min): ";
  buf += String(intTempoDesligado);
  buf += "<br>";
  buf += "Tempo ligado (min): ";
  buf += String(intTempoLigado);
  buf += "<br>";
  buf += "Numero maximo reinicio: ";
  buf += String(intNumeroMaximoReinicio);
  buf += "<br>";
  buf += "Numero reinicio: ";
  buf += String(intNumeroReinicio);
  buf += "<br>";
  buf += "Email Emitente: ";
  buf += String(strEmailEmitente);
  buf += "<br>";
  buf += "Email Recebedor: ";
  buf += String(strEmailRecebedor);
  buf += "<br>";
  buf += "Usuario: ";
  buf += String(strUsuario);
  buf += "<br>";
  buf += "Senha: ";
  buf += String(Senha_base64);
  // buf += String(strSenha);
  buf += "<br>";
  buf += "Servidor: ";
  buf += String(strServidor);
  buf += "<br>";
  buf += "Porta: ";
  buf += String(intPorta);
  buf += "<br>";
  buf += "Email Tempo: ";
  buf += String(intEmailTempo);
  buf += "<br>";
  buf += "Tempo (em segundos) restante enquanto o dispositivo nao e desligado: ";
  buf += String(ulngTempoRestanteTempoLigado);
  buf += "<br>";
  buf += "Tempo (em segundos) restante para o dispositivo enviar e-mail: ";
  buf += String(ulngTempoRestanteEmailEnviado);
  buf += "<form method=get>";
  buf += "<br>";
  buf += "<label>Email Emitente</label><br>";
  buf += "<input type='text' name='email_emitente' maxlength='30' size='15'><br>";
  buf += "<label>Email Recebedor</label><br>";
  buf += "<input type='text' name='email_recebedor' maxlength='30' size='15'><br>";
  buf += "<label>Usuario</label><br>";
  buf += "<input type='text' name='usuario' maxlength='30' size='15'><br>";
  buf += "<label>Senha</label><br>";
  buf += "<input type='password' name='senha' maxlength='30' size='15'><br>";
  buf += "<label>Servidor</label><br>";
  buf += "<input type='text' name='servidor' maxlength='30' size='15'><br>";
  buf += "<label>Porta</label><br>";
  buf += "<input type='text' name='porta' maxlength='30' size='15'><br>";
  buf += "<label>Email Tempo (s)</label><br>";
  buf += "<input type='text' name='email_tempo' maxlength='30' size='15'><br>";
  buf += "<label>Tempo Desligado (min)</label><br>";
  buf += "<input type='text' name='tempo_desligado' maxlength='30' size='15'><br>";
  buf += "<label>Tempo Ligado (min)</label><br>";
  buf += "<input type='text' name='tempo_ligado' maxlength='30' size='15'><br>";
  buf += "<br>";
  buf += "<input type='submit' value='Salvar' >";
  buf += "<br>";
  buf += "</form>";
  buf += "<p>A pagina sera atualizada a cada 10 minutos. Clique <a href=\"javascript:window.location.reload();\">aqui</a> para atualizar a pagina agora.</p>";
  buf += "</html>\n";

  client.flush();
  client.print(buf);

  if(req.startsWith("/?email_emitente=") )
  {
    mtdEscreverVariaveisEEPROM();

    ulngIntervaloTempoLigado = millis();

    blnPrimeiroEmail = true;
  }

  if(req.indexOf("btnModoDispararRele_on") != -1)
  {
    modoAcionarRele = true;
  }

  if(req.indexOf("btnResetWiFiManager") != -1)
  {
    intAtivarModoDormir = 0;
    mtdEscreverEEPROM(String(intAtivarModoDormir), 0, 0);

    mtdResetarGerenciadorWiFi();
    mtdResetarHardwareESP();
  }
}

byte eRcv(WiFiClientSecure client_)
{
  byte respCode;
  byte thisByte;
  int loopCount = 0;

  while (!client_.available())
  {
    Delay_(1);
    loopCount++;
    // if nothing received for 10 seconds, timeout
    if(loopCount > 10000)
    {
      client_.stop();
      Serial.println(F("\r\nLimite de tempo atingido."));
      return 0;
    }
  }

  respCode = client_.peek();
  while (client_.available())
  {
    thisByte = client_.read();
    Serial.write(thisByte);
  }

  if(respCode >= '4')
  {
    //  efail();
    return 0;
  }
  return 1;
}

void efail(WiFiClientSecure client_)
{
  byte thisByte = 0;
  int loopCount = 0;

  client_.println(F("QUIT"));

  while (!client_.available())
  {
    Delay_(1);
    loopCount++;
    // if nothing received for 10 seconds, timeout
    if(loopCount > 10000)
    {
      client_.stop();
      Serial.println(F("\r\nLimite de tempo atingido."));
      return;
    }
  }

  while (client_.available())
  {
    thisByte = client_.read();
    Serial.write(thisByte);
  }
  client_.stop();
  Serial.println(F("Desconectado."));
}

byte mtdEnviarEmail(String Emitente, String Recebedor, String Usuario, String Senha, String Servidor, int Porta, String Assunto, String Mensagem)
{
  Delay_(10);

  String EmitenteCompleto = "MAIL From:<" + Emitente + ">";
  String RecebedorCompleto = "RCPT TO:<" + Recebedor + ">";
  String AssuntoCompleto = "Subject: " + Assunto + "\r\n";
  String MensagemCompleto = "" + Mensagem + "";

  char from_email[EmitenteCompleto.length() + 1];
  EmitenteCompleto.toCharArray(from_email, EmitenteCompleto.length() + 1);

  char to_email[RecebedorCompleto.length() + 1];
  RecebedorCompleto.toCharArray(to_email, RecebedorCompleto.length() + 1);

  rbase64.encode(Usuario);
  String Usuario_base64 = rbase64.result();
  rbase64.encode(Senha);
  Senha_base64 = rbase64.result();

  char user_base64[Usuario_base64.length() + 1];
  Usuario_base64.toCharArray(user_base64, Usuario_base64.length() + 1);

  char user_password_base64[Senha_base64.length() + 1];
  Senha_base64.toCharArray(user_password_base64, Senha_base64.length() + 1);

  char server[Servidor.length() + 1];
  Servidor.toCharArray(server, Servidor.length() + 1);

  int port = Porta;

  char subject[AssuntoCompleto.length() + 1];
  AssuntoCompleto.toCharArray(subject, AssuntoCompleto.length() + 1);

  char message[MensagemCompleto.length() + 1];
  MensagemCompleto.toCharArray(message, MensagemCompleto.length() + 1);
  
  WiFiClientSecure client_;

  if(client_.connect(server, port) == 1)
  {
    Serial.println(F("Conectado."));
  }
  else
  {
    Serial.println(F("Falha ao conectar."));
    return 0;
  }

  if(!eRcv(client_)) return 0;
  Serial.println(F("--- Sending EHLO")); client_.println("EHLO 1.2.3.4"); if(!eRcv(client_)) return 0;
  Serial.println(F("--- Sending login")); client_.println("AUTH LOGIN"); if(!eRcv(client_)) return 0;
  Serial.println(F("--- Sending User base64")); client_.println(user_base64); if(!eRcv(client_)) return 0;
  Serial.println(F("--- Sending Password base64")); client_.println(user_password_base64); if(!eRcv(client_)) return 0;
  Serial.println(F("--- Sending From")); client_.println(from_email); if(!eRcv(client_)) return 0;
  Serial.println(F("--- Sending To")); client_.println(to_email); if(!eRcv(client_)) return 0;
  Serial.println(F("--- Sending DATA")); client_.println(F("DATA")); if(!eRcv(client_)) return 0;
  client_.println(subject);
  client_.println(message);
  client_.println(F("."));
  if(!eRcv(client_)) return 0;
  Serial.println(F("--- Sending QUIT"));
  client_.println(F("QUIT"));
  if(!eRcv(client_)) return 0;
  client_.stop();
  Serial.println(F("Desconectado."));

  Delay_(10);

  return 1;
}

void mtdGerarAssuntoMensagemEmail()
{
  assunto = "ESP 8266 - Disparador de Rele";

  mensagem = "";
  mensagem += "Chip Id: ";
  mensagem += String(chipId);
  mensagem += "\n\r";
  mensagem += "Numero IP: ";
  mensagem += String(numeroIP);
  mensagem += "\n\r";
  mensagem += "Endereco MAC: ";
  mensagem += String(numeroMAC);
  mensagem += "\n\r";
  mensagem += "Horario: ";
  mensagem += String(mtdObterDataHoraFormatada());
  mensagem += "\n\r";
  mensagem += "Uptime: ";
  mensagem += uptime;
  mensagem += "\n\r";
  mensagem += "Quantidade de Disparos do Rele: ";
  mensagem += String(quantidadeDisparoRele);
  mensagem += "\n\r";
  mensagem += "Numero boot: ";
  mensagem += String(boot_num);
  mensagem += "\n\r";
  mensagem += "Vdd (V): ";
  mensagem += String(vdd);
  mensagem += "\n\r";
  mensagem += "Tempo desligado (min): ";
  mensagem += String(intTempoDesligado);
  mensagem += "\n\r";
  mensagem += "Tempo ligado (min): ";
  mensagem += String(intTempoLigado);
  mensagem += "\n\r";
  mensagem += "Numero maximo reinicio: ";
  mensagem += String(intNumeroMaximoReinicio);
  mensagem += "\n\r";
  mensagem += "Numero reinicio: ";
  mensagem += String(intNumeroReinicio);
  mensagem += "\n\r";
  mensagem += "Email Emitente: ";
  mensagem += String(strEmailEmitente);
  mensagem += "\n\r";
  mensagem += "Email Recebedor: ";
  mensagem += String(strEmailRecebedor);
  mensagem += "\n\r";
  mensagem += "Usuario: ";
  mensagem += String(strUsuario);
  mensagem += "\n\r";
  mensagem += "Senha: ";
  mensagem += String(Senha_base64);
  // mensagem += String(strSenha);
  mensagem += "\n\r";
  mensagem += "Servidor: ";
  mensagem += String(strServidor);
  mensagem += "\n\r";
  mensagem += "Porta: ";
  mensagem += String(intPorta);
  mensagem += "\n\r";
  mensagem += "Email Tempo: ";
  mensagem += String(intEmailTempo);
  mensagem += "\n\r";
  mensagem += "Tempo (em segundos) restante enquanto o dispositivo nao e desligado: ";
  mensagem += String(ulngTempoRestanteTempoLigado);
  mensagem += "\n\r";
  mensagem += "Tempo (em segundos) restante para o dispositivo enviar e-mail: ";
  mensagem += String(ulngTempoRestanteEmailEnviado);
  mensagem += "\n\r";

  Serial.println(assunto);
  Serial.print(mensagem);
}

bool mtdGerarEmail(bool Imediato)
{
  bool Retorno = false;

  if(intEmailTempo > 0 || Imediato)
  {
    ulngDiferencaIntervaloEmailEnviado = millis() - ulngIntervaloEmailEnviado;
    ulngTempoRestanteEmailEnviado = (int)((intEmailTempo * 1000 - ulngDiferencaIntervaloEmailEnviado) / 1000);
    
    if((ulngDiferencaIntervaloEmailEnviado >= intEmailTempo * 1000) || Imediato)
    {        
      Delay_(10);
  
      // if(mtdEnviarEmail("esp8266u@gmail.com", "esp8266u@gmail.com", "esp8266u@gmail.com", "esp8266u", "smtp.gmail.com", 465, assunto, mensagem))
      if(mtdEnviarEmail(strEmailEmitente, strEmailRecebedor, strUsuario, strSenha, strServidor, intPorta, assunto, mensagem))
      {
        Serial.println(F("Email enviado."));

        Retorno = true;
      }
      else
      {
        Serial.println(F("Email nao enviado."));

        Retorno = false;
      }
      
      ulngIntervaloEmailEnviado = millis();
    }
  }
  else
  {
    ulngIntervaloEmailEnviado = millis();   
  }

  return Retorno;
}

void mtdZerarVariaveisEEPROM()
{
  Serial.println(String(cntintAtivarModoDormir));
  mtdEscreverEEPROM(String(cntintAtivarModoDormir), 0, 0);

  Serial.println(String(cntintNumeroBoot));
  mtdEscreverEEPROM(String(cntintNumeroBoot), 451, 460);

  Serial.println(cntstrEmailEmitente);
  mtdEscreverEEPROM(cntstrEmailEmitente, 1, 50);

  Serial.println(cntstrEmailRecebedor);
  mtdEscreverEEPROM(cntstrEmailRecebedor, 51, 100);

  Serial.println(cntstrUsuario);
  mtdEscreverEEPROM(cntstrUsuario, 101, 150);

  Serial.println(cntstrSenha);
  mtdEscreverEEPROM(cntstrSenha, 151, 200);

  Serial.println(cntstrServidor);
  mtdEscreverEEPROM(cntstrServidor, 201, 250);

  Serial.println(String(cntintPorta));
  mtdEscreverEEPROM(String(cntintPorta), 251, 300);

  Serial.println(String(cntintEmailTempo));
  mtdEscreverEEPROM(String(cntintEmailTempo), 301, 350);

  Serial.println(String(cntintTempoDesligado));
  mtdEscreverEEPROM(String(cntintTempoDesligado), 351, 400);

  Serial.println(String(cntintTempoLigado));
  mtdEscreverEEPROM(String(cntintTempoLigado), 401, 450);

  Serial.println(String(cntintNumeroMaximoReinicio));
  mtdEscreverEEPROM(String(cntintNumeroMaximoReinicio), 461, 470);

  Serial.println(String(cntintNumeroReinicio));
  mtdEscreverEEPROM(String(cntintNumeroReinicio), 471, 480);
  
  ulngIntervaloTempoLigado = millis() + intTempoDesligado * 60 * 1000;
  ulngIntervaloEmailEnviado = millis();
}

void mtdCarregarVariaveisEEPROM()
{
  String strAtivarModoDormir = mtdLerEEPROM(0, 0);
  intAtivarModoDormir = strAtivarModoDormir.toInt();
  if(strAtivarModoDormir.length() == 0)
  {
    intAtivarModoDormir = cntintAtivarModoDormir;
    mtdEscreverEEPROM(String(intAtivarModoDormir), 0, 0);
  }
  Serial.print(F("intAtivarModoDormir: "));
  Serial.println(String(intAtivarModoDormir));
  strEmailEmitente = mtdLerEEPROM(1, 50);
  if(strEmailEmitente.length() == 0)
  {
    strEmailEmitente = cntstrEmailEmitente;
    mtdEscreverEEPROM(strEmailEmitente, 1, 50);
  }
  Serial.print(F("strEmailEmitente: "));
  Serial.println(strEmailEmitente);
  strEmailRecebedor = mtdLerEEPROM(51, 100);
  if(strEmailRecebedor.length() == 0)
  {
    strEmailRecebedor = cntstrEmailRecebedor;
    mtdEscreverEEPROM(strEmailRecebedor, 51, 100);
  }
  Serial.print(F("strEmailRecebedor: "));
  Serial.println(strEmailRecebedor);
  strUsuario = mtdLerEEPROM(101, 150);
  if(strUsuario.length() == 0)
  {
    strUsuario = cntstrUsuario;
    mtdEscreverEEPROM(strUsuario, 101, 150);
  }
  Serial.print(F("strUsuario: "));
  Serial.println(strUsuario);
  strSenha = mtdLerEEPROM(151, 200);
  if(strSenha.length() == 0)
  {
    strSenha = cntstrSenha;
    mtdEscreverEEPROM(strSenha, 151, 200);
  }
  Serial.print(F("strSenha: "));
  Serial.println(strSenha);
  strServidor = mtdLerEEPROM(201, 250);
  if(strServidor.length() == 0)
  {
    strServidor = cntstrServidor;
    mtdEscreverEEPROM(strServidor, 201, 250);
  }
  Serial.print(F("strServidor: "));
  Serial.println(strServidor);
  String strPorta = mtdLerEEPROM(251, 300);
  intPorta = strPorta.toInt();
  if(strPorta.length() == 0)
  {
    intPorta = cntintPorta;
    mtdEscreverEEPROM(String(intPorta), 251, 300);
  }
  Serial.print(F("intPorta: "));
  Serial.println(String(intPorta));
  String strEmailTempo = mtdLerEEPROM(301, 350);
  intEmailTempo = strEmailTempo.toInt();
  if(strEmailTempo.length() == 0)
  {
    intEmailTempo = cntintEmailTempo;
    mtdEscreverEEPROM(String(intEmailTempo), 301, 350);
  }
  Serial.print(F("intEmailTempo: "));
  Serial.println(String(intEmailTempo));
  String strTempoDesligado = mtdLerEEPROM(351, 400);
  intTempoDesligado = strTempoDesligado.toInt();
  if(intTempoDesligado <= 0)
  {
    intTempoDesligado = cntintTempoDesligado;
    mtdEscreverEEPROM(String(intTempoDesligado), 351, 400);
  }
  Serial.print(F("intTempoDesligado: "));
  Serial.println(String(intTempoDesligado));
  String strTempoLigado = mtdLerEEPROM(401, 450);
  intTempoLigado = strTempoLigado.toInt();
  if(intTempoLigado < -1)
  {
    intTempoLigado = cntintTempoLigado;
    mtdEscreverEEPROM(String(intTempoLigado), 401, 450);
  }
  Serial.print(F("intTempoLigado: "));
  Serial.println(String(intTempoLigado));
  String strNumeroMaximoReinicio = mtdLerEEPROM(461, 470);
  intNumeroMaximoReinicio = strNumeroMaximoReinicio.toInt();
  if(intNumeroMaximoReinicio < 0)
  {
    intNumeroMaximoReinicio = cntintNumeroMaximoReinicio;
    mtdEscreverEEPROM(String(intNumeroMaximoReinicio), 461, 470);
  }
  Serial.print(F("intNumeroMaximoReinicio: "));
  Serial.println(String(intNumeroMaximoReinicio));
  String strNumeroReinicio = mtdLerEEPROM(471, 480);
  intNumeroReinicio = strNumeroReinicio.toInt();
  if(intNumeroReinicio < 0)
  {
    intNumeroReinicio = cntintNumeroReinicio;
    mtdEscreverEEPROM(String(intNumeroReinicio), 471, 480);
  }
  Serial.print(F("intNumeroReinicio: "));
  Serial.println(String(intNumeroReinicio));
}

void mtdEscreverVariaveisEEPROM()
{
    // Serial.println(String(intAtivarModoDormir));
    // mtdEscreverEEPROM(String(intAtivarModoDormir), 0, 0);
    String strEmailEmitente_ = urldecode(getValueSplitString(getValueSplitString(req, '&', 0), '=', 1));
    if(strEmailEmitente_.length() > 0)
    {
      strEmailEmitente = strEmailEmitente_;
    }
    else
    {
      strEmailEmitente = cntstrEmailEmitente;
      strUsuario = cntstrUsuario;
      strSenha = cntstrSenha;
      strServidor = cntstrServidor;
      intPorta = cntintPorta;
    }
    Serial.println(strEmailEmitente);
    mtdEscreverEEPROM(strEmailEmitente, 1, 50);
    String strEmailRecebedor_ = urldecode(getValueSplitString(getValueSplitString(req, '&', 1), '=', 1));
    if(strEmailRecebedor_.length() > 0)
    {
      strEmailRecebedor = strEmailRecebedor_;
    }
    else
    {
      strEmailRecebedor = cntstrEmailRecebedor;
    }
    Serial.println(strEmailRecebedor);
    mtdEscreverEEPROM(strEmailRecebedor, 51, 100);
    String strUsuario_ = urldecode(getValueSplitString(getValueSplitString(req, '&', 2), '=', 1));
    if(strUsuario_.length() > 0)
    {
      strUsuario = strUsuario_;
    }
    else
    {
      strEmailEmitente = cntstrEmailEmitente;
      strUsuario = cntstrUsuario;
      strSenha = cntstrSenha;
      strServidor = cntstrServidor;
      intPorta = cntintPorta;
    }
    Serial.println(strUsuario);
    mtdEscreverEEPROM(strUsuario, 101, 150);
    String strSenha_ = urldecode(getValueSplitString(getValueSplitString(req, '&', 3), '=', 1));
    if(strSenha_.length() > 0)
    {
      strSenha = strSenha_;
    }
    else
    {
      strEmailEmitente = cntstrEmailEmitente;
      strUsuario = cntstrUsuario;
      strSenha = cntstrSenha;
      strServidor = cntstrServidor;
      intPorta = cntintPorta;
    }
    Serial.println(strSenha);
    mtdEscreverEEPROM(strSenha, 151, 200);
    String strServidor_ = urldecode(getValueSplitString(getValueSplitString(req, '&', 4), '=', 1));
    if(strServidor_.length() > 0)
    {
      strServidor = strServidor_;
    }
    else
    {
      strEmailEmitente = cntstrEmailEmitente;
      strUsuario = cntstrUsuario;
      strSenha = cntstrSenha;
      strServidor = cntstrServidor;
      intPorta = cntintPorta;
    }
    Serial.println(strServidor);
    mtdEscreverEEPROM(strServidor, 201, 250);
    String strPorta_ = urldecode(getValueSplitString(getValueSplitString(req, '&', 5), '=', 1));
    if(strPorta_.length() > 0)
    {
      intPorta = strPorta_.toInt();
    }
    else
    {
      strEmailEmitente = cntstrEmailEmitente;
      strUsuario = cntstrUsuario;
      strSenha = cntstrSenha;
      strServidor = cntstrServidor;
      intPorta = cntintPorta;
    }
    Serial.println(String(intPorta));
    mtdEscreverEEPROM(String(intPorta), 251, 300);
    String strEmailTempo_ = urldecode(getValueSplitString(getValueSplitString(req, '&', 6), '=', 1));
    if(strEmailTempo_.length() > 0)
    {
      intEmailTempo = strEmailTempo_.toInt();
    }
    else
    {
      intEmailTempo = cntintEmailTempo;
    }
    Serial.println(String(intEmailTempo));
    mtdEscreverEEPROM(String(intEmailTempo), 301, 350);
    String strTempoDesligado_ = urldecode(getValueSplitString(getValueSplitString(req, '&', 7), '=', 1));
    if(strTempoDesligado_.length() > 0)
    {
      intTempoDesligado = strTempoDesligado_.toInt();
      
      if(intTempoDesligado > cntintTempoMaximoDesligado)
      {
        intNumeroMaximoReinicio = (int) (intTempoDesligado / cntintTempoMaximoDesligado);      
      }
      else
      {
        intNumeroMaximoReinicio = 0;
      }
      
      intNumeroReinicio = intNumeroMaximoReinicio;
    }
    else
    {
      intTempoDesligado = cntintTempoDesligado;
      intNumeroMaximoReinicio = cntintNumeroMaximoReinicio;
      intNumeroReinicio = cntintNumeroReinicio;
    }
    Serial.println(String(intTempoDesligado));
    mtdEscreverEEPROM(String(intTempoDesligado), 351, 400);
    Serial.println(String(intNumeroMaximoReinicio));
    mtdEscreverEEPROM(String(intNumeroMaximoReinicio), 461, 470);
    Serial.println(String(intNumeroReinicio));
    mtdEscreverEEPROM(String(intNumeroReinicio), 471, 480);
    String strTempoLigado_ = urldecode(getValueSplitString(getValueSplitString(req, '&', 8), '=', 1));
    if(strTempoLigado_.length() > 0)
    {
      intTempoLigado = strTempoLigado_.toInt();
    }
    else
    {
      intTempoLigado = cntintTempoLigado;
    }
    Serial.println(String(intTempoLigado));
    mtdEscreverEEPROM(String(intTempoLigado), 401, 450);

    ulngIntervaloTempoLigado = millis() + intTempoDesligado * 60 * 1000;
    ulngIntervaloEmailEnviado = millis();
}

String mtdLerEEPROM(int Inicio, int Fim)
{
  EEPROM.begin(MEM_ALOC_SIZE);

  Delay_(10);
  
  String Retorno;
  
  Serial.println();
  Serial.println(F("Startup"));
  Serial.println(F("Reading EEPROM"));
  Serial.println();

  for (int i = Inicio; i <= Fim; i++)
  {
    char c = char(EEPROM.read(i));
    Serial.print(F("Read: "));
    Serial.println(c);

    if(c != 0)
    {
      Retorno += c;
    }
  }

  // Retorno.trim();

  EEPROM.end();
  
  Delay_(10);

  return Retorno;
}

void mtdEscreverEEPROM(String Entrada, int Inicio, int Fim)
{
  int intTamanhoStringEntrada = Entrada.length();

  if(intTamanhoStringEntrada <= Fim - Inicio + 1)
  {
    EEPROM.begin(MEM_ALOC_SIZE);
  
    Delay_(10);

    Serial.println();
    Serial.println(F("Startup"));
    Serial.println(F("Writing EEPROM"));
    Serial.println();
  
    // Entrada.trim();
    char charBuf[Fim - Inicio + 1];
    Entrada.toCharArray(charBuf, Entrada.length() + 1);
  
    for (int i = Inicio; i <= Fim; i++)
    {
      Serial.print(F("Write: "));

      if(i <= Inicio + Entrada.length() - 1)
      {
        Serial.println(charBuf[i - Inicio]);
        EEPROM.write(i, charBuf[i - Inicio]);
      }
      else
      {
        Serial.println(0);
        EEPROM.write(i, 0);
      }
    }
  
    EEPROM.commit();
  }
  else
  {
    Serial.print(F("O comprimento da String deve ser menor do que a variacao entre Inicio e Fim: ")); 
    Serial.println(Fim - Inicio + 1);
  }

  Delay_(10);
}

void mtdLimparEEPROM(int Inicio, int Fim)
{
  EEPROM.begin(MEM_ALOC_SIZE);

  Delay_(10);

  Serial.println();
  Serial.println(F("Startup"));
  Serial.println(F("Cleanning EEPROM"));
  Serial.println();

  for (int i = Inicio; i <= Fim; i++)
  {
    EEPROM.write(i, 0);
  }

  EEPROM.commit();

  Delay_(10);
}

void mtdLerEscreverNumeroBootEEPROM()
{
  Delay_(10);

  String strNumeroBoot = mtdLerEEPROM(451, 460);
  boot_num = strNumeroBoot.toInt();
  if(strNumeroBoot.length() == 0)
  {
    boot_num = cntintNumeroBoot;
    mtdEscreverEEPROM(String(boot_num), 451, 460);
  }
  Serial.print(F("boot_num: "));
  Serial.println(String(boot_num));
  boot_num++;
  mtdEscreverEEPROM(String(boot_num), 451, 460);
  
  Delay_(10);
}

void mtdInicializarPinos()
{
  pinMode(PINO_GPIO4, OUTPUT);
  digitalWrite(PINO_GPIO4, HIGH);
  pinMode(PINO_GPIO13, INPUT);
}

void setup()
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Delay_(10);

  ESP.wdtDisable();
  ESP.wdtEnable(WDTO_8S);

  rst_info *rsti;
  rsti = ESP.getResetInfoPtr();
  Serial.println(F("\r\nStart..."));
  Serial.println(String("ResetInfo.reason = ") + rsti->reason);

  mtdInicializarPinos();

  Delay_(10);

  if(digitalRead(PINO_RESET) == LOW)
  {
    Serial.println(F("\r\nSe entrou nessa condicao, fudeu..."));
   
    mtdZerarVariaveisEEPROM();
    
    mtdResetarGerenciadorWiFi();
    mtdResetarHardwareESP();
  }
  
  mtdCarregarVariaveisEEPROM();

  mtdLerEscreverNumeroBootEEPROM();

  if(boot_num <= 1)
  {
    mtdEscreverVariaveisEEPROM();  
  }
 
  Delay_(10);

  if(intAtivarModoDormir == 1)
  {
    Serial.printf("ESP8266 in deep sleep mode for %i minute(s) of %i minute(s)...\n\r", (intTempoDesligado - ((intNumeroMaximoReinicio - intNumeroReinicio) * cntintTempoMaximoDesligado)), intTempoDesligado);
    Serial.println("going to sleep now...");

    if(intNumeroReinicio == 0)
    {
      intNumeroReinicio = intNumeroMaximoReinicio;
      Serial.print(F("intNumeroReinicio: "));
      Serial.println(String(intNumeroReinicio));
      mtdEscreverEEPROM(String(intNumeroReinicio), 471, 480);

      intAtivarModoDormir = 0;
      mtdEscreverEEPROM(String(intAtivarModoDormir), 0, 0);
      
      ESP.deepSleep((intTempoDesligado == cntintTempoMaximoDesligado ? intTempoDesligado : intTempoDesligado % cntintTempoMaximoDesligado) * 60 * 1000 * 1000, WAKE_RF_DEFAULT);
    }
    else
    {
      intNumeroReinicio--;
      Serial.print(F("intNumeroReinicio: "));
      Serial.println(String(intNumeroReinicio));
      mtdEscreverEEPROM(String(intNumeroReinicio), 471, 480);

      intAtivarModoDormir = 1;
      mtdEscreverEEPROM(String(intAtivarModoDormir), 0, 0);

      ESP.deepSleep((cntintTempoMaximoDesligado) * 60 * 1000 * 1000, WAKE_RF_DISABLED);    
    }
  }

  blnPrimeiroEmail = true;
  
  numeroMAC = String(WiFi.macAddress());
  chipId = String(ESP.getChipId());
  String chipId_ = chipId;
  chipId_.replace(":", "_");
  String strssid = String(ssid) + String("_") + chipId_;
  char vetchar[strssid.length() + 1];
  strssid.toCharArray(vetchar, strssid.length() + 1);
  ssid = vetchar;

  mtdConectarGerenciadorWiFi();
  mtdIniciarServidor();

  mtdIniciarClienteDataHora();
  for(int contador = 0; contador <= cntintTentativaAtualizarClienteDataHora - 1; contador++)
  {
    if(mtdAtualizarClienteDataHora(utc))
    {
      break;
    }
  }

  ulngIntervaloTempoLigado = millis();
  ulngIntervaloEmailEnviado = millis() - intEmailTempo * 1000;
  
  Delay_(10);
}

void loop()
{
  if(cycleCheck(&thread1LastMillis, CycleThread1))
  {
    // Cole aqui o codigo que devera ser executado na thread1

    if(digitalRead(PINO_RESET) == LOW)
    {
      mtdZerarVariaveisEEPROM();

      mtdResetarGerenciadorWiFi();
      mtdResetarHardwareESP();
    }
   
    if((millis() % (60 * 60 * 1000)) == 0)
    {
      mtdAtualizarClienteDataHora(utc);
    }

    mtdObterIp();
    mtdObterUptime();    

    vdd = ESP.getVcc() / 1024.0;
    mtdExecutarModoDispararRele();
    
    thread1State = !thread1State;
  }

  if(cycleCheck(&thread2LastMillis, CycleThread2))
  {
    // Cole aqui o codigo que devera ser executado na thread2

    //if(intTempoDesligado < 0 || intTempoDesligado > cntintMaxTempoDesligado)
    if(intTempoDesligado < 0)
    {
      intTempoDesligado = cntintTempoDesligado;
    }

    mtdConexaoWiFi();
    
    if(intTempoLigado >= 0)
    {
      ulngDiferencaIntervaloTempoLigado = millis() - ulngIntervaloTempoLigado;
      ulngTempoRestanteTempoLigado = (int)((intTempoLigado * 60 * 1000 - ulngDiferencaIntervaloTempoLigado) / 1000);

      if(ulngDiferencaIntervaloTempoLigado >= intTempoLigado * 60 * 1000)
      {
        if(!blnPrimeiroEmail)
        {
          mtdInicializarPinos();
  
          intAtivarModoDormir = 1;
          mtdEscreverEEPROM(String(intAtivarModoDormir), 0, 0);
  
          ESP.deepSleep(1, WAKE_RF_DISABLED);
        }
      }
    }
    else
    {
      // intAtivarModoDormir = 0;
      // mtdEscreverEEPROM(String(intAtivarModoDormir), 0, 0);

      ulngIntervaloTempoLigado = millis() + intTempoDesligado * 60 * 1000;
    }

    thread2State = !thread2State;
  }

  if(cycleCheck(&thread3LastMillis, CycleThread3))
  {
    // Cole aqui o codigo que devera ser executado na thread3

    mtdAtualizarClienteDataHora(utc);

    mtdGerarAssuntoMensagemEmail();

    for(int contador = 0; contador <= cntintTentativaEnviarEmail - 1; contador++)
    {
      if(mtdGerarEmail(blnPrimeiroEmail))
      {
        blnPrimeiroEmail = false;

        break;
      }
    }

    thread3State = !thread3State;
  }

  if(cycleCheck(&thread4LastMillis, CycleThread4))
  {
    // Cole aqui o codigo que devera ser executado na thread4

    mtdGerarPaginaWebService();
    
    thread4State = !thread4State;
  }
}
