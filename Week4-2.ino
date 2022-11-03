

#include <DFRobot_DHT11.h>
DFRobot_DHT11 DHT;
#define DHT11_PIN 33
#define fan 25

void setup(){
  Serial.begin(115200);
  pinMode(fan, OUTPUT);
}

void loop(){
  DHT.read(DHT11_PIN);
  Serial.print("temp:");
  Serial.print(DHT.temperature);
  Serial.print("  humi:");
  Serial.println(DHT.humidity);
  delay(1000);
  if(DHT.temperature<40){
    digitalWrite(fan, HIGH);
    }
    else{
      digitalWrite(fan, LOW);
      }
}
