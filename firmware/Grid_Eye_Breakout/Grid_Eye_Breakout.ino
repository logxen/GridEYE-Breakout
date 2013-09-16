#include <Wire.h>

byte pixelTempL;
byte pixelTempH;
char addr = 0x68;
float celsius;
float aveTemp;

int irqPin = 2;
int pwmPin = 3;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  
  pinMode(irqPin, INPUT);
  pinMode(pwmPin, OUTPUT);

//  analogWrite(pwmPin, 255);
}

void loop() {
  Serial.print("Grid-EYE:\r\n");
  
  pixelTempL = 0x80;
  aveTemp = 0;
  
  for(int pixel = 0; pixel < 64; pixel++){
    Wire.beginTransmission(addr);
    Wire.write(pixelTempL);
    Wire.endTransmission();
    Wire.requestFrom(addr, 2);
    byte lowerLevel = Wire.read();
    byte upperLevel = Wire.read();

/*    
    Wire.beginTransmission(addr);
    Wire.write(pixelTempH);
    Wire.endTransmission();
    Wire.requestFrom(addr, 1);
    byte upperLevel = Wire.read();
*/

    int temperature = ((upperLevel << 8) | lowerLevel);
//    int temperature = temp - 2048;
    if (temperature > 2047){
      temperature = temperature - 4096;
//      temperature = -(2048 - temperature);
    }
    
    celsius = temperature * 0.25;
    
    Serial.print(celsius);
    Serial.print(" ");
    if((pixel+1)%8 == 0){
      Serial.print("\r\n");
    }
    
    switch(pixel){
    case 27:
    case 28:
    case 35:
    case 36:
      aveTemp += celsius;
      break;
    default:
      break;
    }
    
    pixelTempL = pixelTempL + 2;
  }
  
  Wire.beginTransmission(addr);
  Wire.write(0x0E);
  Wire.endTransmission();
  Wire.requestFrom(addr, 2);
  byte upperLevelTherm = Wire.read();
  byte lowerLevelTherm = Wire.read();
  
/*
  Wire.beginTransmission(addr);
  Wire.write(0x0F);
  Wire.endTransmission();
  Wire.requestFrom(addr, 1);
  byte lowerLevelTherm = Wire.read();
*/

  int temperatureTherm = ((lowerLevelTherm << 8) | upperLevelTherm);
  
  float celsiusTherm = temperatureTherm * 0.0625;
  
  Serial.print(celsiusTherm);
  Serial.print("\r\n\r\n");
  
  aveTemp *= 0.25;
  
  
  delay(25);
}
