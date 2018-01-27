# I made a LED dog collar with JavaScript.

_Captured: 2017-11-13 at 08:41 from [medium.com](https://medium.com/@secretsquirrel/i-made-a-led-dog-collar-with-javascript-1c10ff973550)_

# I made a LED dog collar with JavaScript.

![](https://cdn-images-1.medium.com/max/1600/1*YUX6d8kzvtBO8ngDi1XUNg.gif)

> _❤️ 💛 💚 💜_

JavaScript is truly _EVERYWHERE_, and now I've even added it to my dog. Last week, I made my dog a snazzy rainbow magic collar with an Arduino, LEDs, and JavaScript.

I've been playing around with hardware for the past year. Mainly, I've been interested in making little, useless things that flash and glow all colors of the rainbow with LEDs. I'm not super interested in using hardware for home automation or for real practical uses, really. For me, working with hardware is where I can be silly and indulge my child-like wonder. I like creating art or fashionable things whose only purpose is to bring a little joy to those around me (& myself).

I recently saw that Adafruit had released a new Arduino board called the [Circuit Playground Express](https://www.adafruit.com/product/3333) and was pretty anxious to try out this little board.

I was quite excited with it because it has a bunch of sensors (temp, light, motion, sound) AND 10 neopixels built-in. But probably the coolest thing about it is the multiple ways in which you can program it! You can program it 3 ways: (1) using [Microsoft MakeCode](https://learn.adafruit.com/makecode) and writing JavaScript or block-based code (like Scratch), (2) using CircuitPython to interpret Python directly on the board, or (3) using C++ with the Arduino IDE. I was most excited to try the [MakeCode Editor](https://makecode.adafruit.com/) and finally write code for my wearables in JavaScript instead of hacking C++(ish) code together!

So, I obviously used this opportunity to make a fancy collar my doggo for night walks. He's a good boye and totally deserves a special collar. I also think that the steps in this build could just as easily be applied to other lighted apparel applications like adding some LEDs to your denim jacket or backpack or hat or <insert your awesome idea here>... ✨

Let's jump into the build process!

> Note: Some thoughts about being a new maker & soldering.

> Don't shy away from jumping into playing around with hardware and LEDs because you don't feel confident or don't have the supplies to solder yet!

> The Circuit Playground Express is extremely versatile. It's tons of fun on its own with the built-in 10 Neopixel LEDs **without** needing to solder any additional LEDs to it. Don't worry about adding additional LEDs until you wanna explore more in-depth and go bigger. :-)

#### Materials:

  * [Adafruit Circuit Playground Express](https://www.adafruit.com/product/3333)
  * [Neopixels RGBW 30/m LED strip](https://www.adafruit.com/product/2842), approximately 12"
  * [LiPoly 2000mAh battery](https://www.adafruit.com/product/2011)
  * An old dog collar
  * Zipties
  * [22 AWG wire](http://www.adafruit.com/products/288)
  * Soldering iron + Soldering wire
![](https://cdn-images-1.medium.com/max/1600/1*8jHUS0U1EpFbWtN_17kFaw.jpeg)

> _The main ingredients: dog collar, leftover neopixels strip, & adafruit circuit playground express_

First, I plugged the Circuit Playground Express into my computer using a micro-B USB cable. I wanted to test the board first and check out the [MakeCode Code Editor](https://learn.adafruit.com/makecode). I've only used the Arduino IDE to create code with C++ on Arduino boards previously. The Arduino IDE is not impossible to use, but sometimes it is frustrating to setup, so I was pretty excited to check out the user friendliness of a web-based code editor instead and work with JavaScript since I'm more comfortable with it than C++. [MakeCode](https://learn.adafruit.com/makecode) works in most browsers, compiles the code in the browser, and works offline. The best part is that loading code onto your board is as easy as dragging and dropping the file while the board is plugged into the usb!

So, for this first step, I wanted the built-in LEDs to flash a simple rainbow animation. You can use multiple `show ring` blocks to create basic animations. The example below is a blinking animation that repeats in a forever loop. With MakeCode, you can code this using the block-style visual editor (like [Scratch](https://scratch.mit.edu/)) or with the JavaScript editor:

#### Blocks Editor:

![](https://cdn-images-1.medium.com/max/1600/1*tobg-5HMXqqQtd6cHFTV2w.png)

> _Piecing together 'show ring' bits with selected colors in a forever loop to create a simple 2-part animation._

#### JavaScript Editor:

![](https://cdn-images-1.medium.com/max/1600/1*k51jFCHBkA91p1v3JoICPw.png)

> _Creating the same 2-part animation as above, but using the javascript editor._

On the left side of the screen, the editor shows a simulator of what your running code will look (or sound) like on the Circuit Playground Express!

When you are ready to load the code onto your board, you just click the 'Download' button, enter Bootloader mode by clicking the reset button on the board, and drag-n-drop the downloaded .utf2 file onto the removable drive CPLAYBOOT in Finder. Adafruit has _great_ tutorials on all of this, so check those out for the most detailed directions: <https://learn.adafruit.com/makecode/downloading-and-flashing>

#### **Building:**

I felt happy with my first go in MakeCode and that it was working on my board, so next I dove into soldering the additional Neopixel LED strip to the board.

To connect the Neopixels LED strip to the Circuit Playground Express, I needed to solder 3 connections:

  * GND to GND (the ground)
  * 5V to VOUT (powers the LEDS)
  * Din to A1 (sends data to the LEDs & tells it what to do)
![](https://cdn-images-1.medium.com/max/1600/1*sDQfU1p6B3XWskFgalZTxQ.png)

> _Pro-tip: Creating a Fritzing diagram can save you so much headache from mis-soldering something 😥(see below)._

![](https://cdn-images-1.medium.com/max/1600/1*WApk23MQJKomjSA-XPrYfg.jpeg)

> _A test fit of the board and LEDs on the dog collar._

![](https://cdn-images-1.medium.com/max/1600/1*SNmUyukIurywVU1fSdYYqA.jpeg)

> _Ready to start soldering!_

![](https://cdn-images-1.medium.com/max/1600/1*n_NeUZ57k63gRWKSFh0cmA.jpeg)

> _Attaching LEDs to dog collar with zipties_

#### Coding the Collar:

I coded the collar using the JavaScript editor and the MakeCode API [reference docs](https://makecode.adafruit.com/reference/). I wanted the collar to do a few different things:

  * It should continually run a rainbow 🌈 animation on the board and strip's LEDs.
  * If it detects a shake, it should sparkle ✨ randomly on the strip for 1 second.
  * If I press button A, it will turn off all the LEDs.
  * If I press button B, it will turn on the rainbow animations on all LEDs again.
![](https://cdn-images-1.medium.com/max/1600/1*SGAXhobFWgJhHr-9flmhnQ.png)

> _Writing and simulating my code as I go in the MakeCode editor._

To start off, I used a forever loop method. In the loop, I first check if the `needsSetup`boolean is `true`. If so, I run the `setupStrip()` method to set the colors initially for the LED strip. Then, I check if the LEDs are paused (this happens if Button A is pressed). If not, it will run the rainbow animation indefinitely.

The only actions that can interrupt the rainbow animation loop are (1) if the collar detects a sudden shaking moment or (2) if Button A is pressed. If a shake is detected, the LED strip will sparkle randomly for 1 second. If Button A is pressed, all the LEDs will turn off until Button B is pressed.

![](https://cdn-images-1.medium.com/max/1600/1*UBXzuVM3dYRVcJzKxT8SsA.gif)

> _Rainbow, Shake sparkles, Button A turns it off, then Button B starts it again._

Below is my final code for the collar (for now, at least).

```
// https://gist.github.com/traumverloren/e809121755da2d48717b69af2d945127#file-dogcollar-js

let strip = light.createNeoPixelStrip(pins.A1, 9, NeoPixelMode.RGBW);
let isPaused = false;
let needsSetup = true;

const setupStrip = () => {
    strip.setPixelColor(0, Colors.Red);
    strip.setPixelColor(1, Colors.Orange);
    strip.setPixelColor(2, Colors.Yellow);
    strip.setPixelColor(3, Colors.Green);
    strip.setPixelColor(4, Colors.Blue);
    strip.setPixelColor(5, Colors.Blue);
    strip.setPixelColor(6, Colors.Indigo);
    strip.setPixelColor(7, Colors.Violet);
    strip.setPixelColor(8, Colors.Pink);
    strip.show();
    needsSetup = false;
}

loops.forever(() => {
    if (needsSetup) {
        setupStrip();
    }

    if (!isPaused) {
        light.showAnimation(light.rainbowAnimation, 100);
        strip.move(LightMove.Rotate, 1);
    }
})

input.onGesture(Gesture.Shake, () => {
    strip.stopAllAnimations();
    strip.showAnimation(light.sparkleAnimation, 1000);
    needsSetup = true;
});

input.buttonA.onEvent(ButtonEvent.Click, () => {
    strip.stopAllAnimations();
    light.stopAllAnimations();
    strip.clear();
    light.clear();
    isPaused = true;
})

input.buttonB.onEvent(ButtonEvent.Click, () => {
    isPaused = false;
    needsSetup = true;
})}
```

let strip = light.createNeoPixelStrip(pins.A1, 9, NeoPixelMode.RGBW);

let isPaused = false;

let needsSetup = true;

const setupStrip = () => {

strip.setPixelColor(0, Colors.Red);

strip.setPixelColor(1, Colors.Orange);

strip.setPixelColor(2, Colors.Yellow);

strip.setPixelColor(3, Colors.Green);

strip.setPixelColor(4, Colors.Blue);

strip.setPixelColor(5, Colors.Blue);

strip.setPixelColor(6, Colors.Indigo);

strip.setPixelColor(7, Colors.Violet);

strip.setPixelColor(8, Colors.Pink);

strip.show();

needsSetup = false;

}

loops.forever(() => {

if (needsSetup) {

setupStrip();

}

if (!isPaused) {

light.showAnimation(light.rainbowAnimation, 100);

strip.move(LightMove.Rotate, 1);

}

})

input.onGesture(Gesture.Shake, () => {

strip.stopAllAnimations();

strip.showAnimation(light.sparkleAnimation, 1000);

needsSetup = true;

});

input.buttonA.onEvent(ButtonEvent.Click, () => {

strip.stopAllAnimations();

light.stopAllAnimations();

strip.clear();

light.clear();

isPaused = true;

})

input.buttonB.onEvent(ButtonEvent.Click, () => {

isPaused = false;

needsSetup = true;

})
[view raw](https://gist.github.com/traumverloren/e809121755da2d48717b69af2d945127/raw/ef30fc0bdf52c3c511c29b05e2d3e2b653c9388e/dogcollar.js) [dogcollar.js](https://gist.github.com/traumverloren/e809121755da2d48717b69af2d945127#file-dogcollar-js) hosted with ❤ by [GitHub](https://github.com)

#### Full build disclosure:

I totally goofed the soldering of the **Din** to the wrong pin on the Circuit Playground Express. 😞

I was so excited to get started, that I neglected to carefully look at the [Pinout info](https://learn.adafruit.com/adafruit-circuit-playground-express/pinouts) on the product page. Always do this first and save yourself the same grief as me!

I didn't and ended up soldering a wire from the Din to **A0**. While this worked, the Circuit Playground made a constant clicking noise when the lights were cycling. This is because the A0 pinout will interfere with the built-in speaker if it's used as an output. I didn't want the collar making weird sounds when it was running, so I had to fix it. But, no fear, I heated up the connections again with the soldering iron, loosened the wire, and re-soldered it to the **A1** pinout. 😎

![](https://cdn-images-1.medium.com/max/1600/1*dWNioYnl24-LKdICbKBaGQ.gif)

> _❤️ 💛 💚 💜_

I hope you feel inspired to check out the Circuit Playground Express, MakeCode, and will try coding your first hardware project! ✌️
