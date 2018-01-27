# Measure Power Supply Noise by probe

_Captured: 2017-11-15 at 10:28 from [forum.digikey.com](https://forum.digikey.com/t/measure-power-supply-noise-by-probe/560?WT.z_sm_link=tfpwrsupnoise&utm_source=twitter&utm_medium=social&utm_campaign=tfpwrsupnoise)_

Switching power supply creates its own undesired noise, usually at harmonic of switching frequency or coherent to the switching frequency. Due to the wide bandwidth of power supply noise, an oscilloscope is often the perferred measurement tool and using an oscilloscope to measure requires a special attention.

Measurement of the noise by probe is performed as close as possible to the power supply output terminals. This can reduce the radiated noise received. The main measurement error is usually come from the unshielded portion of the probe.

To reduce the measurement error, an unsheilded leads must keep as short as possible. Below figure shows an incorrect method, because the ground wire of proble will collect the radiated noise. The oscilloscope display is dependent on the probe position and the ground lead length.

![incorrect](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/1X/d384712bf9f0584c940fd9710e58946fd0624436_1_690x289.JPG)

[ incorrect.JPG750x315 15.2 KB](https://cdn-enterprise.discourse.org/digikey/uploads/default/original/1X/d384712bf9f0584c940fd9710e58946fd0624436.JPG)

So before measurement, please remove the clip-on ground wire and the probe body fishhook adapter firstly. Then a special tip and ground lead assembly are attached as below figure.

![Correct](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/1X/0e513fa2f7a5d623f343244e1c3137b9dc837595_1_690x224.JPG)

[ Correct.JPG759x247 12.4 KB](https://cdn-enterprise.discourse.org/digikey/uploads/default/original/1X/0e513fa2f7a5d623f343244e1c3137b9dc837595.JPG)

Afterward, the ground ring of the probe is pressed directly against the output ground of the power supply and the tip is in contact with the output voltage pin of power supply.
