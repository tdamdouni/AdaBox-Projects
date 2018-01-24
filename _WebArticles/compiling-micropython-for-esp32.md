# Compiling MicroPython for ESP32

_Captured: 2017-11-19 at 15:18 from [medium.com](https://medium.com/@alwint3r/compiling-micropython-for-esp32-85cc1968e424)_

# Compiling MicroPython for ESP32

MicroPython is an implementation of Python 3 programming language that is optimized to run on a microcontroller. It supports many popular microcontroller such as STM32, Teensy, ESP8266 including its official board, Pyboard and of course ESP32 as well.

As I said before, MicroPython is already supporting ESP32. We can download the firmware and simply flash it to any ESP32-based board. So, why do I bother compiling it by myself? Because I am interested to dive in a little bit deeper to find out how it actually works.

It turns out that MicroPython port for ESP32 is built on top of ESP-IDF, the official development framework for ESP32. It means If you have knowledge and experience in working with ESP-IDF, you can extend the MicroPython port for ESP32 and build your own version.

#### What We Need

  1. Latest version of [MicroPython port for ESP32 source code](https://github.com/micropython/micropython-esp32).
  2. Latest version of ESP-IDF.

#### Compiling the Code

To compile the code, we need to move to `ports/esp32` directory inside the MicroPython for ESP32 code directory. There's a README.md file inside that directory. The complete instruction for compiling the code is written there. In short, we need to compile the cross-compiler and then build the firmware by compiling code inside `ports/esp32` directory including ESP-IDF.

To compile the cross-compiler, we need to move to the MicroPython root directory. Then, we run the following command:
    
    
    make -C mpy-cross

We move back to the `ports/esp32` directory to build the firmware. Before doing any compilation, let's see what's in the Makefile. It turns out that MicroPython uses an (not necessarily) old revision of ESP-IDF.
    
    
    ESPIDF_SUPHASH := 2c95a77cf93781f296883d5dbafcdc18e4389656  
    ESPIDF_CURHASH := $(shell git -C $(ESPIDF) show -s --pretty=format:'%H')

The snippet is taken from line 32 to line 33 in the Makefile. As you can see, the commit hash used is [2c95a77cf93781f296883d5dbafcdc18e4389656](https://github.com/espressif/esp-idf/commit/2c95a77cf93781f296883d5dbafcdc18e4389656) which is published on October 24th.

If we look further, running `make` will print a warning if our ESP-IDF version is different with the one that MicroPython use. For now, let's stick with the latest version of ESP-IDF and see how the compilation process goes.

If we go up in the Makefile, you may also notice something at line 25 to line 27.
    
    
    ifeq ($(ESPIDF),)  
    $(error Please configure the ESPIDF variable)  
    endif

So, we need to assign the path to our ESP-IDF to `ESPIDF` variable. If we installed the ESP-IDF correctly, we should have the path to our ESP-IDF stored in an environment variable called `IDF_PATH` .

You can also configure the port name and baud rate for flashing the firmware. Take a look at line 17 to 22.
    
    
    PORT ?= /dev/ttyUSB0  
    BAUD ?= 460800  
    FLASH_MODE ?= dio  
    FLASH_FREQ ?= 40m  
    FLASH_SIZE ?= 4MB  
    CROSS_COMPILE ?= xtensa-esp32-elf-

These are the default values for flashing the firmware. You may only want to change the value for `PORT` and `BAUD` unless you know what you are doing, feel free to change the rest.

Now we compile the code.
    
    
    ESPIDF=$IDF_PATH make -j4

Here we create 4 parallel jobs of make.
    
    
    components/spi_flash/flash_ops.c:35:25: fatal error: esp_ota_ops.h: No such fileor directory  
    compilation terminated.

So we got an error, yay! The error says that the compiler can not find `esp_ota_ops.h` file. File`esp_ota_ops.h` belongs to `app_update` component, and it turns out that this component is not included. Let's include this component and re-compile.

Add this line right after line 84 where the components are included.
    
    
    INC_ESPCOMP += -I$(ESPCOMP)/app_update/include

Let's re-compile the code. Hopefully, we don't get any compilation error.
    
    
    LINK build/application.elf  
    build/components/spi_flash/flash_ops.o:(.literal.is_safe_write_address$part$0+0x0): undefined reference to `esp_ota_get_running_partition'  
    build/components/spi_flash/flash_ops.o: In function `is_safe_write_address$part$0':  
    flash_ops.c:(.text.is_safe_write_address$part$0+0x3): undefined reference to `esp_ota_get_running_partition'

So we got another error. Instead of compilation error, we got a linker error. The missing file is included correctly but I think the object is not linked. Let's check the Makefile.

Take a look at line 568 to 641, the objects from compiled components are assigned to the linker parameters. So we need to assign the objects from `app_update` as well.

Add this line right before `OBJ_ESPIDF` definition.
    
    
    ESPIDF_APP_UPDATE_O = $(addprefix $(ESPCOMP)/app_update/,esp_ota_ops.o)

Also add this line right after the last assignment to `OBJ_ESPIDF` variable.
    
    
    OBJ_ESPIDF += $(addprefix $(BUILD)/, $(ESPIDF_APP_UPDATE_O))

We define a variable that points to the object file of `app_update` component and append it to the `OBJ_ESPIDF` variable so the `app_update` component is linked together with the other components. Now let's recompile to see whether it works or not.
    
    
    LINK build/application.elf  
     text data bss dec hex filename  
     714850 171596 173456 1059902 102c3e build/application.elf  
    Create build/application.bin  
    esptool.py v2.1  
    Create build/firmware.bin  
    bootloader 16048  
    partitions 3072  
    application 886576  
    total 952112

It works! We have compiled MicroPython with latest ESP-IDF successfully!

#### Conclusion

We have compiled MicroPython for ESP32 with latest revision of ESP-IDF. We need to modify the Makefile to fix the compilation & linker error by including the missing component header & object file.

The next step is flashing the firmware to an ESP32-based board and test the firmware, we should expect something breaks during runtime.
