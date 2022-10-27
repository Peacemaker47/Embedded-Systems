#include <Servo.h>                 // include servo library
Servo myservo;                     // create servo object
#define servopin 11;
#define trigger 26;
#define echo 27;

int angle = 0;                    // initialize servo angle
long cm, cm_old;
void setup() {
  // put your setup code here, to run once:
  myservo.attach(servopin);
 
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
   cm_old = cm
   long duration;
   digitalWrite(trigger, LOW);
   delayMicroseconds(2);
   digitalWrite(trigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigger, LOW);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);

   long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
   if(cm_old>cm){
    myservo.write(angle++);
    }
    else if(cm_old<cm){
      myservo.write(angle--);
      }
   delay(500);   

}
