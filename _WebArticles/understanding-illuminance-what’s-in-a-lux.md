# Understanding Illuminance: What’s in a Lux?

_Captured: 2017-11-18 at 12:35 from [www.allaboutcircuits.com](https://www.allaboutcircuits.com/technical-articles/understanding-illuminance-whats-in-a-lux/)_

### Lux Matters

Measuring the intensity of light is nothing new. However, modern electronic devices are increasingly influenced by operational requirements--autonomy, energy efficiency, etc.--that depend upon standardized, human-vision-based assessments of ambient illumination. Such assessments are measuring something called **illuminance**, and the SI unit for illuminance is the **lux**. A closely related measurement is **luminous flux**, the SI unit for which is the **lumen**.

Luminous flux corresponds conceptually to a quantity of light; illuminance, on the other hand, is the quantity of light _relative_ to the size of the illuminated surface. Thus, it just so happens that lux is defined as lumens per square meter. For example, a 60 W incandescent light bulb might generate 850 lumens; this luminous flux does not vary according to where you locate the bulb.

But the illuminance provided by this bulb is entirely dependent on external circumstances--if the bulb's light is distributed over a floor area of 16 square meters, you have 53 lux, which is probably adequate for walking up a staircase without tripping. That same bulb in a 1-square-meter closet gives you 850 lux, which is enough for administering first aid.

### The Luminosity Function

This is where illuminance gets particularly interesting. It is essential to understand that illuminance (and therefore also luminous flux) does not reflect an objective physical quantity. Temperature is the average kinetic energy of molecules; voltage is the difference in electrical potential between two points. These measurements represent objective physical realities. Another objective measurement is **irradiance**, which indicates the amount of electromagnetic radiation per unit area; the SI unit for irradiance is watts per square meter.

This sounds a lot like illuminance, which is lumens (i.e., the amount of light) per square meter. The crucial difference is that illuminance is _subjective_, in the sense that lux values are adjusted according to the spectral sensitivity of the human eye. In other words, when calculating illuminance, 1 W/m2 of red light doesn't equal 1 W/m2 of green light, because the human eye is more sensitive to green. Thus, illuminance is designed to convey information about _how well a human being could see_ under certain lighting conditions.

Take a good look at the following curve, which is called a luminosity function.

![](https://www.allaboutcircuits.com/uploads/articles/LUX1_Curve1.PNG)

This particular curve is referred to as "CIE photopic modified by Judd (1951) and Vos (1978)." You can download the actual data as a CSV file from [this website](http://www.cvrl.org/lumindex.htm). CIE stands for _Commission Internationale de l'Eclairage_ (aka International Commission on Illumination), and as you may have guessed, this curve incorporates corrections based on the research of Judd and Vos. Much more relevant to us is the word "photopic," which means that this particular curve is valid for human vision influenced by adequate lighting (i.e., "day vision"). A curve that conveys data for night vision would be labeled "scotopic."

The first thing to notice here is the extreme variations within the visible spectrum (i.e., 400 to 700 nm). The values are normalized, meaning that the luminous efficiencies are expressed as relative to the maximum efficiency at 555 nm. Thus, if you had 555 nm and 450 nm light sources producing _equal irradiance_, a human being would interpret the 450 nm light as _20 times less intense_ than the 555 nm light.

### The Colors of White

Usually our homes and offices are illuminated not with single-color LEDs but with bulbs that generate enough different wavelengths to give us light that appears more or less white. Nonetheless, the spectral composition of different light sources can vary significantly, and we need to take this into account when measuring illuminance.

If you are not in the habit of intuitively translating wavelength into color, this version of the luminosity function might be helpful:

![](https://www.allaboutcircuits.com/uploads/articles/LUX1_Curve2.PNG)

Right away we can see that a light source will provide more illuminance--i.e., higher lux values--if it concentrates its electromagnetic energy near the green wavelengths. The best example of such a source is the sun; outdoor lux values are extremely high not only because the sun is so powerful but also because more of its irradiance is near the peak of the luminosity function (I suppose it is no surprise that the human eye is optimized for use with the sun). However, the luminosity curve does not mean that the ideal light source for human activity is something that generates all of its electromagnetic radiation at 555 nm. It is true that this would produce the highest ratio of irradiance to illuminance, but human beings generally prefer to live in a world with more colors than green.

### What to Expect

If you design your own lux meter, you will need a way to verify that your results are reasonable. The best way to do this is with a preexisting lux meter, but preexisting lux meters cost money. Maybe you are designing your own precisely because you don't already have one and don't want to buy one. So here is some approximate illuminance data that you can use to assess the accuracy of your measurements.

twilight
10 lux ([source](http://www.stow-ma.gov/pages/StowMA_Planning/terminology_guide.pdf))

nighttime household lighting
30 lux ([source](http://www.stow-ma.gov/pages/StowMA_Planning/terminology_guide.pdf))

hallway/stairwell in an office building
200 lux ([source](http://www.gsa.gov/portal/content/101308))

typical office
500 lux ([source](http://www.gsa.gov/portal/content/101308))

outdoors, overcast
1000 lux ([source](https://web.archive.org/web/20131207065000/http://stjarnhimlen.se/comp/radfaq.html#10))

outdoors, full daylight, but not in direct sun
10,000 to 20,000 lux ([source](http://www.stow-ma.gov/pages/StowMA_Planning/terminology_guide.pdf))

outdoors, direct sunlight
100,000 lux ([source](https://www.cci-icc.gc.ca/resources-ressources/agentsofdeterioration-agentsdedeterioration/chap08-eng.aspx))

### Conclusion

We now know enough to formulate a concise definition for illuminance: **the perceived level of ambient brightness, taking into account the objective light intensity and the spectral response of the human eye**. Thus, the lux value in a particular environment depends on the amount of light produced by natural and/or artificial sources as well as the spectral characteristics of this light. In a follow-up article we will discuss how to actually calculate a lux value based on the output of a light-sensitive device.
