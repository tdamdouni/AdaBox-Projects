# Circuit Board Trace Repair

_Captured: 2017-11-29 at 19:41 from [forum.digikey.com](https://forum.digikey.com/t/circuit-board-trace-repair/826?WT.z_sm_link=tfcircbrdrpr&utm_source=twitter&utm_medium=social&utm_campaign=tfcircbrdrpr)_

The other day I was tasked with a project from a co-worker of mine. He was given an older CB radio he said would not power up and wondered if I could have a look at it. I verified the symptom and sure enough, it was "dead" and did not power on as stated. So, off with the covers on the unit to see what's up. A pretty common problem I remembered would happen is the user would hookup the radio with reverse polarity. The design of the radio included a diode, who's operation was to provide reverse polarity protection. Basically if you hooked up the radio the wrong polarity, the diode would conduct (D23) and it would blow the 2 amp fuse (F201) in the power cord. This was a pretty typical circuit used for the power input.

![image](https://cdn-enterprise.discourse.org/digikey/uploads/default/original/2X/6/649b7a5a25417237058401fd93f08dee62ee81f9.jpg)

Naturally the fuse would blow, but the user would not always replace the fuse with the same current rating. Typically they would replace it with a higher current rating. So, with the radio still hooked up backwards for power, now instead of the fuse blowing, a circuit trace on the printed circuit board would blow. The result is as shown in the image below.

![_MG_8884](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/2X/4/47710c221636872136b37e5d756832c2cd6e7ea0_1_690x459.JPG)

Many times besides the copper trace being blown on the circuit board, the reverse polarity diode would also short out and would have to be replaced too. But in this case, we lucked out and the diode tested good in circuit.

So, now we have to fix this open trace. First step is go use a small precision screwdriver (blade type) to remove the coating on the copper trace on the board. Gently scrape away the coating on the trace to expose the bare copper as shown here.

![_MG_8887](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/2X/5/5037564a52c8b654ce4787bb1bc4285b9f2b2d05_1_690x459.JPG)

> _Clean both ends of the open trace._

![_MG_8889](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/2X/4/4f1a2974d46998d4edca7ce04668c6b1236aea18_1_690x459.JPG)

Now apply some [flux](https://www.digikey.com/short/q3fwrh) to prep the copper for tinning (which is simply a thin layer of solder on the copper pads)

![_MG_8890](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/2X/0/0d219b47198a690167c6382260b9c451a12e70d9_1_690x459.JPG)

Once you have the copper traces tinned, with a piece of solid wire (also referred to as [bus bar wire2](https://www.digikey.com/short/q3fw55)), solder one end of the wire to the first half of the open trace.

![_MG_8894](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/2X/b/bf67e73714b57c7995e6212cdce1f4c5e288e346_1_690x459.JPG)

> _And a little bend with a needle nose pliers to get it to line up with the other half of the trace…_

![_MG_8896](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/2X/e/ef2753912193fa6459a321e6c5ab917299ce72f2_1_690x459.JPG)

> _Solder the other end of the wire to the other half of the open pattern._

![_MG_8897](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/2X/8/85178f850b41cede66e9ed110fa06fa1cffaf34d_1_690x459.JPG)

> _Trim the wire back to the solder and clean with some flux remover 2 …_

![_MG_8903](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/2X/0/01c7a1aa6899d485eef3e67c001fcf098a6b1cd6_1_690x459.JPG)

> _And the repair is made_

![_MG_8904](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/2X/5/5a59468bd3b075381a01fed5beed9284ffcb2063_1_690x459.JPG)

Final step was to check if the radio worked, and it powered up after the repair. This procedure can be used anytime you have to repair a printed circuit board trace. Whether is a burned trace such as this, broken trace on a cracked board, or maybe even a trace you have lifted and broken in a repair attempt .
