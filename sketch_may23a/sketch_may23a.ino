#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include <SPI.h>
#include <SD.h>

File myFile;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);

    if (!SD.begin(5)) {
      Serial.println("Error with SD Card!");
      while (1);
  }
  
  Serial.println("SD Card pass!");
  myFile = SD.open("suka.txt");
    
}
void loop() {


  Serial.println("In loop!");
  
  lcd.setCursor(16, 0); //
  Serial.println("lcd.set pass!");
  lcd.autoscroll(); //enable auto-scrolling
  Serial.println("lcd.autoscroll pass!");
  
  if (myFile) {
    Serial.println("if (myFile)");
  
      while (myFile.available()) { //execute while file is available

        
        Serial.println("myFile.available()");
        
        char letter = myFile.read(); //read next character from file
        Serial.println("myFile.read();");
        lcd.print(letter); //display character
        Serial.print(letter);
        delay(300);
      }
  
      myFile.close(); //close file
    }

  lcd.clear();

  while(1);
  
}
