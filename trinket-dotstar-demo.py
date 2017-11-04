# Trinket DotStar demo
# Welcome to CircuitPython 2.1.0

import board
import adafruit_dotstar as dotstar
import time

# Turn off the one pixel connected internally! autoshow is on
idot = dotstar.DotStar(board.APA102_SCK, board.APA102_MOSI, 1, brightness=0.2)
idot[0] = (0, 0, 0)

# DotStar strip (of LEDs) ...
NUMPIXELS = 8
# ... connected externally!
edot = dotstar.DotStar(board.D3, board.D4, NUMPIXELS, brightness=1)

# Helper to give us a nice color swirl
def wheel(pos):
    # Input a value 0 to 255 to get a color value.
    # The colours are a transition r - g - b - back to r.
    if (pos < 0):
        return [0, 0, 0]
    if (pos > 255):
        return [0, 0, 0]
    if (pos < 85):
        return [int(pos * 3), int(255 - (pos*3)), 0]
    elif (pos < 170):
        pos -= 85
        return [int(255 - pos*3), 0, int(pos*3)]
    else:
        pos -= 170
        return [0, int(pos*3), int(255 - pos*3)]

######################### MAIN LOOP ##############################

i = 0
print("Entering main loop!")
while True:
  # also make the neopixels swirl around
  for p in range(NUMPIXELS):
      idx = int ((p * 256 / NUMPIXELS) + i)
      edot[p] = wheel(idx & 255)
  edot.show()

  i = (i+8) % 256  # run from 0 to 255
  time.sleep(0.01) # make bigger to slow down

