#include <car_bluetooth.h>
#include "MotorDriver.h"
#include <SoftwareSerial.h> //Software Serial Port
#include <String.h>
#include "TM1637.h"
#include <Ultrasonic.h>

#define TRIGGER_PIN  A3 //connect Trip of the Ultrasonic Sensor moudle to A3 of Arduino and can be changed to other ports
#define ECHO_PIN     A2

#define CLK A5 //connect CLK of the 4-Digit Display to A5 of Arduino and can be changed to other ports    
#define DIO A4
TM1637 disp(CLK, DIO);

#define RxD 2 //D2 of Arduino should connect to TX of the Serial Bluetooth module
#define TxD 3 //D3 of Arduino should connect to RX of the Serial Bluetooth module
CarBluetooth bluetooth(RxD, TxD);
#define CMD_INVALID                 0XFF
#define CMD_FORWARD                 'F'
#define CMD_RIGHT_FRONT             'R'
#define CMD_BACKWARD                'B'
#define CMD_LEFT_FRONT              'L'
#define CMD_STOP                    'S'
#define CMD_FRONTS_LIGHTS_ON        'W'
#define CMD_FRONTS_LIGHTS_OFF       'w'

#define cntVelocidadeInicial 200
#define SPEED_STEPS 20
uint8_t speed0 = cntVelocidadeInicial;
#define BIN1 8
#define BIN2 7
#define PWMB 6
#define AIN1 9
#define AIN2 10
#define PWMA 11

#define cntDistanciaMinima 10

#define LINEFINDER_PIN 12 // Define as the Arduino Digital Pin 15 - D12

int intReadLineFinder = 0; // Line detection limit

int intIteracoesAvancar = 10000;
char chrEstadoFarol = CMD_FRONTS_LIGHTS_ON;

void setup()
{
  Serial.begin(9600); // Start serial port for displaying the status of the sensor in baurd rate 9600 
  pinMode(LINEFINDER_PIN, INPUT); //C onfigure the Input Operation pin in the sensor will be connected to as an input

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  disp.set(BRIGHT_TYPICAL); // BRIGHT_TYPICAL = 2, BRIGHT_DARKEST = 0, BRIGHTEST = 7;
  disp.init(D4056A); // D4056A is the type of the module

  motordriver.init(BIN1, BIN2, PWMB, AIN1, AIN2, PWMA);
  motordriver.setSpeed(speed0, MOTORA);
  motordriver.setSpeed(speed0, MOTORB);
  controlCar(CMD_STOP);
  bluetooth.waitConnected();
}
uint8_t bt_command;

#define CAR_STOP 0
#define CAR_FORWARD 1
#define CAR_BACK 2
uint8_t car_status = CAR_STOP;
uint8_t new_status = car_status;
long intervalo_Tempo_Pulso = 0;
int distancia_cm = 0;
// int distancia_in = 0;
int distancia_01 = 0;
int distancia_02 = 0;
int distancia_03 = 0;
int distancia_04 = 0;

void loop()
{
  intReadLineFinder = !digitalRead(LINEFINDER_PIN);

  mtdMedirDistancia();
  disp.display((int16_t)distancia_cm); // in centimeters

  bt_command = bluetooth.readByte();

  if (bt_command != CMD_INVALID)
  {
    if (bt_command == CMD_FRONTS_LIGHTS_OFF)
    {
      chrEstadoFarol = CMD_FRONTS_LIGHTS_OFF;
    }

    if (bt_command == CMD_FRONTS_LIGHTS_ON)
    {
      chrEstadoFarol = CMD_FRONTS_LIGHTS_ON;
    }
    
    if (chrEstadoFarol == CMD_FRONTS_LIGHTS_ON)
    {
      if (!(distancia_cm > 0 && distancia_cm <= cntDistanciaMinima))
      {
        if (intReadLineFinder)
        {
          mtdAvancarVeiculo(bt_command);
        }
        else
        {
          mtdRepararDirecaoVeiculo();
        }
      }
      else
      {
        mtdRepararDirecaoVeiculo();
      }
    }
    
    if (chrEstadoFarol == CMD_FRONTS_LIGHTS_OFF)
    {
      if (!(distancia_cm > 0 && distancia_cm <= cntDistanciaMinima))
      {
        if (intReadLineFinder)
        {
          mtdAvancarVeiculo(CMD_FORWARD);
        }
        else
        {
          mtdModoPatrulhaVeiculo();
        }
      }
      else
      {
        mtdModoPatrulhaVeiculo();
      }
    }
  }
  else
  {
    // controlCar(CMD_STOP);
  }
}

