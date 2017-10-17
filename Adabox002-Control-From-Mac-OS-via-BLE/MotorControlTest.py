# Example of interaction with a BLE UART device using a UART service
# implementation.
# Author: Tony DiCola

# Motor Control implementation by Sifan Ye

import time
import Adafruit_BluefruitLE
from Adafruit_BluefruitLE.services import UART


# Get the BLE provider for the current platform.
ble = Adafruit_BluefruitLE.get_provider()


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
        
        print("FORWARD!!!")
        # Press forward button
        uart.write('!B51')
        time.sleep(5)
        
        print("HALT!!!")
        # Release forward button
        uart.write('!B50')
        time.sleep(5)
    
        print("FALL BACK!!!")
        # Press backward button
        uart.write('!B61')
        time.sleep(5)

        print("HALT!!!")
        # Release forward button
        uart.write('!B60')
        time.sleep(5)

        print("TURN LEFT!!!")
        # Press left button
        uart.write('!B71')
        time.sleep(5)
    
        print("HALT!!!")
        # Release left button
        uart.write('!B70')
        time.sleep(5)
    
        print("TURN RIGHT!!!")
        # Press right button
        uart.write('!B81')
        time.sleep(5)
    
        print("HALT!!!")
        # Release right button
        uart.write('!B80')
        time.sleep(5)
    
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
