# Create Your Own Battery Backup Power Supplies

_Captured: 2017-12-13 at 08:08 from [www.allaboutcircuits.com](https://www.allaboutcircuits.com/projects/battery-backup-power-supplies/)_

Learn to build a battery backup supply for small electronics so you never run out of power.

![](https://www.allaboutcircuits.com/uploads/articles/IMG_9760b.JPG)

There are a lot of electronics that need to be reliably on all the time. Alarm clocks are a good example of this. If the power goes out in the middle of the night and your alarm doesn't go off, you could miss a very important appointment. The simplest solution to this problem is a battery backup system. That way, if the grid power drops below a certain threshold, the batteries will automatically take over and keep everything running until the grid power is restored.

## ![](https://www.allaboutcircuits.com/uploads/articles/Img_9748b.jpg)

### **Materials:**

DC Power Supply

Rechargeable Batteries

Battery Pack

Voltage Regulator (optional)

1k ohm Resistor

2 x Diode (rated for a higher current than the power supply)

Male DC Connector

Female DC Connector

![](https://www.allaboutcircuits.com/uploads/articles/Battery_Backup_Power_Supplies2.png)

### **The Circuit**

There are many different kinds of battery backup systems, and the type that you use is largely dependent on what you are powering. For this project, I designed a simple circuit that you can use to power low power electronics that run at 12 volts or less.

First, you need a DC power supply. These are very common and come in a variety of voltages and current ratings. The power supply connects to the circuit with a DC power connector. This is then connected to a blocking diode. The blocking diode prevents electricity from the battery backup system from feeding back into the power supply. Next, a rechargeable battery is connected using a resistor and another diode. The resistor allows the battery to be slowly charged from the power supply, and the diode provides a low resistance path between the battery and the circuit so that it can power the circuit if the voltage of the power supply ever drops too low. If the circuit that you are driving requires a regulated power supply then you can simply add a voltage regulator onto the end.

![](https://www.allaboutcircuits.com/uploads/articles/battery-backup-power-supply.png?v=1476856129781)

If you are powering an Arduino or similar microcontroller, you should keep in mind that the Vin pin and the DC power connector are already connected to an internal voltage regulator. So you can connect any voltage between 7V and 12V directly to the Vin pin.

### ![](https://www.allaboutcircuits.com/uploads/articles/Img_9748res.jpg)

### **Choose the Resistor Value**

The value of the resistor needs to be chosen carefully so that the battery isn't over charged. To figure out which value resistor you should use, you first need to consider your power supply. When you are working with a non-regulated power supply, the output voltage is not fixed. When the circuit that it's powering is turned off or disconnected, the voltage at the output terminals goes up. This open circuit voltage can be as much as 50% higher than the voltage label on the housing of the power supply. To check this, take a multimeter and measure the voltage at the output terminals of the power supply while no other circuit is connected. This will be the maximum voltage of the power supply.

A NiMH battery can be safely charged at a rate of C/10 or one tenth of its capacity per hour. Once the battery is fully charged, however, continuing to apply this amount of current could quickly damage it. If a battery is to be continuously charged over an indefinite time period (such as in a battery backup system), then the charge rate needs to be very low. Ideally, you will want the charge current to be C/300 or less.

In my case, I'm using a battery pack that is made from AA NiMH batteries that have a capacity of 2500mAh. To be safe, I want the charge current to be 8mA or less. Given this, you can calculate what the value of the resistor needs to be.

To calculate the necessary value of your resistor, start with the open circuit voltage of the power supply, then subtract the voltage of the fully charged battery pack. This gives you the voltage across the resistor. To find the resistance, divide the voltage difference by maximum current. In my case, the power supply had an open circuit voltage of 9V and the voltage of the battery pack was about 6V. This gave a voltage difference of 3V. Dividing these 3 volts by the current of 0.008 amps gives a resistance of 375 ohms. So your resistor should be at least 375 ohms. I used a 1 kohm resistor to be extra safe. Keep in mind, however, that using a larger resistor will slow down the charging significantly. This isn't a problem if the backup power system is very rarely used.

![](https://www.allaboutcircuits.com/uploads/articles/IMG_9760bs.JPG)

### **Using Your Battery Backup Power Supply**

Using the battery backup circuit that I designed, you can plug your power supply into a female DC power connector. This is connected to the battery backup circuit. Then at the output of the battery backup circuit, there is a male DC power connector that can plug into the electronic device that you want to power. This simple plug-in design means that you don't have to modify either the power supply or the appliance.
