#define PINO_LEDVERMELHO LED_BUILTIN

bool high = HIGH;
bool low = LOW;

void mtdInicioTerminoMensagem(bool Inicio, bool Inversor, int PinoLed)
{
  digitalWrite(PinoLed, low);
  delay(1000);

  high = HIGH;
  low = LOW;

  if(Inversor)
  {
    high = LOW;
    low = HIGH;
  }

  for(int contador = 0 ; contador <= 100 - 1; contador++)
  {
    digitalWrite(PinoLed, low);
    if(Inicio)
    {
      delay(50);
    }
    else
    {
      delay(25);
    }
    digitalWrite(PinoLed, high);
    if(Inicio)
    {
      delay(25);
    }
    else
    {
      delay(50);
    }
  }

  digitalWrite(PinoLed, low);
  delay(1000);
}

void mtdEspacoMensagem(int Tamanho, bool Inversor, int PinoLed)
{
  digitalWrite(PinoLed, low);
  delay(250);
  
  high = HIGH;
  low = LOW;
  
  if(Inversor)
  {
    high = LOW;
    low = HIGH;
  }
  
  for(int contador = 0 ; contador <= Tamanho - 1; contador++)
  {
    digitalWrite(PinoLed, low);
    delay(25);
    digitalWrite(PinoLed, high);
    delay(25);
  }
  
  digitalWrite(PinoLed, low);
  delay(250);
}

void mtdProduzirPiscadaCaractereMorse(char Caractere, bool Inversor, int PinoLed)
{
  high = HIGH;
  low = LOW;
  
  if(Inversor)
  {
    high = LOW;
    low = HIGH;  
  }

  if(Caractere == '.')
  {
    digitalWrite(PinoLed, low);
    delay(950);
    digitalWrite(PinoLed, high);
    delay(100);
    digitalWrite(PinoLed, low);
    delay(950);
  }
  else if(Caractere == '-')
  {
    digitalWrite(PinoLed, low);
    delay(250);
    digitalWrite(PinoLed, high);
    delay(2000);
    digitalWrite(PinoLed, low);
    delay(250);
  }
  else
  {
    digitalWrite(PinoLed, low);
    delay(1500);
  }
}

void mtdGerarCodigoMorse(String Mensagem, bool Inversor, int PinoLed)
{
  char* codigoMorse[] = {".-   ", "-... ", "-.-. ", "-..  ", ".    ", "..-. ", "--.  ", ".... ", "..   ", ".--- ", "-.-  ", ".-.. ", "--   ", "-.   ", "---  ", ".--. ", "--.- ", ".-.  ", "...  ", "-    ", "..-  ", "...- ", ".--  ", "-..- ", "-.-- ", "--.. ", "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "     "};

  int lenMensagem = Mensagem.length();
  char vetCharMensagem[lenMensagem];
  
  Mensagem.toCharArray(vetCharMensagem, lenMensagem + 1);

  mtdInicioTerminoMensagem(true, Inversor, PinoLed);

  for(int contador = 0; contador <= lenMensagem - 1; contador++)
  {
    int numCaractere = vetCharMensagem[contador];
    String cadeiaCodigoMorse;

    if(numCaractere >= 65 && numCaractere <= 90)
    {
      cadeiaCodigoMorse = codigoMorse[numCaractere - 65];

      for(int cont = 0; cont <= cadeiaCodigoMorse.length() - 1; cont++)
      {
        mtdProduzirPiscadaCaractereMorse(cadeiaCodigoMorse[cont], Inversor, PinoLed);
      }
    }
    else if(numCaractere >= 97 && numCaractere <= 122)
    {
      cadeiaCodigoMorse = codigoMorse[numCaractere - 97];

      for(int cont = 0; cont <= cadeiaCodigoMorse.length() - 1; cont++)
      {
        mtdProduzirPiscadaCaractereMorse(cadeiaCodigoMorse[cont], Inversor, PinoLed);
      }
    }
    else if(numCaractere >= 48 && numCaractere <= 57)
    {
      cadeiaCodigoMorse = codigoMorse[numCaractere - 48 + 26];
      
      for(int cont = 0; cont <= cadeiaCodigoMorse.length() - 1; cont++)
      {
        mtdProduzirPiscadaCaractereMorse(cadeiaCodigoMorse[cont], Inversor, PinoLed);
      }
    }
    else
    {
      cadeiaCodigoMorse = codigoMorse[36];
      
      for(int cont = 0; cont <= cadeiaCodigoMorse.length() - 1; cont++)
      {
        mtdProduzirPiscadaCaractereMorse(cadeiaCodigoMorse[cont], Inversor, PinoLed);
      }
    }

    if(contador != lenMensagem - 1)
    { 
      mtdEspacoMensagem(25, Inversor, PinoLed);
    }
  }

  mtdInicioTerminoMensagem(false, Inversor, PinoLed);
}

void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() 
{
  bool inversor = false;
    
  mtdGerarCodigoMorse(String("SOS"), inversor, PINO_LEDVERMELHO);
}
