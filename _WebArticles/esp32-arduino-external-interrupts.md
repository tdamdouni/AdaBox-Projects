# ESP32 Arduino: External interrupts

_Captured: 2017-10-01 at 12:39 from [techtutorialsx.com](https://techtutorialsx.com/2017/09/30/esp32-arduino-external-interrupts/)_

The objective of this post is to explain how to handle external interrupts using the ESP32 and the Arduino core. The tests were performed on a DFRobot's [ESP-WROOM-32](https://www.dfrobot.com/product-1559.html?tracking=5977b2a20858a) device integrated in a [ESP32 FireBeetle board](https://www.dfrobot.com/product-1590.html?tracking=5977b2a20858a).

## **Introduction**

The objective of this post is to explain how to handle external interrupts using the ESP32 and the Arduino core.

The tests were performed on a DFRobot's [ESP-WROOM-32](https://www.dfrobot.com/product-1559.html?tracking=5977b2a20858a) device integrated in a [ESP32 FireBeetle board](https://www.dfrobot.com/product-1590.html?tracking=5977b2a20858a).

## **The setup code**

We will start by declaring the pin where the interrupt will be attached on a global variable. Note that depending on your ESP32 board the pin numbering of the ESP32 microcontroller and the one labeled on the board may not match. In the FireeBeetle board, the pin used below (digital pin 25) matches with the one labeled **IO25/D2**.

1
`const` `byte interruptPin = 25;`

We will also declare a counter that will be used by the interrupt routine to communicate with the main loop function and signal that an interrupt has occurred. Note that this variable needs to be declared as volatile since it will be shared by the ISR and the main code. Otherwise, it may be removed due to compiler optimizations.

1
`volatile` `int` `interruptCounter = 0;`

Additionally we will declare a counter to keep track of how many interrupts have already occurred globally since the start of the program. So this counter will be incremented each time an interrupt occurs.

1
`int` `numberOfInterrupts = 0;`

Finally, we will declare a variable of type [portMUX_TYPE](http://esp32.info/docs/esp_idf/html/dd/dbc/structportMUX__TYPE.html), which we will need to take care of the synchronization between the main code and the interrupt. We will see how to use it later.

1
`portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;`

Moving to the setup function, we start by opening a serial connection, in order to be able to output the results of our program.

Next, since we are going to be working with an external pin interrupt, we need to configure the previously declared pin number as an input pin. To do so we call the [pinMode](https://www.arduino.cc/en/Reference/PinMode) function, passing as argument the the number of the pin and the operating mode.

In order to know the state of the input when no electric signal is applied to our pin, we use the **INPUT_PULLUP** mode. So, when no signal is applied, it will be at a voltage level of **VCC** instead of floating, avoiding the detection of non existing external interrupts.

Next we attach the interrupt to the pin with a call to the [attachInterrupt](https://www.arduino.cc/en/Reference/AttachInterrupt) function. As first argument, we pass the result of a call to the **digitalPinToInterrupt** function, which converts the pin number used to the corresponding internal interrupt number.

Next we pass the function that will handle the interrupts or, in other words, that will be executed when an interrupt on the specified pin occurs. We will call it **handleInterrupt** and specify its code later.

Finally we pass the interrupt mode, which basically specifies which type of change in the pin input signal triggers the interrupt. We will use **FALLING**, which means that the interrupt will occur when a change from VCC to GND is detected on the pin.

The final setup code can be seen below.

## **The main loop**

Now we will move to the main loop. There we will simply check if our interrupts counter is greater than zero. If it does, it means that we have interrupts to handle.

So, if an interrupt has occurred we first take care of decrementing this interrupts counter, signalling that the interrupt has been detected and will be handled.

Note that this counter approach is better than using a flag since if multiple interrupts occur without the main code being able to handle them all, we will not loose any events. On the other hand if we use a flag and multiple interrupts occur without the main code being able to handle them, then the flag value will keep being set to true in the ISR and the main loop handler will only interpret as if only one has occurred.

Other important aspect to keep in mind is that we should disable interrupts when writing on a variable that is shared with an interrupt. This way we ensure that there is no concurrent access to it between the main code and the ISR.

In the Arduino environment, we usually have the [NoInterrupts](https://www.arduino.cc/en/Reference/NoInterrupts) and [Interrupts](https://www.arduino.cc/en/Reference/Interrupts) function to disable and re-enable interrupts. Nonetheless, at the time of writing, these functions were [not yet implemented](https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/Arduino.h#L82-L85) in the ESP32 Arduino core.

So, we perform the decrement of the variable inside a critical section, which we declare using a **portENTER_CRITICAL** and a **portEXIT_CRITICAL** macro. These calls both receive as input the address of the previously declared global **portMUX_TYPE** variable.

12345678
`if``(interruptCounter>0){``portENTER_CRITICAL(&mux);``interruptCounter--;``portEXIT_CRITICAL(&mux);``//Handle the interrupt``}`

After taking care of decrementing the counter, we will now increment the global counter that holds the number of interrupts detected since the beginning of the program. This variable doesn't need to be incremented inside a critical section since the interrupt service routine will not access it.

After that, we will print a message indicating an interrupt was detected and how many interrupts have happened so far. Note that sending data to the serial port should never be done inside an interrupt service routine due to the fact that ISRs should be designed to execute as fast as possible. If you do this, you will most likely run into runtime problems.

This way, in our architecture, the ISR only takes care of the simple operation of signaling the main loop that the interrupt has occurred, and then the main loop handles the rest.

You can check the full main loop code below.

12345678910111213
`void` `loop() {``if``(interruptCounter>0){``portENTER_CRITICAL(&mux);``interruptCounter--;``portEXIT_CRITICAL(&mux);``numberOfInterrupts++;``Serial.print(``"An interrupt has occurred. Total: "``);``Serial.println(numberOfInterrupts);``}``}`

## **The interrupt handling function**

To finish the code, we will declare our interrupt handling function. As previously mentioned, it will only take care of incrementing the global variable that is used to signalize to the main loop that an interrupt has occurred.

We will also enclose this operation in a critical section, which we declare by calling the **portENTER_CRITICAL_ISR** and **portExit_CRITICAL_ISR** macros. They also both receive as input the address of the global **portMUX_TYPE** variable.

This is needed because the variable we are going to use is also changed by the main loop, as seen before, and we need to prevent concurrent access problems.

The full code for the interrupt handling function is shown below.

12345
`void` `handleInterrupt() {``portENTER_CRITICAL_ISR(&mux);``interruptCounter++;``portEXIT_CRITICAL_ISR(&mux);``}`

## **The final code**

The final source code can be seen below. You can copy and paste it to your Arduino environment to test it.

## **Testing the code**

To test the code, simply upload it to your ESP32 and open the Arduino IDE serial monitor. The easiest way to trigger interrupts is to use a wire to connect and disconnect the digital pin where the interrupt was attached to GND.

Since the pin was declared as **INPUT_PULLUP**, then this will trigger a transition from VCC to GND and an external interrupt will be detected. **Please be careful to avoid connecting the ground pin to the wrong GPIO and damaging the board.**

You should get an output similar to figure 1, which shows the interrupts being triggered and the global counter being printed.

![ESP32 Arduino external interrupts.png](https://techtutorialsx.files.wordpress.com/2017/09/esp32-arduino-external-interrupts.png)

**Figure 1** - Output of the interrupt handling program.
