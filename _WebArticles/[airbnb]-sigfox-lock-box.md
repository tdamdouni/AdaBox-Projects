# [Airbnb] Sigfox Lock Box

_Captured: 2017-09-10 at 18:36 from [www.instructables.com](http://www.instructables.com/id/Airbnb-Sigfox-Lock-Box/)_

![\[Airbnb\] Sigfox Lock Box](https://cdn.instructables.com/F6F/0LJE/J77R7ZWK/F6F0LJEJ77R7ZWK.MEDIUM.jpg)

![lock.png](https://cdn.instructables.com/FMQ/IDTE/J77R7ZW9/FMQIDTEJ77R7ZW9.SMALL.jpg)

![unlock.png](https://cdn.instructables.com/F2P/JDQA/J77R7ZWJ/F2PJDQAJ77R7ZWJ.SMALL.jpg)

![making.png](https://cdn.instructables.com/FW6/7QVT/J77R7ZWC/FW67QVTJ77R7ZWC.SMALL.jpg)

What if you had to store something precious to be picked up by someone you do not know? What if you were far away from the box and had to change the password for security reasons?

This is where Sigfox comes in! Indeed, Sigfox allows you to use 4 downlink messages per day. The idea is to be able to **update the password controlling the opening of the box**. Therefore in this tutorial, every 6 hours (4 times per day), the box's password will be set with a newly generated one from a web application. The owner can then decide to share the password to whom he wants. He will also **be notified every time the box is opened**!

This tutorial includes:

  * the firmware to upload on the MKRFox1200 
  * the web API generating a new password and receiving the box's notifications

A video presentation is available **[here**](https://youtu.be/BI61gZuiOqs)!

Some photos show how the mechanical part works.

## Step 1: Hardware Requirements

![Hardware Requirements](https://cdn.instructables.com/F1X/ORZT/J77R7ZWF/F1XORZTJ77R7ZWF.MEDIUM.jpg)

## Step 3: MKRFox1200

  1. [Activate](https://backend.sigfox.com/activate/arduino) your board on the Sigfox Backend (_you can follow **[this**](https://www.arduino.cc/en/Guide/MKRFox1200) and **[this**](https://www.arduino.cc/en/Tutorial/SigFoxFirstConfiguration) tutorials_)
  2. Flash the MKRFox1200 with the firmware located in this folder: MKRFox1200_lock_box/MKRFox1200/src (I used PlatformIO a new great IDE for IoT. After being installed on Atom, the folder "MKRFox1200" can be imported with _File>Open Folder...>Select_ and the project will be configured automatically with the Arduino core and libraries - defined in the file _platformio.ini_)
  3. Make sure to respect the correct **pin mapping** (check _Defines & variables_ in the code)

Some informations regarding the data frames being sent from the MKRFox1200 to the Sigfox Backend (12 bytes maximum):

  * getPasswordBySigfox() sends the following:

1 -> 6 char = "UPDATE"

7 -> 10 float - Little Endian = Estimated battery voltage

  * sendAlertBySigfox() sends the following:

1 -> 4 char = "OPEN"

5 -> 8 float - Little Endian = Estimated battery voltage

You can help yourself with [this](http://www.scadacore.com/field-tools/programming-calculators/online-hex-converter/) website to decode hexadecimal (the battery voltage is a _Float - Little Endian (DCBA)_).  
**FYI**: the estimated battery voltage is only indicating a **very** rough approximation. It is not a reliable piece of information at all but it will help you get an idea. A better approximation would be made with a 5V battery using the following formula: _float voltage = sensorValue * (5 / 1023)_

## Step 4: Web Application

![Web Application](https://cdn.instructables.com/FP2/SEPZ/J77R7ZWE/FP2SEPZJ77R7ZWE.MEDIUM.jpg)

In this tutorial we will use Flask to build our little API. Flask is a microframework for Python which simplifies the creation of web applications. ngrok will be used to expose it through an online tunnel, this means it will be deployed on YOUR computer for simplicity purposes. Of course, you can decide to deploy it on a private server or PaaS (Platform as a Service) if you wish (this is not presented in this tutorial in order to keep it as short as possible).

> Please keep in mind Python with Flask can be substituted with any other kind of web application created with a totally different programming language!

  * Edit the "app.py" script (in folder _MKRFox1200_access_control/**API**/_)
  * Set the __deviceId__variable with your own MKRFox1200 device ID (you can find it when you actived your board or on the [Sigfox Backend](https://backend.sigfox.com/devicetype/list))
  * Install the Flask module with pip (Linux commands):
    
    
    $ sudo apt-get update && sudo apt-get -y upgrade  
    $ sudo apt-get install python-pip3
    $ pip3 install flask

  * Launch the Python script (_on windows, if a PATH environment variable has not been created, the Python executable must be accessible from__**C:\Users\USERNAME\AppData\Local\Programs\Python\Python36-32\python.exe**_):
    
    
    $ cd MKRFox1200_access_control/API/  
    $ python app.py

If everything went fine, you must be able to access [ http://localhost:5000/ ](http://localhost:5000/) and see a result in your browser. There is an endpoint configured to generate a new password when calling [ http://localhost:5000/ ](http://localhost:5000/getPassword.) This will also be used for the Sigfox Backend Callback configuration.

Now we'll take a look at ngrok as a method of exposing your Python server publicly so that the Sigfox Backend can GET/POST data to it. This is particularly useful for testing purposes as we do not have to spend time on server configurations.
    
    
    $ ngrok http 5000

This will expose your server publicly (on port 5000). To double check that this has worked, copy the address that has appeared in your terminal window under "forwarding" and navigate to it using your browser; it should look something like on the image. Make note of this as we'll need it below!

## Step 5: Sigfox Backend Callback

![Sigfox Backend Callback](https://cdn.instructables.com/FIL/JS00/J77R7ZWO/FILJS00J77R7ZWO.MEDIUM.jpg)

![downlink.png](https://cdn.instructables.com/F08/DU3E/J77R7ZV1/F08DU3EJ77R7ZV1.MEDIUM.jpg)

  * Go to [ https://backend.sigfox.com/devicetype/list, ](https://backend.sigfox.com/devicetype/list,) click left on your device row and select "Edit"

  * Under "Downlink data", select the CALLBACK "Downlink mode"

  * Now go to the "CALLBACKS" section on the left, select "new" on the top right, select "Custom Callback"

Type: DATA | BIDIR

Channel URL

Url pattern: http://YOUR_ngrok_SERVER_ADDRESS/getPassword

Use HTTP Method: POST

Content Type: application/json

Body: (_this will be sent to the API_)
    
    
    {  
          "device" : "{device}",
          "time" : "{time}",
          "duplicate" : "{duplicate}",
          "snr" : "{snr}",
          "rssi" : "{rssi}",
          "avgSnr" : "{avgSnr}",
          "station" : "{station}",
          "lat" : "{lat}",
          "lng" : "{lng}",
          "seqNumber" : "{seqNumber}",
          "data" : "{data}"
    }

  * Select "OK" to validate
  * **Tick **the "Downlink" button to activate the newly created callback, make sure it looks like below

## Step 6: Usage

  * Power up the system
  * The default password is **2017**
  * The buffer storing the input (keys pressed) is 4 characters long
  * This buffer is emptied every 3 seconds and the timer emptying it is paused every time there is a new key being pressed
  * Press ***** to reset the input or **lock **the box
  * For debug purposes, you can press **#** to **reset **the password to its default (2017)
  * A new generated password will be set every 6h by default, see: const long interval = 1000 * 60 * 60 * 6 (this means a downlink will be asked every 6h = 4 per day to the [Sigfox ](http://www.sigidwiki.com/wiki/SIGFOX)Backend, this respects the [ETSI](http://www.etsi.org/) Standards)
  * The new password will be stored in the MKRFox1200 flash memory (this means that if you reboot the board, the default password (2017) is set again)
  * The new password is accessible on the ngrok Python API (home page - http://localhost:5000/)
  * Each time the correct password is entered, the message "OPEN" is sent to the Sigfox Backend so the owner can be notified it has been opened by someone (this takes 6 seconds)

## Step 7: TODO - Going Further

**treated**: send notification when the box is opened

**treated**: send the approximated voltage of the 3.7V battery when there is a downlink (every 6h)

**untreated**: add multi-tasking to allow asynchronous jobs

**untreated**: put the board in deepsleep when not in use to preserve battery consumption

**Have fun and always keep your keys safe!**
