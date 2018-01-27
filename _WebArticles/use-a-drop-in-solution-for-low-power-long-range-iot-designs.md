# Use a Drop-In Solution for Low-Power, Long-Range IoT Designs

_Captured: 2017-09-29 at 20:12 from [www.digikey.com](https://www.digikey.com/en/articles/techzone/2017/sep/use-a-drop-in-solution-for-low-power-long-range-iot-designs?WT.z_sm_link=TZwrls)_

Contributed By Digi-Key's North American Editors

In many IoT applications, designers increasingly need devices capable of operating over a longer range but with lower power consumption. Normally, this would require matching low-power MCUs to transceivers and then developing the appropriate protocol stack. Fortunately, new solutions greatly reduce or even eliminate this extra work, speeding time to market and lowering costs.

The [SAM R30](https://www.digikey.com/product-detail/en/microchip-technology/ATSAMR30G18A-MUT/ATSAMR30G18A-MUTCT-ND/7164913) from [Microchip Technology](https://www.digikey.com/en/supplier-centers/m/microchip-technology) is one example of a solution that eliminates these detailed development steps by providing an optimized integration of MCU and transceiver in a single package. Used in combination with Microchip's MiWi protocol stack, the SAM R30 offers a near drop-in solution for low-power, long-range wireless IoT designs.

This article will discuss the key attributes of the SAM R30 and how developers can get up and running with it, quickly.

## Long-range IoT challenges

Long-range applications go well beyond those supported with more common wireless technologies such as Bluetooth or Wi-Fi. Also, these deployments carry a related requirement for multi-year battery life due to physical placement constraints or limited maintenance capabilities.

MCUs based on the 32-bit, ARM® Cortex®-M0+ core are typically relied upon to address the processing end of applications due to their combination of low power and high performance. By pairing these MCUs with sub-GHz transceivers, developers can create a solid foundation for IoT designs capable of operating over much longer ranges than practical with 2.5 GHz Bluetooth or Wi-Fi devices. For developers, however, integrating these devices into a low-power, long-range wireless solution can present multiple challenges.

At the hardware level, engineers must deal with sources of interference, such as switching noise, while maximizing processor performance and transceiver power output. In creating suitable software, engineers can also find themselves forced to develop low-level hardware abstraction layers needed for device support, protocol stacks, and IoT services.

## Simplified IoT wireless solution

To reduce the effort required, the Microchip Technology SAM R30 integrates an ultra-low-power MCU and sub-GHz radio transceiver in a 5 x 5 mm system-in-package (SiP) device. Because the SAM R30 handles the details of integration and radio optimization, designers need only a few additional components to implement a complete wireless solution (Figure 1).

![Diagram of Microchip Technology SAM R30 system-in-package \(click to enlarge\)](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/September/Use%20a%20Drop-In%20Solution%20for%20Low-Power%20Long-Range%20IoT%20Designs/article-2017september-use-a-drop-in-fig1.jpg?ts=6a425a08-be25-4e0b-9ee5-47c14240def6&la=en-US)

> _Figure 1: Because the Microchip Technology SAM R30 system-in-package integrates an MCU and sub-GHz transceiver, developers need only a few additional components to complete the design of a low-power, long-range wireless system. (Image source: Microchip Technology)_

Along with a primary VDD supply, developers can also add a VBAT battery power source, relying on the SAM R30's integrated automatic power switch to source device supply from VDD or VBAT as needed. By leveraging the SAM R30's extensive power management features, developers can create battery powered wireless IoT designs able to communicate over distances of up to a kilometer.

At the heart of the SAM R30, a Microchip ARM Cortex-M0+-based [SAM L21](https://www.digikey.com/products/en/integrated-circuits-ics/embedded-microcontrollers/685?k=SAM+L21&pv7=2&FV=ffe002ad&nstock=1) MCU integrates 256 Kbytes of flash, 40 Kbytes of SRAM, timers, GPIOs, standard digital interfaces, and analog peripherals required in typical IoT designs. In the interest of maximizing performance, however, Microchip made some modifications to the SAM L21 MCU used in the SiP. For example, to reduce noise interference with radio operations, the MCU included in the SAM R30 omits the switching regulator normally included in standard SAM L21 devices.

The SiP's Microchip [AT86RF212B](https://www.digikey.com/product-detail/en/microchip-technology/AT86RF212B-ZUR/AT86RF212B-ZURCT-ND/4805998) transceiver operates in standard sub-GHz bands from 769 to 935 MHz with -110 dBm receiver sensitivity and +10 dBm transmit power. Designers can use the IEEE 802.15.4 compatible radio to create standards-based wireless networks. Still, designers may prefer to use the device with Microchip's proprietary MiWi protocol, which leverages the device's support for an 802.15.4 variant to achieve low-power, extended range operation with a minimal software footprint.

## Flexible power management

For power sensitive designs, the SAM R30's MCU builds on the inherent low-power performance of the Cortex-M0+ core by providing a range of power saving features. In a typical design, the MCU can operate in active mode at power levels as low as 60 microamps (μA)/MHz, and consumes less than 500 nanoamps (nA) in a dormant state configured to wake on external signals.

Using the SAM R30, designers are not confined to these extremes of power and performance. The device provides developers with the ability to apply more finely tuned gradations in balancing power consumption and processor performance.

As with most advanced MCUs, the integrated SAM L21 offers low-power sleep states that allow developers to scale back power consumption by turning off the processor core during periods of inactivity. The SAM L21 MCU, however, offers another option that keeps the processor turned on, allowing developers to programmatically set the device to one of two active performance levels.

Designed to maximize energy efficiency, performance level 0 (PL0) lowers the core voltage to the minimum level needed to maintain a reduced CPU clock frequency of 12 MHz max, and a 24 MHz max generic clock (GCLK) used throughout the device. Along with lower performance, however, PL0 significantly reduces power consumption, requiring only 77 μA/MHz while running the CoreMark benchmark. Performance level 2 (PL2) is designed to provide maximum performance by supporting maximum clock frequency (48 MHz CPU clock and 96 MHz GCLK). Using PL2, power consumption increases accordingly, typically reaching 93 μA/MHz (CoreMark) or more.

For periods when the processor is not required, developers can place the device into one of four sleep modes - idle, standby, backup, and off. Although off mode completely shuts down the device, the other three sleep modes stop the processor core but maintain power to other blocks depending on the mode. For example, idle mode stops the core but maintains power to the rest of the MCU's functional blocks, resulting in power consumption of about 17 μA/MHz. In contrast, backup mode reduces power consumption to 1 μA or less by maintaining power only to the real-time clock (RTC), a clock source, and wake-up logic.

The final mode, standby, offers the greatest flexibility for dramatically reducing power consumption while retaining some key functional capability. In standby mode, developers can achieve the lowest level of power consumption that maintains logic and RAM state. In addition, standby mode supports power gating features that offer further power savings as described below.

Although a design based on the SAM R30 initially wakes up in PL0, developers can change performance level on the fly by setting the performance level select (PLSEL) bits in the performance level configuration (PLCFG) register when the device is in active mode. While operating at either performance level, developers can move the device between different sleep states as needed by setting the sleep mode (SLEEPMODE) bits in the sleep configuration (SLEEPCFG) register (Figure 2). On executing a wait-for-interrupt (WFI) instruction, the MCU then enters the specified sleep mode until an appropriate interrupt request (IRQ) signal wakes the processor.

![Diagram of SAM R30’s MCU](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/September/Use%20a%20Drop-In%20Solution%20for%20Low-Power%20Long-Range%20IoT%20Designs/article-2017september-use-a-drop-in-fig2.jpg?ts=42e63459-1201-492e-8a75-2769178fa54d&la=en-US)

> _SAM R30's MCU_

_Figure 2: Although the SAM R30's MCU initially comes up at its lower performance level (PL0), developers can programmatically modify power consumption on the fly by adjusting the performance level in active mode (horizontal) or by setting the sleep stage (vertical). (Image source: Microchip Technology)_

## Power domains and response latency

Although performance levels and sleep states each impact power consumption, the mechanisms used in each case are significantly different. Performance levels achieve their effects by scaling operating frequency and core supply voltage (VDDCORE), both of which result in reduced current draw.

In contrast, sleep states shut down device circuitry grouped into distinct power domains (Figure 3). For example, the "backup" power domain, PDBACKUP, contains the power manager module and essential circuits such as the RTC needed to wake the MCU. PDBACKUP is always on, except of course when the entire device is turned off (off sleep state). Thus, the backup sleep state is simply that minimal functional state enabled by the backup power domain.

![Diagram of SAM R30’s internal SAM L21 MCU](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/September/Use%20a%20Drop-In%20Solution%20for%20Low-Power%20Long-Range%20IoT%20Designs/article-2017september-use-a-drop-in-fig3.jpg?ts=bcf63260-8c66-486e-968d-3f8dcc91444b&la=en-US)

> _Figure 3: The SAM R30's internal SAM L21 MCU groups its functional elements into distinct power domains that enable a finer degree of control over power consumption. (Image source: Microchip Technology)_

Conversely, at the top of the power hierarchy, PD2 includes critical system blocks including the Cortex-M0+ core, non-volatile memory (NVM) controller, and SRAM. PD1 is the intermediate power domain, containing serial communications, crypto, and direct memory access (DMA), among others.

At the bottom of the power domain hierarchy, PD0 contains controllers for MCU clocks and oscillators as well as peripherals and logic used to wake the processor. Along with digital interfaces, this domain includes most of the MCU's analog blocks including op amp, compare/capture (CC) channels, analog-to-digital converter (ADC), and analog comparator (AC). As described below, this grouping provides substantial power savings while enabling the function of peripherals typically required for IoT applications.

Within the power domain hierarchy defined by PD2, PD1, and PD0, any activity that switches on a particular power domain also activates the power domain(s) below it in the hierarchy. For example, turning on PD2 also switches on PD1 and PD0. As with any advanced MCU, this sequential restoration of power naturally requires more time to complete the deeper the sleep state - and consequently the more power domains that need to be activated (Figure 4).

![Image of waking from a low-power standby mode](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/September/Use%20a%20Drop-In%20Solution%20for%20Low-Power%20Long-Range%20IoT%20Designs/article-2017september-use-a-drop-in-fig4.jpg?ts=a2c3133a-8abb-4c51-bb34-bbaa8b59c1ff&la=en-US)

> _Waking from a low-power standby mode_

_Figure 4: In waking from a low-power standby mode due to an interrupt (IRQ), the device activates its power domains sequentially. As a result, the time between an interrupt and execution of the first instruction in an interrupt handler can become quite extended in deep sleep states. (Image source: Microchip Technology)_

In the SAM R30, the transition from the off state to the active state can take over 2 milliseconds (ms). Sleep states with more active power domains take correspondingly less time: The SAM R30 MCU in its default configuration needs only 76 μs to wake from standby to PL2, or just 5.1 μs to wake from standby to PL0. Because the idle state keeps everything but the CPU active, transitioning from idle state to active (either PL0 or PL2) takes only 1.2 μs.

The specific nature of the wake-up process can be of critical importance to an IoT developer. Extended wake up time results in "wasted" power consumed during the process. Consequently, developers need to balance power savings achieved by placing the MCU in a deep sleep state against power lost to the wake-up process.

The effects of wake-up time can be more acute for applications with specific real-time requirements. For these applications, an extended wake-up time means an overall coarser granularity of time-based measurements. If the application requires minimal latency between event and response, longer wake-up times at the hardware level can present additional challenges for streamlining interrupt handlers at the software level to meet tight requirements for response latency.

Fortunately, the SAM L21 MCU used in the SAM R30 provides a power management feature, called SleepWalking, which offers an alternative to these large excursions between dormant and functionally active states. When the MCU is in standby mode, SleepWalking lets some peripherals wake from standby to respond to external events without requiring the MCU to initiate a full wake-up cycle. The MCU's power manager achieves this special operating mode by limiting power to the lowest level of the power domain hierarchy for the required peripheral.

Unlike performance levels or sleep modes, the developer does not explicitly set the required power domains associated with SleepWalking. When operating in standby sleep mode, the MCU power architecture automatically activates the required power domains to achieve this effect. As a result, the developer gains a more functional view of the process, focusing on defining the conditions and setting the registers that trigger the associated peripheral, and cause the MCU to automatically engage the SleepWalking mechanism.

The MCU's ability to automatically activate only a subset of its power domains results in significant power savings. In standby mode with 1.8 V operation, the MCU consumes only 11.3 μA with PD2, PD1, and PD0 active. When PD1 and PD0 are held active but only PD2 is turned off, current drops down to 5.94 μA because PD2 includes some of the MCU's most active circuit blocks including the Cortex-M0+ core and SRAM.

By turning off the last two power domains, current consumption continues to drop but not as dramatically. With PD1 turned off but PD0 held active, current drops to 3.94 μA. When PD0 is also turned off, current consumption drops to 3.44 μA.

When all three domains (PD2, PD1, and PD0) are turned off in standby mode, the resulting very-low-power standby mode differs from backup mode only in maintaining power to the PDTOP domain, which includes the watchdog timer (WDT), external interrupt controller (EIC), and I/O pin controller (PORT). In contrast, PD0 includes many of the blocks required for basic IoT functionality as mentioned earlier. Consequently, the device can even perform typical signal sampling operations while maintaining the lowest possible standby state (PD2, PD1, and PD0 off), turning on PD0 only periodically to power the required analog peripheral (Figure 5).

![Image of SAM R30’s MCU SleepWalking feature](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/September/Use%20a%20Drop-In%20Solution%20for%20Low-Power%20Long-Range%20IoT%20Designs/article-2017september-use-a-drop-in-fig5.jpg?ts=50f94abf-c355-46ec-ac26-ab5febfc4f6b&la=en-US)

> _Figure 5: In standby mode, the SAM R30's MCU can use its SleepWalking feature to power up only the power domain associated with a required peripheral, such as the ADC or analog comparator located in PD0, resulting in significant overall power savings without comprising function. (Image source: Microchip Technology)_

## Simplified wireless

This combination of simplified design and sophisticated capability also extends to the wireless communications functionality of the SAM R30. As with the MCU's power management features, developers can easily take advantage of the SAM R30's long-range wireless capabilities. By integrating the SAM L21 MCU and the AT86RF212B sub-GHz transceiver, the SAM R30 SiP eliminates the design challenges that developers often encounter in optimizing RF performance and coping with sources of interference between digital and RF domains.

Using the SAM R30 SiP, developers can quickly implement a wireless system with minimal additional components as noted earlier. At the same time, the SAM R30 supports more sophisticated wireless configurations for antenna diversity or extended range operation.

Built into the AT86RF212B transceiver, an RF control module provides control signals for managing the RF switches used to implement antenna diversity, or for switching the RX and TX signals respectively through a low-noise amp (LNA) or power amp (PA). The SAM R30 brings these RF control signals out, allowing developers to extend their wireless systems with a custom signal path or an off-the-shelf RF front-end module (Figure 6).

![Diagram of SAM R30 RF signal control outputs](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/September/Use%20a%20Drop-In%20Solution%20for%20Low-Power%20Long-Range%20IoT%20Designs/article-2017september-use-a-drop-in-fig6.jpg?ts=44be9867-446f-4abb-b220-01bdf398cc22&la=en-US)

> _Figure 6: Using SAM R30 RF signal control outputs to manage an RF front-end module, designers can easily extend the base SAM R30 application design to implement antenna diversity or to boost transmitter power and radio sensitivity. (Image source: Microchip Technology)_

Within the SiP, the SAM L21 MCU connects to the transceiver through a simple interface that combines a conventional SPI interface with a few additional control signals. For developers, the transceiver appears simply as a dedicated device managed by familiar SPI sequences or MCU port register manipulations.

This simple view of the transceiver translates into a correspondingly basic operating model (Figure 7). Here, software commands delivered through the SPI interface manage basic TX and RX operations, while IC port signals place the transceiver in different power states including sleep and a low-power RX listen state.

![Image of software running on the SAM R30 MCU](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/September/Use%20a%20Drop-In%20Solution%20for%20Low-Power%20Long-Range%20IoT%20Designs/article-2017september-use-a-drop-in-fig7.jpg?ts=e39faeeb-c325-42fc-88b8-670bd99e10c4&la=en-US)

> _Figure 7: Software running on the SAM R30 MCU uses the common SPI bus to manage communications through the transceiver or uses MCU I/O ports to control transceiver power states. (Image source: Microchip Technology)_

Of course, developers will not find themselves forced to operate the transceiver at the SPI command level or I/O register level. Instead, developers using the SAM R30 can take advantage of the software compatibility of the internal SAM L21 MCU and AT86RF212B transceiver with higher level software from Microchip or third-party sources. Functions within Microchip's software library provide intuitive abstractions that handle the underlying SPI commands and I/O port manipulation (Listing 1).

`...`

`/*************************************************************************/ /**`

`*****************************************************************************/`

`// Radio Initialization`

`void PHY_Init(void)`

`{`

`    trx_spi_init();`

`    PhyReset();`

`    phyRxState = false;`

`    phyWriteRegister(RG_IRQ_MASK, 0xFF);`

`    do {`

`        phyWriteRegister(RG_TRX_STATE, TRX_CMD_TRX_OFF);`

`    } while (TRX_STATUS_TRX_OFF != (phyReadRegister(RG_TRX_STATUS) & TRX_STATUS_MASK));`

`    phyWriteRegister(RG_TRX_CTRL_1,`

`        (1 << TX_AUTO_CRC_ON) | (3 << SPI_CMD_MODE) | (1 << IRQ_MASK_MODE));`

`    phyWriteRegister(RG_TRX_CTRL_2,`

`        (1 << RX_SAFE_MODE) | (1 << OQPSK_SCRAM_EN));`

`...`

`/*************************************************************************/ /**`

`*****************************************************************************/`

`// Radio Sleep`

`void PHY_Sleep(void)`

`{`

`    phyTrxSetState(TRX_CMD_TRX_OFF);`

`    TRX_SLP_TR_HIGH();`

`    phyState = PHY_STATE_SLEEP;`

`/*************************************************************************/ /**`

`*****************************************************************************/`

`// Radio Wake Up`

`void PHY_Wakeup(void)`

`{`

`    TRX_SLP_TR_LOW();`

`    phySetRxState();`

`    phyState = PHY_STATE_IDLE;`

`}`

`...`

_Listing 1: As illustrated in this snippet from the Microchip [P2P/Star Network Stack](http://ww1.microchip.com/downloads/en/DeviceDoc/MiWi_P2P_StarV1.0.zip) source, developers maintain a high-level, functional view of transceiver operations that ultimately use SPI-based command sequences (e.g., `PHY_Init`) or I/O port operations (e.g., `PHY_Sleep` and `PHY_Wakeup`) indicated in the transceiver state diagram. (Code source: Microchip Technology)_

Along with standard 802.15.4 based protocol stacks, developers can use the SAM R30 with Microchip's free MiWi protocol. The proprietary MiWi protocol uses a simplified variant of 802.15.4 to deliver an efficient wireless communications protocol for applications that require the extended range and battery life. Using Microchip's MiWi development environment, developers can implement a complete peer-to-peer networking solution with a code footprint of only a few thousand bytes. The MiWi stack occupies only 4 Kbytes.

For hardware development, the Microchip [SAM R30 Xplained Pro](https://www.digikey.com/product-detail/en/microchip-technology/ATSAMR30-XPRO/ATSAMR30-XPRO-ND/6217839) evaluation kit provides a fully realized implementation of a wireless system based on the SAM R30. Developers can immediately begin examining SAM R30 operation simply by plugging the eval board into a USB slot on a Windows-based system running the free [Atmel Studio](http://www.atmel.com/tools/atmelstudio.aspx) development system. For hardware developers looking to build on the eval board base design, Microchip provides a full set of schematics and manufacturing files in its associated [reference design](http://ww1.microchip.com/downloads/en/DeviceDoc/SAMR30%20Xplained%20Pro%20Design%20Documentation.zip).

## Conclusion

Designers have traditionally faced significant challenges in optimizing power and performance for long-distance IoT wireless designs. Using the Microchip Technology SAM R30, designers can instead take advantage of an optimized system-in-package solution that handles the integration of a low-power 32-bit MCU and a sub-GHz transceiver in an optimized design. As a result, developers need only combine the SAM R30 with a few additional components to create wireless systems able to meet requirements for maximum range and minimal power consumption.

Disclaimer: The opinions, beliefs, and viewpoints expressed by the various authors and/or forum participants on this website do not necessarily reflect the opinions, beliefs, and viewpoints of Digi-Key Electronics or official policies of Digi-Key Electronics.
