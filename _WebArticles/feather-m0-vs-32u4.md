# Feather M0 vs 32u4

_Captured: 2018-03-03 at 06:59 from [forums.adafruit.com](https://forums.adafruit.com/viewtopic.php?f=24&t=85750&sid=ce7c28de02703e89baec70fd47b1a933)_

They're the same price because the cost of the PCB and connectors is more than the cost of the microcontroller.

The M0 doesn't cut into the utility of ATmega32u4-based Feather boards, ATmega328-based Pro Trinkets, or even ATtiny85-based Trinkets because different jobs require different tools. A list of unused features doesn't support the claim that one chip is better than another for a given job, so the question isn't, "why use an ATtiny85 when you can use an M0?", it's "what makes this chip better for this job than that one?"

If you want to decode and mix multiple MP3 tracks in real time, the M0 is clearly better than the ATtiny85. If you want to debounce a couple of buttons and blink a few LEDs, not so much. You can use the M0 if you want, but it becomes a matter of personal preference instead of technical merit.

You also have to consider the complexity and learning curve for a given platform. As an example, the SAM21D has a GPIO multiplexer that can associate pins with up to eight different functions. That makes the chip highly flexible, but it also means you have to configure the multiplexer to make the pins do anything. To get real value out of the system, you have to know how all the functions map to various pins, what conflicts exist between the mappings, and how to get the features you want working on the pins you've selected. Given the number of possible combinations, you can probably forget about finding a pre-existing library for the configuration you've chosen, and can expect plenty of fun if you try to combine code from different projects. The same is true for the SAM21D's nested interrupt system and seven different clock sources.

For many jobs, configuring the SAM21D with the features you want on the pins you want will require more technical knowledge than solving the actual problem on a simpler chip. That can lead to Sirius Cybernetics Corporation Syndrome: the sense of accomplishment you feel from getting it to do anything at all distracts attention from the fact that you haven't gotten it to do what you want.

In general, it's a good idea to start with the simplest possible platform and ask, "can this do what I want?" If not, move up to the next simplest platform and ask again. When you find a platform that can do what you want, you look at the next one up and ask, "will this make the job easier?" If the answer is yes, move up to the next platform and ask again. If the answer is no, you've probably found the best platform for the job.

The interrupts wouldn't be any problem, especially if they're only for wakeup purposes. Memory limits tend to be harder to budge though.

You probably have some learning curve ahead of you.. either digging into the libraries and trimming them down to fit on an ATmega32u4, or learning how to make them work on the M0 platform.

> Would it be beneficial from a power consumption point of view to go to the M0 for this task?

Not really. Both the 32u4 and M0 Feathers have a normal operating current of about 9mA.

If you're willing to sleep and wake the microcontroller, you could use a TPL5110 or TPL5111 breakout:

<https://www.adafruit.com/product/3435>  
<https://www.adafruit.com/product/3573>

They're bot low-power timer chips. If you cut the connection to the power LED they consume less than 100nA while idle.

The TPL5110 controls all power to a load, so the total current is the <100nA for the timer. The TPL5111 can pull a Feather's EN pin low, which will drop its current consumption to about 90uA. That's a thousand times higher than the TPL5110, but it lets the Feather recharge a LiPo while the EN pin is low.

In either case, the microprocessor wakes up when it gets power, runs whatever code you want, and can then toggle a DONE pin to shut itself off again.

The TPL5110 breakout has an LED that comes on when the power is active. It only uses a couple milliamps of current when it's lit, but its leakage current is around 20uA while the timer is idle. Cutting the jumper to the LED drops the timer's idle current by a factor of about 200.
