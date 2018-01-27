# How A Power Supply Works

_Captured: 2017-11-26 at 23:33 from [www.kitronik.co.uk](https://www.kitronik.co.uk/blog/how-a-power-supply-works/)_

## External Power Supplies Used With Electronic Products

### Battery eliminators

A battery eliminator or adjustable power supply is a device that can be used in place of batteries. It takes mains AC power and converts it to 3v, 4.5v, 6v, 9v or 12v DC allowing an equivalent voltage to be supplied for various different numbers of batteries. The selection of the voltage is normally done by turning a small control on the case of the power supply. Adjustable power supplies are usually sold with a range of adapters allowing them to connect to most electronic equipment (provided they have a power-in connection).

### External power supplies

When an electronic product is sold with a power supply, this supply will be fixed to one voltage and one connector. This will make it a little cheaper than the adjustable alternative.

### Labelling

When you look at a power supply it will tell you what the input voltage and current are as well as the output voltage and current, it may also indicate which pin on the output connector is ground and power. You will also see some symbols; the meaning of these symbols is described below:

![how_a_power_supply_works_1](https://www.kitronik.co.uk/wp/wp-content/uploads/2014/01/how_a_power_supply_works_1.jpg)

## How power supplies work

![how_a_power_supply_works_2](https://www.kitronik.co.uk/wp/wp-content/uploads/2014/01/how_a_power_supply_works_2.jpg)

A power supply is used to reduce the mains electricity at 240 volts AC down to some thing more useable, say 12 volts DC. There are two types of power supply, linear and switch mode.

A linear power supply uses a transformer to reduce the voltage. The ratio of primary windings (connected to the mains) to the number of secondary windings (connected to the output) would give the ratio of how much the voltage reduced by, in this case a ratio of 20:1 reduces the 240 volts AC input in to 12 volts AC on the secondary windings.

![how_a_power_supply_works_9](https://www.kitronik.co.uk/wp/wp-content/uploads/2014/01/how_a_power_supply_works_9.jpg)

A switch mode supply works by turning the mains electricity on and off very quickly to reduce the voltage. In this case the reduction in voltage depends upon the ratio of the on time and off time. Switching takes place very fast, at 10,000 times a second or quicker. Using this technique the bulky transformer found in a linear supply can be replaced with a smaller one.

Below is a block diagram of a switch mode power supply. The AC signal is rectified and regulated to produce a high DC voltage. This is then switched on and off rapidly by a FET. Then the switched signal goes through a transformer, although this can reduce the voltage it isolates the output from the mains electricity (for safety reasons). Feedback of the output is then used to control the mark space ratio of the switching so that the output stays at the required voltage. The transformer used in a switch mode supply is much smaller and cheaper than the type used in linear supply, but must be able to handle the higher switching frequencies.

![how_a_power_supply_works_4](https://www.kitronik.co.uk/wp/wp-content/uploads/2014/01/how_a_power_supply_works_4.jpg)

## Transformers

We have already mentioned that there are two types of transformer, those used at low frequencies (50Hz) in a linear power supply and the high speed (>10KHz) version used in switch mode supplies. The linear power supply transformer typically uses a steel core. Because eddy currents would occur in a solid steel core and reduce the efficiency the core is made from insulated steel plates stacked next to each other with the windings wrapped around them.

Because a large transformer is not needed in a switch mode supply it is smaller, lighter and cheaper.

The switch mode supply is more efficient than a linear supply so generates less heat.

Switch mode supplies can be designed to run off different input voltages (240v or 115v) so they can be used world wide.

All of the above reasons mean that the switch mode supply is far more common than linear supplies.

Unfortunately the very fast switching of a switch mode supply puts electrical noise or voltage spikes on to the supply each time it switches. If a clean supply is needed it will have to be a linear supply.

![how_a_power_supply_works_7](https://www.kitronik.co.uk/wp/wp-content/uploads/2014/01/how_a_power_supply_works_7.jpg)

Ferrite toroid (donut shaped) cores work much better with higher frequencies and are used in switch mode supplies.

### Regulated supplies

In the block diagram of the switch mode power supply, the final stage was to smooth out the pulses by adding a large capacitor. Depending upon how accurate the supply needs to be this solution may be adequate. In this design the output will have some ripple; it will vary from the required voltage by a small amount, maybe a few percent.

A regulated supply uses an IC, where the IC monitors the output voltage relative to a reference voltage and adjusts the output accordingly. Regulators have a much lower ripple and often include over current and over temperature protection, whereby they automatically shut down making them and the rest of the supply indestructible. The part shown right is a 7805, a common 5 volt regulator.

### Case types

The most common case type is the plastic case. This is because it can be easily made using an injection moulding process and features such as PCB mounting holes or clips, holes for cable entry exit etc can be included in the design at virtually no extra parts cost. The more expensive alternative is a metal enclosure; however these must be grounded for safety reasons.

Download a pdf version of this page [here ](https://www.kitronik.co.uk/pdf/How_a_power_supply_works.pdf)

Learn more about the author [read more »](https://www.kitronik.co.uk/about/geoff-hampson/)

(C)Kitronik Ltd - You may print this page & link to it, but must not copy the page or part thereof without Kitronik's prior written consent.

![Same Day Dispatch](https://www.kitronik.co.uk/img/banners/same_day_dispatch.png)

> _<- Previous Post Next Post ->_
