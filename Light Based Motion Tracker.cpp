#include <MaxMatrix.h>

int DIN = 7;   // DIN pin of MAX7219 module
int CLK = 6;   // CLK pin of MAX7219 module
int CS = 5;    // CS pin of MAX7219 module
int maxInUse = 1;


MaxMatrix m(DIN, CS, CLK, maxInUse);
//poop

int newLED = 0;// 0 means array unlit


float sensorTopLeft = A3;
float sensorBottomLeft = A2;
float sensorTopRight = A1;
float sensorBottomRight = A0;

float TopLeft = 0;
float BottomLeft = 0;
float TopRight = 0;
float BottomRight = 0;

float TopLeftRightTilt = 0;
float BottomLeftRightTilt = 0;
float RightUpDownTilt = 0;
float LeftUpDownTilt = 0;

float UpDownTilt = 0;
float LeftRightTilt = 0;

// Left/Right Constants
float TRC = 3/-0.75; //top right constant
float TLC = 3/0.75; //top left constant
float BRC = 3/-0.75; //bottom right constant
float BLC = 3/0.75; //bottom left constant

// Up/Down Constants (opposite signs of left/right constants because of how tilts are calculated)
// Defined separately in case we do calibration step later
float RUC = 3/0.75; //right up constant
float RDC = -3/0.75; //right down constant
float LUC = 3/0.75; //left up constant
float LDC = -3/0.75; //left down constant


int x_pos = 0;
int y_pos = 0;



void setup(void) {
    Serial.begin(9600);
    m.init(); // MAX7219 initialization
    m.setIntensity(8); // initial led matrix intensity, 0-15
}

void loop(void) {
    TopLeft = analogRead(sensorTopLeft);
    BottomLeft = analogRead(sensorBottomLeft);
    TopRight = analogRead(sensorTopRight);
    BottomRight = analogRead(sensorBottomRight);
    TopLeftRightTilt = (TopLeft - TopRight)/(TopLeft + TopRight);  // + tilt is left, - tilt is right
    BottomLeftRightTilt = (BottomLeft - BottomRight)/(BottomLeft + BottomRight);
    RightUpDownTilt = (TopRight - BottomRight)/(TopRight + BottomRight); // + tilt is top
    LeftUpDownTilt = (TopLeft - BottomLeft)/(TopLeft + BottomLeft);

    UpDownTilt = ((TopRight + TopLeft) - (BottomRight + BottomLeft)) / (TopRight + TopLeft + BottomRight + BottomLeft);

    LeftRightTilt = ((TopLeft + BottomLeft) - (TopRight + BottomRight)) / (TopRight + TopLeft + BottomRight + BottomLeft);

    Serial.print("Top Left");
    Serial.print(TopLeft);  // display left sensor

    Serial.print("          Bottom Left");
    Serial.print(BottomLeft);  // display right sensor

    Serial.print("          Top Right");
    Serial.print(TopRight);  // display left sensor

    Serial.print("          Bottom Right");
    Serial.print(BottomRight);  // display right sensor


    Serial.print("          Left/Right Tilt ");
    Serial.print(LeftRightTilt);  //display calculated tilt

    Serial.print("          Up/Down Tilt ");
    Serial.println(UpDownTilt);  //display calculated tilt



  int UDPixel;
  int LRPixel;
  m.clear();
  UDPixel = round((-UpDownTilt)*4.3+3.5);
  LRPixel = round((-LeftRightTilt)*4.3+3.5);
  m.setDot(LRPixel, UDPixel, true);
  
  
  
  


   

    
       
       
}


//   float voltage=5*(sensorValue/1023.0);
// Serial.print("Voltage= ");