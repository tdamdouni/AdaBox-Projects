# Create an Object Tracking System: Using Built-in Arduino Libraries

_Captured: 2017-12-10 at 14:46 from [www.allaboutcircuits.com](https://www.allaboutcircuits.com/projects/create-an-object-tracking-system-using-built-in-arduino-libraries/)_

How to use the native Arduino libraries, how to create a custom library, and generate the framework that is to be used for the duration of this project series.

### Table of Contents:

  1. Using Native Libraries
  2. Write a Custom Library
  3. Framework for Project Series

### Using Native Libraries

The [standard Arduino IDE](https://www.arduino.cc/en/Main/Software) comes loaded with a variety of example sketches and libraries. Using native libraries gives the user access to pre-baked functions and methods that are designed to simplify interfacing with more complex peripherals such as Ethernet communications, mouse functionality, SPI communications, etc. To implement a given library, all that is required is the **#include** preprocessor directive followed by the file name of the library you wish to use. Here is an example:
    
    
                        #include "ExampleLibraryName.h"  // preprocessor directive
    
    void Setup()
    {
    pinMode(13, OUTPUT);             // Set Pin 13 as Output
    }
    
    void loop()
    {
      digitalWrite(13, HIGH);        // turn the LED on (HIGH is the voltage level)
      delay(100);                    // wait for a second
      digitalWrite(13, LOW);         // turn the LED off by making the voltage LOW
      delay(100);    
    }
                      

The code snippet above just shows the syntax required to implement a library named "ExampleLibraryName.h" and does not actually call any methods or functions from the fictitious library.

A library consists of 2 parts: a header file and a source file. The header file (denoted by the *.h extension) is a essentially a list of all functions and methods that are defined in the source file. A header file may reference other libraries by including preprocessor directives like in the code snippet above. The source file is where the methods or functions are actually coded. The source and header files can be written in C or C++ as the Arduino sketch compiler (avr-gcc) works with the C and C++ languages. For a tutorial on writing a C++ library you can refer to The [Arduino Guide](https://www.arduino.cc/en/Hacking/LibraryTutorial). The next section will cover writing a library using the simplified Arduino syntax.

### Writing a Custom Library

The following example is a bit like swatting a fly with a brick: the methodology far exceeds the need but for the sake of simple examples it gets the job done. I want to write a sketch to flash an LED: turn on for X time and then off for Y time. The following code will do this:
    
    
                        void setup()              // initialize function
    {
     pinMode(13, OUTPUT);     // define pin 13 as an output.
    }
    
    void loop()               // main loop
    {
      digitalWrite(13, HIGH);  // turn the LED ON
      delay(100);              // wait for 100ms
      digitalWrite(13, LOW);   // turn the LED OFF
      delay(100);              // wait for 100ms
    }
                      

It is considered good practice to not execute code inside the main loop directly. In order to change the previous code snippet to adhere to this convention you will need to open a second tab. Look at the differences between the code snippets below and compare them to one above. As you will notice the executable code is in the second snippet and that file is referenced in the preprocessor directive at the top of the main file.
    
    
                        /*************  Main File  *************/
    
    #include "BlinkLibraryTest.C"   // PREPROCESSOR DIRECTIVE
    
    void setup()
    {
     pinMode(13, OUTPUT);           // initialize digital pin 13 as an output.
    }
    
    void loop()                     // main loop
    {
      BlinkPattern();               // function being called
    }
                      
    
    
                        /*************  Source File  *************/
    
    #include "Arduino.h"        // PREPROCESSOR DIRECTIVE referencing Arduino library for sketch syntax
    
    void BlinkPattern()         // function being called in main file
    {
      digitalWrite(13, HIGH);   // turn the LED ON
      delay(100);               // wait for 100ms
      digitalWrite(13, LOW);    // turn the LED OFF
      delay(100);               // wait for 100ms
    }
                      

For larger programs a header file can be used to create an aggregate point for source files and other preprocessor directives. The image below shows a rudimentary flow diagram of the interaction of a header file, source files, and a main.

![](https://www.allaboutcircuits.com/uploads/articles/FW_flow.JPG)

In the last example below, you will see the alterations to include a header file with the previous LED blinking program. If the previous code structure was excessive for this tiny bit of code, adding a header is even more so. See the changes below:
    
    
                        /*************  Main File  *************/
    
    #include "BlinkLibraryTest.h"    // PREPROCESSOR DIRECTIVE calling header file
    
    void setup()
    {
     pinMode(13, OUTPUT);            // initialize digital pin 13 as an output.
    }
    
    void loop()
    {
      BlinkPattern();
    }
                      
    
    
                        /*************  Source File  *************/
    
    #include "Arduino.h"       // PREPROCESSOR DIRECTIVE calling Arduino library
    
    void BlinkPattern()        // function being called in main file
    {
      digitalWrite(13, HIGH);  // turn the LED ON
      delay(100);              // wait for 100ms
      digitalWrite(13, LOW);   // turn the LED OFF
      delay(100);              // wait for 100ms
    }
                      
    
    
                        /*************  Header File  *************/
    
    #include "BlinkLibraryTest.c"  // PREPROCESSOR DIRECTIVE calling source file
    
                      

### Framework for Project Series

Now that we have a general understanding of source/header file hierarchy, we can start the framework for this project series. We will need a header and sections dedicated to the following operations:

  1. Servo Control
  2. Ultrasonic Sensor Operation
  3. Object Detection Algorithm
  4. Bluetooth Connectivity
  5. Smart Device Control

You should have a *.c file for every bullet above, a header, and a main file. Most of the files will be left blank. The header should be filled with the #include statements linking all the source files together and main file should have the #include statement linking the header file. The next segment in the project series will cover servo control and will build on this code framework.

**Next Article in Series: [Create an Object Tracking System Part 2: Controlling a Servo](https://www.allaboutcircuits.com/projects/create-an-object-tracking-system-part-2-controlling-a-servo/)**
