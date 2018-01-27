# DIY Action Cam Macro Lens

_Captured: 2017-11-23 at 10:17 from [www.instructables.com](http://www.instructables.com/id/DIY-Action-Cam-Macro-Lens/)_

![](https://cdn.instructables.com/F04/938F/JA2TIXLA/F04938FJA2TIXLA.MEDIUM.jpg)

Action cameras have fish eye lenses so they can gather the widest field of view possible. With a macro lens, you can use one to get closeups of small objects with less distortion and more definition.

With a macro lens, the background will be out of focus, so that the object you're trying to shoot takes center stage without any background distractions.

![](https://www.instructables.com/files/deriv/FT5/VH3Q/JA2TJ0PX/FT5VH3QJA2TJ0PX.ANIMATED.LARGE.gif)

> _I've provided a Fusion 360 file that you can use to quickly and easily make a custom adaptor for whatever action cam you have and 3D print it._

## Step 1: Tools + Materials

  * Fusion 360 
  * 3D Printer
    * I use a [Creality CR-10](https://www.gearbest.com/3d-printers-3d-printer-kits/pp_441281.html?lkid=11217563). It's the best bang for your buck, in my opinion.
    * Use this coupon code at Gearbest to get it for $340: 1111CR10.
  * 3D Print Filament
    * I used **Black**[Matte Fiber HTPLA](https://www.proto-pasta.com/collections/new-releases-favorites/products/matte-fiber-htpla-white) from Proto-pasta for this project, but pretty much any filament will work. This stuff is great for this project because it's important to avoid any kind of glare from the adaptor onto the back of the lens. Any black filament will do, but this stuff having a matte finish will ensure that there are no reflections at all from a glossy surface.
  * [Macro Filter Set](http://www.amazon.com/dp/B002P9HXMW/?tag=instructabl09-20): This is a 4-pack of 1X, 2X, 4X, and 10X lenses that will fit using the files I'm providing here (52mm). I'm using the +10 lens because the camera is super close to the subject.
  * [Action Camera](https://www.gearbest.com/action-cameras/pp_449914.html?): This design will work with the first 4 generations of GoPro, but I'm using an SJCam (works pretty well and is $90 on Gearbest with this coupon code: AFF1186).
  * [Calipers](http://www.amazon.com/dp/B000GSLKIW/?tag=instructabl09-20): These are as important to a digital fabrication maker as a tape measure is to a carpenter. You'll need them for this project and almost every other project I've posted.

**Fusion 360** is free and it's awesome. I use it for everything I design and fabricate.

[Student / Educator License](https://www.autodesk.com/products/fusion-360/students-teachers-educators?mktvar004=711322&internalc=true) (renew free every 3 years)

[Hobbyist / Startup](http://www.autodesk.com/products/fusion-360/overview?mktvar004=711323&internalc=true) (renew free yearly)

## Step 2: Using the Model

![](https://cdn.instructables.com/FFO/DIG6/J9YJG1JT/FFODIG6J9YJG1JT.MEDIUM.jpg)

![](https://cdn.instructables.com/FE6/3SRE/J9YJG1J2/FE63SREJ9YJG1J2.MEDIUM.jpg)

Follow this link to open the Fusion 360 file: <http://a360.co/2zZrXTc>

When it's open, go to Modify > Change Parameters and make sure the "lensDiameter" parameter matches the diameter of your action cam lens.

![](https://www.instructables.com/files/deriv/FVJ/85FJ/J9YJG1KS/FVJ85FJJ9YJG1KS.LARGE.jpg)

My lens is 22.4mm in diameter, but each camera model will probably be different. Use a pair of calipers to measure your lens diameter and enter that value under Expression in "lensDiameter". I usually stick to one decimal place when I use measurements of real things because 1/100th of a millimeter is way out of the range of precision for just about everything I make. It helps to keep these measurements simple so you can keep the project in your head more easily.

![](https://www.instructables.com/files/deriv/FHA/0WY9/JA2TJ5PC/FHA0WY9JA2TJ5PC.LARGE.jpg)

The other parameter there is "fitOffset" which is the tolerance. If you increase this, the fit will be _looser, _if you decrease it the fit will be _tighter. _This takes a bit of trial and error and it's different for different materials.

![](https://www.instructables.com/files/deriv/FJ8/KB65/J9YJG1JZ/FJ8KB65J9YJG1JZ.LARGE.jpg)

If you turn on the section analysis (Browser > Analysis > Section), you'll see a cross-section of the lens, adaptor, and cap. If you adjust the parameters, you'll be able to see the diameter of the adaptor change and the gaps between the parts change.

![](https://www.instructables.com/files/deriv/FJT/IJ7N/J9YJG1JY/FJTIJ7NJ9YJG1JY.LARGE.jpg)

> _Here's an example where the lens is 20mm in diameter._

![](https://www.instructables.com/files/deriv/FIX/81OC/J9YJG1JV/FIX81OCJ9YJG1JV.LARGE.jpg)

> _Here's an example where the lens is 25mm in diameter._

## Step 3: Assembly

![](https://cdn.instructables.com/FOR/T085/J9YJG2TF/FORT085J9YJG2TF.MEDIUM.jpg)

![](https://cdn.instructables.com/FI6/RFYY/J9YJG2UD/FI6RFYYJ9YJG2UD.SMALL.jpg)

![](https://cdn.instructables.com/FD2/3LPF/J9YJG2UF/FD23LPFJ9YJG2UF.SMALL.jpg)

![](https://cdn.instructables.com/F1X/H0GJ/J9YJG2UG/F1XH0GJJ9YJG2UG.SMALL.jpg)

![](https://cdn.instructables.com/F65/0UPT/J9YJG2UJ/F650UPTJ9YJG2UJ.SMALL.jpg)

![](https://cdn.instructables.com/FJY/OPSI/J9YJG2V6/FJYOPSIJ9YJG2V6.SMALL.jpg)

![](https://www.instructables.com/files/deriv/FDB/W6JI/J9YJG1CB/FDBW6JIJ9YJG1CB.ANIMATED.LARGE.gif)

There's nothing to it. Just press-fit the lens into the adaptor and press-fit the adaptor onto the camera lens. If the fit is too tight or too loose, adjust the **tolerance** parameter accordingly and print another version.

## Step 4: Get Some Time-lapse!

![](https://cdn.instructables.com/F5U/E2LG/J9YJG32A/F5UE2LGJ9YJG32A.MEDIUM.jpg)

![](https://cdn.instructables.com/FSN/5W57/J9YJG32O/FSN5W57J9YJG32O.SMALL.jpg)

![](https://cdn.instructables.com/F39/OHIJ/JA1TQ28M/F39OHIJJA1TQ28M.SMALL.jpg)

![](https://cdn.instructables.com/FEC/KUEX/JA1TQ28S/FECKUEXJA1TQ28S.SMALL.jpg)

This macro lens is good for 3D printing time-lapses because it doesn't distort the image so much and it puts all the background stuff out of focus.

I'm using my macro lens with a time-lapse rig I made that's pictured here. It's got a USB cable clip that takes pressure off of the usb power jack and an LED grid for direct lighting.

Here's a link to that Fusion file if you want to print the parts and make your own, if there's any interest I might make an instructable on the assembly and electronics too: <http://a360.co/2iWYPkf>

![](https://cdn.instructables.com/F3C/RDM1/J9YJFY1E/F3CRDM1J9YJFY1E.ANIMATED.LARGE.gif)
