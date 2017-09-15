# The New Wireless Thread Network Protocol

_Captured: 2017-09-14 at 11:42 from [www.allaboutcircuits.com](https://www.allaboutcircuits.com/technical-articles/thread-network-protocol/)_

### Recent Beginnings

Thread is a new wireless network protocol standard optimized for the connected home. It doesn't have a long history... proposed in 2014 by founding members of the Thread Group (ARM, Big Ass Fans, Freescale Semiconductor, Nest Labs, Samsung Electronics, Silicon Laboratories and Yale Security), the standard was released in July 2015. Thread has a specific design target: home connectivity to the Internet of Things ( IoT ). It uses internet protocol version 6 (IPv6) for routing device-to-device communication within an IEEE standard 802.15.4 wireless Personal Area Network (PAN) network. With such a recent initial release, information in this article may change.

The [Thread Group](http://www.threadgroup.org) is the not-for-profit organization responsible for the education, marketing, certification and promotion of Thread. From the Thread Group:  
"We designed Thread to have these important features:

  * Simple for consumers to use
  * Always secure
  * Power efficient
  * An open protocol that carries IPv6 natively
  * Based on a robust mesh network with no single point of failure
  * Run over existing 802.15.4 radio silicon

Thread was designed to support a wide variety of applications in the home: appliances, access control, climate control, energy management, lighting, safety, and security."

The Thread Group has grown steadily since membership opened. A 'Thank you' goes out to the Thread Group for their support.

### An Introduction to Thread

Thread was designed to address issues with connecting smart devices within the home. A quick look at current offerings will show there are many different devices working on various networks with applications that may or may not work together. A smart ceiling fan in a den is easily installed and controlled from a smartphone using the manufacturer's application. A smart thermostat from another manufacturer can also be installed in the den and report to a smartphone... but what if the homeowner wants the ceiling fan to operate when the thermostat indicates the ambient air temperature is above 75 degrees (F)? What if the fan shouldn't operate when a smart window in the den is open? How does the thermostat get the message to the fan that it's time to start operating? How would the fan know the window is open? It can get complicated working with details from each manufacturer and attempting to link devices. Even if all the devices are IP-based, if different network protocols are used, they may not work together.

This is the scenario Thread was designed to handle. It forms an IP-based network with each IP-enabled smart device acting as a host. As shown in Figure 1 (from the Thread Group), the network connects the hosts via routers. The devices have a unique IPv6 address and the routers within the network can forward messages between devices. Devices on the Thread network can also be connected to the internet via border routers, so all the devices can be controlled from smartphones and tablets or forward data to be stored in the cloud. Unlike some other mesh networks, automatic discovery and adhoc network additions aren't allowed. All devices added to the Thread network are the result of the network owner initiating the join and only authenticated devices can be added to the network.

![](https://www.allaboutcircuits.com/uploads/articles/Thread-Network-Protocol-\(1\).jpg)

> _Figure 1. Thread network._

Thread addresses the network layers of the Open System Interconnection (OSI) model. The OSI model standardizes communication systems with the hardware and physical components at the bottom and applications at the top. The Thread protocol stack (from the Thread Group) is shown in Figure 2.

![](https://www.allaboutcircuits.com/uploads/articles/Thread-Network-Protocol-\(2\).jpg)

> _Figure 2. Thread Protocol Stack_

Thread uses the IEEE Standard 802.15.4 for the physical (PHY) and media access control (MAC) levels and does not specify the top application layer. It operates in the Industrial, Scientific and Medical (ISM) 2.4GHz frequency band and can be run on the same radio modules currently supporting 802.15.4, like ZigBee and WirelessHART. Table 1 provides some information about Thread.

Specification Thread Data Table 1. Thread Specifications 

Design Focus

Home connectivity to IoT

IEEE Standard

802.15.4

Network Type

Mesh

Network

Thread

Distance

Normally 20-30 meters

Max Nodes Connected

250

Operating Band

2.4GHz (The ISM unlicensed band)

Spread Spectrum

Radio uses direct sequence spread spectrum (DSSS)

Throughput

Radio operates at 250 kbps

Data

Monitoring and control data

Voice Capable

No

Security

Banking-class, public-key cryptography

Power Consumption

Low power

Modulation

Radio specification is O-QPSK modulation

The Thread Group says that a software upgrade may allow Thread to run on ZigBee networks. Microcontrollers are currently available with both Thread and ZigBee stacks. These Dual PAN devices use the same radio and application developers can focus on their programs, with the decision of which network to run on made later in the design cycle. As with other standards, Thread product offerings will have to go through a certification process and all thread-certified products will interconnect. There are fees associated with membership and certification.

Figure 2 shows the network layers specified by Thread are based on existing standards, optimized for the home connectivity environment with added security and commissioning (the process of authenticating devices.) Thread uses the Internet Engineering Task Force (IETF) standard 6LoWPAN (IPv6 over low power Wireless Personal Area Networks), IP Routing and the User Datagram Protocol (UDP).

6LoWPAN enables efficient IPv6 communication over IEEE 802.15.4 networks, making it possible to send IPv6 packets over the low power, low speed links. Note that Thread uses UDP with IP Routing and not the more familiar Transmission Control Protocol (TCP), the TCP part of the TCP/IP networking suite. UDP offers faster packet delivery with reliability provided outside the packet handling mechanism.

In addition to reliability, Thread adds security, mesh network topology, power management and a simple way to commission and join devices to the network. The result is a secure, robust, mesh home network that handles IoT connections so homeowners can easily monitor, configure and control their various smart devices.

### Certification

While the Thread specification will be maintained by the Thread Group, certification and testing will be done by UL (Underwriters Laboratories) and Granite River Labs (GRL). The Thread Group's Technical Task Group is working with UL to manage the certification process while GRL is providing the test harness, a platform consisting of hardware and software to validate the Thread protocol stack. Only certified Thread products will bear the Thread logo.

### The Application Layer

Thread doesn't specify an application layer and doesn't care what application is running on it. Just as a a Wi-Fi network can run various applications, a Thread network can run various applications. Thread guarantees that devices that are Thread-certified will interconnect. Applications may address lighting, temperature control, security, smoke detection; as Thread matures into the market, it is expected applications will be developed to easily control all smart devices in the home.

In April 2015, the Thread Group and [ZigBee Alliance](http://www.zigbee.org) announced a collaboration that would enable ZigBee Control Libraries (ZCL) to run on Thread networks. Developers already familiar with ZCL from writing applications for ZigBee based stacks could leverage their knowledge to write applications for Thread based stacks. ZCL defines a standard framework for how connected devices communicate: how they identify what they are and what capabilities they have.

Although there is an IPv6 version of ZigBee, ZigBee IP, Thread's IP routing for device-to-device communication targets a wider variety of applications for the IoT and the connected home.

### Thread Network Components

The Thread network, Figure 1, consists of host devices, routers and border routers.

Host devices are the individual IP-enabled functional equipment, like a light bulb, fan or thermostat, and are endpoints in the network. A device may also be referred to as a sleepy node or sleepy child; with a router being the (not sleeping) parent. The sleepy terminology indicates that the devices spends most of the time in sleep mode, with low duty cycles as required for low power operation. Devices communicate only through the parent router and do not forward messages for other devices. Since devices cannot receive data while in a sleep mode, the parent holds their messages until the device wakes to either poll for data or to send data.

A typical send cycle for a device might be:

  1. Wake from sleep mode.
  2. Perform any required startup and radio initialization.
  3. Go into receive mode and check if clear to transmit.
  4. Go into transmit mode.
  5. Transmit data.
  6. Get acknowledgment as applicable.
  7. Sleep.

Routers provide routing for the network devices. They are also responsible for handling devices joining the network and providing security; they can function in the leader role and start a Thread network. Always active, they maintain neighbor, child and routing tables and connect with each other so the mesh remains intact. If a router goes down, the remaining Thread routers update their routing information so messages can still be forwarded using existing nodes. If a parent router goes down, another router will function as a device's parent. Thread's mesh topology provides a self-healing communication framework. Routers can be also be downgraded to router-eligible end devices (REEDs) which do not forward messages if conditions require; REEDs and routing algorithms are managed by the Thread network without user intervention.

Border routers function as simplified gateways, handling connections between a Thread network and a non-Thread network, as shown in Figure 1. They have the capability to handle 802.15.4 and a Wi-Fi (802.11) or an Ethernet (802.3) connection. Border routers can be separate communication equipment like an access point or a host device within the Thread network that incorporates both a Thread and Wi-Fi interface. A Thread network can have more than one border router.

Figure 3 shows a partial Thread network. A Thread-certified fan and thermostat, each an endpoint in the network, communicate through the parent routers.

![](https://www.allaboutcircuits.com/uploads/articles/Thread-Network-Protocol-3.jpg)

> _Figure 3. Partial Thread Network_

A Thread network including a fan and thermostat is shown in Figure 4. This network view assumes a suitable application is running that controls the smart devices so:

  * the fan starts when the thermostat indicates the ambient air temperature is above 75 degrees (F)
  * lights turn on if the door opens and it's after 8pm local time
  * if the window is opened, the fan is stopped if running

The homeowner can start the fan any time by using their smartphone or tablet. The message from the smartphone is handled by the Thread border router, which forwards it to the Thread network. Within the Thread network, the routers get the message to the specific fan device using it's IP address. (Or to it's parent router if the fan is in sleep mode). Upon waking from sleep and polling the parent, the fan will be forwarded the message. In response, it will start.

![](https://www.allaboutcircuits.com/uploads/articles/Thread-Network-Protocol-4.jpg)

> _Figure 4. A Thread network_

### Joining Devices

Adding devices to the Thread network and authenticating network credentials are handled routers or border routers functioning in leader and commissioner roles. Thread networks identify a leader which has responsibility for certain network functions like assigning router addresses and handling new router requests. If the current leader goes down, another router or border router assumes the role automatically. The commissioner functions as the authentication server for new Thread devices and the authorizing agent for providing the network credentials required to join the network.

If a homeowner buys a new Thread-certified device they initiate the join, having the device discover the network and providing the security passphrase. Devices are only joined to the network when credentials are authenticated. Once joined the device is configured to a parent router and can participate in the network. Routing tables and other network information gets updated to reflect the addition.

### Summary

Thread is a network protocol focused on the connected home and the IoT. Specifically designed for low power consumption and IP-based communication, it provides a secure, robust, mesh network for IP-enabled smart home devices. Thread-certified devices are guaranteed to interconnect. Homeowners or network administrators can easily add devices to the network and application developers can be sure devices will work together.
