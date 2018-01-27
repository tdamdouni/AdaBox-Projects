# Using an ESP8266 to Announce Your Presence at the B&B

_Captured: 2017-11-15 at 17:24 from [blog.hackster.io](https://blog.hackster.io/using-an-esp8266-to-announce-your-presence-at-the-b-b-6303045f5cea)_

Emilio Pietro Giovanni Ficara had a unique problem at the bed and breakfast he's been staying at: the owner would often lock the front door, not realizing he was there. Ficara has been staying at the B&B for a while as he's been in town for contract work, but he's a quiet man. Unlike many other guests, he never turns on the TV or music, leading the owner to think he was out.

![](https://cdn-images-1.medium.com/freeze/max/60/1*tUA91ThnJhUF5fK35-JR8g.jpeg?q=20)![](https://cdn-images-1.medium.com/max/1600/1*tUA91ThnJhUF5fK35-JR8g.jpeg)

To solve this problem with a minimum of fuss, he set out to build [a simple LED indicator](http://ficara.altervista.org/?p=3744) that would announce his presence in the room. The device he came up with is devastatingly simple and very clever. A low-cost ATtiny2313 is paired with a similarly affordable [ESP8266-based ESP-01](https://www.hackster.io/esp). Where it gets clever is how the system determines if he's in the room.

Ficara is a cautious person, and never uses public WiFi hotspots. Instead, for [security and privacy](https://www.hackster.io/security), he uses his cell phone's hot spot function (which is limited to his preset MAC address list). Because he always has the phone on him, and the phone's hot spot is always active, his presence-detection device only has to check to see that hot spot's SSID is in range.

Every six seconds, the ATtiny2313 asks the ESP-01 to look for that SSID. If it finds it, then the module's LED is set to blink. If the network isn't found, then the LED stays off, and the B&B owner will know that Ficara is out. If you find yourself in a similar situation, [this is an inexpensive, low-power, and easy to build option](http://ficara.altervista.org/?p=3744) that doesn't require any [fancy IoT apps or platforms](https://www.hackster.io/home-automation).
