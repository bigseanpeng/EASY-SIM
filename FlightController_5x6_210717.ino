// Program used to test the USB Joystick library when used as 
// a Flight Controller on the Arduino Leonardo or Arduino 
// Micro.
//
// Matthew Heironimus
// 2016-05-29 - Original Version
//------------------------------------------------------------

#include "Joystick.h"



// Set to true to test "Auto Send" mode or false to test "Manual Send" mode.
//const bool testAutoSendMode = true;
const bool testAutoSendMode = false;
int i;
int j;
int k;
int Axis_X_Val;
int Axis_Y_Val;
int RZ_Val;
int S0_Val;
int KeyStatus[30];
const int numCols=5;    
const int numRows=6;    
const int debounceDelay=1;
const int col[]={0,1,2,3,4};    
const int row[]={5,6,7,8,9,10};
const int keyMap[numRows][numCols]= 
{  {1, 2, 3, 4, 5},
   {6, 7, 8, 9, 10},
   {11, 12, 13, 14, 15},
   {16, 17, 18, 19, 20},
   {21, 22, 23, 24, 25},
   {26, 27, 28, 29, 30},  };
const int S0_MAP[]=
{   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  1,  1,  1,  2,  2,  2,  3,  3,  3,  4,  4,  4,  5,  5,  5,
    6,  6,  6,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10, 10, 10, 11,
   11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 18, 18, 19, 20,
   20, 21, 22, 22, 23, 24, 24, 25, 26, 26, 27, 28, 28, 29, 30, 30, 
   31, 32, 32, 33, 34, 34, 35, 36, 36, 37, 38, 39, 39, 40, 41, 42, 
   42, 43, 44, 45, 45, 46, 47, 48, 48, 49, 50, 51, 52, 52, 53, 54, 
   55, 56, 56, 57, 58, 59, 60, 60, 61, 62, 63, 64, 65, 66, 67, 68, 
   69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 
   85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 97, 98, 99,101,102,
  103,105,106,107,109,110,111,113,114,115,117,118,119,121,122,123,
  125,126,127,129,130,131,133,134,135,136,137,139,140,142,143,145,
  146,148,149,151,152,154,155,157,158,160,161,163,164,166,167,169,
  170,172,174,176,178,180,182,184,186,188,190,192,194,196,198,200,
  202,204,206,208,210,212,213,215,216,218,220,222,224,226,228,230,
  232,234,235,237,238,240,242,244,245,247,248,250,252,254,255,255};
/*{   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 
   16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 
   32, 33, 34, 35, 36, 37, 38  39, 40, 41, 42, 43, 44, 45, 46, 47,
   48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
   64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
   80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
   96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,
  112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
  128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
  144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
  160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
  176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
  192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
  208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
  224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
  240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};
*/

void testSingleButtonPush(unsigned int button)
{
  if (button > 0)
  {
    Joystick.releaseButton(button - 1);
  }
  if (button < 30)
  {
    Joystick.pressButton(button);
  }
}

void testMultiButtonPush(unsigned int currentStep) 
{
  for (int button = 0; button < 30; button++)
  {
    if ((currentStep == 0) || (currentStep == 2))
    {
      if ((button % 2) == 0)
      {
        Joystick.pressButton(button);
      } else if (currentStep != 2)
      {
        Joystick.releaseButton(button);
      }
    } // if ((currentStep == 0) || (currentStep == 2))
    if ((currentStep == 1) || (currentStep == 2))
    {
      if ((button % 2) != 0)
      {
        Joystick.pressButton(button);
      } else if (currentStep != 2)
      {
        Joystick.releaseButton(button);
      }
    } // if ((currentStep == 1) || (currentStep == 2))
    if (currentStep == 3)
    {
      Joystick.releaseButton(button);
    } // if (currentStep == 3)
  } // for (int button = 0; button < 30; button++)
}

void testXYAxis(unsigned int currentStep)
{
  int xAxis;
  int yAxis;
  
  if (currentStep < 256)
  {
    xAxis = currentStep - 127;
    yAxis = -127;
    Joystick.setXAxis(xAxis);
    Joystick.setYAxis(yAxis);
  } 
  else if (currentStep < 512)
  {
    yAxis = currentStep - 256 - 127;
    Joystick.setYAxis(yAxis);
  }
  else if (currentStep < 768)
  {
    xAxis = 128 - (currentStep - 512);
    Joystick.setXAxis(xAxis);
  }
  else if (currentStep < 1024)
  {
    yAxis = 128 - (currentStep - 768);
    Joystick.setYAxis(yAxis);
  }
  else if (currentStep < 1024 + 128)
  {
    xAxis = currentStep - 1024 - 127;
    Joystick.setXAxis(xAxis);
    Joystick.setYAxis(xAxis);
  }
}

