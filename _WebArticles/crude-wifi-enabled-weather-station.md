# Crude WiFi-Enabled Weather Station

_Captured: 2017-11-11 at 18:54 from [www.instructables.com](http://www.instructables.com/id/Crude-WiFi-Enabled-Weather-Station/)_

![](https://cdn.instructables.com/FP9/V850/J9EH2RI6/FP9V850J9EH2RI6.MEDIUM.jpg)

Today you are going to learn how you can build a simple WiFi-enabled weather station that sends you the temperature and humidity data using IFTTT directly to your e-mail. The parts that I've used can be found on [kumantech.com](http://www.kumantech.com/)

## Step 1: Parts Needed & the Necessary Conections

![](https://cdn.instructables.com/FI0/DRZL/J9EH2RO5/FI0DRZLJ9EH2RO5.MEDIUM.jpg)

To complete this project, you will need:

**How do I connect the sensor to the board?**

DHT11 | NodeMCU

**GND (-)** -> **GND**

**5V (+) **-> **3.3V**

**OUT (Signal****)** -> **D5**

## Step 2: Setting Up IFTTT

![](https://cdn.instructables.com/F6M/GZLJ/J9EH2RGD/F6MGZLJJ9EH2RGD.MEDIUM.jpg)

![](https://cdn.instructables.com/F39/2ZY6/J9EH2RHF/F392ZY6J9EH2RHF.SMALL.jpg)

![](https://cdn.instructables.com/FKF/D4VN/J9EH2RHY/FKFD4VNJ9EH2RHY.SMALL.jpg)

![](https://cdn.instructables.com/FFO/Y444/J9EH2RHK/FFOY444J9EH2RHK.SMALL.jpg)

Head over to [IFTTT.com](http://ifttt.com) and register an account (if you haven't already). After that, go to **My Applets** and then click on **[New Applet](https://ifttt.com/create)**. Then, click on **\+ this** and when asked to choose a service, select, **Webhooks**. A list of triggers will popup, and at the time of writing this, there is only one available option - **Receive a web request. **Next, choose a name for the event and remember it (it will be used in the code). After creating the trigger, you need to click n **+that **and choose the service that we are going to use. In this case, it is email. In the next page, you need to choose how is the email going to look like. This is entirely up to you, but remember, **you need to include the Value1 and Value2 fields for the incoming data. For reference, take a look at the third screenshot above. One last thing, go to the **[settings of the Webhooks service](https://ifttt.com/services/maker_webhooks/settings)**and at the bottom you will see an url. Copy the string after use/**** and save it somewhere. This is your unique API key, you will need it later in the code. **After completing this step, you are done with IFTTT for now. It's time for the code for the NodeMCU

## Step 3: Uploading the Code and Customizing

![](https://cdn.instructables.com/FH4/MPCD/J9EH2WUB/FH4MPCDJ9EH2WUB.MEDIUM.jpg)

Before uploading the code (which can be found [here](https://pastebin.com/06HN8Vyn)), take your time and look at the commented lines and variables in the begging. You need to change some things up, and then upload the code to the NodeMCU.

After uploading the code and powering up the board, you will receive emails every **x** amount of time (can be modified in the code above). If you have the IFTTT app on your smartphone, you can receive notifications every time the applet runs. Now, check your email and you will see the weather data. You can add more sensors and connect with other applets.

## Comments
