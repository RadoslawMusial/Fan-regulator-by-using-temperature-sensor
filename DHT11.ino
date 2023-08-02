#include <DHT.h>

#define DHTPIN 10     
#define DHTTYPE DHT11 
int PWM_PIN = 9;
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastMoveTime = 0;
const int moveInterval = 100;

void setup() {
  pinMode(PWM_PIN, OUTPUT); // Ustawienie pinu jako wyjście do sterowania PWM
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
    analogWrite(PWM_PIN, 255); // Ustawienie PWM na 255 (maksymalna prędkość wiatraka)
    if (currentTime - lastMoveTime >= moveInterval) {
      Serial.print("Wiatrak obrót: ");
      Serial.print(currentTime / 100); // Wyświetlenie obrotów wiatraka (czas w dziesiątkach milisekund)
      Serial.println(" RPM");
      lastMoveTime = currentTime;
    }
  } else if (t < 31) {
    analogWrite(PWM_PIN, 128); // Ustawienie PWM na 128 (połowa maksymalnej prędkości wiatraka)
    if (currentTime - lastMoveTime >= moveInterval) {
      Serial.println("Wiatrak zatrzymany");
      lastMoveTime = currentTime;
    }
  }
}
