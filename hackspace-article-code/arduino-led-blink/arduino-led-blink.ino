// the setup function runs once when you press reset or 
// power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);  
  // wait for a second
  delay(1000);                      
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);   
  // wait for a second
  delay(1000);                      
}

