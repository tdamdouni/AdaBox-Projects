Hey !
Thanks for downloading and using my library !!!

This library allows you to read the raw data from a MPU6050 multifunctional accelerometer,
compute them and then allows you to do whatever you want with them!

Why did I call this library "GY6050" and not MPU6050 ?
Well because the name was already taken... And if you want
to experiment with the one called "MPU6050", it won't interfere
with this one, and vice-versa.


For starters, put at the very beginning of your code : 

#include <Wire.h>
#include <GY6050.h>

GY6050 [something](0x68);

Note : the "Ox68" is the I2C address of the MPU6050, but sometimes it can be a different one.
You can verify that with a simple I2C bus scanner sketch that you can find online (google it ;) !!)

The "#include <Wire.h>" line is used to include the I2C library, in order to make the Arduino talk to the
MPU6050. The "#include <GY6050.h>" line is used to include, well, the main library for the MPU6050.

Note : Replace "[something]" by whatever you want (but for convinience, I'll use "gyro" for the rest of this tutorial).

Then, in the "void setup", put : 

gyro.initialisation();

This line initialises the MPU6050 and makes it talk properly to your Arduino.

Ok, now, the big part.
In your "void loop", put : 

int CustomVariable = gyro.refresh([Argument1], [Argument2]);

Note : Because the library returns an integer value, you can store it to another integer value (here CustomVariable),
       but you can also use this parameter as : Serial.println(gyro.refresh([Argument1], [Argument2]); .

[Argument1] is used for the "device" you want to use : 

'A' : Accelerometer,
'T' : Temperature, 
'G' : Gyroscope.

[Argument2] is used for the axis (or unit, for temperature) that you want to use : 

Accelerometer & Gyroscope :
'X'
'Y'
'Z'

Temperature : 
'C' : Celsius
'F' : Farenheit


Note : These letters HAVE TO be between apostrophes ('), like : gyro.refresh('A', 'X');
       It was the only way I could deal with the alterable arguments without having to use integers...

The values from the axis of the accelerometer should be between -90 and 90 (angular degree), but it can also be 110 or -110,
because of the inertia of the "moving parts" inside the accelerometer.
The values for the gyroscope should be between -120 and 120 (no particular unit), but it can be a bit more, it all depends on the rotational speed.

 
You can open the "MPU6050_test_Serial" file to see a more straightforward example code.

Thanks for reading this,
Frédéric Druppel.
