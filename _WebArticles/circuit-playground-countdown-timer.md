# Circuit Playground Countdown Timer

_Captured: 2017-12-29 at 10:55 from [roques.xyz](https://roques.xyz/?p=103)_

This Christmas I was fortunate enough to receive an [Adafruit Circuit Playground Express](http://adafruit.com/product/3333) (UK stockist link)- an all round (haha) fun experimentation/development board. It's an awesome piece of kit (and a steal at £25). It's got all sorts of cool stuff on board (capacative touch, 10 Neopixel LEDs, sensors galore, IR comms…), and is based on the awesome ATSAMD21G18 MCU, which I'm definitely going to have a play with in the future.

We've been playing a lot of _Who's/What's/When's in the Bag _this Christmas, but the sand timer that comes with the game is quite hard to see (and my team kept forgetting to check it). What would be better, I thought, is some sort of more obvious lightey-soundy solution. I fancied a quick play with my new toy, and it seemed like an ideal fit. I decided to base the timer on the UK game-show Countdown - I just really like that tune it plays at the end.

> Christmas project: [@adafruit](https://twitter.com/adafruit?ref_src=twsrc%5Etfw) Circuit Playground Express Countdown Timer. Blog on the way… Also annoyingly plinky music! [pic.twitter.com/bYjgxXwT8b](https://t.co/bYjgxXwT8b)
> 
> -- Archie Roques (@archieroques) [December 27, 2017](https://twitter.com/archieroques/status/946057902334402560?ref_src=twsrc%5Etfw)

The code is quite poorly written but it does the job. I wrote the program in MakeCode, a Microsoft-made visual Scratch-like programming environment (also used with micro:bit), with JavaScript doing the legwork. It's online-based and simple so was ideal for a quick trial.

I never had much luck with getting the built-in _graph_ function to run as a background process (very possibly my own fault), so I ended up just shoehorning everything in to one big thread. This is hopelessly inefficient (the code takes a good minute to compile) but it works.

![](https://roques.Xyz/wp-content/uploads/2017/12/Screenshot-2017-12-27-at-17.47.27.png)

> _Where ma other note values at?_

I used [some online sheet-music of the Countdown Plinky Song](https://musescore.com/sarcastic_fantastic/scores/3572356) (as it shall henceforth be known) to figure out the notes and note values. They aren't spot-on but you can tell what it's meant to be. MakeCode's inbuilt music library is pretty good, but it won't do stuff like 3/2s of a note (which is needed if you need to do dotted notes, as are in the Countdown Plinky Song). I wrote the tune in single-note values, and then switched over to JavaScript to change the time manually. As-standard, it uses `music.beat(BeatFraction.XXX)` where `XXX` is a value such as `half`or `quarter`. However, you can swap the whole `music.beat(BeatFraction.XXX)`for a simple millisecond value. I decided that 250ms was about right for a whole note - one advantage of using the beat system is that you can add a block changing the tempo and all note values change themselves automagically.

Every 12 notes (12 * 250ms = 3 seconds or 1/10th of the full 30-second period), I added two blocks. One to increase the light indexing variable by one, and another to light the relevant light up.

I repeated the main sequence twice, because it lasts for around 15 seconds per revolution of the tune.

After the loop, I had to add the nice ending tune, I again used the sheet music for that. On telly, there's a really satisfying 'peeeew' noise at the end of the time. I wanted to add that, so I made a loop which plays ever decreasing note values. Originally I couldn't get this to work on the Circuit Playground despite it being fine in the simulator. This turned out to just be a timing thing - there's a minimum note value which you have to be above for an audible note to be produced. Once I decreased the 'resolution' of the sound all was fine.

And that's basically it. I also made a 60-second version that fires when you hit the other button.

You can find the full code for this project [here](https://makecode.com/_JjAR0rCaJC57).
