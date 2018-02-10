# I2C - Inter Integrated Circuit

_Captured: 2018-02-06 at 11:20 from [pinout.xyz](https://pinout.xyz/pinout/i2c)_

### I2C pins in BCM mode are: 2, 3

### I2C pins in WiringPi are: 8, 9

The Raspberry Pi's I2C pins are an extremely useful way to talk to many different types of external peripheral; from the MCP23017 digital IO expander, to a connected ATmega.

The I2C pins include a fixed 1.8 kohms pull-up resistor to 3.3v. This means they are not suitable for use as general purpose IO where a pull-up is not required.

You can verify the address of connected I2C peripherals with a simple one-liner:

```
sudo apt-get install i2c-tools
sudo i2cdetect -y 1
```

You can then access I2C from Python using the smbus library:

```
import smbus
DEVICE_BUS = 1
DEVICE_ADDR = 0x15
bus = smbus.SMBus(DEVICE_BUS)
bus.write_byte_data(DEVICE_ADDR, 0x00, 0x01)
```

