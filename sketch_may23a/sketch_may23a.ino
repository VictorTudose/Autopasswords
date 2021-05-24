#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include <SPI.h>
#include <SD.h>
#include <Vector.h>

#define outputA 6
#define outputB 7

int index=1;
int count=0;

File root;
File current;

Vector<String> fileContent;

int aState;
int aLastState;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void setup() {


  Serial.begin(9600);
  Serial.println("Set up had begun");

  String buff="";

  lcd.init();
  lcd.backlight();

  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  
  if (!SD.begin(5)) {
      while (1);
  }
  

  root = SD.open("/");

  Serial.println("Opened root");

  countFiles(root);

  aLastState = digitalRead(outputA);   

  Serial.println("Set up donne");

}

void countFiles(File dir) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    Serial.println(entry.name());
    count++;
    entry.close();
  }
  Serial.println(count);
}


void loop() {
  
   aState = digitalRead(outputA); // Reads the "current" state of the outputA
   // If the previous and the current state of the outputA are different, that means a Pulse has occured
   if (aState != aLastState){     
     lcd.clear();
     if (digitalRead(outputB) != aState) { 
       index ++;
       if(index > count-1)
        index = 1;
     } else {
       index --;
       if(index < 1)
        index = count-1;
     }
     Serial.print("Position: ");
     Serial.println(index);
     openNthFile(index);
   } 
   aLastState = aState; // Updates the previous state of the outputA with the current state
 
}

void openNthFile(int n)
{
  root.rewindDirectory();
  for(int i=0;i<n;i++){
    current = root.openNextFile();
    current.close();
  }
  current = root.openNextFile();
  lcd.print(current.name());
  current.close();
}
