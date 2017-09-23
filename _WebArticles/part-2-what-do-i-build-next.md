# Part 2 - What Do I Build Next?

_Captured: 2017-09-15 at 10:39 from [www.hackster.io](https://www.hackster.io/alien-energy-3/part-2-what-do-i-build-next-8caa4c)_

![Part 2 - What Do I Build Next?](https://hackster.imgix.net/uploads/attachments/252314/20170110_175556resize_5fNEgEqBiz.jpg?auto=compress%2Cformat&w=900&h=675&fit=min)

My continued saga first utilizes the NEW Adabox002 Mini Robot with Feather 32u4 and the Feather Motor Controller in stacked format and have it updated to use the Piezo code to play sound when an on-screen button is pressed. I used the Adafruit revised Piezo code and added it to all four on-screen buttons which code can be revised later.

The second build again utilizes another Adafruit Mini Robot but will utilize the HUZZAH ESP and Feather Motor Control left over from Part 1's build for the tank platform to fit it up.

I experimented with the supporting standoffs when I initially assembled each Mini Robot to keep things symmetric and to allow for maximum battery storage and electronic layout space. You'll notice slight differences in the pictures.

So once again, I used Adafruit's documentation for each construction step and viewed the available videos to clear up issues that I discovered.

I even needed to go back to their forum because I had made a few "Tech 101" oversights/mistakes (i.e., I drilled an oversized hole in one plate because I didn't realize that the plates weren't symmetric). I changed the battery size/type I was going to use so I needed to move the brass supports multiple times, as Lady Ada said in the Christmas unboxing video.

When she assembled one motor and wheel incorrectly: "what's a project if you don't have to undo a step or two" ...at least that's her jest.

I even decided not to use the half-breadboard and instead use a 1/4 mini breadboard instead (I would have used another Double Feather Wing if I had one available).

I am still waiting for a power switch for the Li-Po battery, so I don't have to keep unplugging it when not in use. Speaking of Li-Po Batteries, that was another "Tech 101" mistake. I had forgotten a lesson learned from 1st build, the Feather needs it's own power source as well as the DC Motors. I figured that if they are stacked, that they would use/share the same power source. Wrong!

1\. When assembling DC Motor mounts be sure that nut face is parallel to mount, not on edge.

2\. Stand-offs can be placed in many holes, be sure to keep plates in-lined symmetrically so that they overlay on top of each other.

3\. Be sure to have battery holder that is selected for use on hand so that during assembly you can orientate power switch in large opening.

4\. Both Feather 32u4 and Motor Controller need separate battery's. DC Motors need 4-AA batteries (6v) but the Feather 32u4ncan use a Li-Po 3.7vdc @350maH.

5\. Use Velcro or tape to hold Li-Po battery to motor battery case.
