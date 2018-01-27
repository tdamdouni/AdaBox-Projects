# How A Thermistor Works

_Captured: 2017-11-26 at 23:32 from [www.kitronik.co.uk](https://www.kitronik.co.uk/blog/how-a-thermistor-works/)_

## Introduction:

A [thermistor](https://www.kitronik.co.uk/switches-and-sensors/thermistors.html) is a component that has a resistance that changes with temperature. There are two types of thermistor, those with a resistance that increase with temperature (Positive Temperature Coefficient - PTC) and those with a resistance that falls with temperature (Negative Temperature Coefficient - NTC).

![how_a_thermistor_works_1](https://www.kitronik.co.uk/wp/wp-content/uploads/2014/01/how_a_thermistor_works_1.jpg)

> _Temperature coefficient:_

The most common type of thermistors are those in which resistance decreases as the temperature increases (NTC).

![ how_a_thermistor_works_2](https://www.kitronik.co.uk/wp/wp-content/uploads/2014/01/how_a_thermistor_works_2.jpg)

The amount by which the resistance decreases as the temperature increases is not constant, it varies in a non linear way. A formula can be used to calculate the resistance of the thermistor at any given temperature. Normally these are calculated for you and the information can be found in the devices datasheet.

## Thermistor Applications:

There are many applications for a thermistor, three of the most popular are listed below.

### Temperature sensing:

The most obvious application for a thermistor is to measure temperature, they are used to do this in a wide range of products such as thermostats.

### In rush current limiting:

In this application the thermistor is used to initially oppose the flow of current (by having a high resistance) into a circuit. Then as the thermistor warms up (due to the flow of electricity through the device) its resistance drops letting current flow more easily.

### Circuit protection:

In this application the thermistor is used to protect a circuit by limiting the amount of current that can flow into it. If too much current starts to flow into a circuit through the thermistor this causes the thermistor to warm up. This in turn increases the resistance of the thermistor reducing the current that can flow into the circuit.

### Example:

The circuit shown below shows a simple way of constructing a circuit that turns on when it goes hot. The decrease in resistance of the thermistor in relation to the other resistor which is fixed as the temperature rises will cause the transistor to turn on. The value of the fixed resistor will depend on the thermistor used, the transistor used and the supply voltage.

![how_a_thermistor_works_3](https://www.kitronik.co.uk/wp/wp-content/uploads/2014/01/how_a_thermistor_works_3.png)

Download a pdf version of this page [here](https://www.kitronik.co.uk/pdf/How_a_thermistor_works.pdf)

Learn more about the author [read more »](https://www.kitronik.co.uk/about/geoff-hampson/)

(C)Kitronik Ltd - You may print this page & link to it, but must not copy the page or part thereof without Kitronik's prior written consent.

![Free Delivery](https://www.kitronik.co.uk/img/banners/free_delivery.png)

> _<- Previous Post Next Post ->_
