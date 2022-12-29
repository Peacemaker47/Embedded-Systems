#include <avr/sleep.h>
#define interruptPin 2 


void setup() {
  Serial.begin(115200);//Start Serial Comunication
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(interruptPin,INPUT_PULLUP);
  digitalWrite(LED_BUILTIN,HIGH);//turning LED on
}

void loop() {
 delay(5000);//wait 5 seconds before going to sleep
 Going_To_Sleep();
}

void Going_To_Sleep(){
    sleep_enable();
    attachInterrupt(0, wakeUp, LOW);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    digitalWrite(LED_BUILTIN,LOW);
    delay(1000); 
    sleep_cpu();
    Serial.println("just woke up!");
    digitalWrite(LED_BUILTIN,HIGH);
  }

void wakeUp(){
  Serial.println("Interrrupt Fired");//Print message to serial monitor
   sleep_disable();//Disable sleep mode
  detachInterrupt(0); //Removes the interrupt from pin 2;
}

