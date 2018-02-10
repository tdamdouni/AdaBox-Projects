# SPI - Serial Peripheral Interface

_Captured: 2018-02-06 at 11:22 from [pinout.xyz](https://pinout.xyz/pinout/spi)_

Known as the four-wire serial bus, SPI lets you daisy-chain multiple compatible devices off a single set of pins by assigning them different chip-select pins.

A useful example of an SPI peripheral is the MCP23S17 digital IO expander chip ( Note the S in place of the 0 found on the I2C version ). You can also use the SPI port to "Bit-Bang" an ATmega 328, loading Arduino sketches onto it with Gordon Hendersons' modified version of AVRDude.

To talk to an SPI device, you assert its corresponding chip-select pin. By default the Pi has CE0 and CE1.

```
import spidev
spi = spidev.SpiDev()
spi.open(0, CHIP_SELECT_0_OR_1)
spi.max_speed_hz = 1000000
spi.xfer([value_8bit])
```
