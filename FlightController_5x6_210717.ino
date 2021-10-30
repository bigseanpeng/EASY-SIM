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
    if(S0_Val<110)
    {
      Joystick.setRudder(0);
    }
    else if(S0_Val>245)
    {
      Joystick.setRudder(255);
    }
    else
    {
      Joystick.setRudder(S0_Val);
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
