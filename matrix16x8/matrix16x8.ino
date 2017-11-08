/*
 Scrolling text on 16x8 matrix 
 */
#include "Alphabet.h"

//Pin connected to ST_CP of 74HC595
const int latchPin = 3; //11
//Pin connected to SH_CP of 74HC595
const int clockPin = 4; //10
//Pin connected to DS of 74HC595
const int dataPin = 2; //12
//Pins connected to anodes
const int row1 = 12;
const int row2 = 11;
const int row3 = 10;
const int row4 = 9;
const int row5 = 8;
const int row6 = 7;
const int row7 = 6;
const int row8 = 5;

const int numRows = 8; 
const int numCols = 16;
const int rows[numRows] = {row1,row2,row3,row4,row5,row6,row7,row8}; //for ease of resetting etc

void setup() {
  Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps
  //Shift register pins
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  //Anodes
  for(int i=0;i<numRows;i++)
  {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], LOW);
  }
}

word frame[8] = { //blank frame
  0, //row 0
  0,
  0,
  0,
  0,
  0,
  0,
  0, //row 7
};

//V2
int bufferLength =0;
int dataReceived =0;
int preloaded = 1;
int data[128];
int dataPointer =0;
int dataLength =0;

int incomingByte = 0;
void loop()
{

  // Test
  if (preloaded)
  {
    char makerspace[] = "Makerspace ";
    dataLength=sizeof(makerspace)-1;
    for (int i=0;i<dataLength;i++)
    {
      if ((int)makerspace[i] >= 32)
      {
        data[i] = (char)((int)makerspace[i]-32);
      }
      else
      {
        data[i] = makerspace[i];
      }
    }

    bufferLength = dataLength*6;
  }
  
  // Serial
  if (Serial.available() > 0) {
    //clear display
    digitalWrite(rows[7], LOW);
    for(int k=0;k<numRows;k++)
    {
       frame[k]=0;
    }
    
    //get data
    dataPointer =0;
    dataLength =0;
    delay(250);
    while(Serial.available() > 0)
    {
      incomingByte = (int)Serial.read()-32;
      data[dataPointer]=incomingByte;
      dataPointer++;
      dataLength++;
    }
    dataReceived=1;
    preloaded=0;
    bufferLength = dataLength*6;
  }
  
  if(preloaded | dataReceived){
    for(int currentFrame=0;currentFrame<bufferLength;currentFrame++)
    { 
      
      //update each row of the frame
      byte currentChar = data[currentFrame/6];
      byte *currentCharArray = alphabet[currentChar];
      for(int j=0;j<numRows;j++) //numRows
      {  
        word currentFrameRow = frame[j]<<1;
        byte currentCharRow = currentCharArray[j];
        
        byte nextChar = bitRead(currentCharRow,7-((currentFrame%6)));
        //byte bitMask = B1000000>>(currentFrame%6);
        //byte maskedRow = currentCharRow | bitMask;
        //byte nextChar = maskedRow>>(8-((currentFrame%6)));
       
        word nextFrameRow = currentFrameRow | nextChar;
        frame[j] = nextFrameRow;
      }
      
      for(int frameLength=0;frameLength<8;frameLength++)
      {
        for(int j=0;j<numRows;j++) //numRows
        {  
          updateRow(j);
          delay(2);
        }
      }      
    }  
  }
}

void updateRow(int row)
{
  //take all rows low as a precaution
  for(int i=0;i<numRows;i++)
  {
    digitalWrite(rows[i], LOW);
  }
  byte leftByte = highByte(frame[row]);
  byte rightByte = lowByte(frame[row]);
 
  digitalWrite(latchPin, LOW);
  // shift out the bits:
  shiftOut(dataPin, clockPin, LSBFIRST, rightByte);  
  shiftOut(dataPin, clockPin, LSBFIRST, leftByte);

  //take the latch pin high so 
  digitalWrite(latchPin, HIGH);
  digitalWrite(rows[row], HIGH);   
}



