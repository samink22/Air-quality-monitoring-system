#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define MQ2_PIN A0

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  dht.begin();

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Air Quality");
  lcd.setCursor(0,1);
  lcd.print("Monitor");
  delay(2000);

  lcd.clear();
}

void loop() {

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  int gasLevel = analogRead(MQ2_PIN);

  String quality;

  if (gasLevel < 150)
    quality = "GOOD";
  else if (gasLevel < 300)
    quality = "NORMAL";
  else if (gasLevel < 500)
    quality = "BAD";
  else
    quality = "DANGER";

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(temperature,0);
  lcd.print("C ");

  lcd.print("H:");
  lcd.print(humidity,0);
  lcd.print("%");

  lcd.setCursor(0,1);
  lcd.print("Air:");
  lcd.print(quality);

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("  Hum: ");
  Serial.print(humidity);
  Serial.print("  Gas: ");
  Serial.println(gasLevel);

  delay(2000);
}
