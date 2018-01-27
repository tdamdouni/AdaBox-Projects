# Fuse Tutorial

_Captured: 2017-10-07 at 15:59 from [www.digikey.com](https://www.digikey.com/en/articles/techzone/2017/oct/fuse-tutorial?WT.z_sm_link=TZCircprotect)_

Contributed By Digi-Key Electronics

Electronics have become exceedingly precise and fast. As the functionality of components increases, so does their fragility. It is much easier to damage an FPGA than it is to damage a large power resistor. The electronics industry has come a long way in regards to providing clean power to a circuit, but there can still be spikes on the line that can be potentially damaging. Along with this, it is always possible for a short to develop in a circuit that can cause overcurrent conditions which can damage devices. This is where the simple fuse enters the equation. A fuse is going to be much cheaper than an entire electronic device. Often, a component that comes in at much less than one dollar can save thousands of dollars of other equipment. This article will cover different considerations for choosing a fuse, some industry vernacular, and applications for different kinds of fuses.

A fuse is a device that protects the rest of the circuit. It is typically an inline device that allows a certain amount of current to flow through it. If too much current is flowing, the fuse will literally melt causing an opening and breaking the current flow. Two of the largest electrical considerations for a fuse are the "Current Rating" and "Voltage Rating". The current rating is the maximum current that can flow through the fuse under normal conditions. Fuses will typically be de-rated at 25% to avoid nuisance blowing at 25˚C. An example from an article titled "[Fuseology](https://www.digikey.com/en/pdf/l/littelfuse/fuseology)" by [Littelfuse](https://www.digikey.com/en/supplier-centers/l/littelfuse) goes on to use a 10 amp fuse for a 7.5 amp circuit at 25˚C. The following equation shows how to find the current rating.

![Equation 1](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-equation1.jpg?ts=7faa6555-c0bc-425b-853d-8de82b63a406&la=en-US)

In the parametric search of the "[Fuses](https://www.digikey.com/products/en/circuit-protection/fuses/139)" section on the Digi-Key website there is a tab for the "Current Rating".Figure 1 illustrates where the "Current Rating" tab can be found. By looking at the image it is possible to see the current rating in the upper right hand corner. To pick the proper current rating, simply scroll through the tab until the desired rating is found. Highlight this by clicking it and then hit the red apply filters button in the bottom left hand of Figure 1.

![Image of current rating location](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig1.jpg?ts=30871ec2-422c-4e6d-91f5-66e8497f535c&la=en-US)

> _Figure 1: Current rating location._

As mentioned earlier, the voltage rating for a fuse is also very important. The voltage rating is the maximum voltage that the fuse can safely operate at when an overcurrent situation happens. The voltage rating on the fuse can be higher than the voltage present on the circuit, but not the other way around. If a 250 VAC fuse is used on a device that uses 120 VAC, there should be no problem. If a 125 VAC fuse is used on a 250 VAC supply, the fuse will be damaged and the likelihood of arching is great when the fuse blows. Another important aspect of a fuse is the "Breaking Capacity". This is the maximum level of current that the fuse can blow open with. Typically, a ceramic fuse will have a higher breaking capacity than a glass fuse.

Size is another general characteristic that cannot be overlooked. There are no standard fuse sizes; however, there are some that are more common than others. One of the more common sizes for a cylindrical fuse is the 5 mm x 20 mm package size. An example of a fuse with the 5 mm x 20 mm package size is the [0235001.HXP](https://www.digikey.com/product-detail/en/littelfuse-inc/0235001.HXP/F2677-ND/778142) from Littelfuse. This is what most people typically associate with as a fuse. It has two metal caps on both ends and a small wire that can melt if overcurrent conditions occur. Figure 2 is an image of the 0235001.HXP.

![Image of Littelfuse’s 0235001.HXP fuse](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig2.jpg?ts=e68cfb22-70d4-4967-a15a-93feb005d393&la=en-US)

> _Figure 2: Littelfuse's 0235001.HXP fuse._

A fuse like this will require a holder. There are different ways to find the appropriate holder for a given fuse. One of the ways is by using the documentation for the fuse. The 0235001.HXP belongs to the 235 series from Littlefuse. The [235 series datasheet](https://www.digikey.com/en/pdf/l/littelfuse/235-series-axial-lead-cartridge-fuses) has a section at the bottom titled "Recommended Accessories". This will have different types of accessories for fuses from this series. There are holders, blocks, and clips. These are the different types of housings that can hold the fuse. Figure 3 depicts this part of the datasheet; there are hyperlinks that can be used on the datasheet that will lead to a page on the Littlefuse website.

![Image of recommended accessories for the Littelfuse 235 series](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig3.jpg?ts=2703f946-cd1d-4d2c-b44c-d394f0a94276&la=en-US)

> _Figure 3: Recommended accessories from the Littelfuse 235 series fuse datasheet (Image courtesy of Littelfuse)._

By clicking on the "[345_ISF](http://www.littelfuse.com/products/fuse-blocks-fuseholders-and-fuse-accessories/fuseholders/345_isf.aspx)" hyperlink, one will be sent to a page on the Littlefuse website that has three different sized holders. Keep in mind that the 0235001.HXP is a 5 mm x 20 mm fuse. On the Littlefuse page for 345_ISF there is a section that has 5 mm x 20 mm options, this is about 2/3 of the way down the page. There will be part numbers for all of these fuse holders. Figure 4 shows the 3455HS2 within the list.

![Image of 3455HS2 entry highlighted Littelfuse’s 345 series fuseholder webpage \(click to enlarge\)](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig4.jpg?ts=b28e4cfe-b588-42ad-bd7d-5470693b4bf0&h=116&w=600&la=en-US)

> _Figure 4: The 3455HS2 entry highlighted Littelfuse's 345 series fuseholder webpage (Image courtesy of Littelfuse)._

By taking the number 3455HS2 and putting it into the Digi-Key search bar, it will be possible to find the 03455HS2H on the Digi-Key website. There is an "H" at the end of the part number on the Digi-Key website. This is only a packaging suffix meaning that this product was shipped to Digi-Key in a package of 100 pieces. The "0" in front of the number is just a place holder; it has no bearing on the product number.

Another way to find the proper housing for a fuse is by searching the Digi-Key website on the "[Fuseholders](https://www.digikey.com/products/en/circuit-protection/fuseholders/140)" page. There will be a tab for "Fuse Size" that can be used to select all of the 5 mm x 20 mm fuse holders. Since fuse holders can sometimes accept multiple fuse package sizes, make sure to highlight all of the applicable options, like in Figure 5, and then select the apply filters button. The 5 mm diameter was included because some holders will only hold the center of the fuse. Fuseholders like this make the length of the fuse irrelevant. An example is the [FC-211-DD](https://www.digikey.com/product-detail/en/bel-fuse-inc/FC-211-22/507-1415-ND/622587) from [Bel Fuse Inc](https://www.digikey.com/en/supplier-centers/b/bel-fuse).

![Selection of 5 mm fuse sizes from the Digi-Key part search field](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig5.jpg?ts=d094c70a-01e9-4e2f-909d-86a38bded95a&la=en-US)

> _Figure 5: Selection of 5 mm fuse sizes from the Digi-Key part search field._

It is important to note that fuse holders have electrical ratings as well. The most important thing to remember for the fuse holder is that the voltage and current rating need to be higher than what will actually be present on the circuit. If there is a 10 amp fuse, using a 20 amp fuse holder will be no problem; whereas using a 10 amp fuse holder with a 20 amp fuse will likely cause problems. The same theory is true for the voltage rating on the fuse holder.

Another easy solution to find the proper holder for a fuse is to use the Digi-Key website's associated products tab. At the bottom of the 0235001.HXP page there is an associated products area. This will have items from the same manufacturer that are associated. Figure 6 illustrates what this associated products area looks like. If there is a "View More" hyperlink, then more options are available than are currently being shown. By simply clicking the "View More" a new page will open with more accessory options.

![Image of associated product area for Littelfuse’s 0235001.HXP fuse](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig6.jpg?ts=f01a4840-d605-46a6-8afd-281341e2b3da&la=en-US)

> _Figure 6: Associated product area for Littelfuse's 0235001.HXP fuse._

Another common size for a fuse is the 3AB/3AG size. This will be 1-1/4" x 1/4", or 6.3 mm x 32 mm. These will look very similar to the 5 mm x 20 mm fuses. So if replacing a fuse, it is worth using a caliper measurement to make sure the fuse is the proper size. An example of a 3AB, 3AG fuse is the [BK/ABC-15R](https://www.digikey.com/product-detail/en/eaton/BK-ABC-15-R/283-2609-ND/954134) from [Eaton](https://www.digikey.com/en/supplier-centers/e/eaton). If searching for a replacement fuse where a part number is known but not in stock, there is a quick and easy way to search on the Digi-Key website. The most important aspects of the BK/ABC-15R are the current rating, voltage rating, size, and response time. On the product specific page of the Digi-Key website there is an area labeled "Product Attributes". This is not only a defining list of the attributes, but also another form of a parametric search. Each attribute has a check box off to the right that, when checked, can select all similar products within the "Fuses" page. By checking the box by "Current Rating", "Voltage Rating - AC", "Response Time", and "Package / Case", the user can now search all similar items by hitting the search button below. After hitting the search button, simply select the "In Stock" button and hit "Apply Filters". Figures 7 and 8 demonstrate this.

![Image of selecting quick filters related to Eaton’s BK/ABC-15R fuse holder](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig7.jpg?ts=7d86531b-cc0e-467f-b932-ff636900d38d&la=en-US)

> _Figure 7: Selecting quick filters related to Eaton's BK/ABC-15R fuse holder._

![Image of selecting “In Stock” before hitting Apply Filters](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig8.jpg?ts=41f2c5ca-7ab3-4292-9e3b-c36c9bb100fd&la=en-US)

> _Figure 8: Selecting "In Stock" before hitting Apply Filters for the selected quick filters in Figure 7._

There are also many surface-mounted options for fuses. An example of this would be the [ERB-RE1R00V](https://www.digikey.com/product-detail/en/panasonic-electronic-components/ERB-RE1R00V/P15124CT-ND/2796818) from [Panasonic Electronic Components](https://www.digikey.com/en/supplier-centers/p/panasonic). This fuse is housed in a 0603 package and meant to be mounted right onto a board. This is great news for the engineer tasked with taking up as little space as possible. Automotive fuses are also very common with two major types, blade and link fuses. An example of a blade fuse would be the [0299030.ZXNV](https://www.digikey.com/product-detail/en/littelfuse-inc/0299030.ZXNV/F1036-ND/146666) from Littelfuse. These types of fuses will fit into a holder. The particular holder for the 0299030.ZXNV is the [0MAB0001F](https://www.digikey.com/product-detail/en/littelfuse-inc/0MAB0001F/F1085-ND/146687). Figures 9 and 10 show the fuse and holder respectively. Like the previous examples, accessories like holders can typically be found in the associated products area.

![Image of Littelfuse’s 0299030.ZXNV 299 series fuse](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig9.jpg?ts=0138b4bc-f87d-4189-81a5-6baa2f703705&la=en-US)

> _Figure 9: Littelfuse's 0299030.ZXNV 299 series fuse._

![Image of Littelfuse’s 0MAB0001F fuseholder](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig10.jpg?ts=78bd768d-b1f4-41fa-8a1d-82a4817c3413&la=en-US)

> _Figure 10: Littelfuse's 0MAB0001F fuseholder for the Figure 9 fuse_

Automotive blade fuses follow a color code based on the current rating that they carry. They will also typically have the current rating printed on the top of the fuse. Figure 11 shows a color code for 0.5 A to 40 A ratings.

![Image of color code for automotive fuses](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig11.jpg?ts=e7f2fc34-e14c-416d-a7e9-d130df5d11aa&la=en-US)

> _Figure 11: Color code for automotive fuses (Image courtesy of Littelfuse)._

Something that has not been covered yet is the response time of the fuse. There are fast blow fuses which are great for products that expect the same current draw the entire time of their operation. For situations where there is an inrush current like a load that is connected to a motor, a slow blow fuse will be more suitable. This is because there will be a high current for just a moment which would destroy a fast blow fuse but allows the slow blow fuse to survive for a limited amount of time. This is a selectable parameter on the Digi-Key website; it is labeled "Response Time". By highlighting the response time that is desired and hitting the red apply filter button, all of the improper fuses will be removed.

Fuses often require agency approvals because they are safety devices. Digi-Key has made a parameter that allows customers to search for a fuse by agency approvals. There are several combinations of approvals on the Digi-Key website, so it is recommended to try finding other parameters first before finding agency approvals. This is because choosing based on approvals will likely filter out several good options that will work for a given application. By selecting the current rating, voltage rating, size, and other parameters first, the user will be able to more clearly see what is available. This is because the number of possible combinations of agency approvals will be greatly diminished by the time the customer has gotten to that point. To further explain, there were about 265 different sets of agency approvals on the "Fuses" page of the Digi-Key website at the time this was written. Imagine the desired outcome was to find a 10 A slow blow fuse with a 5 mm x 20 mm size that needed CE, CSA, KC, PSE, SEMKO, UL, VDE approvals. By searching through the approvals alone it would take a long time to find the CE, CSA, KC, PSE, SEMKO, UL, VDE option to highlight. By selecting all other parameters first, the approvals list will drop to less than ten options.

Fuses also have a parameter that relates to thermal energy caused by current flow. This is referred to as I2t and is measured in ampere-squared-seconds. There is a parameter on the Digi-Key parametric search that is labeled "Melting I2t". This allows the user to pick what the proper melting I2t value.

Often, a service technician can be in the field and come across a piece of equipment that has a fuse blown. A simple electrical component, while being able to protect a more expensive circuit, can render a piece of equipment completely useless when it goes out. For this reason having a fuse kit lying around may not be such a bad idea. Luckily Digi-Key sells several fuse kits. There is an entire section on the Digi-Key website for fuse kits titled "[Circuit Protection Kits - Fuse](https://www.digikey.com/products/en/kits/circuit-protection-kits-fuse/667)". An example is the [0034.9871](https://www.digikey.com/product-detail/en/schurter-inc/0034.9871/486-3021-ND/642783) from [Schurter, Inc.](https://www.digikey.com/en/supplier-centers/s/schurter) which comes with 180 individual 5 mm x 20 mm fuses ranging from 800 mA to 10 A. Figure 12 depicts the 0034.9871.

![Image of Schurter’s 0034.9871 fuse kit](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig12.jpg?ts=c3acc0af-e4d2-4a02-ac0f-8661b46b7eb4&la=en-US)

> _Figure 12: Schurter's 0034.9871 fuse kit._

Service centers that work on vehicles could also benefit greatly by having a kit of automotive fuses like the [187.6085.9702](https://www.digikey.com/product-detail/en/littelfuse-inc/187.6085.9702/F7079-ND/3997229) from Littelfuse which contains 475 individual fuses ranging from 3 - 80 amps and all rated at 32 VDC. Figure 13 illustrates the 187.6085.9702.

![Image of Littelfuse’s 187.6085.9702 automotive fuse kit](https://www.digikey.com/-/media/Images/Article%20Library/TechZone%20Articles/2017/October/Fuse%20Tutorial/article-2017october-fuse-tutorial-fig13.jpg?ts=5d944755-e16a-4658-9010-ec38f230e306&la=en-US)

> _Figure 13: Littelfuse's 187.6085.9702 automotive fuse kit._

## Conclusion

Fuses are simple devices that are meant to protect a circuit from potentially damaging overcurrent situations. They are a cheap way to make sure that nothing gets damaged. In today's world, circuits can be very complicated with very delicate parts. Fuses come in many different styles and shapes. While these all do the same thing, it is important to make sure to use the proper sized fuse for the given fuse holder. There are no standards when it comes to fuse size, but there are some package sizes that are more common than others. There are a few ratings that are very important when it comes to selecting a fuse. The voltage and current ratings are paramount. A fuse should be de-rated by 25% at room temperature, meaning if there is a 7.5 amp circuit, a 10 amp fuse should be used at 25˚C. Voltage ratings on a fuse can be higher than the voltage on the circuit, but not lower. At the end of the day, a simple fuse is a great way to effectively protect a circuit.

## Resources

  1. "[Fuseology](https://www.digikey.com/en/pdf/l/littelfuse/fuseology)". Retrieved 18 September. 2017
  2. "[Fast Fuses Versus Slow: How do You Choose?](https://www.digikey.com/en/pdf/l/littelfuse/fast-fuses-versus-slow-how-do-you-choose)". Retrieved 18 September. 2017

Disclaimer: The opinions, beliefs, and viewpoints expressed by the various authors and/or forum participants on this website do not necessarily reflect the opinions, beliefs, and viewpoints of Digi-Key Electronics or official policies of Digi-Key Electronics.
