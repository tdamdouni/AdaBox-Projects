# LEA - Light Environment Automation

_Captured: 2018-02-02 at 12:55 from [www.hackster.io](https://www.hackster.io/felix-grammling-and-matthias-geckeler/lea-light-environment-automation-759616?utm_source=Hackster.io+newsletter&utm_campaign=994f82f734-EMAIL_CAMPAIGN_2017_07_26&utm_medium=email&utm_term=0_6ff81e3e5b-994f82f734-141949901&mc_cid=994f82f734&mc_eid=1c68da4188)_

![LEA - Light Environment Automation](https://hackster.imgix.net/uploads/attachments/411666/lea_i7Rc6VNPbu.png?auto=compress%2Cformat&w=900&h=675&fit=min)

**Intro**

This project is created in context of the lecture "Internet of Things Ecosystems" atthe University of Applied Science Esslingen. It covers the invention of an own IoT Idea and Application from the scratch solving a real-world problem. In the design sprints the students learn about design, implementation (full-stack) and business aspects of Internet of Things applications.

**IoT** **Prototyping** **Framework**

The IoT Prototyping Framework (IoTPF) is a collection of tools, modules and samples with the aim to empower students and developers creating full-stack IoT prototypes in a short time period.

**Contact: **

Idea and Application: Felix Grammling and Matthias Geckeler

Lecture and IoTPF: dionysios.satikidis@gmail.com

Tools:

University of applied SciencesEsslingen 2018

The project name LEA is an abbreviation and stands for **L**ight **E**nvironment **A**utomation. The idea behind that is to control the lights according to the brightness of the environment and in a user-defined period of time.

Think about the Christmastime or Halloween. You have several chains of lights at home and you have to turn them on one by one. Or see, there are chains with an integrated timer, which is always activated for a certain time, although you don't want this at all.

With LEA, you can solve all this problems. For this purpose LEA defines a start and a end time. The start time marks the beginning of the functionality. The functionality can be described in following easy states and processes:

  * The environment around LEA is dark - LEA turns the lights on. 
  * The environment around LEA is bright - LEA turns the lights off. 

But only in the given time period as defined before. If the time period is over all lights turn off automatically. So the light won't be on all night.

To demonstrate the proof of concept, our prototype uses the NeoPixel-Ring as a symbol for a lamp or a chain of light that is switched on in the dark. In the later final release the luminaires should be connected wired or wirelessly with LEA.

The below shown state-machine shows how LEA works.

![](https://hackster.imgix.net/uploads/attachments/411724/activitydiagramlea_oZ8L5DBwf3.png?auto=compress%2Cformat&w=680&h=510&fit=max)

> _state-machine of LEA_

The first action is to check whether LEA is online or offline. The status LEDs are set depending on the result. If LEA is offline unfortunately nothing can be done, because LEA can't send commands to the connected luminaires.

If LEA is online, the next step is to check which mode LEA is in. We defined three modes:

`Enabled Mode` \- all lights will be turned on independently to the brightness and the time period.

`Disabled Mode` \- all lights will be turned off independently to the darkness, even in the time period.

`Automatic Mode` \- LEA checks the brightness and the period of time and turns the lights on according to the settings.

Following picture shows the implemented prototype of the board.

![](https://hackster.imgix.net/uploads/attachments/411730/board_ItWeUiYmuF.png?auto=compress%2Cformat&w=680&h=510&fit=max)

> _Particle Photon LEA prototype_

In the upper left corner of the board you can see the installed status LEDs. They are showing the online (green) and offline (red) status of LEA.

In the middle of the board you see the NeoPixel-Ring, which represents any illuminant that is connected to LEA.

The light-sesor is mounted on the right-handside. The used hardware is a photocell which measures the brightness. The below shown diagrams should show the brightness values over a three-hours period in Esslingen am Neckar.

Between the NeoPixel-Ring and the light-sensor there are buttons for switching between the different modes of LEA. From left to right:

  * Enabled mode (turn light on) 
  * Automatic mode 
  * Disabled mode (turn light off)
![](https://hackster.imgix.net/uploads/attachments/412167/licht_-_3h_-_20min_oc6Ka1nxoy.PNG?auto=compress%2Cformat&w=680&h=510&fit=max)

> _light sensor brightness values_

The threshold of brightness to define dark and bright can be user defined. So we implemented a simple Webinterface to define the period of time and the just mentioned threshold for the brightness. Following picture should give an impression to the Webinterface.

![](https://hackster.imgix.net/uploads/attachments/412015/webinterface_lrOJrKcpJ8.png?auto=compress%2Cformat&w=680&h=510&fit=max)

> _Webinterface of LEA_

In the upper half, you can specify the time:

  * Startzeit (start-time) - save the start-time by clicking on "Speichern" (save)
  * Endzeit (end-time) - save the end-time by clicking on "Speichern" (save)

In the lower half, you can specify the threshold for the brightness:

  * Aktuell gemessen (measured currently) - get the currently measured brightness value by clicking on "Aktualisieren" (refresh). 
  * Schwellwert (threshold) - set the threshold by clicking on "Speichern" (save)

Behind the Webinterface we communicate with the particle cloud to get and set the variables.
