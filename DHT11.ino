#include <DHT.h>
#include <Servo.h>

#define DHTPIN 10     
#define DHTTYPE DHT11 
int speed = 128; 
int PWM_PIN = 9;
DHT dht(DHTPIN, DHTTYPE);
Servo myServo;

unsigned long lastMoveTime = 0;
const int moveInterval = 100;
int servoPos = 0;

void setup() {
  myServo.attach(8); 
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Błąd odczytu z czujnika DHT!");
  } else {
    Serial.print("Wilgotność: ");
    delay(1000); 
    Serial.print(h);
    Serial.println(" %");
    Serial.print("Temperatura: ");
     delay(1000); 
    Serial.print(t);
    Serial.println(" *C");
  }

  unsigned long currentTime = millis();

  if (t >= 31) {
    if (currentTime - lastMoveTime >= moveInterval) {
      myServo.write(servoPos);
      servoPos++;
      Serial.print(servoPos);
      if (servoPos > 180) {
        servoPos = 0;
      }
      lastMoveTime = currentTime;
      Serial.print(lastMoveTime);
    }
  } else if (t < 31) {
    if (currentTime - lastMoveTime >= moveInterval) {
      myServo.write(90);
      lastMoveTime = currentTime;
    }
  }
}
