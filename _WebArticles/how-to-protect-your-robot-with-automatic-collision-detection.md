# How to Protect Your Robot with Automatic Collision Detection

_Captured: 2017-12-02 at 23:21 from [www.allaboutcircuits.com](https://www.allaboutcircuits.com/projects/how-to-protect-your-robot-with-automatic-collision-detection/)_

In this article, we'll develop and test an algorithm for automatically shutting down a robot in response to a collision (or some other violent event).

### Why?

Sooner or later, your robot is going to crash into something. It might fly off your workbench because you forgot to put a block underneath it before you flipped the power switch. It might make a wrong turn and head down the staircase. But it seems to me more likely that a simple programming error or communication failure will cause the robot to continue moving after it should have stopped, resulting in an unplanned encounter with a wall, a door, or some other solid object.

This article most certainly does not offer a way to _prevent_ collisions; this would require a sensor that can detect the presence of a rapidly approaching object. The present objective is to _detect_ collisions, i.e., enable the robot to realize that something bad has happened and then take appropriate action.

The automated response could be to send a distress signal, disable the power supply, or initiate a self-test procedure that attempts to evaluate the nature of the damage. In this article, though, we'll keep it simple: if a collision is detected, the robot stops the motors. This at least avoids the situation in which a confused or wounded or half-ruined robot continues careening at high speed until finding another solid object or otherwise exacerbating the damage suffered in the initial crash.

We'll need two articles to fully address this topic. This current article describes the development procedure and leaves you with firmware that is just what you need for bench-testing and refining your algorithm. In the next article, we'll attempt to collect real collision data and fine-tune (or overhaul) the algorithm accordingly, and the final firmware will be intended for independent robot operation.

### Supporting Information:

If you'd like to catch up on how I built my robot for this project, please read the articles below:

### How?

We'll be using the [Romi robot chassis](https://www.pololu.com/category/203/romi-chassis-kits) in conjunction with a custom-designed [Romi control board](https://www.allaboutcircuits.com/projects/design-a-control-board-for-a-romi-robot-chassis/), which includes a three-axis accelerometer.

![](https://www.allaboutcircuits.com/uploads/articles/proj_autocollisiondet_photo.jpg)

It should come as no surprise that a collision involves significant acceleration (specifically, deceleration). Thus, with proper signal processing we can use the accelerometer data to detect a collision event, and then the microcontroller can stop the motors.

Damaging events could theoretically originate from any direction, especially if your robot will be subjected to one of those contests where people build machines that become instruments for safely expressing the long-standing tendency of humans to attack and kill one another. However, in this project, we will assume that a collision will always consist of a forward-moving robot crashing directly into a solid object. This means that the acceleration will be in the reverse direction, which (as mentioned in [this article](https://www.allaboutcircuits.com/projects/gathering-and-analyzing-a-robots-accelerometer-data/)) corresponds to the accelerometer's positive x-axis.

#### Analog-to-Digital Conversion

We'll use the EFM8 microcontroller's internal 14-bit ADC to digitize the analog acceleration signal. Here is the configuration:

![](https://www.allaboutcircuits.com/uploads/articles/proj_autocollisiondet_ADCconfig.JPG)

  * The sample rate is 1 kHz, which is significantly higher than the bandwidth (~200 Hz) of the accelerometer signal.
  * Since we are concerned only with the type of collision described above, we ignore the z-axis and the y-axis; the ADC input signal is always the x-axis output, which is connected to P1.7.
![](https://www.allaboutcircuits.com/uploads/articles/proj_AccData_ADCchannels.JPG)

  * We will be using the ADC's automatic accumulate-and-divide functionality. This is a simple way to reduce noise and hopefully make it easier to identify a low-amplitude acceleration event. Every conversion trigger will result in four ADC samples; these are added together and then shifted right by two bits (which is equivalent to dividing by four).

#### Gathering Data

I gathered test data using my custom serial-port-logger application, which is discussed [here](https://www.allaboutcircuits.com/projects/gathering-and-analyzing-a-robots-accelerometer-data/) in the "YAT and Excel" section. However, the current version is greatly improved: it now can send ASCII commands, and it has multiple text-to-be-sent boxes so that commonly used commands are available with just a single click.

![](https://www.allaboutcircuits.com/uploads/articles/proj_autocollisiondet_serialportapp_2.JPG)

This code excerpt gives you the functions associated with the three-letter ASCII commands:
    
    
                        char RecordAccelerometerData[] = "RAD";
    char TransferAccelerometerData[] = "TAD";
    char EnableCollisionDetection[] = "ECD";
    char DisableCollisionDetection[] = "DCD";
    char SoftwareReset[] = "SWR";
    char MotorsFullForward[] = "MFF";
    char DisableBothMotors[] = "DBM";
    char BrakeBothMotors[] = "BBM";
                      

I use the following Excel file to process and plot the acceleration data:

### Let's Look at Some Data

I used my hand to produce a backward acceleration event that hopefully is somewhat comparable to the rapid deceleration caused by a collision. (The technique is demonstrated in the first video.)

Here are three data sets:

![](https://www.allaboutcircuits.com/uploads/articles/proj_autocollisiondet_testacc1.JPG)

![](https://www.allaboutcircuits.com/uploads/articles/proj_autocollisiondet_testacc2.JPG)

![](https://www.allaboutcircuits.com/uploads/articles/proj_autocollisiondet_testacc3.JPG)

I put these waveforms next to one another and identified two characteristics that they all have in common:

  * The acceleration signal rapidly exceeds 1660 mV, which is also significantly above the noise floor.
  * They all maintain a high slope until at least 1670 mV.

Thus, I built my algorithm around these two values: the detection algorithm begins when an ADC sample exceeds 1660 mV (=11332 ADC counts). It then waits to see if the signal will exceed 1670 mV (=11401 counts) within a certain period of time; the time-to-second-threshold restriction is based loosely on the slope of the initial rising edge seen in these three waveforms.

### Problem, Solution

I quickly discovered that my first algorithm was a total failure: a light tap on the front of the robot chassis was being identified as a collision event. It turns out that a light tap produces an acceleration profile similar to this one:

![](https://www.allaboutcircuits.com/uploads/articles/proj_autocollisiondet_tap.JPG)

The amplitude is quite high, but the duration is very short. I realized that I needed to incorporate a minimum-duration condition: if the acceleration falls below the first threshold too soon, the event is ignored. I set the minimum duration (starting with the second-threshold crossing) at 30 samples, i.e., 30 ms. This is shorter than the typical duration from second threshold (rising) to first threshold (falling) for a simulated collision event, yet it seems to be consistently longer than the corresponding duration for the spikes generated by tap events.

The following video shows some initial success with the revised algorithm. The green LED indicates that collision detection is active, and the red LED illuminates immediately after a collision signal is identified. As you can see in the video, taps are successfully ignored and simulated collisions are correctly identified.

### Disabling vs. Braking

If you look at the code you will see that I use the function BrakeMotors() in response to a collision event. In this case, it is important to stop the robot as quickly as possible, and thus we use the [MAX14870](https://www.allaboutcircuits.com/electronic-components/datasheet/MAX14870ETCT-Maxim-Integrated/)'s brake mode instead of simply disabling the motors:

![](https://www.allaboutcircuits.com/uploads/articles/proj_autocollisiondet_brakemode.JPG)

> _From the MAX14870 datasheet._

The following video conveys the difference between stopping the motors (by setting the nEN pins to logic high) and braking the motors.

### Firmware

You can use the following link to download the source and project files:

The comments and descriptive identifiers will help you to understand what's going on.

Note that the collision detection algorithm is located in the ADC0WC (WC = "window compare") interrupt service routine (in the "Interrupts.c" source file). You can read more about the window-compare functionality in the [EFM8LB1 reference manual](https://www.silabs.com/documents/public/reference-manuals/EFM8LB1-RM.pdf). It's a handy feature because it allows the initial threshold detection to occur automatically, i.e., the CPU doesn't have to compare the ADC samples to the threshold or do anything else related to the ADC conversions. The ADC operates independently and doesn't bother the processor at all until a sampled value has exceeded the first threshold.

### Final Bench Testing

The following video shows a successful simulated operation of the collision detection functionality. (The acceleration signal is very different when the motors are running; we'll look at that in the next article.)

### Conclusion

We've developed a collision detection algorithm and confirmed that it correctly identifies simulated collision events. It also can ignore high-amplitude, short-duration acceleration signals resulting from a rapid, localized impact (i.e., a tap). The next step is to gather data from and test functionality with real collisions.
