# Digital Isolators protect RS-232, RS-485, and CAN Buses

_Captured: 2018-03-25 at 12:16 from [www.analog.com](http://www.analog.com/en/analog-dialogue/articles/digital-isolators-protect-rs232-bus.html)_

### Introduction

In applications such as industrial process control, power supply regulation, and point-to-point communications between computers, serial communication buses transmit data over various types of physical networks, such as RS-232, RS-485, and the _Controller Area Network_ (CAN). Each of the interconnected systems usually has its own power supply, and the systems are often separated by long distances, so galvanic isolation is typically required to break up ground loops, protect the system from high-voltage transients, and reduce signal distortion, as well as for physical safety.

### Isolation

Transformers, coupling capacitors, optocouplers--and now, iCouplers--are typical means of providing galvanic isolation, which blocks current from flowing between two points, while allowing data to pass unimpeded (Figure 1). Isolation is used to protect against high voltages or currents caused by line surges or ground loops, which can occur in any system that has multiple ground paths. System grounds that are separated by long cables will not be at the same potential, so ground current will flow between the two systems. Without isolation, this current could introduce noise, degrade measurements, or even destroy system components.

![Figure 1](http://www.analog.com/-/media/images/analog-dialogue/en/volume-39/number-4/articles/digital-isolators-protect-rs232-bus/3910_01.gif?la=en)

> _Figure 1. Galvanic isolation allows information flow but prevents current flow._

Currents that are inductively coupled into the long cables found in industrial environments by motors switching _on_ and _off_, electrostatic discharge (ESD), or nearby lightning strikes can cause rapid changes in ground potential, often as large as hundreds, or thousands, of volts. When this occurs, the logic-level switching signal expected by the remote system would be superimposed on a high voltage with respect to its local ground. Without isolation, this voltage could corrupt the signal or damage the system. Referring all devices connected to the bus to a single ground will protect the system against this destructive energy, and isolating the devices will prevent ground loops and electrical surges.

To completely isolate the system, _all_ signal lines and power supplies must be isolated. An isolated dc-to-dc converter can provide power supply isolation, while the iCoupler digital isolator provides the signal isolation.

iCoupler isolators are magnetic couplers based on chip-scale transformers (Figure 2), as compared with the LEDs and photodiodes used in optocouplers. The planar transformers use CMOS metal layers, plus a gold layer that is placed on top of the passivation. A high breakdown polyimide layer underneath the gold layer insulates the top transformer coil from the bottom. High-speed CMOS circuits connected to the top and bottom coils provide the interface between each transformer and its external signals. Wafer-scale processing provides a low-cost method for integrating multiple isolation channels, as well as other semiconductor functions, in a single package. iCoupler technology eliminates the uncertain current transfer ratios, nonlinear transfer functions, and drift (with time and temperature) associated with optocouplers; reduces power consumption by as much as 90%; and eliminates the need for external drivers or discrete devices.

![Figure 2](http://www.analog.com/-/media/images/analog-dialogue/en/volume-39/number-4/articles/digital-isolators-protect-rs232-bus/3910_02.gif?la=en)

> _Figure 2. iCoupler cross section._

Circuitry on the primary side of the transformer encodes the input logic transitions into 1-ns pulses, which are then coupled through the transformer; circuitry on the secondary side detects them and recreates the input signal, as shown in Figure 3. A _refresh_ circuit on the input side ensures that the output state matches the _input_ state even if no input transitions are present. This is important in _power-up_ situations and for input waveforms with low data rates or constant dc inputs.

![Figure 3](http://www.analog.com/-/media/images/analog-dialogue/en/volume-39/number-4/articles/digital-isolators-protect-rs232-bus/3910_03.gif?la=en)

> _Figure 3. The digital input is recreated at the output of the iCoupler._

Because the purpose of iCoupler products is to isolate an input from an output, the circuitry on one side of the transformers must be contained on a separate chip from the circuitry on the second side of the transformers. The transformers themselves can be placed on either chip--or on a third chip, as in the [ADuM140x](http://www.analog.com/en/products/interface-isolation/isolation/standard-digital-isolators/adum1400.html) shown in Figure 4. The entire chipset is assembled within a standard plastic package similar to that used for a wide variety of semiconductor devices.

![Figure 4](http://www.analog.com/-/media/images/analog-dialogue/en/volume-39/number-4/articles/digital-isolators-protect-rs232-bus/3910_04.gif?la=en)

> _Figure 4. ADuM140x 4-channel isolator construction._

A novel feature of iCoupler devices is their ability to combine both _transmit_ and _receive_ channels in the same package. The iCoupler transformers are inherently bidirectional, so signals can pass in either direction as long as the appropriate circuitry is present on each side of the transformers. In this manner, multichannel isolators are offered with a variety of transmit/receive channel configurations.

### Serial Communication Buses

RS-232 (EIA232) and RS-485 (EIA/TIA485) specifications define the physical layer only, allowing the signal protocol to be defined by the user, or by other standards that specify their use in the physical layer. On the other hand, the CAN bus defines both the physical layer and the data link layer.

**_RS-232:_** The RS-232 bus standard, one of the most popular serial communication buses, was originally specified in 1962 for communication between computers and modems. Still widely used as an intersystem communication link, its simplicity, flexibility, and long history of successful use account for its continued popularity. Designed for point-to-point communications, it provides full-duplex communication using two dedicated, unbalanced single-ended lines with ground-referred signals.

Data rates are limited to 20 kbps, or 64 kbps in a low-voltage variation. The maximum practical cable length is limited to about 16 meters by the 2500-pF maximum load capacitance and the 3-kohm to 7-kohm load impedance. RS-232 specifies _driver_ output levels of -5 V to -15 V for Logic 1 and +5 V to +15 V for Logic 0--and receiver input levels of -3 V to -15 V for Logic 1 and +3 V to +15 V for Logic 0. Voltages between -3 V and +3 V are undefined. The wide voltage swing and undefined region ensures a high level of noise immunity and allows valid signal levels to be received over lengthy cables.

The RS-232 specification defines the pinout for a 25-pin D connector with 20 signal lines, but the 9-pin connector with eight signal lines, shown in Figure 5, is more common. One line in each direction is used for data transmission; the remaining lines are designated for the communications protocol. At its simplest, RS-232 can be implemented with just three lines: _Tx_ (transmit data), _Rx_ (receive data), and GND (ground). A protective ground, used for equipment safety, is defined in the 25-pin connector. This line, typically connected to the power ground or chassis ground, should not be connected to the signal ground or from system to system.

![Figure 5](http://www.analog.com/-/media/images/analog-dialogue/en/volume-39/number-4/articles/digital-isolators-protect-rs232-bus/3910_05.gif?la=en)

> _Figure 5. 8-signal RS-232 network configuration._

The RS-232 standard divides equipment into two categories: DCE (data communications equipment) and DTE (data terminal equipment). These designations are a legacy of their computer and modem heritage; the terms now simply define which lines are connected as inputs and which are connected as outputs.

RS-232 is typically used to connect multiple systems, so isolation between each system and the bus is critical. Digital isolators do not support the RS-232 standard, so they cannot be used between the transceiver and the cable; instead they are used between the transceiver and the local system. The _system_ side of the transceiver typically connects to a universal asynchronous receiver/transmitter (UART) or a processor, using 0 V to 3 V or 0 V to 5 V logic levels. Because the input and output circuits of the iCoupler isolator are electrically isolated from each other, one can be placed between the UART and transceiver as a simple way of isolating the system from the cable. To complete the isolation, an isolated dc-to-dc converter is used to supply power to the isolator and transceiver. The combination of the [ADuM1402](http://www.analog.com/en/products/interface-isolation/isolation/standard-digital-isolators/adum1402.html) iCoupler digital isolator, [ADM232L](http://www.analog.com/en/products/interface-isolation/rs-232-rs-422-rs-485/interface-rs-232/adm232l.html) RS-232 transceiver, and isolated power supply, shown in Figure 6, eliminates ground loops and provides effective protection against surge damage.

![Figure 6](http://www.analog.com/-/media/images/analog-dialogue/en/volume-39/number-4/articles/digital-isolators-protect-rs232-bus/3910_06.gif?la=en)

> _Figure 6. 5-signal isolated RS-232 circuit (DTE side illustrated)._

**_RS-485:_** The RS-485 standard is specified to drive up to 32 pairs of drivers and receivers. Its versatility and ability to drive 4000-meter cables make it popular for a wide range of applications, especially for interconnecting systems over very long distances. The _Small Computer Systems Interface_ (SCSI) and PROFIBUS protocols both use RS-485 for communications.

Usable cable lengths are dependent upon data speed requirements, with speed/length combinations ranging from 200 kbps at 1200 meters to 12 Mbps at 100 meters. Using balanced differential signaling, RS-485 drivers send data across two output lines. The receiver determines the logic state by comparing the two signals; a difference greater than 200 mV provides a valid logic level. Differential amplifiers in the drivers and receivers steer current between the signal lines. This provides a high level of noise immunity in comparison with single-ended schemes such as RS-232.

An _enable_ function allows the drivers to be put into a high-impedance state; so multiple drivers can share a single bus without contention. The software protocol defines the bus arbitration procedure, keeping all but one driver inactive at all times and allowing line-sharing by up to 32 drivers. A half-duplex, 2-wire bidirectional configuration is shown in Figure 7. Each node contains a driver and receiver, with all drivers and receivers sharing the same 2-wire twisted-pair cable. While this simplifies installation and reduces cost, it limits the maximum throughput rate. A 4-wire full-duplex configuration--using one node as a master and the remaining nodes as slaves--is more complex but provides higher data rates.

![Figure 7](http://www.analog.com/-/media/images/analog-dialogue/en/volume-39/number-4/articles/digital-isolators-protect-rs232-bus/3910_07.gif?la=en)

> _Figure 7. 2-wire, multidrop, half-duplex RS-485 network._

Because RS-485 is typically used to connect multiple systems, isolation between each system and the bus is critical. As with RS-232, digital isolators do not support the RS-485 standard, so they cannot be used between the transceiver and the cable; instead they are used between the transceiver and the local system. The _system_ side of the transceiver typically connects to the local bus or a processor. Since the input and output circuits of the iCoupler isolator are electrically isolated from each other, interposing one between the processor and transceiver is a simple way of isolating the system from the cable. To complete the isolation, an isolated dc-to-dc converter is used to supply power to the isolator and transceiver. The combination of [ADuM1301](http://www.analog.com/en/products/interface-isolation/isolation/standard-digital-isolators/adum1301.html) iCoupler digital isolator and isolated power supply shown in Figure 8 eliminates ground loops and provides effective protection against surge damage.

![Figure 8](http://www.analog.com/-/media/images/analog-dialogue/en/volume-39/number-4/articles/digital-isolators-protect-rs232-bus/3910_08.gif?la=en)

> _Figure 8. Isolated RS-485 circuit._

Figure 9 shows the [ADM2486](http://www.analog.com/en/products/interface-isolation/isolation/isolated-rs-485/adm2486.html) single-chip isolated RS-485 transceiver.

![Figure 9](http://www.analog.com/-/media/images/analog-dialogue/en/volume-39/number-4/articles/digital-isolators-protect-rs232-bus/3910_09.gif?la=en)

> _Figure 9. ADM2486 isolated RS-485 transceiver._

_**CAN Bus:**_ The CAN bus standard, originally developed for automotive applications, specifies a 2-wire serial communications protocol that allows data rates up to 1 Mbps, with up to 30 nodes and a 40-meter maximum cable length. It transmits asynchronous data in frames that consist of _start_ and _stop_ bits, an arbitration field, a control field, a cyclic redundancy check (CRC) field, and an _acknowledge_ field. Every node can listen and transmit at the same time, so one of the most important features of the protocol is its nondestructive bit arbitration, which ensures that no data is lost. Each node transmits a dominant _start of message_ (SOM) bit at the beginning of each message. Other nodes will see this activity and will not attempt to start a transmission until the message is complete. Next, the 11-bit or 29-bit arbitration field is transmitted. Also known as the identifier, this field prioritizes the messages sent on the bus. The highest priority node always takes control of the bus, leaving lower-priority nodes to wait. This nondestructive arbitration ensures that the highest priority message always gets through.

The CAN bus, shown in Figure 10, uses a balanced, 2-wire differential interface and typically operates at 3 V or 5 V. _Non-return-to-zero_ (NRZ) encoding is used, ensuring compact messages with a minimum number of transitions and high noise immunity. CAN bus transceivers use a pair of open-drain devices to create a differential signal of CANH (VCC - 0.9 V) to CANL (1.5 V). When driven, the transmitter produces the dominant signal, which represents a logic _low_. When no transmitter is driven, pull-up resistors set the bus to VCC/2, producing the recessive signal, which represents a logic _high_. A _standby_ control puts the transceiver into a low-power mode. A low-power receiver remains active during standby mode, monitoring the bus for state changes--and signaling the controller to activate the local node when activity is detected.

![Figure 10](http://www.analog.com/-/media/images/analog-dialogue/en/volume-39/number-4/articles/digital-isolators-protect-rs232-bus/3910_10.gif?la=en)

> _Figure 10. CAN bus network._

As with RS-232 and RS-485, digital isolators do not support the CAN bus standard, so they cannot be used between the transceiver and the cable; instead they are used between the transceiver and the local CAN controller using standard 3-V or 5-V logic levels. Because the input and output circuits of the iCoupler isolator are electrically isolated from each other, a simple way of isolating the system from the cable is to interpose one between the processor and transceiver. To complete the isolation, an isolated dc-to-dc converter is used to supply power to the isolator and transceiver. The combination of iCoupler digital isolators and an isolated power supply, shown in Figure 11, eliminates ground loops and provides effective protection against surge damage.

![Figure 11](http://www.analog.com/-/media/images/analog-dialogue/en/volume-39/number-4/articles/digital-isolators-protect-rs232-bus/3910_11.gif?la=en)

> _Figure 11. Isolated CAN bus network._

### More About iCouplers

Digital isolators based on iCoupler technology can be compared favorably with optocouplers in terms of integration, performance, power consumption, ease of use, and reliability. iCoupler devices are self-contained, requiring no extra components except for the usual bypass capacitors; they are generally faster, with higher data rates (to 100 Mbps) and shorter propagation delays (18 ns); their power consumption (from 5 mW @ 1 Mbps to 22 mW @ 25 Mbps) is from 1/70 to 1/5 that of comparable optocouplers, with negligible heating of adjacent components; they can be used in the same way as standard digital CMOS; they can work at higher temperatures--with propagation delay essentially insensitive to temperature; and they have increased lifetimes, without LED wearout. They have similar safety approvals to high-quality optocouplers. Currently available iCoupler devices have insulation rated at 2.5 kV rms (400 V rms steady state), with prospects of better than 50% future improvement.

### Full Disclosure

Since _Analog Dialogue_ is not a cookbook, these examples basically illustrate how iCoupler technology can be used in network communications; they are not detailed schematics of tested applications. Please consult product data sheets and any available application notes (see below) for more information. As always, _use extreme caution when working with high-voltage circuits_.

###  References 

[AN-727: iCoupler Isolation in RS-485 Applications.](http://www.analog.com/media/en/technical-documentation/application-notes/AN-727.pdf)  
[AN-740: iCoupler Isolation in RS-232 Applications.](http://www.analog.com/media/en/technical-documentation/application-notes/AN-740.pdf)  
[AN-770: iCoupler Isolation in CAN Bus Applications.](http://www.analog.com/media/en/technical-documentation/application-notes/AN-770.pdf)  
[iCoupler Digital Isolation - Unparalleled Performance and Integration.](http://www.analog.com/en/products/interface-isolation/isolation.html)  
Wayne, Scott, "[Finding the Needle in a Haystack](http://www.analog.com/en/analog-dialogue/articles/measuring-small-differential-voltages.html)," _Analog Dialogue_ 34-01, January-February 2000.

Scott Wayne joined Analog Devices as a design engineer in 1978. Before transferring to the Analog Dialogue staff, he designed a variety of precision analog-to-digital and digital-to-analog converters using modular, hybrid, and monolithic technologies. Scott holds an SBEE from MIT and continues his education through their edX program. He is the author of several articles and holds two patents. In his free time, Scott enjoys hiking, bicycling, and kayaking.
