//DHT11 Sensor:
#include "DHT.h"
#define DHTPIN 12     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11
#define relay1 2
#define relay2 4

DHT dht(DHTPIN, DHTTYPE);


//I2C LCD:
#include <Wire.h> // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>

// Set the LCD I2C address
LiquidCrystal_I2C lcd(0X3F, 16, 2);


void setup() {
  Serial.begin(9600);
  lcd.begin();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t Light");

  dht.begin();

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int light = analogRead(A0);
  lcd.clear();
    // set the cursor to (0,0):
  lcd.setCursor(0, 0);
  // print from 0 to 9:

   lcd.print("Temp: ");
   lcd.print(t);
   lcd.print("C");
  
  // set the cursor to (16,1):
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  delay(1500);

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if(h > 80){
    digitalWrite(relay1,LOW);
    digitalWrite(relay2, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("It may be rain.");
    lcd.setCursor(0,1);
    lcd.print("Pls take umbrella.");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Or don't go outside.");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(h);
    lcd.print("%");
    delay(1500);
    }
  else if((t > 30 && h <= 80) || light < 30){
    digitalWrite(relay1,LOW);
    digitalWrite(relay2, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("It's hot!!!");
    lcd.setCursor(0,1);
    lcd.print("Take sunscreen.");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(h);
    lcd.print("%");
    delay(1500);
    }
  else if((h >= 60 && h < 80) || (t > 23 && t < 30)){
    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, LOW);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("It's normal now.");
    lcd.setCursor(0,1);
    lcd.print("Have a nice day!");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(h);
    lcd.print("%");
    delay(1500);
    }
  else if(h < 60 && t < 23){
    digitalWrite(relay1,LOW);
    digitalWrite(relay2, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("It's cold now");
    lcd.setCursor(0,1);
    lcd.print("Pls take sweater.");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(t);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("Humidity: ");
    lcd.print(h);
    lcd.print("%");
    delay(1500);
    }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t ");
  Serial.print("Light: ");
  Serial.print(light);
  Serial.println();
  delay(500);

}

