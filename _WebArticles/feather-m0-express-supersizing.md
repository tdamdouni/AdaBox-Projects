# Feather M0 Express supersizing

_Captured: 2017-10-16 at 17:21 from [daveastels.com](https://daveastels.com/2017/10/15/feather-m0-express-supersizing/)_

### **NOTE:** This is based on an earlier fork of circuitpython (the first 2.0.0 release) and doesn't yet work on the lastest from the master branch.

In my last post I described how I hacked a 2Mbyte SPI flash onto a Trinket M0 to give it the memory space for CircutiPython of one of the M0 Express boards. This time I supersized an M0 Express board, specifically a Feather M0 Express, although the same hack should work on a Circuit Playground Express.

## Hardware

Replacing the 2Mbyte SPI flash chip with an 8Mbyte version was easy: I used a solderwick to remove the bulk of the solder on and around the pins, then gently pulled/pried the chip off while heating the pins (one side at a time). Then I put a bit of solder on opposite corner pins and used that to tack the new 8Mbyte chip onto the board. Be careful orient the chip correctly! To finish I soldered each other pin to the board. Done.

The one thing that took a bit of effort up front was finding a larger flash ship that was physically and functionally compatible. I found the [S25FL064L](http://www.cypress.com/file/316661/download). This is a hardware drop in replacement with 4 times the space. The chip is physically bigger as well, but still fits the 8-SOIC footprint and pads.

## Software

The only change needed to the firmware was to create a definition file for the 8Mbyte flash chip, and include that into the Feather config header. I made a copy of the Feather M0 Express board directory, tweaked the header file, and added a new flash definition header.

The only change to `boards/feather_m0_express/mpconfigboard.h` (or a copy, I used `feather_m0_supersized`) is the replacement of the flash definition with:
    
    
    #include "flash_S25FL064L.h"
    

That `boards/flash_S25FL064L.h` file is just slightly different than `boards/flash_S25FL216K.h`, specifically the size and JDEC information:
    
    
    /*
     * This file is part of the MicroPython project, http://micropython.org/
     *
     * The MIT License (MIT)
     *
     * Copyright (c) 2017 Scott Shawcroft for Adafruit Industries
     * Copyright (c) 2017 Dave Astels
     *
     * Permission is hereby granted, free of charge, to any person obtaining a copy
     * of this software and associated documentation files (the "Software"), to deal
     * in the Software without restriction, including without limitation the rights
     * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
     * copies of the Software, and to permit persons to whom the Software is
     * furnished to do so, subject to the following conditions:
     *
     * The above copyright notice and this permission notice shall be included in
     * all copies or substantial portions of the Software.
     *
     * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
     * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
     * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
     * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
     * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
     * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
     * THE SOFTWARE.
     */
    
    #ifndef MICROPY_INCLUDED_ATMEL_SAMD_BOARD_FLASH_S25FL064L_H
    #define MICROPY_INCLUDED_ATMEL_SAMD_BOARD_FLASH_S25FL064L_H
    
    // Settings for the Cypress (was Spansion) S25FL064L 8MiB SPI flash.
    // Datasheet: http://www.cypress.com/file/316661/download
    
    // The total flash size in bytes.
    #define SPI_FLASH_TOTAL_SIZE  (1 << 23) // 8 MiB
    
    // The size of the smallest erase unit thats erased with command 0x20.
    #define SPI_FLASH_ERASE_SIZE  (1 << 12) // 4 KiB
    
    // The size of a page that is programmed with page program command 0x02.
    #define SPI_FLASH_PAGE_SIZE   (256)     // 256 bytes
    
    // These are the first three response bytes to the JEDEC ID command 0x9f that is
    // used to confirm we're talking to the flash we expect.
    #ifndef SPI_FLASH_JEDEC_MANUFACTURER
    #define SPI_FLASH_JEDEC_MANUFACTURER 0x01
    #define SPI_FLASH_SECTOR_PROTECTION false
    #else
    #define SPI_FLASH_JEDEC_MANUFACTURER_2 0x013
    #define SPI_FLASH_SECTOR_PROTECTION_2 false
    #endif
    #define SPI_FLASH_JEDEC_MEMORY_TYPE  0x60
    #define SPI_FLASH_JEDEC_CAPACITY     0x17
    
    #endif  // MICROPY_INCLUDED_ATMEL_SAMD_BOARD_FLASH_S25FL216K_H
    

If you made a copy of the `feather_m0_express` directory to `feather_m0_supersized`, you build (sitting in the `/circuitpython/atmel-samd` directory) with `make BOARD=feather_m0_supersized`. If all goes well, you will have the file `circuitpython/atmel-samd/build-feather_m0_supersized/firmware.uf2` that you can copy on to the `FEATHERBOOT` usb drive that shows up when you connect the supersized feather and double press reset.

## Gallery

![IMG_1058](https://daveastels.files.wordpress.com/2017/10/img_1058-e1508100086762.jpg?w=1424)

The new 8Mbyte flash chip next to the original on the Feather.

![IMG_1062](https://daveastels.files.wordpress.com/2017/10/img_1062.jpg?w=1424)

2Mbyte flash chip removed.

![IMG_1064](https://daveastels.files.wordpress.com/2017/10/img_1064.jpg?w=1424)

New flash chip in place.

![feather_M0_supersized-CIRCUITPY](https://daveastels.files.wordpress.com/2017/10/feather_m0_supersized-circuitpy.png)

The new `CIRCUITPY` directory.
