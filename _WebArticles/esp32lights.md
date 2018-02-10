# ESP32lights

_Captured: 2018-02-06 at 10:20 from [www.lucadentella.it](http://www.lucadentella.it/en/2018/01/08/esp32lights/)_

Today's project, **ESP32lights**, is a _smart_ device based on the esp32 chip.

![esp32lights-004](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-004-300x221.jpg)

![esp32lights-005](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-005-300x221.jpg)

Thanks to ESP32lights you can turn a load on and off (I used it for my christmas lights)

  * manually
  * based on daily schedules
  * based on the light intensity

ESP32lights connects to your wifi network, can be configured and operated via a web browser and it's optimized for mobile devices (**responsive** web interface based on [jQuery Mobile](https://jquerymobile.com/)).

#### Components

The heart of ESP32lights is the **Lolin32 Lite** devboard by [Wemos](https://wiki.wemos.cc/products:lolin32:lolin32_lite). One of its digital pins is connected to a **relay module**, which controls the load. Two digital pins are assigned to the first i2c _controller _of the esp32 chip and are connected to a **BH1750 **light intensity sensor. All the elements are powered by an **HLK-PM01 **module by [Hi-Link](http://www.hlktech.net/product_detail.php?ProId=54), which directly converts the mains' 220V AC to 5V DC without the need of any external components:

![esp32l-001](http://www.lucadentella.it/blog/wp-content/uploads/2017/12/esp32l-001.jpg)

> _All the components are placed in a waterproof enclosure, to be able to use the device outdoor:_

![esp32lights-006](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-006-300x200.jpg)

![esp32lights-007](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-007-300x200.jpg)

#### Programming

The firmware for the esp32 devboard is available in my [Github_ repository_](https://github.com/lucadentella/esp32lights).

In a following paragraph I'll explain how it works. If you just want to build the device, you can program the firmware as it follows:

1) **clone** my _repository_ in a local folder of your PC (you also have to [install the development env](https://esp-idf.readthedocs.io/en/latest/get-started/index.html) esp-idf):

2) configure the correct settings for your wifi network and your timezone via **menuconfig**:

![esp32lights-003](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-003.jpg)

> _3) compile and flash the firmware:_
    
    
    make flash

4) store the image of the SPIFFS partition into the _flash_ memory (replace the COM port of your devboard and the path where you saved the img file):
    
    
    python $IDF_PATH/components/esptool_py/esptool/esptool.py --chip esp32 --port COM15
     --baud 115200 write_flash --flash_size detect 0x180000 /home/esp32lights.img

If everything is ok, when you connect to the serial console of the devboard (**make monitor**) you should see the following output:

![esp32lights-025](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-025.jpg)

#### Use

ESP32light publishes an **HTTP interface** you can use to set the schedules or the light intensity threshold or to manually turn the load on and off.

You can open the web interface connecting - through a PC or a smartphone -to the address http://<esp_ip> (the IP address of the board is displayed in the serial output as shown in the previous paragraph).

The interface has** 3 tabs**, one for each working mode:

![esp32lights-001](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-001.jpg)

> _The page footer displays the actual working mode and the relay status:_

![esp32lights-002](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-002.jpg)

> _In this short video, you can see how the device works:_

#### Software

I developed the firmware for ESP32lights leveraging what I explained in my previous tutorials about the esp32 chip. If you follow my blog, you probably understood that I really like the **divide et impera** method, that is divide a complex project into small, simpler tasks.

All the configuration settings of ESP32lights (actual working mode, start and stop time…) are stored in the **NVS** partition of the flash memory, as I explained in [this tutorial](http://www.lucadentella.it/en/2017/06/03/esp32-19-nvs/). In this way, it's possible to keep them even if the chip is restarted:
    
    
    nvs_handle my_handle;
    int working_mode;
    [...]
    esp_err_t err = nvs_flash_init();
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    err = nvs_get_i32(my_handle, "mode", &working_mode);

The different elements of the web interface (html page, css style sheets…) are stored in an SPIFFS partition. In a [previous tutorial](http://www.lucadentella.it/en/2017/09/30/esp32-22-spiffs/) you learned how to prepare the image and, in your program, get its content:

![esp32l-002](http://www.lucadentella.it/blog/wp-content/uploads/2017/12/esp32l-002.jpg)

In other tutorials I've also already explained you how to [connect to a wifi network](http://www.lucadentella.it/en/2017/01/16/esp32-6-collegamento-ad-una-rete-wifi/) and [how to use digital pins](http://www.lucadentella.it/en/2017/02/07/esp32-9-basic-io/).

The setup phase is completed after having configured the [BH1750](http://www.mouser.com/ds/2/348/bh1750fvi-e-186247.pdf) light intensity sensor. This sensor offers an i2c interface and therefore can be connected to one of the two i2c _controllers_ of the esp32 chip as shown in [this tutorial](http://www.lucadentella.it/en/2017/02/07/esp32-9-basic-io/). In my program I included a [driver](https://github.com/pcbreflux/espressif/blob/master/esp32/app/ESP32_bh1750_oled/main/bh1750.c) developed by **pcbreflux**.

The main program runs two different tasks:
    
    
    xTaskCreate(&http_server, "http_server", 20000, NULL, 5, NULL);
    xTaskCreate(&monitoring_task, "monitoring_task", 2048, NULL, 5, NULL);

![esp32l-003](http://www.lucadentella.it/blog/wp-content/uploads/2017/12/esp32l-003.jpg)

The first one [publishes the web interface](http://www.lucadentella.it/en/2017/07/08/esp32-20-webserver/), while the second one verifies - every second - if conditions exist (time or light intensity) to turn the load on or off:
    
    
    if(working_mode == MODE_LIGHT && lux_valid) {
      int actual_light_value = get_light_value();
      if(actual_light_value < lux) {
        if(relay_status == false) {
          gpio_set_level(CONFIG_RELAY_PIN, 1);
          relay_status = true;
        }

Here's in details how the http server fetches a **static** resource, stored in the SPIFFS partition.

First it adds to the resource path the _root_ prefix for the SPIFFS partition (/spiffs):

then it checks if the resource exists in the partition:

if so, it opens the file in **read mode**:

and sends the content of the file to the client, reading blocks of 500 bytes:

Finally, this is how the web interface works. The interface is made by an html page (**index.html**) which uses [jQuery](https://jquery.com) to perform AJAX requests to the server and update the different page elements. You don't need to enter the page name in the browser because of the http server automatically performs a **redirect** to it if the default page is requested:

3 **endpoints** are published by the server and accessed using AJAX calls::

  * **setConfig**, to send a new configuration
  * **getConfig**, to read the actual configuration
  * **getLight**, to get the actual light intensity

When the page is loaded, it calls the **getConfig** endpoint to display the actual configuration; moreover it schedules every 5 seconds a call to the **getLight** endpoint to keep the light value updated:

When you click on the SET button, the page calls **setConfig** to send to the server the new configuration:

![esp32l-004](http://www.lucadentella.it/blog/wp-content/uploads/2017/12/esp32l-004.jpg)

All the information are sent using the [JSON](https://en.wikipedia.org/wiki/JavaScript_Object_Notation) format. The esp-idf framework includes the [cJSON](https://github.com/DaveGamble/cJSON) library which makes it easy to create or parse a json message:
    
    
    cJSON *root = cJSON_Parse(body);
    cJSON *mode_item = cJSON_GetObjectItemCaseSensitive(root, "mode");
    [...]
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "lux", light_value);
    char *rendered = cJSON_Print(root);

#### Making of

I started the build of the device cutting a perfboard to the size of the enclosure:

![esp32lights-008](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-008-300x200.jpg)

![esp32lights-009](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-009-300x200.jpg)

The perfboard is screwed to the enclosure using two spacers:

![esp32lights-010](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-010-300x200.jpg)

![esp32lights-011](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-011-300x200.jpg)

I made two holes in one side of the enclosure for the main switch and for a status led:

![esp32lights-012](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-012-300x200.jpg)

![esp32lights-013](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-013-300x200.jpg)

I soldered all the different components on the perfboard and made the electric connections using wires:

![esp32lights-014](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-014-300x200.jpg)

![esp32lights-015](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-015-300x200.jpg)

To simplify the installation, all the external components (led, relay module…) are connected using jumpers:

![esp32lights-016](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-016-300x200.jpg)

![esp32lights-017](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-017-300x200.jpg)

First test:

![esp32lights-018](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-018-300x205.jpg)

I attached the light sensor to the top of the enclosure, after having made a hole to allow it to "see" the external light:

![esp32lights-019](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-019-300x200.jpg)

![esp32lights-020](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-020-300x200.jpg)

Finally I made the external connections, installing the main switch:

![esp32lights-021](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-021-300x200.jpg)

![esp32lights-022](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-022-300x200.jpg)

and connecting the output of the relay module to a wire with an universal plug at its end:

![esp32lights-023](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-023-300x200.jpg)

![esp32lights-024](http://www.lucadentella.it/blog/wp-content/uploads/2018/01/esp32lights-024-300x200.jpg)
