# Want a Temperature-Controlled Cordless Soldering Iron? Here’s How to Make One

_Captured: 2017-11-05 at 14:19 from [spectrum.ieee.org](https://spectrum.ieee.org/geek-life/hands-on/want-a-temperaturecontrolled-cordless-soldering-iron-heres-how-to-make-one)_

![f1](https://spectrum.ieee.org/image/Mjk2NzY3MA.jpeg)

> _Photo: Randi Klett_

**When I first learned to solder,** I did so using a cheap iron, not realizing how atrocious such things are. It wasn't until several years later that I purchased a temperature-controlled soldering station. These use thermal feedback to keep the tip at a set temperature, and I soon learned that good solder joints are easy to make when you have good equipment. I've had that very same Weller WTCPN soldering station for almost four decades now, having forsaken non-temperature-controlled irons completely.

This stance on soldering irons did, however, put me in a quandary recently when I started to explore the options for cordless soldering irons. Cordless irons are essential for those times when you need to solder something and there's no power outlet available. Yet I could not find a cordless iron for sale that had temperature control. So I figured I'd build myself one.

My fondness for my faithful Weller soldering station dictated the first design criterion--it had to provide the same quality temperature control--and also suggested a strategy to attain that goal: [Weller's Magnastat system](https://neurophysics.ucsd.edu/Manuals/Weller%20Tech/Weller%20Tech%20Sheet%20WTCPR.pdf) [PDF]. Let me explain. Weller long ago devised a clever way to provide temperature feedback and control without using any electronics. It's based on the physics of ferromagnetic materials, which lose their magnetism when heated above a certain temperature, known as the [Curie point](https://en.wikipedia.org/wiki/Curie_temperature). Weller's Magnastat system uses three magnetic components near the tip: two inside a normally open switch, the other built into the tip itself. The components inside the switch (one movable) have a very high Curie point, whereas the one in the tip has a Curie point equal to the desired soldering temperature.

When the iron is cold, a movable permanent magnet in the switch is drawn to the ferromagnetic tip, closing the switch and sending power to the heating element. The tip then gets hot. When the magnet in the tip exceeds its Curie temperature and loses its magnetism, the movable magnet shifts toward the fixed one in the switch, causing the switch to open and shutting off power. When the tip cools below its Curie point, it is magnetized by virtue of the field from the nearby movable magnet, which is then drawn to it, closing the switch and reapplying power. Presto--temperature feedback!

![img](https://spectrum.ieee.org/image/Mjk2NzI2NA.jpeg)

> _Photo: David Schneider_

For my cordless iron, I duplicated this system by ordering some Magnastat replacement parts from Mouser Electronics: the [magnetic switch](http://www.mouser.com/search/ProductDetail.aspx?r=578-SW60), the [heating element](http://www.mouser.com/search/ProductDetail.aspx?r=578-TC208), a [tip](http://www.mouser.com/search/ProductDetail.aspx?r=578-PTR8), and the [barrel](http://www.mouser.com/search/ProductDetail.aspx?r=578-PTR8) used to hold the tip on. The challenge was to supply the tip with 24 volts or so. My Weller soldering station contains a massive transformer that runs off a wall socket, whereas my cordless iron would obviously need to run off batteries.

You could easily take an entire Magnastat soldering iron and power it with a couple of 12-volt lead-acid batteries. But I was aiming for something more portable. That's when it occurred to me to package my cordless iron into another piece of equipment I'm fond of: a Maglite flashlight.

Maglites are made of nicely machined and anodized aluminum with attractive knurling. I purchased a [non-LED, two-D-cell model](https://www.amazon.com/Maglite-Heavy-Duty-Incandescent-2-Cell-Flashlight/dp/B00002N6SG/ref=sr_1_fkmr0_1?ie=UTF8&qid=1503935501&sr=8-1-fkmr0&keywords=maglite+incandescent+flashlight+2D) at a nearby hardware store and took it apart, which required purchasing a [replacement switch](https://www.amazon.com/Maglite-108-000-208-Switch-Assembly-Lights/dp/B00D79O430) for the flashlight so I could get the needed Torx wrench.

Of course, two D batteries would provide only a meager 3 volts. But this flashlight offers sufficient space for six 14500 lithium-ion cells, which together can provide about 22 volts. After considerable digging, I found a source for [a three-cell holder](https://picclick.com/3-AA-SERIAL-45-Volt-Battery-Adapter-112288517154.html) for AA batteries that puts them in series and is about the size of a D battery. So all I needed to do was to purchase two such holders and outfit them with 14500 lithium-ion rechargeable batteries, which are about the size of AA cells.

The difficulty here is that I wanted to use protected lithium-ion cells. These have a little bit of circuitry built in that handles problems like overcharging or short circuits, which can cause lithium-ion batteries to do unpleasant things, like bursting into flame. These cells tend to be a little long because the protection circuit awkwardly adds to their length. (Flashlight enthusiasts, it seems, run into this problem a lot.) My solution was to purchase six [Xtar cells,](http://www.batteryjunction.com/xtar-14500-800.html) which are a little shorter than most 14500s. I was happy I did that because they fit into my holders perfectly.

![img](https://spectrum.ieee.org/image/Mjk2NzY4NQ.jpeg)

> _Photo: David Schneider_

These 800-milliampere-hour cells are nominally rated for only 1.6 amperes, but that's the most they'd need to supply for all but perhaps a few tens of seconds in a charge cycle. And [a very helpful online reviewer](http://lygte-info.dk/review/batteries2012/Xtar%2014500%20800mAh%20\(Black\)%20UK.html) showed that their protection circuits don't kick in until almost 3 A, which is higher than my soldering iron would ever need.

Usually packaging a DIY gizmo is the hardest part. But marrying the Weller Magnastat technology with a Maglite flashlight proved remarkably easy. It required drilling just five holes into two [aluminum disks](http://www.ebay.com/itm/1-16-0625-Aluminum-Disc-x-2-Diameter-5052-Aluminum-Circle-Round-/201988322936?hash=item2f07713678:g:5XoAAOSwDNdVqZN3) purchased on eBay for US $1 each. The disks take the place of the clear plastic lens of the flashlight and provide a sturdy and heat-insensitive surface onto which to mount the heating element. All that was left was to make four solder connections (to the flashlight contacts and a [5-A fuse](http://www.mouser.com/search/ProductDetail.aspx?r=576-0287005%2eH)), connect the Magnastat components with wire nuts, and put the disassembled flashlight back together. I turned it on, and soon made a perfect solder joint with my new cordless iron.

_This article appears in the November 2017 print issue as "A DIY Soldering Iron for Tinkering on the Go."_
