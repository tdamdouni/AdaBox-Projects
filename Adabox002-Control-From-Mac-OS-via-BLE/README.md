# Adabox002-Control-From-Mac-OS-via-BLE

Based on [Adafruit Python BluefruitLE Library](https://github.com/adafruit/Adafruit_Python_BluefruitLE) example `uart_service.py` for macOS

Motor control via Bluetooth is based on sending 4-bit string via `uart.write(<string>)`

Information on this can be found in a mobile app called "Bluefruit"

 - Press Forward: `!B51`

 - Release Forward: `!B50`
 
 - Press Backward: `!B61`

 - Release Backward: `!B60`
 
 - Press Left: `!B71`

 - Release Left: `!B70`
 
 - Press Right: `!B81`

 - Release Right: `!B80`
 

## MotorControlTest

Sends command for forward, backward, left turn, right turn respectively. Each action is executed for 5 seconds, and will be stopped before next action.


## MotorControlWithKeyboard

Key listening in Python found [here](https://stackoverflow.com/questions/11918999/key-listeners-in-python)

Press W, A, S, D respectively for Forward, Left, Backward, Right action.

Press SPACE for to stop action.

Press key once will put the Adabox002 bot in the action until SPACE is pressed.

Press C to end program and disconnect


