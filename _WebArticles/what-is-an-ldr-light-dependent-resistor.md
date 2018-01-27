# What is an LDR (Light Dependent Resistor)?

_Captured: 2017-11-26 at 23:28 from [www.kitronik.co.uk](https://www.kitronik.co.uk/blog/how-an-ldr-light-dependent-resistor-works/)_

An [LDR](https://www.kitronik.co.uk/products/components/leds/light-sensors/) is a component that has a (variable) resistance that changes with the light intensity that falls upon it. This allows them to be used in light sensing circuits.

![A typical LDR \(Light Dependent Resistor\)](https://www.kitronik.co.uk/wp/wp-content/uploads/2015/03/how_a_light_dependant_resistor_works_typical_ldr.jpg)

> _A typical LDR_

![Light Dependent Resistor LDR Circuit Symbol](https://www.kitronik.co.uk/wp/wp-content/uploads/2015/03/how_a-light_depedant_resistor_works_circuit_symbol.jpg)

> _LDR Circuit Symbol_

## Variation in resistance with changing light intensity

![Typical LDR \(Light Dependent Resistor\) resistance vs light intensity graph](https://www.kitronik.co.uk/wp/wp-content/uploads/2015/03/how_a-light_depedant_resistor_works_resistance_v_light_intensity.jpg)

> _Typical LDR resistance vs light intensity graph_

The most common type of LDR has a resistance that falls with an increase in the light intensity falling upon the device (as shown in the image above). The resistance of an LDR may typically have the following resistances:

You can therefore see that there is a large variation between these figures. If you plotted this variation on a graph you would get something similar to that shown by the graph shown above.

## Applications of LDRs

There are many applications for Light Dependent Resistors. These include:

### Lighting switch

The most obvious application for an LDR is to automatically turn on a light at a certain light level. An example of this could be a street light or a garden light.

### Camera shutter control

LDRs can be used to control the shutter speed on a camera. The LDR would be used to measure the light intensity which then adjusts the camera shutter speed to the appropriate level.

### Example - LDR controlled Transistor circuit

![LDR \(Light Dependent Resistor\) controlled transistor circuit](https://www.kitronik.co.uk/wp/wp-content/uploads/2015/03/how_a-light_depedant_resistor_works_ldr_controlled_transistor_circuit.jpg)

> _LDR controlled transistor circuit_

The circuit shown above shows a simple way of constructing a circuit that turns on when it goes dark. In this circuit the LDR and the other Resistor form a simple 'Potential Divider' circuit, where the centre point of the Potential Divider is fed to the Base of the NPN Transistor.

When the light level decreases, the resistance of the LDR increases. As this resistance increases in relation to the other Resistor, which has a fixed resistance, it causes the voltage dropped across the LDR to also increase. When this voltage is large enough (0.7V for a typical NPN Transistor), it will cause the Transistor to turn on.

The value of the fixed resistor will depend on the LDR used, the transistor used and the supply voltage.

## Project kits and components

We have an electronic kit which utilises an LDR to detect lowering light levels and light a colour changing LED once it gets dark. This is a great example of an LDR in action. We also sell two different sizes of light dependant resistor, see below for more details.

Download a pdf version of this page [here](https://www.kitronik.co.uk/pdf/How_an_LDR_works.pdf)

Learn more about the author [read more »](https://www.kitronik.co.uk/about/geoff-hampson/)

If you found this article helpful and you would like to receive product updates and free electronic resources from us then sign up [here](http://eepurl.com/e6BGI). We hate spam too and promise to never sell or share your email address, and you can unsubscribe at any time.
