# Back to Basics: SPI (Serial Peripheral Interface)

_Captured: 2017-09-14 at 11:49 from [www.allaboutcircuits.com](https://www.allaboutcircuits.com/technical-articles/spi-serial-peripheral-interface/)_

The Serial Peripheral Interface is used to transfer data between integrated circuits using a reduced number of data lines. This article provides the background information needed for novices to understand the interface.

  * [Serial In, Serial Out Shift Registers](http://www.allaboutcircuits.com/textbook/digital/chpt-12/serial-in-serial-out-shift-register/)

The three most common multi-wire serial data transmission formats that have been in use for decades are [I2C](http://www.allaboutcircuits.com/technical-articles/introduction-to-the-i2c-bus/), [UART](http://www.allaboutcircuits.com/technical-articles/back-to-basics-the-universal-asynchronous-receiver-transmitter-uart/), and SPI. This article looks at the Serial Peripheral Interface (SPI) Bus, which has escaped explicit standardization, so always check the datasheet of the integrated circuit that you are working with before you implement the protocol.

### Capabilities and Characteristics

The Serial Peripheral Interface Bus provides full-duplex synchronous communication between a master device and a slave using four data lines.

#### Basic Master-Slave Configuration

The Serial Peripheral Interface allows bits of data to be shifted out of a master device into a slave, and at the same time, bits can be shifted out of the slave into the master.

_Animation 1 shows data shifted out of Microchip A into Microchip B, and from Microchip B into Microchip A._

![](https://www.allaboutcircuits.com/uploads/articles/Hughes_TechnicalArticles_SPI51.gif)

_Animation 2 shows a virtual 4-channel oscilloscope trace of an SPI transaction between two microchips. Created with Mathematica by Mark Hughes_

As SPI is not standardized, it is possible to encounter situations where either the Most Significant Bit (MSb) or the Least Significant Bit (LSb) is transferred first. Check the datasheet for your device and set up your data-handling routines accordingly. If you are using an Arduino, you can refer to [this page](http://www.arduino.cc/en/Reference/SPISettings) for information on configuring your SPI port.

#### Clock Polarity and Phase

Clock transitions govern the shifting and sampling of data. SPI has [four modes (0,1,2,3)](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus#Clock_polarity_and_phase) that correspond to the four possible clocking configurations.

![](https://www.allaboutcircuits.com/uploads/articles/Hughes_TechnicalArticles_SPI71.jpg)

_Bits that are sampled on the rising edge of the clock cycle are shifted out on the falling edge of the clock cycle, and vice versa._

Each transaction begins when the slave-select line is driven to logic low (slave select is typically an active-low signal). The exact relationship between the slave-select, data, and clock lines depends on how the clock polarity (CPOL) and clock phase (CPHA) are configured.

With non-inverted clock polarity (i.e., the clock is at logic low when slave select transitions to logic low):

  * Mode 0: Clock phase is configured such that data is sampled on the rising edge of the clock pulse and shifted out on the falling edge of the clock pulse. This corresponds to the first blue clock trace in the above diagram. Note that data must be available before the first rising edge of the clock.
  * Mode 1: Clock phase is configured such that data is sampled on the falling edge of the clock pulse and shifted out on the rising edge of the clock pulse. This corresponds to the second blue clock trace in the above diagram.

With inverted clock polarity (i.e., the clock is at logic high when slave select transitions to logic low):

  * Mode 2: Clock phase is configured such that data is sampled on the falling edge of the clock pulse and shifted out on the rising edge of the clock pulse. This corresponds to the first orange clock trace in the above diagram. Note that data must be available before the first falling edge of the clock.
  * Mode 3: Clock phase is configured such that data is sampled on the rising edge of the clock pulse and shifted out on the falling edge of the clock pulse. This corresponds to the second orange clock trace in the above diagram.

### Key Terms

**CLK: **Serial Clock. Controlled by the master device. A new data bit is shifted out with each clock cycle.

**SSN: **Slave Select (the "N" identifies it as an active-low signal). Controlled by the master device. An active slave-select line indicates that the master is sending data to or requesting data from the corresponding slave device.

**MOSI: **Master Out ⇒ Slave In. Data leaves the master device and enters the slave device. MOSI lines on chip A are connected to MOSI lines on chip B.

**MISO: **Master In ⇐ Slave Out. Data leaves the slave device and enters the master device (or another slave, in a daisy-chain configuration; see the next section). MISO lines on chip A are connected to MISO lines on chip B.

**CPOL: **Clock Polarity. This governs the initial logic state of the clock signal. Refer to the previous section for more information.

**CPHA: **Clock Phase. This governs the relationship between the data transitions and the clock transitions. Refer to the previous section for more information.

### Slave Select and Daisy Chain

#### Multiple-Slave-Select Configuration

In the standard SPI arrangement, the master device can write data to or request data from individual devices that share common data lines by enabling the device, i.e., by setting the slave-select line of the corresponding device to logic low. Care should be taken not to enable multiple slaves simultaneously, as the data returned to the master will be corrupted by driver contention between the MISO lines. Certain applications do not require data to be returned to the master; in such cases, multiple slaves can be addressed simultaneously if the master wants to send the same data to multiple slaves.

![](https://www.allaboutcircuits.com/uploads/articles/Hughes_TechnicalArticles_SPI80.jpg)

In the multiple-slave-select configuration, each slave requires a unique slave-select line from the master. If the master does not have enough I/O pins for the required number of slaves, I/O expansion can be implemented by incorporating a decoder/demultiplexer, such as the [74HC(T)238](http://www.nxp.com/documents/data_sheet/74HC_HCT238.pdf) (PDF) (3-to-8 line decoder/demultiplexer).

#### Daisy-Chain Configuration

In this configuration, data moves from one device to the next. The final slave device can return data to the master.

![](https://www.allaboutcircuits.com/uploads/articles/Hughes_TechnicalArticles_SPI81.jpg)

In the daisy-chain configuration, all slaves share a common slave-select line. Data is shifted out of the master into the first slave, and then out of the first slave into the second, and so on. The data cascades down the line until the last slave in the series, which can then use its MISO line to send data to the master device.

This configuration would be well suited to the individually addressable LED light strings that are popular during the holidays.

### Conclusion

The Serial Peripheral Interface has been around for decades, and there is no reason to expect it to go away anytime soon. While I2C and UART might enjoy more popularity, SPI is a versatile and straightforward serial-communications interface that is excellent for certain applications.
