# Temperature and Humidity Monitor

_Captured: 2018-01-25 at 16:21 from [www.instructables.com](http://www.instructables.com/id/Temperature-and-Humidity-Monitor/)_

## Introduction: Temperature and Humidity Monitor

![Picture of Temperature and Humidity Monitor](https://cdn.instructables.com/FNF/P4I9/JBWJW9N4/FNFP4I9JBWJW9N4.LARGE.jpg)[ ](https://cdn.instructables.com/FNF/P4I9/JBWJW9N4/FNFP4I9JBWJW9N4.LARGE.jpg)![Picture of Temperature and Humidity Monitor](https://cdn.instructables.com/FR4/OK6C/JBWK7ZX3/FR4OK6CJBWK7ZX3.LARGE.jpg)[ ](https://cdn.instructables.com/FR4/OK6C/JBWK7ZX3/FR4OK6CJBWK7ZX3.LARGE.jpg)

![](https://cdn.instructables.com/FA1/689N/JAMTRQ5Y/FA1689NJAMTRQ5Y.SMALL.jpg)

In this instructable I'm going to show you how to make your own temperature and humidity monitor for your living room. The device also features WiFi capabilities, for the purpose of logging the data on a remote server (e.g. a Raspberry Pi) and accessing it later through a simple web interface.

The main parts of the device are an ESP8266 microcontroller, a DHT11 temperature and humidity sensor and a 16x4 character LCD. The project is fully open source, so feel free to download the schematic, board layout and design files for the enclosure and make any changes you like.

## Step 1: Tools and Parts

![Picture of Tools and Parts](https://cdn.instructables.com/FNJ/TMB8/JBWJW9FD/FNJTMB8JBWJW9FD.LARGE.jpg)[ ](https://cdn.instructables.com/FNJ/TMB8/JBWJW9FD/FNJTMB8JBWJW9FD.LARGE.jpg)![Picture of Tools and Parts](https://cdn.instructables.com/FWG/WPVP/JBWJW9KK/FWGWPVPJBWJW9KK.MEDIUM.jpg)[ ](https://cdn.instructables.com/FWG/WPVP/JBWJW9KK/FWGWPVPJBWJW9KK.LARGE.jpg)![Picture of Tools and Parts](https://cdn.instructables.com/FSR/X12D/JBWJW9EJ/FSRX12DJBWJW9EJ.MEDIUM.jpg)![Picture of Tools and Parts](https://cdn.instructables.com/F3B/8TT9/JBWJW9FE/F3B8TT9JBWJW9FE.SMALL.jpg)[ ](https://cdn.instructables.com/F3B/8TT9/JBWJW9FE/F3B8TT9JBWJW9FE.LARGE.jpg)![Picture of Tools and Parts](https://cdn.instructables.com/F7O/N1NZ/JBWJW9G9/F7ON1NZJBWJW9G9.SMALL.jpg)![Picture of Tools and Parts](https://cdn.instructables.com/FGK/KR3Q/JBWJW9G8/FGKKR3QJBWJW9G8.MEDIUM.jpg)Show All 10 Items

### To build the monitor you are going to need the following parts:

1 x **ESP-12F** [2€] - As far as I know ESP-12E and ESP-12F are basically identical, with the difference that ESP-12F has a better antenna.

1 x **DHT11** Temperature and Humidity Sensor [0.80€] - The DHT22 is also going to work but some changes will need to be made on the 3D model of the enclosure, DHT22 is also a bit more expensive.

1 x **16x4 Character LCD 5V** [3.30€] - Yes, you will need a 5V one as the PCB is designed so the LCD will be powered directly from 5V rather than the voltage regulator. This was done in order to reduce the load on the voltage regulator but also because 5V displays tend to be cheaper. But don't worry, even though the ESP8266 operates at 3.3V it will still work just fine.

1 x **LD1117V33** SMD Voltage Regulator, also known as LD33 (**SOT223** package) [0.80€]

1 x **100nF** Ceramic SMD Capacitor (**0603** package)

1 x **10uF** Tantalum SMD Capacitor (**3528** package)

1 x **10K** SMD Resistor (**0805** package)

1 x **10K Trimmer Pot** (Through hole)

1 x **47Ω** SMD Resistor (0805 package) - This is just for limiting the current that goes to the backlight of the LCD. Feel free to experiment with different resistance values and choose the intensity you prefer.

1 x SMD **Momentary Switch** [0.80€] - The particular I used is [this](https://www.sparkfun.com/products/8720), but you can use any momentary switch you want with the same footprint. I was also able to find the same switches on eBay for less by getting more than one.

1 x **5.5x2.1mm DC Jack** (Panel mount) [0.50€] - The one I used has an 8mm panel cutout diameter and a 9mm length. It can be easily found on eBay by searching for "[Panel Mount DC Jack](https://www.ebay.com/sch/i.html?_from=R40&_trksid=p2050601.m570.l1313.TR0.TRC0.H0.XPanel+Mount+DC+Jack.TRS0&_nkw=Panel+Mount+DC+Jack&_sacat=0)" (see attached [picture](https://www.instructables.com/files/deriv/F62/QF2F/JBWJW9JO/F62QF2FJBWJW9JO.LARGE.jpg)).

1 x 2.54mm (100mil) 40-pin **Male Pin Header** (Through hole)

1 x 2.54mm (100mil) 40-pin **Machined Female Pin Header** (Through hole)

1 x 2.54mm (100mil) **Jumper** \- It's the same like the ones used on computer motherboards.

4 x **M3 8mm Bolts**

4 x **M3 4x4mm Threaded Inserts** \- They can be easily found by searching for "[M3 Press-In Brass Copper Inserts](https://www.ebay.com/sch/i.html?_from=R40&_trksid=p2050601.m570.l1313.TR0.TRC0.H0.TRS0&_nkw=M3+Press-In+Brass+Copper+Inserts&_sacat=0)" on eBay (see attached [picture](https://www.instructables.com/files/deriv/F6O/VPZS/JBWJW9IU/F6OVPZSJBWJW9IU.LARGE.jpg)).

4 x **M2 12mm Bolts**

4 x **M2 Nuts**

1 x USB Type A to 5.5x2.1mm DC Plug **Cable** [1.5€] - This will allow to power your device either from a standard phone charger or pretty much any computer with a USB port. The device only draws 300mA worst case and 250mA on average, so even a USB 2.0 port will do.

1 x **PCB** \- The board thickness is not critical, so just go for 1.6mm which is usually the cheapest option with most PCB manufacturers.

3 x Pieces of **Stranded Wire** (about **60mm** each)

3 x Pieces of **Heatshrink Tubing** (about **10mm** each)

### And the following tools:

Soldering Iron

USB to Serial Converter - You will need this for programming the ESP8266 on the board.

Phillips Screwdriver and/or Hex Key - Depending the type of screws you'll use.

3D Printer - If you don't have access to a 3D printer, you can always use a generic plastic project box and make the cutouts yourself with a Dremel. The minimum inner dimensions for such a box will need to be **24mm** height, **94mm** length and **66mm** width. You'll also need to use **8mm M2 stand-offs** for mounting the LCD.

Dremel - Only needed if you don't go for the 3D printed enclosure.

## Step 2: Making the PCB

![Picture of Making the PCB](https://cdn.instructables.com/FH6/TA0C/JBWJW9CS/FH6TA0CJBWJW9CS.LARGE.jpg)[ ](https://cdn.instructables.com/FH6/TA0C/JBWJW9CS/FH6TA0CJBWJW9CS.LARGE.jpg)![Picture of Making the PCB](https://cdn.instructables.com/FRO/E9JG/JBWJW9DM/FROE9JGJBWJW9DM.MEDIUM.jpg)[ ](https://cdn.instructables.com/FRO/E9JG/JBWJW9DM/FROE9JGJBWJW9DM.LARGE.jpg)![Picture of Making the PCB](https://cdn.instructables.com/F7R/JXAW/JBWJW9DP/F7RJXAWJBWJW9DP.MEDIUM.jpg)

The first step is to make the PCB. You can do so by either etching it yourself, or just going to the website of your favorite PCB manufacturer and place an order. If you don't plan making any changes to the board layout, you can simply grab the ZIP file containing the gerber files attached on this step and send it directly to the manufacturer. In case you want to make changes though, the KiCAD schematic and board layout files can be found [here](https://github.com/magkopian/esp-arduino-temp-monitor/tree/master/board).

After getting your hands on the boards it is time to solder the components. This should be pretty much straightforward, but there are a few things that should be noted. First, do not proceed to solder the PCB on the LCD header just yet, this will need to be done during the final assembly due to the way the enclosure was designed. If you are making your own enclosure though feel free to ignore that advice.

The **U3** connector is where the **DHT11** sensor is going to be connected. Ideally, you should use a 90° angled machined female pin header for that purpose. But if you like me aren't able to find one, just get a straight one and bend it yourself. If you do the later, the leads of the DHT11 are also going to be bit short, so you'll have to solder some extensions. The distance between the pin header and the sensor once connected needs to be roughly **5mm**.

The reason why you want to use a machined pin header, is because the holes are smaller compared to the regular female pin headers. So, the leads of the sensor can sit there tightly creating a solid connection. But you could also try soldering the DHT11 on a piece of male pin header and connect it that way to a regular angled female pin header, which should work just as well.

## Step 3: Making the Enclosure

![Picture of Making the Enclosure](https://cdn.instructables.com/FA9/1Y1Z/JBWJW9N3/FA91Y1ZJBWJW9N3.LARGE.jpg)[ ](https://cdn.instructables.com/FA9/1Y1Z/JBWJW9N3/FA91Y1ZJBWJW9N3.LARGE.jpg)![Picture of Making the Enclosure](https://cdn.instructables.com/FZN/OXMG/JBWJWD0Q/FZNOXMGJBWJWD0Q.MEDIUM.jpg)[ ](https://cdn.instructables.com/FZN/OXMG/JBWJWD0Q/FZNOXMGJBWJWD0Q.LARGE.jpg)![Picture of Making the Enclosure](https://cdn.instructables.com/FEG/ACK6/JBWJW9M9/FEGACK6JBWJW9M9.MEDIUM.jpg)![Picture of Making the Enclosure](https://cdn.instructables.com/FMC/W2PZ/JBWJWD0O/FMCW2PZJBWJWD0O.MEDIUM.jpg)

Now that the PCB is soldered it's time to make the enclosure. There are two different parts that need to be printed, the main body of the enclosure and the lid. The lid also features mounting holes for attaching it on your wall.

Both parts can be printed with a standard 0.4mm nozzle at 0.2mm layer height, for my case the print time was about 4 hours for both parts combined. The lid doesn't require any supports the main part of the enclosure however does, mainly for the part under the screw sockets. After printing be very careful with removing the supports, I managed to break one of the stand-offs for the LCD while doing that and had to glue it back on with superglue.

The enclosure is designed on FreeCAD, so if you want to make any changes it should be pretty much straightforward. The STL files for printing the enclosure as well as the FreeCAD design files can be found on [Thingiverse](https://www.thingiverse.com/thing:2740731/#files).

## Step 4: Assembling the Monitor

With the enclosure printed, time to put everything together. First, place the LCD inside the case and slide it to the left, so there will be a gap between it and the hole for the sensor.

![](https://cdn.instructables.com/FKB/XJSJ/JBWJWJ5Q/FKBXJSJJBWJWJ5Q.LARGE.jpg)

Next, place the PCB on top of it, with the sensor already attached on the pin header.

![](https://cdn.instructables.com/F9A/9KDE/JBWJWJ6R/F9A9KDEJBWJWJ6R.LARGE.jpg)

After that, push the sensor into the hole, slide the LCD back to position and insert the PCB on the pin header. Now fix the LCD in place using M2 nuts and bolts, and solder the PCB on the pin header.

![](https://cdn.instructables.com/F0Z/GE9A/JBWJWJ5R/F0ZGE9AJBWJWJ5R.LARGE.jpg)

Next, put the power jack in place, attach some wires to it and solder their other ends to the PCB. The use of some heatshrink tubing here would also be a good idea.

![](https://cdn.instructables.com/F81/XMKM/JBWJWJ5T/F81XMKMJBWJWJ5T.LARGE.jpg)

Last step is to install the metal threaded inserts so the lid can be screwed in place with M3 bolts. For that purpose you'll need to use your soldering iron to heat them up, so they can be pushed into the holes. You can take a look on [this](https://www.instructables.com/id/Add-Metal-Threads-to-Your-3D-Prints-Make-Them-Func/) instructable if you need more information about adding metal threads to your 3D prints.

![](https://cdn.instructables.com/F6F/RDLP/JBWJWJ5Z/F6FRDLPJBWJWJ5Z.LARGE.jpg)

## Step 5: Setting Up the Server

![Picture of Setting Up the Server](https://cdn.instructables.com/FQV/NK7L/JBWJZVTN/FQVNK7LJBWJZVTN.LARGE.jpg)[ ](https://cdn.instructables.com/FQV/NK7L/JBWJZVTN/FQVNK7LJBWJZVTN.LARGE.jpg)

Before uploading the firmware to the ESP8266 there is one more thing that needs to be done, which is setting up a server for logging the data received by the device. For that purpose you can use pretty much any Linux machine you want, from a Raspberry Pi on your private network to a DigitalOcean droplet. I went with the later, but the process is pretty much the same no matter what you choose.

### Installing Apache, MySQL (MariaDB) and PHP

First we need to setup LAMP, or in other words install Apache, MySQL (MariaDB) and PHP on the server. For that you'll need to use the package manager of your distro, for the sake of the example I will use **apt** which is the package manager used by pretty much any Debian based distro, including Raspbian.
    
    
    sudo apt update
    sudo apt install apache2 mysql-server mysql-client php libapache2-mod-php php-mysql

After that is done, if you put the IP address of your server to the address bar of your browser you should be able to see the default page of Apache.

### Setting up the database

Now we need a database for logging the data. First, connect to MySQL as root by running,
    
    
    sudo mysql

And create the database and a user with access to it as follows,
    
    
    CREATE DATABASE `sensors`
    USE `sensors`;
    CREATE TABLE `temperature` (`id` bigint(20) NOT NULL AUTO_INCREMENT, `client_id` smallint(6) NOT NULL, `value` smallint(6) NOT NULL, `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP, PRIMARY KEY (`id`)) ENGINE=InnoDB;
    CREATE TABLE `humidity` (`id` bigint(20) NOT NULL AUTO_INCREMENT, `client_id` smallint(6) NOT NULL, `value` smallint(6) NOT NULL, `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP, PRIMARY KEY (`id`)) ENGINE=InnoDB;
    CREATE USER '[username]'@'localhost' IDENTIFIED BY '[password]';
    GRANT ALL PRIVILEGES ON 'sensors'.* TO 'sensors'@'localhost';
    EXIT

Make sure to replace **[username]** and **[password]** with the actual username and password for the MySQL user that you like. Also, keep a note of them because you'll need them for the next step.

### Configuring the logging and web interface scripts

Change to the **/var/www/html** directory which is the document root of the default virtual host of Apache, delete the HTML file that contains the default webpage and download the logging and web interface scripts inside it.
    
    
    cd /var/www/html
    sudo rm index.html
    sudo wget https://raw.githubusercontent.com/magkopian/esp-arduino-temp-monitor/master/server/log.php
    sudo wget https://raw.githubusercontent.com/magkopian/esp-arduino-temp-monitor/master/server/index.php
    

Now edit the logging script using **nano**,
    
    
    sudo nano log.php

You'll need to replace the **[username]** and **[password]** with the username and password for the MySQL user that you created on the previous step. Also, replace the **[client key]** with a unique string and take a note of it. This is going to be used as a password so the monitor can authenticate itself to the server.

Finally, edit the **index.php** with **nano**,
    
    
    sudo nano index.php

and replace the **[username]** and **[password]** with the username and password for the MySQL user as you did with the logging script.

### Setting up HTTPS (Optional)

This may be optional, but if the connection between the ESP8266 and the server is over the Internet it is highly recommended to use some encryption.

Unfortunately, you can't just go ahead and use something like Let's Encrypt for obtaining a certificate. That is because at least at the time of the writing, the HTTP client library for the ESP8266 still requires the fingerprint of the certificate to be provided as a second argument when calling the **http.begin()**. This means that if you use something like Let's Encrypt, you'll have to reflash the firmware to the chip every 3 months in order to update the certificate fingerprint after each renewal.

A way around that, would be to generate a self-signed certificate that expires after a very long time (e.g. 10 years) and keep the logging script on its own virtual host with its own subdomain. That way, you can have the web interface for accessing the data on a separate subdomain, that will use a proper certificate from a trusted authority. The usage of a self-signed certificate in this case is not a security issue, as the fingerprint of the certificate which uniquely identifies it will be hardcoded into the firmware and the certificate is only going to be used by the ESP8266.

Before we start, I will assume that you already own a domain name and you're able to create subdomains on it. So, to generate a certificate that expires after 10 years run the following command and answer the questions.
    
    
    sudo openssl req -x509 -nodes -days 3650 -newkey rsa:2048 -keyout /etc/ssl/private/sensors.key -out /etc/ssl/certs/sensors.crt

As this is a self-signed certificate what you answer in most questions doesn't matter too much, except for the question that asks for the **Common Name**. This is where you'll need to provide the full subdomain that is going to be used for this virtual host. The subdomain you'll give here will need to be the same with the **ServerName** that you'll set later in your virtual host configuration.

Next create a new virtual host configuration,
    
    
    sudo nano /etc/apache2/sites-available/sensors-ssl.conf
    

with the following contents,
    
    
    <VirtualHost *:443>
    	ServerName [subdomain]
    	DocumentRoot /var/www/sensors
    
    	SSLEngine ON
    	SSLCertificateKeyFile /etc/ssl/private/sensors.key
    	SSLCertificateFile /etc/ssl/certs/sensors.crt
    
    	<Directory /var/www/sensors/>
    		Options +FollowSymlinks -Indexes
    		AllowOverride All
    	</Directory>
    
    	ErrorLog ${APACHE_LOG_DIR}/sensors-error-ssl.log
    	CustomLog ${APACHE_LOG_DIR}/sensors-access-ssl.log combined
    </VirtualHost>
    

Again, be sure to replace the **[subdomain]** with the same subdomain that you used with the certificate. At this point you will need to disable the default virtual host of Apache,
    
    
    sudo a2dissite 000-default

change the name of the document root directory,
    
    
    sudo mv /var/www/html /var/www/sensors

and finally enable the new virtual host and restart Apache,
    
    
    sudo a2ensite sensors-ssl
    sudo systemctl restart apache2

Last thing that needs to be done is to obtain the fingerprint of the certificate, because you'll need to use it in the firmware code.
    
    
    openssl x509 -noout -fingerprint -sha1 -inform pem -in /etc/ssl/certs/sensors.crt

The **http.begin()** expects the delimiters between the bytes of the fingerprint to be spaces, so you'll need to replace the colons with spaces before using it in your code.

Now, if you don't want to use a self-signed certificate for the web interface setup a new subdomain and create a new virtual host configuration,
    
    
    sudo nano /etc/apache2/sites-available/sensors-web-ssl.conf

with the following contents,
    
    
    <VirtualHost *:443>
    	ServerName [subdomain]
    	DocumentRoot /var/www/sensors
    	#SSLEngine ON
    	#SSLCertificateFile /etc/letsencrypt/live/[subdomain]/cert.pem
    	#SSLCertificateKeyFile /etc/letsencrypt/live/[subdomain]/privkey.pem
    	#SSLCertificateChainFile /etc/letsencrypt/live/[subdomain]/chain.pem
    
    	<Directory /var/www/sensors/>
    		Options +FollowSymlinks -Indexes
    		AllowOverride All
    	</Directory>
    	ErrorLog ${APACHE_LOG_DIR}/sensors-web-error-ssl.log
    	CustomLog ${APACHE_LOG_DIR}/sensors-web-access-ssl.log combined
    </VirtualHost>
    

Be sure to replace the **[subdomain]** with the subdomain that you have setup for the web interface. Next enable the new virtual host, restart Apache, install **certbot** and obtain a certificate for the new subdomain from Let's Encrypt,
    
    
    sudo a2ensite sensors-web-ssl
    sudo systemctl restart apache2
    sudo apt update
    sudo apt install certbot
    sudo certbot certonly --apache -d [subdomain]
    

After obtaining the certificate edit the virtual host configuration again to uncomment the **SSLEngine**, **SSLCertificateFile**, **SSLCertificateKeyFile** and **SSLCertificateChainFile** lines, and restart Apache.

And now you can use the first subdomain which uses the self-signed certificate for sending the data from the ESP8266 to the server, while using the second for accessing the web interface from your browser. Certbot will also take care of automatically renewing you Let's Encrypt certificate every 3 months, using a systemd timer which should be enabled by default.

## Step 6: Programming the ESP8266

![Picture of Programming the ESP8266](https://cdn.instructables.com/FOD/Q948/JBWJZW6N/FODQ948JBWJZW6N.LARGE.jpg)[ ](https://cdn.instructables.com/FOD/Q948/JBWJZW6N/FODQ948JBWJZW6N.LARGE.jpg)

Finally, the only thing left to do is to load the firmware on the microcontroller. To do so, download the source code for the firmware from [here](https://github.com/magkopian/esp-arduino-temp-monitor/blob/master/firmware/temp_hum_monitor.ino) and open it using the Arduino IDE. You will need to replace **[SSID]** and **[Password]** with the actual SSID and password of your WiFi network. You'll also need to replace **[Client ID]** and **[Client Key]** on the **sprintf** function call with the ones that you used on the PHP script on the server. Finally, you'll have to replace the **[Host]** with the domain name or the IP address of the server. If you're using HTTPS you will also need to supply the fingerprint of your certificate as a second argument on the function call of the **http.begin()**. I've explained how to obtain the fingerprint of the certificate at the "Setting Up HTTPS" section on the previous step.

Next, if you haven't already you're going to need to install the **ESP8266 Community** core package using the [Board Manager](https://www.arduino.cc/en/Guide/Cores) of the Arduino IDE. Once this is done, select the **NodeMCU 1.0 (ESP-12E Module)** from the **boards** menu. Next, you'll need to install the the **SimpleDHT** library using the [Library Manager](https://www.arduino.cc/en/Guide/Libraries#toc2). Finally, hit the **Verify** button on the upper left corner of your IDE window to make make sure that the code compiles without errors.

And now, it's finally time to burn the firmware to the microcontroller. To do so move the jumper **JP1** on the right, so **GPIO0** of the ESP8266 will be connected to **ground** which will enable the programming mode. Then, attach your USB to serial converter using jumper wires to the programming header that is labeled as **P1**. The **pin 1** of the programming header is **ground**, **pin 2** is the **receive** pin of the ESP8266 and **pin 3** the **transmit**. You need the receive of the ESP8266 to go to the transmit of your USB to serial converter, the transmit to the receive and of course the ground to ground.

Finally, power the device with 5V using your USB to DC jack cable and connect the USB to serial converter to your computer. You should now be able to see the virtual serial port where the ESP8266 is connected, as soon as you open the **tools** menu on your IDE. Now, just hit the **Upload** button and that's it! If everything went as expected you should be able to see the temperature and humidity readings on the LCD of the device. After the ESP8266 connects to your network and starts communicating with the server, the current date and time should also show up on the display.

After a few hours when the server will have collected a good amount data you should be able to see the temperature and humidity charts by visiting **http(s)://[host]/index.php?client_id=[client id]**. Where **[host]** is either the IP address of your server or the subdomain you're using for the web interface, and **[client id]** the client id of the device which if you left it to its default value it should be **1**.
