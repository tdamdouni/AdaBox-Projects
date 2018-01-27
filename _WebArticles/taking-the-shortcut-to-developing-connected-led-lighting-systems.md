# Taking the Shortcut to Developing Connected LED Lighting Systems

_Captured: 2017-12-13 at 10:07 from [www.digikey.com](https://www.digikey.com/en/articles/techzone/2017/dec/taking-the-shortcut-to-developing-connected-led-lighting-systems?WT.z_sm_link=tzlgt&utm_source=twitter&utm_medium=social&utm_campaign=tzlgt)_

In the developed world, efficiency drives innovation. One area now undergoing significant change in the quest for increased efficiency is lighting. Solid-state lighting, predominantly in the form of semiconductor-based LEDs (although organic and polymer LEDs are emerging), continues to supplant conventional and less energy efficient forms of lighting such as incandescent, compact fluorescent and gas discharge lamps.

While LED lighting offers inherent energy savings, it can come at the cost of design complexity. The control circuitry needed to drive an LED light is, at best, an AC-DC converter, but typically will include some level of intelligent control. While this added complexity can potentially add cost, with careful design it is possible to produce an LED lighting solution that offers significant value at the right price point.

The end applications for LED lighting are virtually unlimited, from low level consumer to high bay industrial, kitchen cabinet, to street illumination. The prospect to include features such as intelligent dimming, connectivity and remote management makes the move to LED lighting a compelling argument, and one that continues to win over decision makers.

Developing a complete LED lighting solution involves the integration of several functions, including AC rectification with power factor correction (PFC), DC-DC conversion, and LED control. If connectivity is added to this list in order to offer a more future-proof solution, the design challenge increases further.

While LEDs are inherently more efficient than other forms of lighting, to preserve this benefit, every stage of the solution must also provide optimal efficiency. This is a major departure from developing a conventional lighting solution, but a necessary one. Another significant trend that has an impact on LED lighting is the move to digitally controlled power conversion. By including digital power in the overall topology, a more efficient and flexible solution can be achieved. If a fully digital approach is taken in the design process, it is possible to integrate a significant amount of the functionality into a smaller number of devices. Microcontrollers are ideally positioned to offer this level of functionality and flexibility.

While AC conversion is a major part of the solution, it is entirely feasible to operate several independent LED lighting circuits from a single DC supply, optimizing the overall design by using just one AC conversion stage. In this scenario, it becomes necessary to consider the remaining part of the solution separately, creating further possibilities for cost optimization through value-added features.

Adding control and connectivity to lighting installations is a significant development as it brings the ability to integrate lighting systems into a Building Management Systems (BMS), or as part of a smart home. One of the benefits of LED lighting is its robustness: lights can be dimmed or turned on/off much more often without impacting their working life or incurring surge currents. LED lights also offer greater flexibility in where they can be located, promoting more distributed installations and a wider range of operating conditions. All of these features increase the appeal of LED lighting but demand even greater levels of control.

In a bid to solve this design challenge, reference designs are emerging. While not available to purchase as a populated PCB, [Texas Instruments](https://www.digikey.com/en/supplier-centers/t/texas-instruments) has developed a fully tested DC-DC LED driver subsystem as a reference design, and has made all of the documentation (BOM, schematic, PCB Gerber) available. Figure 1 shows a block diagram of the reference design.

![Block diagram of Texas Instruments TIDA-01096 reference design](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/December/Taking%20the%20Shortcut%20to%20Developing%20Connected%20LED%20Lighting%20Systems/article-2017december-taking-the-shortcut-fig1.jpg?ts=d88b3124-2d87-4288-9bcd-0ee7e744385a&h=287&w=600&la=en-US)

> _Figure 1: Block diagram of the TIDA-01096 reference design._

The [TIDA-01096](http://www.ti.com/tool/TIDA-01096) is TI's high-efficiency, tunable white LED DC-DC driver with Bluetooth Smart connectivity reference design, which provides engineers with a full hardware and software platform for developing smart lighting solutions.

By combining both warm white and cool white LED strings in a single luminaire, it is possible to simulate daylight conditions for indoor lighting in residential and retail settings. The TIDA-01096 is intended for this application space and uses a number of advanced components to deliver 98% efficiency across a wide range of operating conditions.

Because this is intended to be a connected LED driver, one of the main differentiating features of the reference design is its connectivity, which takes the form of Bluetooth Smart. This is a function that is fully integrated into the MCU selected for the design, supported by software resources also developed by TI. Together with the other major components in the design, this provides a range of 'smart' features such as dimming, color temperature adjustment and daylight harvesting. Because the design is intended to control LED strings to simulate daylight, it can also be used to create a circadian rhythm, which has been shown to have health and wellness benefits.

Utilizing the ability of LEDs to produce variable levels of output requires an integrated solution. One such product is the [TPS92513/HV](https://www.digikey.com/product-detail/en/texas-instruments/TPS92513HVDGQT/296-42114-1-ND/5253915) 1.5 A buck LED driver with integrated analog current adjust; one of the main components in the reference design. When combined with the SimpleLink [CC2650](https://www.digikey.com/catalog/en/partgroup/cc2650/52359?mpart=CC2650F128RGZT&vendor=296) multi-standard MCU, it provides the perfect platform for developing intelligent LED lighting systems running from a regulated DC supply. The additional components in the design complete the picture, as explained below.

The TPS92513/HV LED driver has been developed for a range of high power lighting applications including streetlights, emergency lighting, and industrial and retail lighting, but is equally suitable for use in smaller appliances. As well as providing inputs for both analog and PWM control signals, it features an integrated N-channel high side MOSFET. Figure 2 shows a simplified schematic of how the device could be used.

![Simplified schematic of a typical application for the Texas Instruments TPS92513/HV LED driver](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/December/Taking%20the%20Shortcut%20to%20Developing%20Connected%20LED%20Lighting%20Systems/article-2017december-taking-the-shortcut-fig2.jpg?ts=37f5fe50-bb42-4441-b65c-7b645b0e90b7&h=231&w=400&la=en-US)

> _Figure 2: Simplified schematic of a typical application for the TPS92513/HV LED driver._

In the reference design, two devices are used for driving two LED strings. In this topology, the devices can be synchronized by using an external oscillator to override each device's internal oscillator. Operating multiple devices with the same clock source avoids undesirable effects such as frequency beating between LEDs on different strings, and can also help minimize the overall EMI of the design. The functional block diagram is shown in Figure 3.

![Functional block diagram of the Texas Instruments TPS92513/HV LED driver](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/December/Taking%20the%20Shortcut%20to%20Developing%20Connected%20LED%20Lighting%20Systems/article-2017december-taking-the-shortcut-fig3.jpg?ts=8d8406b5-0194-4c47-82e1-46578435a183&h=325&w=600&la=en-US)

> _Figure 3: Functional block diagram of the TPS92513/HV LED driver._

Synchronization is achieved by applying a square wave to the RT/CLK pin (pin 5), between 300 kHz and 2 MHz. The source of the internal MOSFET is on pin 10, labeled PH. Its rising edge is synchronized to the falling edge of the RT/CLK signal.

In the reference design, dimming can be achieved in three ways: through varying the analog input on the IADJ pin (pin 6); digitally, through a PWM signal applied to the PDIM pin (pin 4), or a combination of both. All control signals are produced by the SimpleLink CC2650 MCU (see Figure 4).

![Functional block diagram of the Texas Instruments SimpleLink CC2650 wireless MCU](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/December/Taking%20the%20Shortcut%20to%20Developing%20Connected%20LED%20Lighting%20Systems/article-2017december-taking-the-shortcut-fig4.jpg?ts=600cc867-5cc0-4fd3-8e05-73b4abe2eacd&h=516&w=400&la=en-US)

> _Figure 4: Functional block diagram of the SimpleLink CC2650 wireless MCU from TI._

Since analog dimming is more efficient, the reference design generates an analog signal by passing PWM signals through low-pass filters, which is then applied as an analog average of the PWM signal to the IADJ pin. The reference design also supports combined analog/PWM dimming control, and supports flicker free low LED current dimming using both analog and PWM methods.

Working closely with the LED driver, the SimpleLink CC2650 wireless MCU provides two key functions; the control signals for the driver, and the ability to influence those signals wirelessly. In this way it is possible to adjust the light output or color temperature from an application running on a smartphone, or allow a BMS to turn the lights off, on, up or down -- potentially using voice commands.

The possibilities are limited only by the imagination when using a connected system. Because the SimpleLink CC2650 is a multi-standard wireless MCU it can support Bluetooth, ZigBee and 6LowPAN. The powerful yet efficient ARM® Cortex®-M3 core offers the ability to include user applications running alongside the high layers of the chosen protocols stacks (the Bluetooth and ZigBee stacks are supplied free of charge by TI when using the CC2650). The RF part of the device also integrates an ARM Cortex-M0 core which handles a large part of the stack, as well as the interface between the baseband and analog front-end. It interfaces to the main CPU using an API, intended to further simplify design.

In addition to the LED driver and wireless MCU, the reference design includes the [OPT3001](https://www.digikey.com/catalog/en/partgroup/opt3001/51557?mpart=OPT3001DNPR&vendor=296) digital ambient light sensor, an optical sensor that closely matches the spectral response of the human eye. The inclusion of this sensor in the reference design supports the use case of adjusting the light output to deliver an environment tuned to human vision. By including the [LMT84](https://www.digikey.com/catalog/en/partgroup/lmt84/38403?mpart=LMT84DCKT&vendor=296) analog output temperature sensor attached to the LED heatsink, thermal runaway is avoided.

Figure 5 shows how the hardware for an LED lighting solution based on the reference design may be configured using TIDA-01096 paired with the [SimpleLink CC2650 LaunchPad](https://www.digikey.com/product-detail/en/texas-instruments/LAUNCHXL-CC2650/296-43750-ND/5844795). The firmware for the project has been developed by TI as a code composer studio project, and is available on request.

![Suggested hardware configuration using the TIDA-01096 reference design](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/December/Taking%20the%20Shortcut%20to%20Developing%20Connected%20LED%20Lighting%20Systems/article-2017december-taking-the-shortcut-fig5.jpg?ts=519f4cf6-0de8-49e8-866a-716440fb4abd&h=524&w=600&la=en-US)

> _Figure 5: Suggested hardware configuration using the TIDA-01096 reference design._

## Conclusion

Solid-state lighting has the potential to revolutionize the way we light our homes, offices, factories, transport hubs and public places. It offers significant cost benefits over incumbent lighting technologies.

Following significant investment from semiconductor manufacturers, there are now many products available that can help engineers design optimized solutions that maximize the potential of LED lighting. Increasingly, that includes adding connectivity in the form of wired or wireless communications.

Developing a full-featured, tunable LED lighting solution that includes wireless connectivity encompasses two potentially difficult design challenges, but thanks to the availability of development platforms and reference designs such as those featured in this article, meeting those challenges is now easier than ever.

Disclaimer: The opinions, beliefs, and viewpoints expressed by the various authors and/or forum participants on this website do not necessarily reflect the opinions, beliefs, and viewpoints of Digi-Key Electronics or official policies of Digi-Key Electronics.
