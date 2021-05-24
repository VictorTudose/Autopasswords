#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
#include <SPI.h>
#include <SD.h>
#include <Vector.h>

#define outputA 6
#define outputB 7
#define interruptPin 2

int index=1;
int count=0;

File root;
File current;

String buff="";
  
Vector<String> fileContent;

int aState;
int aLastState;

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

void writeBufferToSerial()
{
  if(buff.length()!=0){
    Serial.print(buff);
    buff="";
  }
}

void setup() {


  Serial.begin(9600);
    
  String buff="";

  lcd.init();
  lcd.backlight();

  pinMode (interruptPin,INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(interruptPin), writeBufferToSerial, FALLING  );

  pinMode (outputA,INPUT);
  pinMode (outputB,INPUT);
  
  if (!SD.begin(5)) {
      while (1);
  }
  

  root = SD.open("/");

  countFiles(root);

  aLastState = digitalRead(outputA);

}

void countFiles(File dir) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      break;
    }
    count++;
    entry.close();
  }
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
     buff="";
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

  while(current.available())
  {
    buff += (char)current.read();
  }
  current.close();

}
