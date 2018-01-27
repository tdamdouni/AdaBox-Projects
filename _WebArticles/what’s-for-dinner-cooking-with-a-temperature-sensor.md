# What’s for dinner? Cooking with a temperature sensor

_Captured: 2017-11-21 at 17:55 from [www.edn.com](https://www.edn.com/electronics-blogs/bakers-best/4458965/What-s-for-dinner--Cooking-with-a-temperature-sensor)_

Integrated circuit (IC) temperature sensors have been inadvertently part of device design since the beginning of the IC days. IC designers have gone through numerous contortions to minimize temperature effects in their chip systems. But the tables have turned. At one point, an IC designer had a brilliant idea to exploit the temperature behavior of an active circuit's p-n junction rather than focusing on ways to minimize it. And far more brilliant were the designers who integrated the digital functionality into the same chip. Out of that has come the current class of temperature sensor ICs. The integrated temperature sensor can easily solve most of your temperature sensing woes if your problems live in the −55 to 200ºC temperature range.

**At the input**

At the temperature sensor IC's input is the environmental temperature. In other words, the soaked temperature of the package changes the behavior of the internal transistors (**Figure 1**).

![](https://www.edn.com/ContentEETimes/Images/01RocketMan/BakersBest146TempSensorF1x600.png)

> _Figure 1_

**  
** This conceptual circuit shows how matched transistors can sense temperature.

The temperature sensing design trick is to eliminate the impact of the transistor's saturation current (IS) through clever configurations and calculations. The saturation current is easy to control by using a constant current source (IC) and a switch, which goes between one transistor and an array of equivalent transistors. In **Figure 1**, we see how the difference between VBE and VBE(N) provides an easy conversion to temperature.

Equation 1 shows the value of one transistor's base-emitter voltage, VBE.

**Equation 1**

Where the

k is Boltzmann constant equaling 1.38×10-23 Joules/Kelvin

q is equal to 1.6021765 × 10 −19 coulomb

T is temperature in Kelvin units

Equation 2 shows the base-emitter value of many transistor's in parallel, VBE(N).

**Equation 2**

If you switch the current source, IC, from one leg to the other, Equation 3 shows the delta between these two base-emitter voltages.

![](https://www.edn.com/ContentEETimes/Images/01RocketMan/BakersBest146TempSensorE3.png)

**Equation 3**

With this calculation, CONSTANT equals k * ln(N)/q or 86.25×10-6 × ln(N).

Conceptually, this gives you an idea of how to quickly measure temperature at the IC level. With a little refinement to the circuit shown in **Figure 1**, the IC temperature sensing accuracy can be a good as ±0.4ºC.

**At the output**

Now that we have an accurate temperature reading, the trick is to present that final value to the world. There are two fundamental ways to present the temperature data: an analog voltage or a digital word.

The analog voltage output is very easy to read. With the proper temperature sensing device, you can capture the analog signal, convert it to a digital representation or servo it back to a point in the circuit.

The digital output capability of temperature sensors is a little more interesting. There are many flavors available, but the main ones are 1-wire, 2-wire or 3-wire.

The 1-wire digital output can provide a pulse width modulation (PWM) pulse count signal or a simple threshold/switch signal. Both signals are useful in fan control circuits. The 2-wire digital output provides I2C or SMBus signals. The digital results are a by-product of an internal analog-to-digital converter. You may also see digital outputs that represent threshold temperatures and possible error conditions. The 3-wire digital output provides an SPI interface.

**The good, the reputable, the attractive**

Quite the opposite of the good, the bad, and the ugly, the temperature sensor family has continued to improve. The next quantum leap for this product family is the size of the device package. The new housing for the most recent temperature sensing devices is a wafer-level package (WLP).

In 1998, Sandia National Laboratories and Fujitsu developed the WLP. The fabrication of this package is completely at the wafer-level, before the dicing process. The assembly of this package concludes with a standard surface mount technology (SMT).

The result of this packaging technique is a super small package outline and low theta junction-to-ambient values. The size of this generation of temperature sensors puts to shame the standard 0.1mF capacitor in a standard 0603 package (**Figure 2**).

![](https://www.edn.com/ContentEETimes/Images/01RocketMan/BakersBest146TempSensorF2x600.png)

**  
Figure 2** The WLP temperature sensor (U1, MAX31875) is smaller than the SMT, 0.1mF capacitor (C1).

**At the dinner table**

The new package for temperature sensors allows you to sprinkle this sensor across your board like you would sprinkle salt and pepper on your dinner. The most recent generation of temperature sensors can perform with accuracy at ±0.4ºC inside a package that has PCB area of 0.76mm2. So, what's on the menu tomorrow??

_[Bonnie Baker](https://www.edn.com/user/BCBaker) has been working with analog and digital designs and systems for more than 30 years.   
_

**References**

  1. "[Thermal Management Handbook](http://pdfserv.maximintegrated.com/en/an/AN4679.pdf)", Maxim Integrated, AN4679
  2. "[Evolution of Wafer-Level Packaging](http://electroiq.com/blog/2004/07/evolution-of-wafer-level-packaging/)," Elenius, Peter, Solid-State Technology 
  3. Baker, Bonnie, "[Cool Down With a Smaller Lower Power Temperature Sensor](https://sub.allaboutcircuits.com/pdfs/DS66-Cool-Down-With-a-Smaller-Lower%20-Power-Temperature-Sensor.pdf)," Maxim Integrated, DS66, Oct 2, 2017 
  4. Baker, Bonnie, "[Designing with temperature sensors, part one: sensor types](https://www.edn.com/electronics-blogs/bakers-best/4368418/Designing-with-temperature-sensors-part-one-sensor-types)," EDN, Sept 22, 2011, pg 22.
  5. Baker, Bonnie, "[Designing with temperature sensors, part two: thermistors,](https://www.edn.com/electronics-blogs/bakers-best/4368522/Designing-with-temperature-sensors-part-two-thermistors)" EDN, Oct 20, 2011, pg 24.
  6. Baker, Bonnie, "[Designing with temperature sensors, part three: RTDs](https://www.edn.com/electronics-blogs/bakers-best/4368684/Designing-with-temperature-sensors-part-three-RTDs)", EDN, Nov 17, 2011, pg 24. 
  7. Baker, Bonnie, "[Designing with temperature sensors, part four: thermocouples](https://www.edn.com/electronics-blogs/bakers-best/4368765/Designing-with-temperature-sensors-part-four-thermocouples)," EDN, Dec 15, 2011, pg 24.
  8. Baker, Bonnie, "[Designing with temperature sensors, part five: IC temperature sensors](https://www.edn.com/electronics-blogs/bakers-best/4368885/Designing-with-temperature-sensors-part-five-IC-temperature-sensors)", EDN, Jan 19, 2012, pg 22. 
