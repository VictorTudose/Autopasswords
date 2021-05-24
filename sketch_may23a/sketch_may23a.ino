#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include <SPI.h>
#include <SD.h>
#include <Vector.h>

#define outputA 6
#define outputB 7

int index=0;
int count=0;
File root;
File current;
Vector<String> fileContent;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {

  String buff="";

  lcd.init();
  lcd.backlight();

  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  
  Serial.begin(9600);

  if (!SD.begin(5)) {
      while (1);
  }
  

  root = SD.open("/");
  
  //aLastState = digitalRead(outputA);

}

void loop() {
  
  lcd.setCursor(2, 0); //
  lcd.autoscroll(); //enable auto-scrolling
  //lcd.print(fileContent[0]);
  //Serial.println(fileContent[0]);
  delay(5000);
  lcd.clear();
}
