# Imaginary AC Circuits Aren’t Really Complex

_Captured: 2017-10-13 at 18:24 from [hackaday.com](https://hackaday.com/2017/06/15/imaginary-ac-circuits-arent-really-complex/)_

![](https://hackadaycom.files.wordpress.com/2017/06/sine_curve_anim.gif?w=800)

If you have ever read advanced textbooks or papers about electronics, you may have been surprised to see the use of complex numbers used in the analysis of AC circuits. A complex number has two parts: a real part and an imaginary part. I've often thought that a lot of books and classes just kind of gloss over what this really means. What part of electricity is imaginary? Why do we do this?

The short answer is phase angle: the time delay between a voltage and a current in a circuit. How can an angle be a time? That's part of what I'll need to explain.

First, consider a resistor. If you apply a voltage to it, a certain current will flow that you can determine by Ohm's law. If you know the instantaneous voltage across the resistor, you can derive the current and you can find the power-how much work that electricity will do. That's fine for DC current through resistors. But components like capacitors and inductors with an AC current don't obey Ohm's law. Take a capacitor. Current only flows when the capacitor is charging or discharging, so the current through it relates to the rate of change of the voltage, not the instantaneous voltage level.

![](https://hackadaycom.files.wordpress.com/2017/06/sincos1.png)

That means that if you plot the sine wave voltage against the current, the peak of the voltage will be where the current is minimal, and the peak current will be where the voltage is at zero. You can see that in this image, where the yellow wave is voltage (V) and the green wave is current (I). See how the green peak is where the yellow curve crosses zero? And the yellow peak is where the green curve crosses zero?

These linked sine and cosine waves might remind you of something -- the X and Y coordinates of a point being swept around a circle at a constant rate, and that's our connection to complex numbers. By the end of the post, you'll see it isn't all that complicated and the "imaginary" quantity isn't imaginary at all.

## Simplifying Assumptions

Start with an audio signal of someone speaking and feed that into your circuit. It is awash with different frequencies that change constantly. If you had a circuit with only resistors in it, you could pick a point in time, find all the frequency components present or the instantaneous amplitude, derive the instantaneous currents, and you could use conventional techniques on it. You'd just have to do it over and over and over again. If the circuit involves inductors or capacitors, whose behavior depends on more than just the voltage across them, this becomes very difficult very quickly.

Instead, it is easier to start with a sine wave at a single frequency and assume that a complex signal of many different frequencies is just the sum of many single sines. One way to think of a capacitor is to consider it a resistor that has higher resistance at lower frequencies. An inductor acts like a resistor that gets larger at higher frequencies. Because we are only considering a single frequency, we can convert any capacitance and inductance values to an _impedance_: a resistance that is only good at the frequency of interest. What's more is that we can represent impedance as a complex number so that we can track the phase angle of the circuit, which directly relates to a particular time delay between voltage and current.

For a true resistor, the imaginary part is 0. That makes sense because the voltage and current are in phase and therefore there is no time delay at all. For a pure capacitor or inductor, the real part is zero. Real circuits will have combinations and thus will have a combination of real and imaginary parts. Numbers like that are complex numbers and you can write them in several different ways.

## Complex Review

The first thing to remember is that the word imaginary is just an arbitrary term. Maybe it is better to forget the normal meaning of the word imaginary. These imaginary quantities are not some kind of magic electricity or resistance. We use imaginary numbers to represent time delays in circuits. That's all.

![](https://hackadaycom.files.wordpress.com/2017/06/nl3.png)

There is a long story about what imaginary numbers mean in pure math and why they are called imaginary. You can look that up if you are a math-head, but you should know that math books use the symbol i for the imaginary part of a complex number. However, since electrical engineers use i for current, we use j instead. You just have to remember when reading math books, you'll see i and it isn't a current, and it is the same as j in electrical books.

There are several ways to represent a complex number. The simplest way is to write the real part and the imaginary part as being added together along with j. So consider this:

5 + 3j

We say the real part is 5 and the imaginary part is 3. Numbers written in this form are in rectangular format. You can plot it on the number lines like this:

![](https://hackadaycom.files.wordpress.com/2017/06/nl4.png)

That leads to the second way to write a complex number: polar notation. If the point on the graph is 5 + 3j, you can note that a vector can represent the same point. It will have a length or magnitude and an angle (the angle it makes with the X-axis of the graph). In this case, the magnitude is 5.83 (about) and the angle is just a little under 31 degrees.

This is interesting because it is a vector and there are a lot of good math tools to manipulate vectors. It is going to become really important in a minute because the angle can correspond to a phase angle in a circuit and the magnitude has a direct physical relationship, as well.

## Phase Angle

Remember that I said we do an AC analysis at a single frequency? If you plot the AC voltage across and the current going through a resistor at some frequency, the two sine waves will line up exactly. That's because a resistor doesn't time delay anything. We'd say the phase angle across the resistor is zero degrees.

However, for a capacitor, the current will appear to rise before the voltage by some amount of time. This makes sense if you think about your intuition about capacitors at DC. When a capacitor is discharged, it has no voltage across it, but it will consume a lot of current -- it temporarily looks like a short circuit. As the charge builds, the voltage rises but the current drops, until the capacitor is fully charged. At that point, the voltage is at a maximum, but the current is zero, or nearly so.

Inductors have the opposite arrangement: voltage leads current, so the curves would look the same but the V curve is now the I and the I curve is now the V. You can remember that with the simple mnemonic ELI the ICE man, where E is voltage just like in Ohm's law. When you talk about phase shift in a circuit, you really mean how much the current leads or lags the voltage at a given frequency. That's a key idea: phase shift or angle is the amount of time the current leads or lags the voltage. You can also measure phase between other things like two different voltage sources, but generally when you say "this circuit has a phase shift of 22 degrees" you mean the voltage vs the current time delay.

Keep in mind a sine wave is like a circle bent to fit a line. So if the start of the sine wave is at 0 degrees, the top of the positive peak is 90 degrees. The second 0 crossing is 180 degrees, and the negative peak is 270 degrees-just like the points on a circle. Since the sine wave is at a fixed frequency, putting something at a particular degree mark is the same as expressing a time.

![](https://hackadaycom.files.wordpress.com/2017/06/sine_curve_anim.gif?w=800&h=250)

In the case of a resistor, the shift is 0 degrees. So in complex notation, a 100 ohm resistor is 100 + 0j. It can also be 100∠0\. For a capacitor, the current rises before the voltage by 90 degrees so a capacitor has a phase shift of -90. But what's the magnitude?

You probably learned that the capacitive reactance is equal to 1/(2πfC) where f is the frequency in Hz. That's the magnitude of the polar form. Of course, since -90 degrees is straight down the number line, it is also the imaginary part of the rectangular form (and the real part is zero). If capacitive reactance (Xc) is equal to 50, for example, then you could write 0-50j or 50∠-90. Inductors work the same but the reactance (Xl) is 2πfL and the phase angle is 90 degrees. So an inductor with the same reactance would be 0 + 50j or 50∠90.

## Finding the Power

Let's look at a quick example of what these phase angles are good for: calculating power. You know that power is voltage times current. So if a capacitor has 1 V across it (peak) and draws 1 A through it (peak), is the power 1 watt? No, because it doesn't draw 1 V at 1 A at the same time.

![](https://hackadaycom.files.wordpress.com/2017/06/sim.png)

Consider [this simulation](http://tinyurl.com/kdhrupr) (see figure to the right). You can see the traces to the left show the 90 degree phase shift very clearly (the green trace is voltage and the yellow one is current). The peak voltage is 1.85 V and the current peaks at about 4.65 mA. The product of the voltage times the current is 8.6 mW. But that's not the right answer. The power is actually 4.29 mW (see the graph on the right). In an ideal capacitor, power isn't consumed. It is stored and released, which is why the power goes negative. Real capacitors, of course, exhibit some loss.

Note that the power supply doesn't provide 4.29 mW, but much less. That's because the resistor is the only thing consuming power. The voltage and current are in phase for it and some of the power it dissipates is coming from the capacitor's stored charge.

![](https://hackadaycom.files.wordpress.com/2017/05/graph-e1495392269798.png)

## Circuits

The magnitude of the vector is usable in Ohm's law. For example, at 40 Hz, the Xc of the example circuit is just under 400 ohms. So the total complex impedance for the RC circuit is 1000 - 400j.

If you are adept with vectors you could do polar by writing 1000∠0 + 400∠-90. However, it is usually easier to write the rectangular version and convert to polar ([Wolfram Alpha](https://www.wolframalpha.com/) is good at that; just remember to use i instead of j). The magnitude is just the Pythagorean theorem and the angle is simple trig. I am not going to go into it, but here's the formula where R and J are the real and imaginary parts, respectively.

mag=SQRT(R^2+J^2)  
phase=arctan(J/R)

Our example, then, is 1077∠-21.8.

So what's the power coming out of the voltage source? Power is E^2/R (or, actually, E^2/Z in this case). So 25/1077 = 23 mW peak. The simulation shows 22.29 and since I rounded a few values, that's close enough.

## That's It?

That's not it, of course, but it is all you need to know for a lot of purposes. Many hobby-level electronic texts skimp on the details and just work with magnitudes. For simple circuits, this can work, but for something complex (no pun intended), it gets hairy fast.

By the way, this example showed to elements in series. However, you can add reactances in parallel just like you do resistors in parallel.

The key concepts you need to remember are:

  * The analysis of an AC circuit mostly occurs at a single frequency with a sine wave input.
  * Imaginary numbers aren't imaginary.
  * Magnitudes of complex numbers in polar forms can be treated like a resistance.
  * Phase angle is the time delay between the voltage and the current waveform.

There are a lot of details I glossed over. You probably don't need to know how i is really the square root of negative one. Or how Euler's number plays into this and the simplicity of integrating and differentiating sine waves written with an amplitude and a phase angle. If you are interested in math history, imaginary numbers have [quite a story](https://en.wikipedia.org/wiki/Complex_number#History) behind them. If you want something more practical, [Khan Academy has some useful videos](https://www.youtube.com/watch?v=wbEEWmJFDVg). However, what's covered here should be all you need to know to work with AC circuits.
