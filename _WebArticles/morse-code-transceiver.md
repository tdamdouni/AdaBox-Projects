# Morse Code Transceiver

_Captured: 2018-02-09 at 09:43 from [www.hackster.io](https://www.hackster.io/achindra/morse-code-transceiver-b5ae38?utm_source=Hackster.io+newsletter&utm_campaign=ca1b82efe4-EMAIL_CAMPAIGN_2017_07_26&utm_medium=email&utm_term=0_6ff81e3e5b-ca1b82efe4-141949901&mc_cid=ca1b82efe4&mc_eid=1c68da4188)_

![Morse Code Transceiver](https://hackster.imgix.net/uploads/attachments/415938/export.gif?auto=compress%2Cformat&w=900&h=675&fit=min)

![](https://hackster.imgix.net/uploads/attachments/415931/export.gif?auto=compress%2Cformat&w=680&h=510&fit=max)

I was teaching a class today on Communication Systems and wanted my students to learn by visualizing and experiencing. We did a few experiments to start with Stone Age and understand need for communication and what it means by Language and Grammar, what is reliable communication, signals, messages, etc.

While discussing all this stuff, we reached to a point where we wanted to define our own language for Visual communication, and there we devised Morse Code!

It was obvious that learning Morse code would be a tedious task for each one of us, and hence we needed a machine. So, we decided to write small program that can encode a given string to equivalent Morse code and another decoder that can give the string back for a given Morse code stream.

To find Morse code for a character, I referred following table -

![](https://hackster.imgix.net/uploads/attachments/415932/maxresdefault.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

To translate Morse code to equivalent character, it can be organized into a binary tree as below. With each 'dot' moving to left sub tree and 'dash' moving to right sub tree.

![](https://hackster.imgix.net/uploads/attachments/415933/morse-tree.png?auto=compress%2Cformat&w=680&h=510&fit=max)

> _Morse Code Tree_

This allowed me to quickly encode a string into respective Morse code and vice versa.

I wrote a program in C# as a PoC

;

;

![](https://hackster.imgix.net/uploads/attachments/415934/decode.png?auto=compress%2Cformat&w=680&h=510&fit=max)
    
    
    Hello World
    .... . .-.. .-.. ---  .-- --- .-. .-.. -..
    

However, Since communication has to happen between two parties, I wanted to transmit this encoded Morse code to another device and decode it there.

I used two Arduino boards to build a transmitter and a receiver.

On the transmitter board, I connected a **Laser diode** from Keyes. Easily available and a cheap device. For the distance I am working, 3v input was more than sufficient, however with 5v, I can see the laser reaching at least 200m.

![](https://hackster.imgix.net/uploads/attachments/415936/transmitter.png?auto=compress%2Cformat&w=680&h=510&fit=max)

My transmitter is connected to a computer with Serial interface (over USB). It reads for any data on Serial port, character by character. Find the equivalent Morse code for the character and generate 'dot' and 'dash' light stream.

I created a 50ms pulse, where each 'dot' is a 50ms light beam and a 'dash' being 150ms light beam. Each 'dot' and 'dash' are separated by a 50ms silence. Each character is followed by another 100ms of silence.
    
    
    const char* MorseTable[] = {
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
            // space, !, ", #, $, %, &, '
            NULL, "-.-.--", ".-..-.", NULL, NULL, NULL, NULL, ".----.",
            // ( ) * + , - . /
            "-.--.", "-.--.-", NULL, ".-.-.", "--..--", "-....-", ".-.-.-", "-..-.",
            // 0 1 2 3 4 5 6 7
            "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",
            // 8 9 : ; < = > ?
            "---..", "----.", "---...", "-.-.-.", NULL, "-...-", NULL, "..--..",
            // @ A B C D E F G
            ".--.-.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
            // H I J K L M N O
            "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
            // P Q R S T U V W
            ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
            // X Y Z [ \ ] ^ _
            "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, "..--.-",
            // ' a b c d e f g
            NULL, ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
            // h i j k l m n o
            "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
            // p q r s t u v w
            ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
            // x y z { | } ~ DEL
            "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, NULL,
            };
    int dotLength = 50;
    int dashLength = dotLength*3;
    void setup() {
      // put your setup code here, to run once:
      pinMode(13, OUTPUT);
      Serial.begin(9600);
    }
    void loop() {
      char ch;
      if(Serial.available()){
        ch = Serial.read();
        flashDashDot(MorseTable[ch]);
        delay(dotLength*2);
      }
    }
    void flashDashDot(const char * morseCode)
    {
      int i = 0;
      while(morseCode[i] != 0)
      {
        if(morseCode[i] == '.'){
          dot();
        } else if (morseCode[i] == '-'){
          dash();
        }
        i++;
      }
    }
    void dot()
    {
      digitalWrite(13, HIGH);
      delay(dotLength);
      digitalWrite(13, LOW);
      delay(dotLength);
    }
    void dash()
    {
      digitalWrite(13, HIGH);
      delay(dashLength);
      digitalWrite(13, LOW);
      delay(dotLength);
    } 
    

On the Receiver Arduino board, I connected an **LDR**, a **Piezo buzzer** and an **LED**. LED and Buzzer are redundant, just that they give Audio and Video feedback and it feels nice to see things work 😉

![](https://hackster.imgix.net/uploads/attachments/415937/receiver.png?auto=compress%2Cformat&w=680&h=510&fit=max)

My receiver is also connected to a computer to read the resulting string character.

On the device, in a loop, I read for any light hitting the LDR that is connected to Analog port 4. I shielded it from any ambient light by encapsulating it with a long tube. When light from my Laser diode hits this LDR, the resulting value goes high and I turn the speaker and led on. When it goes down, I turn the speaker and led off.

I am calculating the length of light beam to determine if it was a 'dot' or a 'dash'. Accounting all delays, it came to ~400 cycles for a pulse on my 16MHz Atmel processor.
    
    
    //Morse Code Binary Tree
    //  Left child at 2n+1
    // Right child at 2n+2
    //         <.|->
    //      .E       -T
    //    .I  -A   .N  -M
    //
    const char MorseTree[] = {'\0','E', 'T', 'I', 'A', 'N', 'M', 'S',
                              'U', 'R', 'W', 'D', 'K', 'G', 'O', 'H',
                              'V', 'F', 'U', 'L', 'A', 'P', 'J', 'B',
                              'X', 'C', 'Y', 'Z', 'Q', '\0','\0','5',
                              '4', '\0','3', '\0','\0','\0','2', '\0',
                              '\0','+', '\0','\0','\0','\0','1', '6',
                              '=', '/', '\0','\0','\0','(', '\0','7',
                              '\0','\0','\0','8', '\0','9', '0', '\0',
                              '\0','\0','\0','\0','\0','\0','\0','\0',
                              '\0','\0','\0','?', '_', '\0','\0','\0',
                              '\0','"', '\0','\0','.', '\0','\0','\0',
                              '\0','@', '\0','\0','\0','\0','\0','\0',
                              '-', '\0','\0','\0','\0','\0','\0','\0',
                              '\0',';', '!', '\0',')', '\0','\0','\0',
                              '\0','\0',',', '\0','\0','\0','\0',':',
                              '\0','\0','\0','\0','\0','\0','\0'
                             };
    int val = 0; // A Variable to Store the Light Value from the LDR
    int ctrHigh = 0;
    int ctrLow = 0;
    int codePtr = 0;
    int dotLen = 400;
    void setup()
    {
      Serial.begin(9600);// Start a Serial Connection
      Serial.print(codePtr);
    }
    void loop()
    {
      val = analogRead(4);
      if (val >= 10)
      {
        ctrHigh++;
        ctrLow = 0;
        digitalWrite(13, HIGH);
        tone(9, 1000);
      } else {
        ctrLow++;
        if ((ctrHigh >= dotLen) && (ctrHigh < dotLen*2)) {
          Serial.print(".");
          codePtr = (2*codePtr) + 1;
        } else if (ctrHigh >= dotLen * 2) {
          Serial.print("-");
          codePtr = (2*codePtr) + 2;
        } else {
          if(ctrLow == dotLen*2){
            Serial.print(MorseTree[codePtr]);
            codePtr = 0;
          }
        }
        ctrHigh = 0;
        digitalWrite(13, LOW);
        noTone(9);
      }
    }
    

Transceiver in Action
    
    
    Output at Receiver
     ....H.E.-..L.-..L---O.--W---O.-.R.-..L-..D-.-.--!
    
    
    
            NULL, "-.-.--", ".-..-.", NULL, NULL, NULL, NULL, ".----.",
            "-.--.", "-.--.-", NULL, ".-.-.", "--..--", "-....-", ".-.-.-", "-..-.",
            "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",
            "---..", "----.", "---...", "-.-.-.", NULL, "-...-", NULL, "..--..",
            ".--.-.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
            "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
            ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
            "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, "..--.-",
            NULL, ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
            "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
            ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
            "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, NULL,
    
