#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int buttonA = 0;
const int buttonB = 16;
const int buttonC = 2;

unsigned long processTime;
int buttonAState = 0;
int buttonBState = 0;
int buttonCState = 0;

int score = 0;
int max_score = 0;

Adafruit_SSD1306 display = Adafruit_SSD1306();

class Ball {
  public:
    int r = 2;
    int x = 100;
    int y = rand() % (31 - 2*r) + r;
    int dx = -2;
    int dy = 1;

  int draw() {
    display.fillCircle(x, y, r, WHITE);
    return 0;
  }

  int update() {
    if (x >= 109 - r - 1) { dx *= -1; }
    if ((y <= r + 1) or (y >= 31 - r - 1)) { dy *= -1; }
    
    x += dx;
    y += dy;
    
    return 0;
  }
};

class Paddle {
  public:
    int height = 10;
    int width = 2;
    int centerx = width;
    int centery = 16;
  
  int draw() {
    display.fillRect(centerx - width/2, centery - height/2, width, height, WHITE);
    return 0;
  }
  
  int update() {
    if ((buttonAState == LOW) and (centery >= height/2 + 1)) {
      centery -= 1;
    }
    if ((buttonCState == LOW) and (centery <= 31 - height/2 - 1)) {
      centery += 1;
    }
    return 0;
  }
};

Ball ball;
Paddle paddle;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);
}

void loop() {
  int oldButtonAState = buttonAState;
  int oldButtonBState = buttonBState;
  int oldButtonCState = buttonCState;

  buttonAState = digitalRead(buttonA);
  buttonBState = digitalRead(buttonB);
  buttonCState = digitalRead(buttonC);
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  
  // check for ball-paddle collision (crude)
  if ((ball.x - ball.r <= paddle.centerx + paddle.width/2 + 1)
  and (ball.y <= paddle.centery + paddle.height/2)
  and (ball.y >= paddle.centery - paddle.height/2)) {
    ball.dx *= -1;
    score +=1;
    if (score > max_score) {
      max_score = score;
    }
  }

  // check for ball-bottom collision
  if (ball.x <= ball.r) {
    ball.x = 100;
    if (score > max_score) {
      max_score = score;
    }
    score = 0;
  }

  // update
  ball.update();
  paddle.update();

  // draw
  display.drawLine(0, 0, 109, 0, WHITE);
  display.drawLine(0, 31, 109, 31, WHITE);
  display.drawLine(109, 0, 109, 31, WHITE);
  display.setRotation(1);
  display.setCursor(0,0);
  display.print(score);
  display.setCursor(0,9);
  display.print("HI:");
  display.print(max_score);
  display.setRotation(0);
  ball.draw();
  paddle.draw();
  
  display.display();
}
