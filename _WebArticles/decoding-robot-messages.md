# Decoding robot messages

_Captured: 2017-11-25 at 09:43 from [orionrobots.co.uk](https://orionrobots.co.uk/2017/11/24/decoding-robot-messages/)_

There are crazy sales this weekend at some of my favourite places to buy stuff to play with. Pimoroni, The PiHut and Cool Components are all having fun.

Pimoroni have been running a [#yarrbooty challenge again on Twitter](https://twitter.com/search?q=%23yarrbooty&src=typd) \- with vouchers and free stuff.

Pimoroni have also been dropping interesting messages about the robots taking over, and then streams of binary-as-text.

I had a bit of fun decoding them.

The first message was in their email:

> 01101100 01101111 01110110 01100101 00100000 00100110 00100000 01101011 01101001 01110011 01110011 01100101 01110011, 01010100 01101000 01100101 00100000 01110000 01101001 01101101 01101111 01110010 01101111 01101110 01101001 00100000 01110010 01101111 01100010 01101111 01110100 01110011

I used python to decode this. Lets put the encoded_message into a variable:
    
    
    encoded_message = "01101100 01101111 01110110 01100101 00100000 00100110 00100000 01101011 01101001 01110011 01110011 01100101 01110011, 01010100 01101000 01100101 00100000 01110000 01101001 01101101 01101111 01110010 01101111 01101110 01101001 00100000 01110010 01101111 01100010 01101111 01110100 01110011"
    

First, I decided to split around the comma - it makes it a bit easier:
    
    
    >>> message_parts = encoded_message.split(",")
    

`split` is an operation a string has, which you can give a separator, and it uses the separator (in this case a comma) to split the string into a list of parts. This gives me an array of two message parts (note I am clipping the full messages):
    
    
    >>> message_parts
    ["01101100 ...part 1... 01110011", "01010100 ...part 2... 01110011"]
    

I can then decode them. I worked on the first one initially - again, easier to take small bites. Lets see about making a list of characters. The default `split`, without giving a separator, uses space.
    
    
    >>> characters = message_parts[0].split()
    >>> characters
    ["01101100", "01101111"..., "01110011"]
    

So now we can start to convert these. Python has a type `int`, and this type can be made from a string and a base. By base - I mean a mathematical base. Base 10 is what you are used to - counting from 0 to 9 then putting in the 1 to make 10. That is called decimal - "dec" meaning 10 - a counting to ten system

The messages above are binary - a counting to 2 system. It goes 0, 1, 10. Sounds odd - but it means you can just use `on` and `off` to write a message - perfect when you are made out of switches like a computer or a robot. So our base here is 2. Lets see if we can get decimal out from the first of our characters in our list:
    
    
    >>> int(characters[0], 2)
    108
    

Now I guess this might be a letter. Letters on computers are numbers, with a code to put them back. For most occasions this code is UTF-8, but there are some other older codes hanging around. In python 3 - it assumes you mean utf-8. The function `chr` can be used to turn a number into a letter.
    
    
    >>> chr(108)
    'l'
    

So these are letters… hmmm… Time to make a loop. We want to go over each letter. Python can turn a thing into a loop in a single line - known as a list comprehension. I love them for decoding stuff. I'll use "c" for character here.
    
    
    >>> message_numbers = [int(c,2) for c in characters]
    >>> message_numbers
    [108, ... ..., 115]
    

Now we are getting somewhere. Lets make each of those into a letter. NO SPOILER HERE - you'll have to run the code yourself…
    
    
    >>> message_letters = [chr(n) for n in message_numbers]
    >>> message_letters
    ['l', ... 's']
    

But wait - this is a list of letters - it's not a message yet. There is however, a way to glue a list back together in python - it's called `join`. It expects a separator. In this case - I'm giving it the empty string `''`.
    
    
    >>> ''.join(message_letters)
    'l ..... s'
    

Sorry - still no spoilers!

Now we have a couple of parts, and besides, there were more messages sent about this way on twitter. So we want to reuse this stuff. The way to do that is to make a function. In python - this is called `def`. I'm going to combine what we've done before into a single function:
    
    
    def decode_message_part(message_part):
        characters = message_part.split()
        message_numbers = [int(c,2) for c in characters]
        message_letters = [chr(n) for n in message_numbers]
        return ''.join(message_letters)
    

Now we can use this for both parts of our message:
    
    
    >>> decode_message_part(message_parts[0])
    'l .... s'
    >>> decode_message_part(message_parts[1])
    'T .... s'
    

Or for other messages
    
    
    >>> decode_message_part('01001110 01101111 01110111 00100000 01111001 01101111 01110101 00100000 01100011 01100001 01101110 00100000 01110010 01100101 01100001 01100100 001 00000 01100010 01101001 01101110 01100001 01110010 01111001')
    'Now you can read binary'
    

But wait, there's more. I decided (and other twitter people) that it would be fun to respond in binary too. And I wrote code for that too. We kind of need to do the same process in reverse. Lets stuff something in a variable to play with:
    
    
    >>> message = "I can now make binary messages"
    

Now to go the other way, it's worth knowing that in python (and many languages) a string is a special case for an array - of characters. If we try to get the first item of it:
    
    
    >>> message[0]
    'I'
    

So we can loop over these, and use the python function `ord` to get the number for the letters.
    
    
    >>> message_numbers = [ord(c) for c in message]
    >>> message_numbers
    [73, 32, 99, 97, 110, 32, 110, 111, 119, 32, 109, 97, 107, 101, 32, 98, 105, 110, 97, 114, 121, 32, 109, 101, 115, 115, 97, 103, 101, 115]
    

Now we have numbers, we need to convert these to binary. This is a little tricky. Python has a way to do this, but it's not quite as obvious. The `string.format` method uses format striings to specify what you want it to do with parameters.

`"{}".format(73)` would just make a string `"73"`. The `{}` means to pick up the first parameter - in this case 73. We want binary. Putting `:b` in the braces tells python how we want it to convert that 73 into binary.
    
    
    >>> "{:b}".format(73)
    '1001001'
    

But wait, it may be subtle - bit did you notice that all the binary above started with 0. We need to pad these out. Putting an `8` in front of the b - says we want 8 characters.
    
    
    >>> "{:8b}".format(73)
    ' 1001001'
    

Only - its padding with spaces. To tell it we mean '0' we just put that in front of the 8.
    
    
    >>> "{:08b}".format(73)
    '01001001'
    

Now we have the binary for one character. Lets get the whole list.
    
    
    >>> message_binary = ["{:08b}".format(n) for n in message_numbers]
    >>> message_binary
    ['01001001', '00100000', '01100011', '01100001', '01101110', '00100000', '01101110', '01101111',
     '01110111', '00100000', '01101101', '01100001', '01101011', '01100101', '00100000', '01100010',
     '01101001', '01101110', '01100001', '01110010', '01111001', '00100000', '01101101', '01100101',
     '01110011', '01110011', '01100001', '01100111', '01100101', '01110011']
    

Now we just need to combine this with spaces. We can do this trick using `join` again.
    
    
    >>> encoded_message = ' '.join(message_binary)
    >>> encoded_message
    '01001001 00100000 01100011 01100001 01101110 00100000 01101110 01101111 01110111 00100000 01101101 01100001 01101011 01100101 00100000 01100010 01101001 01101110 01100001 01110010 01111001 00100000 01101101 01100101 01110011 01110011 01100001 01100111 01100101 01110011'
    

So we've encoded our message. You can take this - put it back through our earlier function to get it back out:
    
    
    >>> decode_message_part(encoded_message)
    'I can now make binary messages'
    

Now what about encoding any old message - well I put that into a function too:
    
    
    def encode_message_part(message_part):
        message_numbers = [ord(c) for c in message_part]
        message_binary = ["{:08b}".format(n) for n in message_numbers]
        return ' '.join(message_binary)
    

I can now encode, and decode messages like this at will, and using these functions, so can you. You can converse on [a binary Twitter thread](https://twitter.com/pimoroni/status/933982270230319104). Have fun!
