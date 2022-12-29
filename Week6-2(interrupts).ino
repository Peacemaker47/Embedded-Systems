const byte ledPin = 9;          //Defines the pin the LED is on
const byte interruptPin = 2;    //Defines the pin the button is on
const byte potPin = 0;          //Defines the pin the potentiometer is on

volatile int level;             //Keeps the brightness level of the LED

void setup() {
  pinMode(ledPin, OUTPUT);              //Sets the LED pin to OUTPUT
  pinMode(interruptPin, INPUT_PULLUP);  //Sets the button pin to INPUT_PULLUP
  pinMode(potPin, INPUT);               //Sets the potentiometer pin to INPUT
  attachInterrupt(digitalPinToInterrupt(interruptPin), brightness, RISING);   //Attaches the interrupt to the input pin and brightness method and set it to rising
}

void loop() {
  analogWrite(ledPin, level);   //Sets the LED to the set brightness
}

void brightness() {
  level = analogRead(potPin);           //Reads in the value from the potentiometer
  level = map(level, 0, 1023, 0, 255);  //Maps those values to value for LED brightness
}

