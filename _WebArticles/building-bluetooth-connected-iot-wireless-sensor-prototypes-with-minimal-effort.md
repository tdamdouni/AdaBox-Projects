# Building Bluetooth-Connected IoT Wireless Sensor Prototypes with Minimal Effort

_Captured: 2017-09-13 at 20:37 from [www.digikey.com](https://www.digikey.com/en/articles/techzone/2017/jul/building-bluetooth-connected-iot-wireless-sensor-prototypes?WT.z_sm_link=TZIoTSNSR)_

As users become more familiar with applications for the Internet of Things (IoT), developers need to respond to emerging opportunities quickly with fully functional prototypes able to prove out new concepts or competitive products. Yet, most IoT development solutions require significant effort to get them working correctly, particularly on the software side.

To accelerate the process, developers need an IoT development solution able to eliminate many of the existing hurdles that slow response times to opportunities for new IoT applications. A rapid development kit from [Nordic Semiconductor](https://www.digikey.com/en/supplier-centers/n/nordic-semiconductor) meets this need with a full hardware/software solution for Bluetooth-connected wireless sensor designs.

This article will discuss design requirements, introduce a suitable Bluetooth wireless solution, and guide developers on how to get it up and running relatively quickly.

## Wireless IoT device requirements and solution options

As the data source for high-level IoT applications, wireless sensor systems need to satisfy a wide range of complex requirements. Among those requirements, expectations for Bluetooth connectivity continues to rise, along with user expectations for easy IoT monitoring and control through smartphone apps. Semiconductor manufacturers have responded to this growing demand with an array of solutions including Bluetooth transceiver ICs, modules, and system-on-chip (SoC) devices.

While each solution addresses different classes of application requirements, Bluetooth SoCs have emerged as a particularly attractive solution for wearables and tiny IoT devices. By integrating a Bluetooth communications subsystem, these devices offer a combination of reduced BOM, small footprint, and minimal power without compromising functionality and performance.

Among devices in this class, the Nordic Semiconductor [nRF52832](https://www.digikey.com/products/en/rf-if-and-rfid/rf-transceiver-ics/879?k=NRF52832+AA&pv7=2) Bluetooth SoC integrates a processor core and radio subsystem with a flexible software architecture designed to simplify development of wireless systems.

## Wireless MCU

Based on a 32-bit ARM® Cortex®-M4F core, the Nordic nRF52832 features an embedded 2.4 GHz transceiver able to support standard protocols including Bluetooth low energy (BLE) and ANT, as well as proprietary protocols. Among its peripherals, the device integrates analog comparators and an 8-channel programmable gain 12-bit analog-to-digital converter (ADC), as well as three real-time counters (RTCs), 32 GPIOs, multiple pulse width modulator (PWM) channels, and serial interfaces.

An on-chip programmable peripheral interconnect (PPI) matrix enables these peripherals to synchronize their activity, interacting directly or through direct memory access (DMA) without processor intervention. In addition, the device integrates multiple hardware blocks for high-level functions including quadrature decoding, AES crypto, and accelerated address resolution for Bluetooth crypto services, among others.

The device consumes 58 μA/MHz running from its 512 Kbyte flash memory or 51.6 μA/MHz running from its 64 Kbyte RAM. Multiple low-power modes enable developers to reduce power when the application is inactive. For example, the device consumes only 1.5 μA in a low-power idle state where the device retains full RAM state and is able to wake on any event. In fact, developers can place the device in a special constant-latency sub-mode that ensures a constant, minimal time for CPU wakeup and PPI subsystem response. Using its flexible operating modes, peripherals, and on-chip hardware blocks, developers can program the nRF52832 to meet specific combinations of requirements for power, performance, and functionality.

## Communications services

For all its integrated capabilities, one of the most distinguishing features of the nRF52832 and other members of the Nordic [nRF52 family](https://www.digikey.com/products/en/rf-if-and-rfid/rf-transceiver-ics/879?k=nrf52&pv7=2&FV=ffe0036f) is their communication services architecture. Nordic introduced its SoftDevice architecture in earlier wireless SoC families as a way of reducing the friction developers experience in using communication protocol stacks.

Implemented as updatable firmware, the SoftDevice architecture simplifies software development by providing a pretested layer of services that programmers can leverage without complicating their own development process. For BLE applications, Nordic's S132 SoftDevice provides a complete Bluetooth protocol stack (Figure 1).

![Diagram of Nordic Bluetooth SoftDevice](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/July/Building%20Bluetooth-Connected%20IoT%20Wireless%20Sensor%20Prototypes/article-2017july-building-bluetooth-connected-fig1.jpg?ts=a39d7703-e250-465f-9f90-9d328ea98b21&la=en-US)

> _Nordic Bluetooth SoftDevice_

_Figure 1: The Nordic Bluetooth SoftDevice implements a full Bluetooth protocol stack as firmware, providing a full set of services without requiring developers to link a protocol stack library to their application. (Image source: Nordic Semiconductor)_

More than a simple layer of software, a SoftDevice uses a sophisticated interrupt-based model that allows developers to use SoftDevice services without linking SoftDevice code into their applications during development. Developers simply access the SoftDevice application programming interface (API) using a series of Supervisor Calls (SVC) defined in a set of C language API header files.

SVCs are implemented as software-triggered interrupts, so when developers call an API function, the SoftDevice SVC interrupt handler locates the correct SoftDevice function and passes the function parameters to it, using callbacks to return results. This approach eliminates the need to link SoftDevice resource addresses at build time, while also providing a thread-safe service implementation.

To realize this model, Nordic ties the SoftDevice into lower-level interrupt mechanisms and hardware resources. Lower-level interrupts bubble up to the SoftDevice, which uses a reserved IRQ to pass application specific interrupts up to the application, and handles the remaining interrupts itself. In addition, as part of its service responsibilities, the SoftDevice directly accesses device hardware including the radio and other peripherals.

To avoid possible contention for shared hardware resources, Nordic provides a timeslot feature that schedules resource allocation between the SoftDevice and the application during defined time intervals. Applications can request the earliest possible timeslot or one at a given time. Despite the underlying complexity of this mechanism, Nordic's API reduces the application's burden to a few high-level calls. For example, an application might start a beacon by opening a radio session (Listing 1) with a callback (Listing 2) for the actual advertising operations. During each pass, the callback increments a simple enum type (Listing 3) to step through a series of states until the advertising process completes (`mode == ADV_DONE`).

`void app_beacon_start(void)`

`{`

`    if (m_beacon.is_running || m_beacon.keep_running)`

`    {`

`        return;`

`    }`

`    DEBUG_PRINTF(0, "app_beacon_start:\r\n");`

`    m_beacon.keep_running = true;`

`    m_beacon.is_running   = true;`

`    uint32_t err_code = sd_radio_session_open(m_timeslot_callback);`

`    if ((err_code != NRF_SUCCESS) && (m_beacon.error_handler != NULL))`

`    {`

`        m_beacon.error_handler(err_code);`

`    }`

`    err_code = m_request_earliest(NRF_RADIO_PRIORITY_NORMAL);`

`    if ((err_code != NRF_SUCCESS) && (m_beacon.error_handler != NULL))`

`    {`

`        m_beacon.error_handler(err_code);`

`    }`

`}`

_Listing 1: The [Thingy software package](https://github.com/NordicSemiconductor/Nordic-Thingy52-FW) includes sample routines such as `app_beacon_start`, which demonstrate interactions with the SoftDevice to create a radio session with a specific callback (__`m_timeslot_callback`) and to request the earliest available radio timeslot for beacon transmission (__`m_request_earliest`). (Code source: Nordic Semiconductor)_

`static nrf_radio_signal_callback_return_param_t * m_timeslot_callback(uint8_t signal_type)`

`{`

`  static nrf_radio_signal_callback_return_param_t signal_callback_return_param;`

`  static enum mode_t mode;`

`  signal_callback_return_param.params.request.p_next  = NULL;`

`  signal_callback_return_param.callback_action        = NRF_RADIO_SIGNAL_CALLBACK_ACTION_NONE;`

`  switch (signal_type)`

`  {`

`    case NRF_RADIO_CALLBACK_SIGNAL_TYPE_START:`

`      m_handle_start();`

`      mode = ADV_INIT;`

`      mode++;`

`      break;`

`    case NRF_RADIO_CALLBACK_SIGNAL_TYPE_RADIO:`

`      if (NRF_RADIO->EVENTS_DISABLED == 1)`

`      {`

`        NRF_RADIO->EVENTS_DISABLED = 0;`

`        m_handle_radio_disabled(mode);`

`        if (mode == ADV_DONE)`

`        {`

`            DEBUG_PRINTF(0, "app_beacon_adv_done:\r\n");`

`            NRF_PPI->CHENCLR = (1 << 8);`

`            if (m_beacon.keep_running)`

`            {`

`                signal_callback_return_param.params.request.p_next = m_configure_next_event();`

`                signal_callback_return_param.callback_action       = NRF_RADIO_SIGNAL_CALLBACK_ACTION_REQUEST_AND_END;`

`            }`

`            else`

`            {`

`                signal_callback_return_param.callback_action       = NRF_RADIO_SIGNAL_CALLBACK_ACTION_END;`

`            }`

`            break;`

`        }`

`        mode++;`

`      }`

`      break;`

`    default:`

`        if (m_beacon.error_handler != NULL)`

`        {`

`            m_beacon.error_handler(NRF_ERROR_INVALID_STATE);`

`        }`

`      break;`

`  }`

`  return ( &signal_callback_return_param );`

`}`

_Listing 2: The Thingy software package offers sample software that provides representative design patterns such as the use of a callback routine shown here to execute a series of radio operations for beacon advertising. (Code source: Nordic Semiconductor)_

`enum mode_t`

`{`

`  ADV_INIT,                                                 /** Initialisation. */`

`  ADV_RX_CH37,                                              /** Advertising on Rx channel 37. */`

`  ADV_RX_CH38,                                              /** Advertising on Rx channel 38. */`

`  ADV_RX_CH39,                                              /** Advertising on Rx channel 39. */`

`  ADV_DONE                                                  /** Done advertising. */`

`};`

_Listing 3: A sample callback routine in the Thingy software package uses this enum type to walk the system through a series of stages during the beacon advertising sequence. (Code source: Nordic Semiconductor)_

The nRF52832's SoftDevice services and integrated hardware functionality provide an effective foundation for development of wireless sensor systems with minimal parts count. Yet, the complexity of these SoC devices can present designers with a significant learning curve in realizing a sensor design, much less a complete IoT application. The Nordic Semiconductor [NRF6936](https://www.digikey.com/product-detail/en/nordic-semiconductor-asa/NRF6936/1490-1061-ND/7175577) Thingy:52 IoT sensor kit helps developers significantly shorten the time required to develop useful Bluetooth-connected sensor systems.

## Rapid development Thingy

The Nordic Thingy:52 kit offers a rapid prototyping solution for wireless sensor designs. Based on the nRF52832 Bluetooth SoC, the kit is designed to deliver full functionality out of the box, requiring no hardware or firmware development to realize an IoT sensor solution complete with connected mobile app.

Among its features, the nRF6936 board includes a full sensor suite including:

Along with the MPU-9250 IMU for full 9-axis motion tracking, the Thingy board includes a separate dedicated motion sensor, the STMicroelectronics [LIS3DH](https://www.digikey.com/product-detail/en/stmicroelectronics/LIS3DHTR/497-10613-1-ND/2334355) accelerometer, to wake the system on movement. The LIS3DH draws power directly from the onboard voltage regulator to ensure it remains powered regardless of VDD status. The reference design includes schematics showing how the LIS3DH maintains isolation, connecting through an external I2C bus provided in the design to support external hardware (Figure 2).

![Diagram of Nordic Thingy reference design](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/July/Building%20Bluetooth-Connected%20IoT%20Wireless%20Sensor%20Prototypes/article-2017july-building-bluetooth-connected-fig2.jpg?ts=1b7c1c63-842a-4fab-a2b2-6f5e255734f6&la=en-US)

> _Figure 2: The Thingy reference design provides full schematics and demonstrates design techniques such as the use of STMicroelectronics LIS3DH accelerometer to wake an idle MCU upon movement. (Image source: Nordic Semiconductor)_

As illustrated in Figure 2, the smart sensors used in this design reduce complexity, requiring a simple two-wire I2C connection to the host. With this reference design, Nordic demonstrates a simple method that trades a minimal increment in design footprint for a significant reduction in power consumption during periods of low activity. Here, the design couples some sensors to a dedicated [NXP](https://www.digikey.com/en/supplier-centers/n/nxp-semiconductors) [NX3DV2567](https://www.digikey.com/product-detail/en/nxp-usa-inc/NX3DV2567GU,115/568-5206-1-ND/2523423) analog switch that allows the MCU (through MPU_WR_CTRL) to disconnect that particular sensor from power, MCU interrupt, and the I2C bus when operating conditions warrant (Figure 3).

![Diagram of Nordic Thingy hardware design \(click for full-size\)](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/July/Building%20Bluetooth-Connected%20IoT%20Wireless%20Sensor%20Prototypes/article-2017july-building-bluetooth-connected-fig3.jpg?ts=aa087fdf-fd59-4a63-82e5-841451351de8&la=en-US)

> _Figure 3: The Thingy hardware design takes advantage of the simple hardware interface required for integrated sensors such as the TDK InvenSense MPU-9250 motion sensor, but adds an NXP NX3DV2567 analog switch_

_ to decouple the sensor from the system to conserve power. (Image source: Nordic Semiconductor)_

Developers can extend the Thingy hardware complement by adding external devices. Four connectors support the Grove 4-pin format, allowing designers to easily add hardware functionality by drawing on the large base of available Grove-compatible devices. An additional 2 x 10 pin header brings out additional MCU ports and even includes four buffered lines. These lines each include a [Diodes](https://www.digikey.com/en/supplier-centers/d/diodes) [DMN3190LDW](https://www.digikey.com/product-detail/en/diodes-incorporated/DMN3190LDW-7/DMN3190LDW-7DICT-ND/4457886) N-MOS transistor able to drive external components such as LEDs or small DC motors. In fact, the number of I/O that the Thingy design makes available to designers exceeds the nRF52832's own GPIO pin count. Nordic added a set of [Semtech Corp](https://www.digikey.com/en/supplier-centers/s/semtech) [SX1509](https://www.digikey.com/product-detail/en/semtech-corporation/SX1509BIULTRT/SX1509BIULCT-ND/2295548) GPIO extenders to enhance the I/O capability of the Thingy system design.

Because of the Thingy's I/O extensibility, hardware developers can create prototype designs simply by connecting external devices to the board. A comprehensive software platform provides the same ease of development to software engineers.

## Software platform

The Thingy development platform extends the nRF52 software development kit (SDK) with a layer of services needed to let application developers focus on higher level processes rather than low-level operations (Figure 4). For example, the Thingy package adds a layer of sensor drivers that build on the SDK's peripheral drivers and hardware abstraction layer (HAL) to handle operations such as configuring sensors, starting or stopping them, and retrieving sensor data.

![Diagram of Thingy software package extends the Nordic nRF52 software development kit](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/July/Building%20Bluetooth-Connected%20IoT%20Wireless%20Sensor%20Prototypes/article-2017july-building-bluetooth-connected-fig4.jpg?ts=0cde8322-a3da-44ef-9cd7-e6b386d05ab5&la=en-US)

> _Thingy software package extends the Nordic nRF52 software development kit_

_Figure 4: The Thingy software package extends the Nordic nRF52 software development kit (SDK) with application-level services and utility modules designed specifically for the Thingy application. (Image source: Nordic Semiconductor)_

Nordic completes the IoT chain from sensor to mobile app with a set of resources for client development. The company provides separate open repositories with libraries and sample apps in Swift for iOS developers and in Java for Android developers. In addition, another open repository offers a JavaScript library for development of web apps built on the Polymer web component library and Web Bluetooth API.

Developers can get a quick taste of Thingy operation simply by downloading the Nordic Thingy app from the Apple App store or Google Play store. The developer then powers up the Thingy, which runs from an embedded 1440 mAh lithium-ion battery that recharges through a USB power connection. After the app discovers and connects to the Thingy system, it provides a running display of sensor data (Figure 5). The app even supports connectivity to IFTTT, allowing users to create cloud-based applets using IFTTT event chains triggered by Thingy data.

![Image of companion app interacts with the Thingy system over Bluetooth](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/July/Building%20Bluetooth-Connected%20IoT%20Wireless%20Sensor%20Prototypes/article-2017july-building-bluetooth-connected-fig5.jpg?ts=a79852ca-a221-4769-9545-ab9729ab3071&la=en-US)

> _Companion app interacts with the Thingy system over Bluetooth_

_Figure 5: A companion app interacts with the Thingy system over Bluetooth, providing a running display of sensor data as well as services for Thingy configuration and firmware update. (Image source: Digi-Key)_

Building on the Thingy reference design and software platform, developers can quickly extend the Thingy system to meet their own specific requirements. Developers can compile new Thingy firmware using Keil μVision or GCC using the GNU toolchain for ARM Cortex-M. The Thingy system provides a secure over-the-air update facility for loading new firmware. The standard Thingy app includes an option for updating to the latest version of Thingy firmware from Nordic, or from custom firmware packages created by developers using an open-source utility provided by Nordic.

## Conclusion

In a market replete with fast-changing IoT opportunities, developers face growing demand to prototype sophisticated applications more quickly. Although developers can find a growing array of IoT development platforms, projects too often stumble as engineers work through the complex implementation details associated with these platforms.

The Nordic Thingy:52 simplifies IoT development with a rapid prototyping platform that hides the complexity of the underlying hardware design and software architecture. Using the Nordic Thingy kit, developers can rapidly prototype Bluetooth-enabled multi-sensor systems - and later build on the Thingy reference design to create custom IoT devices.

Disclaimer: The opinions, beliefs, and viewpoints expressed by the various authors and/or forum participants on this website do not necessarily reflect the opinions, beliefs, and viewpoints of Digi-Key Electronics or official policies of Digi-Key Electronics.
