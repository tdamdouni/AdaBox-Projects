# Example of interaction with a BLE UART device using a UART service
# implementation.
# Author: Tony DiCola

# Motor Control implementation by Sifan Ye

# Keylistener implementation from: https://stackoverflow.com/questions/11918999/key-listeners-in-python

import time
import sys
import termios
import contextlib
import Adafruit_BluefruitLE
from Adafruit_BluefruitLE.services import UART


# Get the BLE provider for the current platform.
ble = Adafruit_BluefruitLE.get_provider()

# For Keylistener
@contextlib.contextmanager
def raw_mode(file):
    old_attrs = termios.tcgetattr(file.fileno())
    new_attrs = old_attrs[:]
    new_attrs[3] = new_attrs[3] & ~(termios.ECHO | termios.ICANON)
    try:
        termios.tcsetattr(file.fileno(), termios.TCSADRAIN, new_attrs)
        yield
    finally:
        termios.tcsetattr(file.fileno(), termios.TCSADRAIN, old_attrs)


# Main function implements the program logic so it can run in a background
# thread.  Most platforms require the main thread to handle GUI events and other
# asyncronous events like BLE actions.  All of the threading logic is taken care
# of automatically though and you just need to provide a main function that uses
# the BLE provider.
def main():
    # Clear any cached data because both bluez and CoreBluetooth have issues with
    # caching data and it going stale.
    ble.clear_cached_data()

    # Get the first available BLE network adapter and make sure it's powered on.
    adapter = ble.get_default_adapter()
    adapter.power_on()
    print('Using adapter: {0}'.format(adapter.name))

    # Disconnect any currently connected UART devices.  Good for cleaning up and
    # starting from a fresh state.
    print('Disconnecting any connected UART devices...')
    UART.disconnect_devices()

    # Scan for UART devices.
    print('Searching for UART device...')
    try:
        adapter.start_scan()
        # Search for the first UART device found (will time out after 60 seconds
        # but you can specify an optional timeout_sec parameter to change it).
        device = UART.find_device()
        if device is None:
            raise RuntimeError('Failed to find UART device!')
    finally:
        # Make sure scanning is stopped before exiting.
        adapter.stop_scan()

    print('Connecting to device...')
    device.connect()  # Will time out after 60 seconds, specify timeout_sec parameter
                      # to change the timeout.

    # Once connected do everything else in a try/finally to make sure the device
    # is disconnected when done.
    try:
        # Wait for service discovery to complete for the UART service.  Will
        # time out after 60 seconds (specify timeout_sec parameter to override).
        print('Discovering services...')
        UART.discover(device)

        # Once service discovery is complete create an instance of the service
        # and start interacting with it.
        uart = UART(device)

        # Write a string to the TX characteristic.
        
        print("Motor control test start")
        
        with raw_mode(sys.stdin):
        
            try:

                status = 0
    
                while True:
                    ch = sys.stdin.read(1)
                    if not ch or ch == chr(4):
                        break              

                    if ch == 'w':
                        print("FORWARD!!!")
                        uart.write('!B51')
                        status = 1
                        
                    if ch == 's':
                         print("FALL BACK!!!")
                         uart.write('!B61')
                         status = -1

                    if ch == 'a':
                         print("Turn Left!")
                         uart.write('!B71')
                         status = 2

                    if ch == 'd':
                         print("Turn Right!")
                         uart.write('!B81')
                         status = 2

                    if ch == ' ':
                         print("HALT!!")
                         if status == 1:
                            uart.write('!B50')
                         elif status == -1:
                            uart.write('!B60')
                         elif status == 2:
                            uart.write('!B70')
                         elif status == 3:
                            uart.write('!B80')

                    if ch == 'c':
                        break
    
            except (KeyboardInterrupt, EOFError):
                pass
    
        print("Motor control test concluded")

    finally:
        # Make sure device is disconnected on exit.
        device.disconnect()
        print("Device disconnected")


# Initialize the BLE system.  MUST be called before other BLE calls!
ble.initialize()

# Start the mainloop to process BLE events, and run the provided function in
# a background thread.  When the provided main function stops running, returns
# an integer status code, or throws an error the program will exit.
ble.run_mainloop_with(main)
