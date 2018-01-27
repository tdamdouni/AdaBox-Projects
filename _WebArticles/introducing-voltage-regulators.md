# Introducing Voltage Regulators

_Captured: 2017-10-05 at 09:03 from [learn.pimoroni.com](https://learn.pimoroni.com/tutorial/electronics-basics/introducing-voltage-regulators)_

If you're keen to build out a circuit on a breadboard that runs under its own steam, whether it be a simple arrangement of LEDs and buttons, or something more complex involving an ATmega then you might need a Voltage Regulator.

A Voltage Regulator does what it says on the tin. It'll take an unstable or unusable high voltage from a power source, typically batteries or a DC mains adaptor, and regulate it down to a stable, usable voltage. 3.3v and 5v are typical useful voltages, and you can get regulators for both of these.

## Picking a Voltage Regulator

Before you select a voltage regulator, it's crucial to take into account the voltage you want out of it ( probably 3.3v or 5v ) and the voltage you've got available to put into it.

Every voltage regulator has a number of properties that let you know if it's suitable for your particular use, the most important of these is probably Dropout Voltage.

### Dropout Voltage

Every voltage regulator will have what's known as a "dropout" voltage. This is the smallest possible difference between the output voltage, and the input voltage required for it to function.

For example: * A 5v voltage regulator with a 2v dropout requires an absolute minimum of 7 volts to function correctly. * A 3.3v voltage regulator with a 1.1v dropout voltage requires an absolute minimum of 4.4v to function correctly.

From this you can decude that a trio of AA batteries ( 1.5v each ) will give you 4.5v, which is just enough to run a 3.3v regulator. To run a 5v regulator you'll need a minimum of 5 AA batteries, or a single 9v battery.

## Mains DC Supply

If you decide to use a mains supply and it's already at the voltage you need, and a decent supply, then you wont need a regulator. If, however, you want to regulate a 5v supply to 3.3v then you'll need two things:

  1. A way of connecting the power supply to your project
  2. A voltage regulator circuit
![Female terminal block](https://learn.pimoroni.com/static/repos/learn/electronics-basics/female-terminal-block.jpg)

To connect a 5v supply with a 2.1mm jack, you can use a female 2.1mm Plug to Screw Terminal adaptor - http://shop.pimoroni.com/products/male-dc-power-adapter-2-1mm-plug-to-screw-terminal-block

## Connecting Batteries

As you might have guessed, you'll need a 9v battery clip or a 3xAA or 4xAA battery holder if you plan on using batteries.

![Battery Holder](https://learn.pimoroni.com/static/repos/learn/electronics-basics/battery-holder.jpg)

A 9v battery will give you a good solid 5v out of a 5v regulator, and 3xAA will do you proud for 3.3v. Rechargeable batteries are a good bet, since they're less wasteful and maintain a more stable voltage as they drain. 4x1.2v rechargable AA will give you 4.8v which you can also regulate down to 3.3v with no problems.

## Using a Voltage Regulator

Wiring up a Voltage Regulator is simple. They have 3 pins; an input, an output and a ground pin.

Looking at the front of one of our 3.3v Voltage Regulators ( LD33V ), the pins will be 1, 2 and 3 from left to right. These are Ground, Output and Input respectively.

Our 5v Voltage Regulators ( L7805CV ) have a slightly different pinout, they are Input, Ground and Output respectively.

As you might have guessed, you want to put your input voltage into Input ( making sure it's at least output + dropout ), connect your breadboards Live rail to the Output, and connect the Ground of both your input power supply and breadboard to the central Ground pin.

![Voltage regulator on a mini breadboard](https://learn.pimoroni.com/static/repos/learn/electronics-basics/voltage-reg-mini-bb.jpg)

> _The above shows a 3.3v regulator seated on a 170pt breadboard. If you use a larger breadboard you can connect the output of the regulator directly to the provided ground/live rails._

![Voltage regulator on a mini breadboard](https://learn.pimoroni.com/static/repos/learn/electronics-basics/5v-voltage-reg-mini-bb.jpg)

> _And the image above shows a 5v regulator. Note that the Voltage In is now the left-most pin, Voltage Out the right most, and Ground the middle pin._

The capacitors are there to help filter any undesired noise from your power supply and prevent it reaching your circuit. They aren't essential in many hobbyist setups, the regulator will work fine without them, but it's always best to get into good habits. Diagnosing a circuit and finding it's a noise problem because you left out capacitors is never fun!
