unsigned long last1 = 0;
unsigned long last2 = 0;
unsigned long lasts = 0;
unsigned int dur1 = 0;
unsigned int dur2 = 0;
byte tgt1 = 128;
byte tgt2 = 128;

void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), tacho1, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), tacho2, FALLING);

  //Timer 1: Prescaler 0
  TCCR1B = TCCR1B & B11111000 | B00000001;

  analogWrite(9, 128);
  analogWrite(10, 128);
}

void getPwm(byte &val) {
  byte tmp = Serial.parseInt();
  if(tmp > 0) val = map(tmp, 0, 100, 0, 255);
}

void loop() {
  unsigned long cm = millis();

  if(Serial.available()) {
    byte tmp = Serial.parseInt();
    switch(tmp) {
      case 1:
        getPwm(tgt1);
        break;
      case 2:
        getPwm(tgt2);
        break;
    }
  }
  
  if(lasts > cm || (lasts + 1000) < cm) {
    digitalWrite(13, !digitalRead(13));
    Serial.print("Delay1: ");
    Serial.print(dur1);
    Serial.println("µs");

    unsigned long freq = 100000000 / dur1;
    Serial.print("Frequenz1: ");
    Serial.print(freq/100);
    Serial.print('.');
    Serial.print(freq%100);
    Serial.println("Hz");

    freq *= 60;
    freq /= 200;
    Serial.print("RPM1: ");
    Serial.println(freq);

    
    Serial.print("Ziel1: ");
    Serial.print(map(tgt1, 0, 255, 0, 100));
    Serial.println('%');

    
    Serial.print("Delay2: ");
    Serial.print(dur2);
    Serial.println("µs");

    freq = 100000000 / dur2;
    Serial.print("Frequenz2: ");
    Serial.print(freq/100);
    Serial.print('.');
    Serial.print(freq%100);
    Serial.println("Hz");

    freq *= 60;
    freq /= 200;
    Serial.print("RPM2: ");
    Serial.println(freq);

    
    Serial.print("Ziel2: ");
    Serial.print(map(tgt2, 0, 255, 0, 100));
    Serial.println('%');
    
    Serial.println("-----");
    lasts = millis();
  }

  analogWrite(9, tgt1);
  analogWrite(10, tgt2);
}

void tacho1() {
  unsigned long cm = micros();
  dur1 = (cm - last1);
  last1 = cm;
}

void tacho2() {
  unsigned long cm = micros();
  dur2 = (cm - last2);
  last2 = cm;
}
