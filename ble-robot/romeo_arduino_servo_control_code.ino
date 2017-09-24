#include <Wire.h>
#include <Servo.h>
Servo left;
Servo right;
void setup() {
  // put your setup code here, to run once:
  left.attach(4);
  right.attach(7);
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);

}
void receiveEvent(int howMany) {
  char c = Wire.read();
  Serial.println(c);
  if(c == 'u')
  {
    Serial.println("moving up");
    left.write(120);
    right.write(75);

  }
  else if(c=='d')
  {
    Serial.println("moving down");
    left.write(75);
    right.write(120);

 
  }
  else if(c=='r')
  {
    Serial.println("moving left");
    left.write(120);
    right.write(120);
 

  }
  else if(c=='l')
  {
    Serial.println("moving right");
    left.write(75);
    right.write(75);
 
  }
  else if(c=='s')
  {
    Serial.println("stopping");
    left.write(90);
    right.write(90);
    
  }
  
  Serial.println();
       // print the integer
}
