## Level Shifting

More complicated sensors may transmit their readings using heavier serial interfaces, like a UART, SPI, or I2C. Many of those sensors operate at a relatively low voltage, in order to conserve power. Unfortunately, it’s not uncommon that those low-voltage sensors are ultimately interfacing with a microcontroller operating at a higher system voltage. This leads to a problem of level shifting, which has a number of solutions including voltage dividing.

## PWM

Pulse Width Modulation (PWM) is a fancy term for describing a type of digital signal. Pulse width modulation is used in a variety of applications including sophisticated control circuitry. A common way we use them here at SparkFun is to control dimming of RGB LEDs or to control the direction of a servo motor. We can accomplish a range of results in both applications because pulse width modulation allows us to vary how much time the signal is high in an analog fashion. While the signal can only be high (usually 5V) or low (ground) at any time, we can change the proportion of time the signal is high compared to when it is low over a consistent time interval.