void controlCar(uint8_t cmd)
{
  switch (cmd)
  {
    case CMD_FORWARD:
      motordriver.goForward();
      break;
    case CMD_RIGHT_FRONT:
      motordriver.goRight();
      break;
    case CMD_BACKWARD:
      motordriver.goBackward();
      break;
    case CMD_LEFT_FRONT:
      motordriver.goLeft();
      break;
    case CMD_STOP:
      motordriver.stop();
      break;
    default: break;
  }
  
  if ((cmd >= '0') && (cmd <= '9'))
  {
    speed0 = cmd - 0x30;
    Serial.print(speed0);
    Serial.print(">");
    speed0 = map(speed0, 0, 9, 0, 255);
    Serial.println(speed0);
    motordriver.setSpeed(speed0, MOTORA);
    motordriver.setSpeed(speed0, MOTORB);
  }
}

void speedUp()
{
  if (speed0 < 236)
  {
    speed0 += SPEED_STEPS;
  }
  else
  {
    speed0 = 255;
  }

  motordriver.setSpeed(speed0, MOTORA);
  motordriver.setSpeed(speed0, MOTORB);
}

void speedDown()
{
  if (speed0 > 70)
  {
    speed0 -= SPEED_STEPS;
  }
  else
  {
    speed0 = 50;
  }

  motordriver.setSpeed(speed0, MOTORA);
  motordriver.setSpeed(speed0, MOTORB);
}

void mtdAvancarVeiculo(uint8_t cmd)
{
  speed0 = cntVelocidadeInicial;
  controlCar(cmd);
}

int intAlterarDirecaoRota = 0;

void mtdRepararDirecaoVeiculo()
{
  for (int i = 0; i < 1000; i++)
  {
    controlCar(CMD_BACKWARD);
  }
}

void mtdModoPatrulhaVeiculo()
{
  for (int i = 0; i < 1000; i++)
  {
    controlCar(CMD_STOP);
  }

  for (int i = 0; i < 5000; i++)
  {
    controlCar(CMD_BACKWARD);
  }

  for (int i = 0; i < 10000; i++)
  {
    controlCar(CMD_RIGHT_FRONT);
  }  
}

void mtdMedirDistancia()
{
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, HIGH);

  Delay_(1);

  digitalWrite(TRIGGER_PIN, LOW);

  pinMode(ECHO_PIN, INPUT);

  intervalo_Tempo_Pulso = pulseIn(ECHO_PIN, HIGH);

  // distancia_cm = intervalo_Tempo_Pulso / 29.4 / 2;
  // distancia_in = intervalo_Tempo_Pulso / 74.7 / 2;
  distancia_01 = intervalo_Tempo_Pulso >> 6;
  if (distancia_01 >= 500)
  {
    distancia_01 = 0;
  }
  distancia_02 = distancia_01;
  distancia_03 = distancia_02;
  distancia_04 = distancia_03;

  distancia_cm = (distancia_01 + distancia_02 + distancia_03 + distancia_04) >> 2;
}

void Delay_(int Intervalo)
{
  int i;

  for (i = 1; i <= Intervalo; i++)
  {
    delay(1);
    if (i % 100 == 0)
    {
      // ESP.wdtFeed();
      yield();
    }
  }
}
