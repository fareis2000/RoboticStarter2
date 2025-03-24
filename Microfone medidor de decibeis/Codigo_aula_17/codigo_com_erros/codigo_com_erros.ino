#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0X27, 16, 2);

const int sampleWindow = 50;
unsigned int sample;

#define SENSOR_PIN A0
#define PIN_QUIET 3
#define PIN_MODERATE 4
#define PIN_LOUD 5



void setup() {
  // put your setup code here, to run once:
  pinMode (SENSOR_PIN, INPUT);
  pinMode (PIN_QUIET, OUTPUT);
  pinMode (PIN_MODERATE, OUTPUT);
  pinMode (PIN_LOUD, OUTPUT);

  digitalWrite(PIN_QUIET, LOW);
  digitalWrite(PIN_MODERATE, LOW);
  digitalWrite(PIN_LOUD, LOW);

  serial.begin(115200);
  lcd.begin();

  lcd.backlight();
    lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long startMillis- millis();

  float peakToPeak = 0;

  unsigned int signalMax = 0;
  unsigned int signalMax = 1024;

  while (millis() - startMillis < sampleWindow){
    sample = analogRead(SENSOR_PIN);
    if (sample <1024){
      if (sample > signalMax){
        signalMax = sample;
      }
      else if (sample < signalMin){
        signalMin = sample; 
      }
    }
  }
  peakToPeak - signalMax - signalMin;

  int db = map(peakToPeak,20,900,49.5,90);

  lcd.setCursor(0, 0);
  lcd.print("Loudness: ");
  lcd.print(db);
  lcd.print("db");

  if (db <= 60)
  {
    lcd.setCursor(0,1);
    lcd.print("level: Quite");
    digitalWrite(PIN_QUIET, HIGH);
    digitalWrite(PIN_MODERATE, LOW);
    digitalWrite(PIN_LOUD, LOW);
  }
  else if (db > 60 && db<85)
  {
    lcd.setCursor(0,1);
    lcd.print("level: Moderate");
    digitalWrite(PIN_QUIET, LOW);
    digitalWrite(PIN_MODERATE, HIGH);
    digitalWrite(PIN_LOUD, LOW);
  } 
  else if (db >= 85)
  {
    lcd.setCursor(0,1);
    lcd.print("level: HIGH");
    digitalWrite(PIN_QUIET, LOW);
    digitalWrite(PIN_MODERATE, LOW);
    digitalWrite(PIN_LOUD, HIGH);
  }

  delay(200);
  lcd.clear();

}
