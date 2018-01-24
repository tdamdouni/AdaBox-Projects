# Paralleling Circuits to Extend Switch Life

_Captured: 2017-11-25 at 09:41 from [forum.digikey.com](https://forum.digikey.com/t/paralleling-circuits-to-extend-switch-life/552?Wt.z_sm_link=twitterposts&utm_source=twitter&utm_medium=social&utm_campaign=techtips)_

I have seen many Rocker and toggle switches wear out and stop functioning prior to their expected life. One suggestion that I have passed on is that if you can find a switch that has twice the poles and run your circuits in parallel it can extend the life of your switch.

One example was when using SPDT rocker switch SW340-ND to run two separate motors. Even though the voltage and current draw of the motors was with-in the specifications of the switch, after using for a short period of times I started to see failures. Here is the schematic of the original circuit.

![image](https://cdn-enterprise.discourse.org/digikey/uploads/default/original/1X/f86fcabc2c40ae9cafc35971254e32df96197a96.png)

With a set cut-out in my panel I was limited in options when looking for a replacement switch. Using a DPDT rocker switch CWI419-ND I was able to run the circuit in parallel. With less current flowing through the individual contacts in the switch I was able to run the switch without having the failure issues we were seeing in the original switch and no modification was needed to the panel. Here is the schematic using the DPDT switch.

![image](https://cdn-enterprise.discourse.org/digikey/uploads/default/optimized/1X/c6d53e4f5b48a4e7e938bfdf1dd243bf9484c2fc_1_448x196.png)

> _Note: You will still need to verify the Voltage and current ratings on your switch to ensure you are using the switches within their capabilities._
