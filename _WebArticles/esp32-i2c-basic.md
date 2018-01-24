# ESP32 (23) – I2C basic

_Captured: 2017-10-09 at 17:29 from [www.lucadentella.it](http://www.lucadentella.it/en/2017/10/09/esp32-23-i2c-basic/)_

In today's tutorial I'll explain you how to interface the esp32 chip to external devices (sensors, displays…) using a very widespread bus: the **I2C** bus.

#### I2C

I2C (pronounced _i-squared-c_) is a **serial** communication bus - invented by Philips in 1982 - that allows two or more devices to communicate. The devices connected to the bus can act as **masters** (devices that "control" the bus) or **slaves**. Usually, a bus has only one _master_ and one or more _slaves_, but the standard allows also [more complex topologies.](http://www.i2c-bus.org/multimaster/) Each _slave_ device must have an **unique address**.

Two different transmission speeds are available: **standard** (100Kbit/s) and **fast** (400Kbit/s).

The I2C bus requires only two communication lines that connect the devices:

  * **SDA**, **S**erial **DA**ta - where data transit
  * **SCL**, **S**erial **CL**ock - where the master generates the _clock_ signal

The two lines must be connected to a reference voltage (Vdd) via _pull-up_ resistors:

![i2c-01](http://www.lucadentella.it/blog/wp-content/uploads/2017/09/i2c-01.jpg)

> _If you want to learn more about the I2C bus, I strongly suggest the website www.i2c-bus.org._

#### esp32

The esp32 chip offers **two** I2C controllers, that can act both as master and slave and communicate in standard and fast speed.

The I2C controllers are internally connected to the IO_MUX matrix, so - as I explained in a [previous post](http://www.lucadentella.it/en/2017/02/07/esp32-9-basic-io/) - you can assign different pins (with some exceptions) to them in your program.

the esp-idf _framework_ includes a **driver** which makes it easy to work with those controllers, without worring about how the different _registers _have to be configured. To use the driver in your program, you only need to **include**its _header_ file:
    
    
    #include "driver/i2c.h"

First you have to configure the controller (_port_) you want to use. The configuration is performed with the **i2c_param_config()** method, which accepts as parameter an **i2c_config_t** struct that contains the settings for the controller:
    
    
    esp_err_t i2c_param_config(i2c_port_t i2c_num, const i2c_config_t* i2c_conf);

The two available _ports_ are listed in an **enum** variable in the i2c.h file:

![i2c-02](http://www.lucadentella.it/blog/wp-content/uploads/2017/09/i2c-02.jpg)

> _The i2c_config_t struct is also defined in the same header file:_
    
    
    typedef struct{
      i2c_mode_t mode
      gpio_num_t sda_io_num;
      gpio_pullup_t sda_pullup_en;
      gpio_num_t scl_io_num;
      gpio_pullup_t scl_pullup_en;
      union {
        struct {
          uint32_t clk_speed;
        } master;
        struct {
          uint8_t addr_10bit_en;
          uint16_t slave_addr;
        } slave;
      };
    } i2c_config_t;

Here's the meaning of the different parameters:

  * **mode** is the working mode of the controller (it can be **I2C_MODE_SLAVE** or **I2C_MODE_MASTER**)
  * **sda_io_num** and **scl_io_num** configure the **pins** connected to SDA and SCL signals
  * **sda_pullup_en** and **scl_pullup_en** allow to enable or disable the internal _pull-up_ resistors (possible values: **GPIO_PULLUP_DISABLE** or **GPIO_PULLUP_ENABLE**)
  * **master.clk_speed** is the speed in _hertz_ of the clock if in master mode (100000 for _standard_ and 400000 for _fast _speed)
  * **slave.slave_addr** is the device address if in slave mode
  * **slave.addr_10bit_en** tells the controller to use an extended (10 instead of 7bits) address (if value is **0**, the 10bit address mode is **disabled**)

The esp32 chip allows, using the IO_MUX matrix, to assign "almost" all the pins to the two I2C controllers. The I2C driver is able to verify if the pins specified in the configuration can be used; if not, it stops the program with an error.

For example, if you want to configure the first I2C controller in master mode, with standard speed and use pins 18 and 19 without enabling the internal _pull-up_ resistors, this is your code:
    
    
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = 18;
    conf.scl_io_num = 19;
    conf.sda_pullup_en = GPIO_PULLUP_DISABLE;
    conf.scl_pullup_en = GPIO_PULLUP_DISABLE;
    conf.master.clk_speed = 100000;
    i2c_param_config(I2C_NUM_0, &conf);

Once configured the controller, you can **install** the driver with **i2c_driver_install()**:
    
    
    esp_err_t i2c_driver_install(i2c_port_t i2c_num, i2c_mode_t mode, 
     size_t slv_rx_buf_len, size_t slv_tx_buf_len, int intr_alloc_flags)

Besides the controller number and its mode, you have to specify the size for the transmitting and receiving buffers (only in _slave_ mode) and additional _flags_ used to allocate the interrupt (usually this parameter is **0**).

For the controller configured in the example above, the driver is installed as it follows:
    
    
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0)

#### Master

Let's now learn how to use the controller in _master_ mode, to send commands and receive data from a _slave._

First, you have to create a **command link**, that is a "logical" element that will contain the list of actions to be performed to interact with the _slave_ device. The command link is created by the i2c_cmd_link_create() method which returns a pointer to the command link _handler_:
    
    
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

You can now use some methods to add actions to the command link:

  * i2c_master_start and i2c_master_stop
  * i2c_master_write and i2c_master_write_byte
  * i2c_master_read and i2c_master_read_byte

To understand their meaning, first you have to learn how a master device communicate with slaves. First, the master sends on the bus the **START** signal, followed by the address (7bits) of the slave device and a bit that specifies the requested operation (**0** for **WRITE**, **1** for **READ**). After every byte sent by the master (including the one that contains the address and the operation bit) the slave answers with an **ACK **bit:

![i2c-04](http://www.lucadentella.it/blog/wp-content/uploads/2017/09/i2c-04.jpg)

> _In your program this translates into:_
    
    
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (slave_addr << 1) | I2C_MASTER_WRITE, true);

The **i2c_master_start()** method adds to the cmd _handler_ the action to send the **START **signal, while the **i2c_master_write_byte()** method sends one byte on the bus. This byte is composed of 7bits for the slave address (slave_addr) _left-shifted_ to 1 bit (**<< 1**) and of the bit **0** (= **IC2_MASTER_WRITE**). If you want to perform a **READ**, you can instead use the **I2C_MASTER_READ **constant.

The last parameter, set to **true**, tells the master to wait for the slave to send the **ACK **bit.

If the requested operation is **write**, now the master can send _n_ bytes to the slave. At the end, the master sends the **STOP** signal:
    
    
    i2c_master_write(cmd, data_array, data_size, true);
    i2c_master_stop(cmd);

I used the **i2c_master_write** method that allows to send an array (uint8_t*) of data. The _data_size_ parameter is the size of the array. Alternatively, I could have used more times the i2c_master_write_byte used previously.

To "execute" the command link, you have to call the **i2c_master_cmd_begin() **method:
    
    
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);

its parameters are the number of the I2C controller, the command link _handler_ and the maximum number of _ticks_ it can wait (this method is indeed **blocking**; in the example below it waits for a maximum of **1 second**).

Finally you can free the resources used by the command link with **i2c_cmd_link_delete(**cmd**)**.

The **read**operation is slightly more complex. First you have to send to the slave device the **command** for the data you want to read. In the following tutorial I'll show you a real application, for now let's assume that the _slave _device is a temperature sensor with address **0x40** and that the command _measure the actual temperature _corresponds to byte **0xF3**.

You've already learned how to send the command:
    
    
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (0x40 << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, (0xF3, true);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

After having successfully sent the command (and eventually after having waited for the sensor to execute it) you can read the output of the sensor creating a new command link with the sensor address (but this time with the **READ **mode) and adding one or mor _read_ actions (based on the number of bytes the sensor sends):
    
    
    uint8_t first_byte, second_byte;
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (0x40 << 1) | I2C_MASTER_READ, true);
    i2c_master_read_byte(cmd, &first_byte, ACK_VAL);
    i2c_master_read_byte(cmd, &second_byte, NACK_VAL);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

The main difference is that, after having read the last byte, the master sends the **NACK **signal. With this signal, it tells that it cannot receive more bytes and therefore the slave must stop transmitting.

ACK and NACK constants are defined as follows:
    
    
    #define ACK_VAL    0x0
    #define NACK_VAL   0x1

#### Demo

At the end of this post, I want to show you a classic example that uses the _master_ mode: an I2C **scanner**. Goal of the program is to analyze the bus looking for any _slave _devices and print their address on screen.

It's a very simple program, up to you to understand its source code in my [Github repository](https://github.com/lucadentella/esp32-tutorial). In the following post you'll learn how to interface with a real sensor to get its data.
