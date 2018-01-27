# How To Use Capacitors

_Captured: 2017-11-26 at 23:29 from [www.kitronik.co.uk](https://www.kitronik.co.uk/blog/how-to-use-capacitors/)_

## Funcionality

A [capacitor](https://www.kitronik.co.uk/components/capacitors.html) is a component that holds or releases electrical charge. It is like a reservoir, in the same way that a reservoir holds rainwater that can be emptied later, the capacitor can be filled with electricity and emptied gradually over time.

## Schematic symbols

![how_to_use_capacitor_values_1](https://www.kitronik.co.uk/wp/wp-content/uploads/2014/01/how_to_use_capacitor_values_1.png)

The basic symbol for a capacitor is two parallel lines. This can be changed slightly to indicate different types of capacitor. Some capacitors will only work if they are used the correct way around. These are called electrolytic capacitors. The symbol for an electrolytic has to indicate the polarisation of the capacitor. This is done by making one of the lines on the basic capacitor curved. Capacitors that can be adjusted have a line running through them with an arrow on one end.

## Values

The value of a capacitor is measured in Farads, though a 1 Farad capacitor would be very big. Therefore we tend to use milli Farads (mF), micro Farads (µF), nano Farads (nF) and pico Farads (pF). A µF is a millionth of a farad, 1 µF = 1000 nF and 1nF = 1000 pF.
1F
=1,000mF

1F
=1,000,000µF

1F
=1,000,000,000nF

1F
=1,000,000,000,000pF

The larger electrolytic capacitors tend to have the value printed on the side of them along with a black band showing the negative lead of the capacitor.

Other capacitors (as shown below), which are often smaller, may not have enough space to print the value in full and can use a 3-digit code. The first 2 digits are the first part of the number and the third digit give the number of zeros to give it's value in pF.

![how_to_use_capacitor_values_2](https://www.kitronik.co.uk/wp/wp-content/uploads/2014/01/how_to_use_capacitor_values_2.png)

> _Examples: 104 = 10 + 0000 (4 zero's) = 100,000 pF (which is also 0.1 µF)_

## Question 1

Printing on capacitor
Two digit start
Number of zeros
Value in pF

222

103

333

473

## RC Constant

The amount of time taken to charge (fill) or discharge (empty) the capacitor to a given voltage depends upon how quickly charge is allowed to flow into the capacitor. If a capacitor is connected across a battery without a resistor it will charge to the same voltage as the battery almost instantly as the flow of charge is not opposed. If however a current limiting resistor is placed in series with the capacitor the charge is opposed and the capacitor charges at a slower rate. When a resistor and capacitor are used together an RC timing circuit is produced. The RC timing circuit can be used to produce delays, the amount of time taken to get to 70% of the final voltage is given by the resistance times the capacitance.

Example of calculating RC constants: For a 1M resistor and a 100µF capacitor  
T = R x C  
T = 1,000,000 (1M) x 0.000,1 (100µF)  
T = 100 seconds

Similarly an RC of 1 second could be produced with a 10K resistor and 100µF capacitor.

## Question 2

Resistor value
Capacitor value
RC Time Constant

2,000,000 (2M)
0.000,1 (100µF)

100,000 (100k)
0.000,1 (100µF)

100,000 (100k)
0.000,047 (47µF)

## Maximum working voltage

Capacitors also have a maximum working voltage that should not be exceeded. This will be printed on the capacitors or can be found in the catalogue the parts came from. You can see that the capacitor below is printed with a 10V maximum working voltage.

![how_to_use_capacitor_values_3](https://www.kitronik.co.uk/wp/wp-content/uploads/2014/01/how_to_use_capacitor_values_3.png)

## Answers

## Question 1

Printing on capacitor
Two digit start
Number of zeros
Value in pF

222
22
00
2200pF (2.2nF)

103
10
000
10,000pF (10nF)

333
33
000
33,000pF (33nF)

473
47
000
47,000pF (47nF)

## Question 2

Resistor value
Capacitor value
RC Time Constant

2,000,000 (2M)
0.000,1 (100µF)
200 seconds

100,000 (100k)
0.000,1 (100µF)
10 seconds

100,000 (100k)
0.000,047 (47µF)
4.7 seconds

Download a pdf version of this page [here](https://www.kitronik.co.uk/pdf/How_to_use_capacitors.pdf)

Learn more about the author [read more »](https://www.kitronik.co.uk/about/geoff-hampson/)

(C)Kitronik Ltd - You may print this page & link to it, but must not copy the page or part thereof without Kitronik's prior written consent.

![Electronic Project Kits](https://www.kitronik.co.uk/img/banners/electronic_project_kits.png)

> _<- Previous Post Next Post ->_
