# Circuit Playground Express Chord Guitar

_Captured: 2017-12-29 at 05:46 from [scruss.com](http://scruss.com/blog/2017/12/27/circuit-playground-express-chord-guitar/)_

Since there are seven touch pads on a [Circuit Playground Express](https://www.adafruit.com/product/3333), that's enough for traditional 3-chord (Ⅰ, Ⅳ, Ⅴ) songs in the keys of C, D and G. That leaves one pad extra for a Ⅵ_min_ chord for so you can play [Neutral Milk Hotel ](https://www.youtube.com/watch?v=wqMZv1DN1Gc)songs in G, of course.

CircuitPython source and samples: [cpx-chord_guitar.zip](http://scruss.com/wordpress/wp-content/uploads/2017/12/cpx-chord_guitar.zip)

The code is really simple: poll the seven touch pads on the CPX, and if one of them is touched, play a sample and pause for a short time:

This is [roughly how I synthesized the samples](http://scruss.com/blog/2017/12/19/synthesizing-simple-chords-with-sox/), but I made them quieter (the MEMS speaker on the CPX went all buzzy at full volume, and not in a [good way](https://www.youtube.com/watch?v=fBTT3VPriV8)) and added a bit of reverb. Here's the sox command from the modified script:
    
    
    sox -n -r 16000 -b 16 "chord-${chord}.wav" synth 1 pl "$first" pl "$third" pl "$fifth" delay 0 .05 .1 remix - fade p 0 1 0.5 norm -5 reverb

Really, you do want to take a look at shortening the delay between the samples: you want it long enough for all of the notes of the chord to sound, but short enough that you can play faster songs. I came up with something that worked for me, kinda, and quickly; it's worth fixing if you have the time.
