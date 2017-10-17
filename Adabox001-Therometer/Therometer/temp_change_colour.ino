#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif


#define PIN 6

int sensorPin = 0;


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(4, 8, PIN,
                            NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
                            NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
                            NEO_GRB            + NEO_KHZ800);
const uint16_t hot[] = {
  matrix.Color(255, 0, 0)
};
const uint16_t mid[] = {
  matrix.Color(0, 255, 0)
};
const uint16_t cold[] = {
  matrix.Color(211, 211, 211)
};
const uint16_t freezing[] = {
  matrix.Color(0, 0, 255)
};
void setup() {
  // put your setup code here, to run once:
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(5);
}
int x    = matrix.width();
int pass = 0;


void loop() {
  // put your main code here, to run repeatedly:
  int reading = analogRead(sensorPin);

  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 3.3;
  voltage /= 1024.0;
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
  //to degrees ((voltage - 500mV) times 100)
  matrix.print(temperatureC);


  if (temperatureC >= 26)
  { if (--x < -32) {
      x = matrix.width();
      matrix.setTextColor(hot[pass]);
    }
  }

  if (temperatureC < 25.9 && temperatureC >= 18)
  { if (--x < -32) {
      x = matrix.width();
      matrix.setTextColor(mid[pass]);
    }
  }

  if (temperatureC < 17.9 && temperatureC >= 0)
  { if (--x < -32) {
      x = matrix.width();
      matrix.setTextColor(cold[pass]);
    }
  }
  if (temperatureC < 0)
  { if (--x < -32) {
      x = matrix.width();
      matrix.setTextColor(freezing[pass]);
    }
  }
  matrix.show();
  delay(150);

}
