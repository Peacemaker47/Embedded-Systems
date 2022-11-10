#include <Servo.h>
Servo myservo;
#define pir 21
#define servo 26
int detect = 0;
int pos = 0;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(servo);
  pinMode(pir, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  detect = digitalRead(pir);
  if (detect == HIGH){
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
    }
   

}