void testThrottleRudder(unsigned int value)
{
  Joystick.setThrottle(value);
  Joystick.setRudder(255 - value);
}

void setup() {
  Joystick.begin();
  for(i=0;i<numCols;i++)  
  {
     pinMode(col[i],OUTPUT);
     digitalWrite(col[i],HIGH);
  }  
  for(j=0;j<numRows;j++)
  {
     pinMode(row[j],INPUT);
     digitalWrite(row[j],HIGH);
  }
  for(k=0;k<30;k++)
  {
    KeyStatus[k]=false;
  }
  
}

void loop() 
{
  int i;
  int j;
  int k;
  if(Axis_X_Val!=analogRead(3))
  {
    /*
    Axis_X_Val=(analogRead(3)*25/32)-127;
    //Axis_X_Val=(analogRead(3)/4)-127;
     Joystick.setXAxis(Axis_X_Val);
  }
 /*//////////////////////////////////////////////
    if (analogRead(3) < 103)
    {      
      Axis_X_Val=-127;
    }
    else if (analogRead(3) < 142)
    {
      Axis_X_Val=-96;
    }
    else if (analogRead(3) < 178)
    {
      Axis_X_Val=-64;
    }
    else if (analogRead(3) < 218)
    {
      Axis_X_Val=-32;
    }
    else if (analogRead(3) < 267)
    {
      Axis_X_Val=0;
    }
      else if (analogRead(3) < 294)
    {
      Axis_X_Val=32;
    }
      else if (analogRead(3) < 332)
    {
      Axis_X_Val=64;
    }
      else if(analogRead(3) < 373)
    {
      Axis_X_Val=96;
    }
    else if (analogRead(3) > 373)
    {
      Axis_X_Val=128;
    }
    Joystick.setXAxis(Axis_X_Val);
  }
  ////////////////////////////////////////
  if(Axis_Y_Val!=analogRead(2))
  {
    Axis_Y_Val=((analogRead(2)*68)/100)-127;
    Joystick.setYAxis(Axis_Y_Val);
  }
  if(RZ_Val!=analogRead(1))
  {
    if (analogRead(1) < 214)
    {      
      RZ_Val=128;
    }
    else if (analogRead(1) < 609)
    {
      RZ_Val=0;
    }
    else if (analogRead(1) > 609)
    {
      RZ_Val=-127;
    }
    Joystick.setZAxis(RZ_Val);
  }
  if(S0_Val!=analogRead(0))
  {
    S0_Val=analogRead(0);
    //Joystick.setRudder(S0_Val-130);
    /*
    // 25 psi
    if(S0_Val<128)
    {
      Joystick.setRudder(0);
    }
    else if(S0_Val>423)
    {
      Joystick.setRudder(255);
    }
    else
    {
      Joystick.setRudder(((S0_Val-150)*255)/70);
    }
  */
    
    //5Kg
    if(S0_Val<130)
    {
      Joystick.setRudder(0);
    }
    else if(S0_Val>384)
    {
      Joystick.setRudder(255);
    }
    else
    {
      Joystick.setRudder(S0_MAP[S0_Val-130]);
    }
    
  }
  
  for(i=0;i<numCols;i++)
  {
    digitalWrite(col[i],LOW);
    for(j=0;j<numRows;j++)
    {
      if(digitalRead(row[j])==LOW)
      {
        delay(debounceDelay);
        if(digitalRead(row[j])==LOW)
        {
          if(KeyStatus[keyMap[j][i]]!=false)
          {
            KeyStatus[keyMap[j][i]]=false;
            Joystick.pressButton(keyMap[j][i]-1);
          }
        }
      }
      
      if(digitalRead(row[j])==HIGH)
      {
        delay(debounceDelay);
        if(digitalRead(row[j])==HIGH)
        {
          if(KeyStatus[keyMap[j][i]]!=true)
          {
            KeyStatus[keyMap[j][i]]=true;
            Joystick.releaseButton(keyMap[j][i]-1);
          }
        }
      }
    }
    digitalWrite(col[i],HIGH);         
  }
}
