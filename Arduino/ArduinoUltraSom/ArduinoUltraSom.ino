// Ultrasonic - Library for HR-SC04 Ultrasonic Ranging Module.
// Rev.4 (06/2012)
// J.Rodrigo ( www.jrodrigo.net )
// more info at http://www.ardublog.com
// Wiki: https://github.com/JRodrigoTech/Ultrasonic-HC-SR04/wiki/Plug-&-Play

#include <Ultrasonic.h>

#define PINO_GND 7
#define PINO_ECHO 6
#define PINO_TRIGGER 5
#define PINO_VCC 4

float intervalo_Tempo_Pulso = 0;
float distancia_cm = 0;
float distancia_in = 0;

Ultrasonic ultrasonic(5,6); // (Trig PIN,Echo PIN)

void setup() {
  Serial.begin(9600);
  pinMode(PINO_VCC, OUTPUT); // VCC pin
  pinMode(PINO_GND, OUTPUT); // GND ping
  digitalWrite(PINO_VCC, HIGH); // VCC +5V mode  
  digitalWrite(PINO_GND, LOW); // GND mode
  
  pinMode(PINO_TRIGGER, OUTPUT);
  digitalWrite(PINO_TRIGGER, LOW);
  
  delayMicroseconds(10);
  
  pinMode(PINO_ECHO, INPUT);
}

void loop()
{
  digitalWrite(PINO_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIGGER, LOW);
  
  intervalo_Tempo_Pulso = pulseIn(PINO_ECHO, HIGH);
  
  distancia_cm = intervalo_Tempo_Pulso / 29.4 / 2;
  distancia_in = intervalo_Tempo_Pulso / 74.7 / 2;
  
  Serial.print("Distancia: ");
  Serial.print(distancia_cm);
  Serial.println(" cm");
  Serial.print("Distancia: ");
  Serial.print(distancia_in);
  Serial.println(" in");

  delay(1000);
}
