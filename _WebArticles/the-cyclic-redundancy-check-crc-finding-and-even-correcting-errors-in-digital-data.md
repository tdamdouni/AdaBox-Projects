# The Cyclic Redundancy Check (CRC): Finding—and Even Correcting—Errors in Digital Data

_Captured: 2018-01-29 at 18:13 from [www.allaboutcircuits.com](https://www.allaboutcircuits.com/technical-articles/the-cyclic-redundancy-check-crc-findingand-even-correctingerrors-in-digital/)_

This technical brief explains what a CRC is and how you can use it to make your digital communication more robust.

The world is now completely dependent on the storage and transmission of digital data. Airplanes, stock markets, security systems, pressure cookers--the fact is, modern life would swiftly descend into chaos if we could not ensure accuracy in the constantly flowing and unfathomably immense torrent of ones and zeros.

There are two primary tasks involved in maintaining the integrity of our digital data. Number one is avoiding errors in the first place; this objective involves a variety of engineering practices that encourage reliable transmission and reception of digital data. But despite our best efforts, errors can happen, and this brings us to the second task: _detecting_ errors. If a system can detect errors, it can also compensate for those errors by simply throwing out the questionable data or by requesting a duplicate transmission.

#### The Error-Detection Method of Choice

If you are familiar with the parity bit sometimes used in UART communication, you know something about error detection. But the parity bit is a rather pathetic error-detection mechanism; actually, as far as I can tell, most of the error-detection methods are more or less pathetic compared to the cyclic redundancy check (CRC), which has clearly emerged as the dominant approach--some big names in digital communication (including CAN, USB, and Ethernet) use a CRC as part of their data-transfer protocol.

##### _Structure of a USB data packet._

#### Effective, but Not Simple

This short article is not the place to explore the details of CRC computation and performance--and, furthermore, I'm not qualified to expound on that subject. The bottom line is that a binary "polynomial" is applied to a data stream in such a way as to generate a checksum that is very likely to change if one or more bits in the message have changed.

This "polynomial" business is simply a mathematically convenient way of referring to a specific sequence of bits. For example:

This is the widely-used "CCITT" polynomial. It is a 16th-order polynomial, which means that the corresponding binary number is 16 bits wide and that the resulting CRC checksum will be 16 bits wide. (Note that the coefficient for the highest-order term is assumed to be 1 and is omitted in the binary version.) Terms that don't appear in the mathematical expression have binary 0 as the coefficient.

![](https://www.allaboutcircuits.com/uploads/articles/TBCRC_HardwareCRC.JPG)

> _Error detection is easier and more efficient with a hardware CRC module; this diagram, from the EFM8LB1 reference manual, conveys the functionality of the CRC peripheral in the EFM8 Laser Bee microcontroller._

#### Two CRCs, Not One

Generating a CRC only for the original message doesn't help you. The key to implementing CRC error detection is ensuring that both transmitter and receiver generate a checksum, and in exactly the same way.

The transmitter generates the checksum on the to-be-transmitted data and includes it in the original message, and the receiver generates its own checksum using the received data. If the receiver's message does not match the transmitter's message, it is highly probable that the checksums will be different; thus, the receiver considers the data to be erroneous if the CRC checksums do not match.

#### Taking It a Step Further

You should be aware of the fact that CRC processing can actually be used to _correct_ errors, rather than merely detect them. We're dealing with binary data here, so if the CRC enables us to identify an erroneous bit, we can restore the original information by simply flipping the bit.

The details of CRC-based error correction are beyond my intellectual comfort zone. If you want more information, you'll have to continue your research elsewhere or hope that this topic is soon covered in a new AAC article!
