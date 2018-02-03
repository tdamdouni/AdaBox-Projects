# Measuring AC Current and Sending Data via MQTT

_Captured: 2018-02-02 at 12:57 from [www.hackster.io](https://www.hackster.io/brijn/measuring-ac-current-and-sending-data-via-mqtt-062c79?utm_source=Hackster.io+newsletter&utm_campaign=994f82f734-EMAIL_CAMPAIGN_2017_07_26&utm_medium=email&utm_term=0_6ff81e3e5b-994f82f734-141949901&mc_cid=994f82f734&mc_eid=1c68da4188)_

![Measuring AC Current and Sending Data via MQTT](https://hackster.imgix.net/uploads/attachments/412708/2018-01-27_23_07_38_tK8F6dJYxe.jpg?auto=compress%2Cformat&w=900&h=675&fit=min)

We own an off-grid cabin that uses a mix of solar and generator power. The solar system has it's own set of monitoring bits (to be documented in another project), This one focusses on just the generator side of things. We actually have two generators:

  * 20 kW diesel generator with remote start
  * Honda EU2000 portable generator

To run small loads and charge the batteries we use the 120V portable generator. When we want to user the larger (wood and metalworking) tools in the garage we start the big 240V diesel generator.

To measure and track the use the use and total power generation of both generator I decided to build this IoT device.

I was also an excuse for the dive into IoT and to learn Python.

As mentioned, we have one (large) 240V diesel generator. The maximum current product is 70A @ L1 (120V) and 70A @ L2 (120V), for a total of 70A @ 240V (or 20kW).

The small generator produces max 15A @ L1 (120V), for a total of 2kW. To measure all of this I purchased a 3-channel sensor board with 70A current clamps. There is a manual interlock the determines what generator is actually feeding the system (as you can see in some of the pictures)

As an early Linux adopter, I really like the Onion Omega boards. They are inexpensive ($10), have build in storage (can be extended), WiFi and run a "full" linux stack. Onion sells several boards that can be added to provide additional functions (relays, ethernet, mini display etc), but most of my sensors are purchased from NCD.IO. I use the I2C interface on the Onion Omega to connect the sensor. The code that [NCD.IO](http://ncd.io/) provides has seen little testing on the Omega's, I've posted my updated code in the linked Github repository.

![](https://hackster.imgix.net/uploads/attachments/412710/components_aXUTxgVGKq.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

> _The main components in the project_

The AC sensor board requires a 12V supply, the Onion Omega is powered via the [NCD.IO](http://ncd.io/) I2C board with a mini USB (5V). The parts bin had a cheap ebay 12/24/48V-5V converter. I could have purchased a much smaller converter, but this is what I had.

A lockable DC barrel plug is used to feed the 3.5x4.5" Hammond project box that contains the small pile of electronics.

![](https://hackster.imgix.net/uploads/attachments/412709/2018-01-27_18_45_59_bROH9p1qOx.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

> _The DIY USB plugs are a pain to solder (and not mechanically strong)_

The Hammond project box is just a little bit to small. So some extra trimming and pushing is required to fit everything in. But it did fit in the end.

![](https://hackster.imgix.net/uploads/attachments/412711/2018-01-27_22_12_01_rsbQWl9NdC.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

> _With a bit of pushing it did all fit in_

Using the Cricut vinyl cutter to add some final details (labelling the box and the current sensors with their respective channels) and it all looks nice!

![](https://hackster.imgix.net/uploads/attachments/412712/2018-01-27_23_07_38_ST9nz6D7ca.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

> _Everything together and tested_

Some small python code reads the sensor data and pushed it out via MQTT to the Losant IoT platform. Since the Internet is not always available, it will cache data locally and push out to Internet when it becomes available. For a local user interface, the data is also pushed to a local NODE-RED install.
