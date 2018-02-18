# Getting Started With IoT Using an Arduino and Google

_Captured: 2018-02-13 at 15:40 from [dzone.com](https://dzone.com/articles/getting-started-with-iot-using-an-arduino-and-google?edition=361106&utm_source=Zone%20Newsletter&utm_medium=email&utm_campaign=iot%202018-02-13)_

Getting started with the Internet of Things using an Arduino and Google helps us to explore this new technological revolution. This tutorial describes how to experiment Internet of things using Arduino and Google. IoT is one of the most important technological trends nowadays. In this post, we want to explore how to build an IoT project using Arduino and Google.

The interesting aspect of IoT is that we can experiment using simple development boards and existing cloud platforms that provide some services. It is not necessary to spend a lot of money to jump into the IoT ecosystem. The purpose of this project is building an IoT system that records the temperature and pressure and stores these values into Google Cloud Platform using Google Sheets.

During this project, as said, we will explore how to build an IoT project using Arduino and Google and how to integrate them. To help Arduino send data to Google Sheets, this IoT project uses [Temboo](https://temboo.com/). This is an [IoT cloud platform](https://www.survivingwithandroid.com/2015/12/comparing-iot-platforms.html) that provides several integration services that simplify the process of integrating different systems.

To build this IoT project using Arduino and Google, we have to follow these steps:

  1. Authorize our device using OAuth 2 and get the token to exchange data with Google
  2. Connect the sensor to the Arduino
  3. Send the data to the Google sheet using Temboo

## Authorizing Your Arduino Using OAuth

In this first step, we have to authorize our Arduino board to send data to Google using OAuth 2. To simplify this authorization process, we will use Temboo that provides a set of services to get the OAuth token. We have covered the [Temboo platform several times, building interesting IoT projects](https://www.survivingwithandroid.com/2016/05/arduino-mkr1000-arduino-tutorial.html) along the way.

During this step, we assume you have already a Google account so that you can access the [Google Developer console](https://console.developers.google.com/projectselector/apis/dashboard?pli=1). Before digging into the details about exploring IoT using Arduino and Goole, it is necessary to have a Google API project. Moreover, it is necessary to enable the Google Sheets API. Once you have your project configured correctly, you should have a _Client ID_ and a _Secret key_. These two keys are very important, and we will use them later during the project. The final result is shown in the picture below:

![Google IoT project](https://www.survivingwithandroid.com/wp-content/uploads/2018/01/Google_IoT_project.png)

Now it is time to focus our attention on Temboo. If you do not have a Temboo account, go to the Temboo homepage and create it for free. Once you have an account, log in and select the OAuth 2 service on the left side of the menu.

Select on the left side of the menu, then the _Initialize OAuth_ item under _Utilities> Authentication > OAuth2_ and fill the form as shown in the picture below:

![IoT oauth google](https://www.survivingwithandroid.com/wp-content/uploads/2018/01/IoT_oauth_google.png)

The _Client Id_ is the one you get from Google as shown in the step above. Now click on the Run Now button and wait for the response. If everything goes well, you will get the result you are looking for:

![Get IoT OAuth token](https://www.survivingwithandroid.com/wp-content/uploads/2018/01/IoT_oauth_token.png)

This result is very important because we will use these values later. Now, you have to enable access to Google Sheets. For this purpose, in your browser, copy and paste the first value, the URL shown above. You should see an authentication request sent by Google and then a blank page. It is almost done. The last step is using _Finalize OAuth _as shown below:

![IoT Google oauh token](https://www.survivingwithandroid.com/wp-content/uploads/2018/01/IoT_Google_oauh_token.png)

The _CallbackID_ value was retrieved in the step above. That's all. Now if you click on Run Now, you get the token we will use during the project:

![Google API Token](https://www.survivingwithandroid.com/wp-content/uploads/2018/01/Google_API_Token.png)

> _Now we have our token to use in the API calls._

## Connecting a Sensor to Your Arduino

This is the easiest step, we simply have to connect a sensor to the Arduino. In this example, we will use an [MKR1000 board](https://www.survivingwithandroid.com/2016/08/iot-rapid-prototyping-board.html), but you can use an Arduino Uno with a Wi-Fi shield. It is important to note that the board must be compatible with Temboo. The schematic is shown below:

![Getting started with Internet of things using Arduino and Google: MRK1000 temp pressure sensor](https://www.survivingwithandroid.com/wp-content/uploads/2018/02/mkr1000_temp_pressure_sensor.png)

> _The code is very simple._

Add these lines at the beginning:

Then, to read the values, you have to add:

That's all.

## Sending the Data to Google Sheets

The last step is sending the data acquired by the sensor to Google. For this purpose, we will use another Temboo choreo called _AppendValue_ under _Google > Sheets_. In the form you get after clicking on this choreo, you have to add the required information, such as _ClientId_, _Token, _and so on as shown in the picture below:

![IoT Google send values](https://www.survivingwithandroid.com/wp-content/uploads/2018/02/IoT_Google_send_values.png)

If you are wondering where you get the SpreadsheetID, you can get it from the URL when accessing the sheet from your browser:

![Google sheet id](https://www.survivingwithandroid.com/wp-content/uploads/2018/02/Google_sheet_id.png)

> _Now you can click on the Run Now button and get the code to use._

Just by writing a few lines of code, you have implemented an IoT system that uses the Google Cloud API. The code you get from Temboo has to be modified by adding the values read from the sensor using the code shown previously.

Now if you run the sketch, you will see that Arduino starts sending data to Google Cloud:

![IoT Google sheet project](https://www.survivingwithandroid.com/wp-content/uploads/2018/02/IoT_Google_sheet_project.png)

## Summary

At the end of this post, you have built an IoT system and explored how to get started with the Internet of Things using Arduino and Google. Writing a few lines of code, you have built an IoT system that sends data to Google Sheets. The interesting part of this project is the way you have implemented it. Getting started with the Internet of Things using Arduino and Google is very simple, and by just configuring a few cloud platform components, without much knowledge about IoT, you have built your first IoT project.
