# Add an MPG Indicator to Your Older Car

_Captured: 2017-12-08 at 09:50 from [blog.hackster.io](https://blog.hackster.io/add-an-mpg-indicator-to-your-older-car-793c811d2d19)_

Driving a car can be expensive. You not only have to worry about insurance, maintenance, and registration, but of course there's also the price of gasoline! In order to get where you're going in an efficient manner, keeping a light touch on your accelerator can help significantly. To see how you're doing, newer cars generally have an indicator for miles per gallon, but what if you want to add this functionality after the fact?

![](https://cdn-images-1.medium.com/freeze/max/60/1*IawKPAKxIdbpzDCT3DvTtA.png?q=20)![](https://cdn-images-1.medium.com/max/1600/1*IawKPAKxIdbpzDCT3DvTtA.png)

The good news is that most likely the sensors for this are already available. All cars made since 1996 require an on-board diagnostic port, commonly known as OBD-II, which outputs a variety of data, including vehicle speed (VSS) and mass air flow (MAF). Since engines maintain a ratio of 14.7 grams of air per gram of gasoline, with some simple math, a value for miles per gallon can be obtained with this data. [This particular hack](https://www.macchina.cc/content/real-time-mpg-display-older-car) uses an Arduino-compatible device called [the Macchina M2](http://docs.macchina.cc/m2/), which plugs into this port, then translates the information as needed.

Instead of a numerical display, this project employs an array of RGB LEDs, which turn red or green depending on the instantaneous MPG reading, helping you maximize your efficiency. You can find the [code available here](https://gist.github.com/rocketjosh/1a2a3ed7f7c7c160d8ae84248f07e61a), or check it out in action in the video below.
