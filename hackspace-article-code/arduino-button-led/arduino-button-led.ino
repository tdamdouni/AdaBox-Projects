// use btnPin to define which arduino input pin the button is 
// connected to
const int btnPin = 2;

// The setup function runs once every time the Arduino 
// powers up or resets (after a sketch update, for example)
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(btnPin, INPUT);
}

// The loop function runs repeatedly as long as a sketch is 
// loaded and the Arduino has power.
void loop() {
  // Read the state of the button; its a digital input,
  // so possible returned values are HIGH or LOW.
  buttonState = digitalRead(buttonPin);
  // When the button is pressed, buttonState will be HIGH,
  // otherwise, it will be low.
  if (buttonState == HIGH) {
    // turn the onboard LED on
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    // turn the onboard LED off
    digitalWrite(LED_BUILTIN, LOW);
  }
}

