#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// LCD (change 0x27 to 0x3F if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Servo
Servo gateServo;

// Sensors
int entrySensor = 2;   // gate sensor
int slot1 = 3;
int slot2 = 4;
int slot3 = 5;
int slot4 = 6;

void setup() {
  pinMode(entrySensor, INPUT);
  pinMode(slot1, INPUT);
  pinMode(slot2, INPUT);
  pinMode(slot3, INPUT);
  pinMode(slot4, INPUT);

  gateServo.attach(9);
  gateServo.write(0); // gate closed

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  delay(2000);
  lcd.clear();
}

void loop() {

  // Read sensors
  int entry = digitalRead(entrySensor);
  int s1 = digitalRead(slot1);
  int s2 = digitalRead(slot2);
  int s3 = digitalRead(slot3);
  int s4 = digitalRead(slot4);

  // Gate control
  if (entry == LOW) {   // car detected
    gateServo.write(90); // open
    delay(2000);
    gateServo.write(0);  // close
  }

  // Display first row (Slot 1 & 2)
  lcd.setCursor(0, 0);
  lcd.print("S1:");
  lcd.print(s1 == LOW ? "F " : "E ");   // F = Full, E = Empty

  lcd.print("S2:");
  lcd.print(s2 == LOW ? "F " : "E ");

  // Display second row (Slot 3 & 4)
  lcd.setCursor(0, 1);
  lcd.print("S3:");
  lcd.print(s3 == LOW ? "F " : "E ");

  lcd.print("S4:");
  lcd.print(s4 == LOW ? "F " : "E ");

  delay(500);
}