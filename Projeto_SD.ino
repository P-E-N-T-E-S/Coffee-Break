#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>
#include <SoftwareSerial.h>

#define col 16 // Serve para definir o numero de colunas do display utilizado
#define lin  2 // Serve para definir o numero de linhas do display utilizado
#define ende  0x3F // Serve para definir o endereço do display.

int distance;
LiquidCrystal_I2C lcd(0x3F,16,2);
Ultrasonic ultrasonic(12, 13);
SoftwareSerial bluetooth(10, 11); // RX, TX

void setup() {
  lcd.init();
  bluetooth.begin(9600);
  Serial.begin(9600);
}

void loop() {
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("A Mensagem é:");
  lcd.setCursor(0,1);
  if (bluetooth.available()) 
  {
    lcd.print(bluetooth.readString());
  }
  else if(Serial.available())
  {
    lcd.print(Serial.readString());
  }
  delay(1000);


  /*
  distance = ultrasonic.read();
  lcd.print("Distance in CM: ");
  lcd.setCursor(0,1);
  lcd.print(distance);
  delay(1000);*/
}
