# Is Your LED in Backwards?

_Captured: 2018-01-01 at 17:28 from [www.makersbox.us](http://www.makersbox.us/2017/12/is-your-led-in-backwards.html?m=1)_

Since the Arduino I/O pins can sink and source current, it is possible to use one pin as the ground and the other the supply for an LED. One of my [very first projects](http://www.instructables.com/id/Buggy-A-Crafty-Programmable-LED-Creature/), actually used bi-colored LEDs and you could change the color by reversing the pins.

I've been doing beginner soldering kits, and putting an LED in backward is a common mistake. It occurred to me I could use this trick so that a reversed LED could still be used without having to remove and reverse it. Better yet, could it be detected and accounted for automatically?

Since the LED only allows current to flow one direction (unless it is bi-colored), and we have the ability to read the pins as well as output to them, we should be able to figure this out. If we apply voltage (via the internal pull up resistor) to one leg of the LED, if it goes high, near the source voltage, we can assume we are dealing with the cathode, or negative side since no current is flowing. Conversely, if the voltage drops, we can assume we have the anode, or positive side since current is flow.

![](https://2.bp.blogspot.com/-vjGyf4kBmeI/WkfSLX-Q0CI/AAAAAAAAFAY/eKlo1rk94AsDHgjF4nkoEJRPJ-4NEIgPwCLcBGAs/s280/LEDs%2BSketch_bb.png)

Enough theory. Time for proof. With the LED correctly installed, an analogRead() on the pulled up port reads ~350, or 1.7 volts. With it in backwards, it reads nearly 5 volts. Since the voltage drop is more than half, the digitalRead() can be used and the resulting true/false value assigned to correct or incorrect orientation.

Seems like a silly thing, but then again, silly things can be useful at times.

Here is my code if you want to try it for yourself:

int ledPinNeg = A0; // assume negative lead  
int ledPinPos = A1; // assume positive lead  
void setup() {  
Serial.begin(9600);  
// test: with a weak pullup, the pin will read HIGH if LED in backward (no path for current)  
pinMode(ledPinPos, INPUT);  
pinMode(ledPinNeg, OUTPUT);  
digitalWrite(ledPinPos, HIGH); // turn on pull up  
digitalWrite(ledPinNeg, LOW); // sink current  
int testVal = digitalRead(ledPinPos); // reads < 400 if orientation is correct

Serial.print("Pin ");  
Serial.print(ledPinPos);  
Serial.print(" = ");  
Serial.println(analogRead(ledPinPos));

// set both pins to OUTPUT and LOW  
digitalWrite(ledPinPos, LOW); // turn off pullup  
pinMode(ledPinPos, OUTPUT);  
if (testVal){// LED is backward, just swap pins  
int temp = ledPinPos;  
ledPinPos = ledPinNeg;  
ledPinNeg = temp;  
Serial.println("LED IS BACKWARDS OR MISSING");  
}  
else {  
Serial.println("LED APPEARS CORRECT");  
}  
}  
void loop() {  
// put your main code here, to run repeatedly:  
digitalWrite(ledPinPos, HIGH);  
delay(1000);  
digitalWrite(ledPinPos, LOW);  
delay(1000);  
}
