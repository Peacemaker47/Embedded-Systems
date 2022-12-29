void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("What is your name?");
  while(Serial.available()==0){

  }
  String input = Serial.readString();
  Serial.print("Welcome to yout first Serial monitor ");
  Serial.println("input");
  Serial.println("You will encounter more complex apps in the future. Good luck!");
  delay(500);
}
