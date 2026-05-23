#define CycleThread1 100U
#define CycleThread2 275U

unsigned long thread1LastMillis = 0;
unsigned long thread2LastMillis = 0;

boolean thread1State = false;
boolean thread2State = false;

boolean cycleCheck(unsigned long *lastMillis, unsigned int cycle) 
{
 unsigned long currentMillis = millis();
 if(currentMillis - *lastMillis >= cycle)
 {
   *lastMillis = currentMillis;
   return true;
 }
 else
   return false;
}

void setup()
{
}

void loop()
{
 if(cycleCheck(&thread1LastMillis, CycleThread1))
 {
    // Cole aqui o codigo que devera ser executado na thread1

   thread1State = !thread1State;
 }
 if(cycleCheck(&thread2LastMillis, CycleThread2))
 {
    // Cole aqui o codigo que devera ser executado na thread2

   thread2State = !thread2State;
 }
}

