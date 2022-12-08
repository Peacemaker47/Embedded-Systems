#include <Servo.h>  // add servo library
#include <EEPROM.h>
 
Servo myservo;  // create servo object to control a servo
 
int potpin = 26;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
 
void setup() {
  myservo.attach(27);  // attaches the servo on pin 9 to the servo object
}
 
void loop() {
  for(int i =0; i;255;i++)
  {
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(val);                  // sets the servo position according to the scaled value
  EEPROM.write(i, val);
  }
  
  delay(15);                           // waits for the servo to get there
}
