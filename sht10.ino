#include <SHT1x.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define dataPin 7
#define sckPin 8

SHT1x th_sensor(dataPin, sckPin);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting up sensor!");
  lcd.begin(20, 4);
  Serial.println("Starting up LCD 20x4!");
}

void loop()
{
  float temp_c;
  float humid;
  float temp_f;

  humid = th_sensor.readHumidity();
  temp_c = th_sensor.retrieveTemperatureC();
  temp_f = (temp_c*9/5)+32;

  Serial.print("Temp (F): ");
  Serial.print(temp_f);
  Serial.print("Temp (C): ");
  Serial.print(", Humidity: ");
  Serial.println(humid);

  lcd.setCursor(0, 0);
  lcd.print("Drogo T/H Monitor V1");
  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.setCursor(0, 2);
  lcd.print("F:");
  lcd.setCursor(3, 2);
  lcd.print(temp_f);
  lcd.setCursor(8,2);
  lcd.print(", C:");
  lcd.setCursor(13, 2);
  lcd.print(temp_c);
  lcd.setCursor(0, 3);
  lcd.print("Humidity:");
  lcd.setCursor(10, 3);
  lcd.print(humid);
  lcd.setCursor(15, 3);
  lcd.print("%");

  delay(4000);
}
