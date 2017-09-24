// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
const int led = 13;

const int sonarTrig = 11;   // Connect the sonar Trig pin (Blue wire) to pin #3 on the Pro Trinket.
const int sonarEcho = 12;   // Connect the sonar Echo pin (Green wire) to pin #4 on the Pro Trinket.
 
// Number in cm when the LED should turn on.
const int obstacle = 8;
 
// Duration of a ping, distance in inches, distance converted to cm.
long duration, inches, cm;
 
void setup()
{
  pinMode(led, OUTPUT); // initialize the LED as an output.
  pinMode(sonarTrig, OUTPUT); //This will send out the sonar Ping.
  pinMode(sonarEcho, INPUT); // This will listen for the Ping if it bounces off of an object. 
}
 
void loop()
{
  /* The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  Give a short LOW pulse beforehand to ensure a clean HIGH pulse:*/
  digitalWrite(sonarTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(sonarTrig, HIGH);
  delayMicroseconds(5);
  digitalWrite(sonarTrig, LOW);
  /* The sonarEcho pin is used to read the signal from the PING))): a HIGH
  pulse whose duration is the time (in microseconds) from the sending
  of the ping to the reception of its echo off of an object.*/
  duration = pulseIn(sonarEcho, HIGH);
  
  // convert the time into a distance.
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  if ( cm < obstacle ) {
   // obstacle avoidance.
   digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
   digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }
}
 
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}
 
long microsecondsToCentimeters(long microseconds)
{
  // The moveSpeed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
