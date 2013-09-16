import processing.serial.*;

Serial uart;
int theKey;
String theBuf;
int theSize = 8;
int theScale = 64;
float[][] theBitmap = new float[8][8];
float theTemp = 27.0;

int state = 0;

void setup(){
  size(theSize*theScale,theSize*theScale);
//  PFont font = createFont(PFont.list()[2],14);
//  textFont(font);
  textSize(24);
  
  String uartName = Serial.list()[0];
  uart = new Serial(this, uartName, 115200);
  uart.bufferUntil('\n');
}

void draw(){
  background(0);
  for(int i=0; i<theSize; i++){
    for(int j=0; j<theSize; j++){
      float temp = theBitmap[i][j];
      float r = 0;
      float b = 0;
      float g = 0;
      if(temp > theTemp){
        r = sqrt(temp - theTemp) * 24;
      } else if(temp < theTemp){
        b = sqrt(theTemp - temp) * 24;
      }
      stroke(r,g,b);
      fill(r,g,b);
      rect(i*theScale,j*theScale,theScale,theScale);
      stroke(255);
      fill(255);
      
      // uncomment this line for celcius display
      text(int(temp), (i+0.1)*theScale,(j+0.5)*theScale);
      // uncomment this line for farenheit display
//      text(int(1.8*temp+32), (i+0.1)*theScale,(j+0.85)*theScale);
    }
  }
}

void serialEvent(Serial port){
  theBuf = trim(port.readString());
//  println(theBuf);
  if(theBuf.length() == 9){
    if(theBuf.equals("Grid-EYE:")) state = 1;
  } else if(state > 0 && state <= 8){
    float[] pix = float(split(theBuf, ' '));
    for(int i=0; i<theSize; i++){
      theBitmap[i][state-1] = pix[i];
//      theBitmap[i][state-1] = (pix[i]-20)*16;
    }
    state++;
  } else if(state == 9){
    // get ambient temp
//    theTemp = float(theBuf);
    // println(pix[i]);
    state = 0;
  }
}

void keyPressed(){
  uart.write(key);
  theKey = key;
}

