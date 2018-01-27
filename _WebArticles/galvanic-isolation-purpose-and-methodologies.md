# Galvanic Isolation: Purpose and Methodologies

_Captured: 2017-11-18 at 19:15 from [www.allaboutcircuits.com](https://www.allaboutcircuits.com/technical-articles/galvanic-isolation-Purpose-and-Methodologies/)_

### Introduction

Galvanic isolation, generally just referred to as isolation, is the convention used whereby individual parts of the electrical system may possess different ground potentials. The two most common reasons for creating isolation are safety from fault conditions in industrial grade products and where wired communication between devices is needed but each device regulates its own power.

### Methods for Power Isolation

#### Transformers

The most common form of isolation is the use of a transformer. When designing a power regulation circuit where isolation is required, the isolation portion of the design is coupled with the need to step up/step down a voltage rail and is not recognized as an individual portion of the system. In the event that an entire electrical system needs to be isolated (Example: Many automotive validation tests requires power sources be isolated from AC mains) a 1:1 transformer can be placed in series with the system to create the required isolation.

![](https://www.allaboutcircuits.com/uploads/articles/TransformerSMDVariety.jpg)

> _Figure 1: An Assortment of SMD Transformers_

#### Capacitors

A less common method of creating isolation is the use of series capacitors. Due to the permissibility of AC signals through capacitors, this can be an effective method of isolating portions of the electrical system from AC mains. This method is less robust than the transformer method, as a transformer's failure mode is an open while one of a capacitor's failure modes is a short. One of the purposes of creating galvanic isolation from the AC mains is such that in the event of a failure the user is safe from a functionally limitless current source.

![](https://www.allaboutcircuits.com/uploads/articles/CapacitorIsolatedSchMax256.gif)

> _Figure 2: Example of Capacitors being used to Create Isolation_

### Methods for Signal Isolation

#### Opto-isolators

When a signal is required to pass between 2 ground potentials, an opto-isolator is a popular solution. An opto-isolator is a photoresponsive transistor that turns ON when its internal LED is energized. The light emitted from the internal LED is the signal path and thus does not violate the isolation barrier between ground potentials.

##### _Figure 3: Schematic of a Typical Opto-Isolator_

### Hall Effect Sensor

Another method of passing information between electrical systems with separate ground potentials is the use of a Hall effect sensor. A Hall effect Sensor detects inductance non-invasively and does not require direct contact with the signal in question and does not violate the isolation barrier. The most common use of passing inductive information across varying ground potentials is in current sensing probes.

##### ![](https://www.allaboutcircuits.com/uploads/articles/FlukeCurrentClamp.jpg)

> _Figure 4: A Current Probe being used to Measure Current through a Conductor_

### Conclusion

Galvanic isolation is the separation of electrical systems/subsystems by which non direct current can flow and may possess different ground potentials. Isolation can be divided into to main categories: power and signal. There are several methods to achieving isolation and depending on the design requirements some methods may be preferential to others.

#### Practical Example:

![](https://www.allaboutcircuits.com/uploads/articles/PoeExampleTiTPS23753RedLine.png)

> _Figure 5: Schematic of a Power over Ethernet Design based on TPS23753PW Controller_

[In the circuit above](http://www.ti.com/lit/an/slva305c/slva305c.pdf), several transformers and an opto-isolator are implemented to create a switching power supply that is used in power over Ethernet PD (Powered Device) devices. The connector J2 has internal magnetics that isolate the entire system from the PoE source. T1 and U2 isolate the switching power supply (The left side of the red line) from the regulated 3.3V output (the right side of the red line).
