
sudo rm -rf /System/Library/Extensions/ProlificUsbSerial.kext

sudo nvram boot-args="kext-dev-mode=1"

sudo nvram boot-args="kext-dev-mode=1 rootless=0"

ProlificUsbSerial.kext

SiLabsUSBDriver.kext

kextstat

tail -n 50 /var/log/install.log

cd /dev

ls -la /dev/ | grep usb

power-cycling the Mac

(kernel) Kext com.silabs.driver.CP210xVCPDriver not found for unload request.
Failed to unload com.silabs.driver.CP210xVCPDriver - (libkern/kext) not found.
(kernel) Kext com.silabs.driver.CP210xVCPDriver not found for unload request.
Failed to unload com.silabs.driver.CP210xVCPDriver - (libkern/kext) not found.

sudo kextload /Library/Extensions/SiLabsUSBDriver.kext

sudo kextutil /Library/Extensions/SiLabsUSBDriver.kext

sudo kextload /Library/Extensions/SiLabsUSBDriver.kext

kextstat | grep silabs

kextutil /Library/Extensions/SiLabsUSBDriver.kext

screen /dev/cu.SLAB_USBtoUART 115200

screen /dev/tty.SLAB_USBtoUART 115200

PL-2303 USB-to-Serial adaptor

ls tty.usbserial*

ls /dev/tty*

ioreg -c IOSerialBSDClient  | grep usb

system integrity:

macworld.com/article/2948140/os-x/private-i-el-capitans-system-integrity-protection-will-shift-utilities-functions.html

csrutil(1)
csrutil status

nvram -xp

lsof | grep usbserial

SiLabs CP2104

First of all, I was never able to get this to work using the USB port like Adafruit showed in their documentation. The only way I was able to get this to work was with a sparkfun FTDI usb adapter, and a 220 OHM resister from ground to G0. Wire everything up like it's shown in the diagram, and then hit the reset button. Then you can upload your sketch. Make sure you disconnect the ground from G0 and reset after the upload and it will come up normally.

As discussed in the following thread, it appears the v5.x SiLabs driver is completely broken.
http://community.silabs.com/t5/Interface/mac-os-10-12-6-and-cp2102/m-p/206785
Fortunately the v4.x driver, which is included in the "Legacy MacVCP Driver" folder in the same download, works fine. Do note that you might have to install it twice for it to work, as the first install will just remove the existing driver. If it's installed, there should be a "SiLabsUSBDriver.kext" file in /Library/Extensions with a date created of June 16, 2017.

I can confirm that the old drivers worked.

Steps:
1. Download old firmware linked here: http://community.silabs.com/t5/Interface-Knowledge-Base/Legacy-OS-Software-and-Driver-Packages/ta-p/182585
2. Run the uninstall that was included with that download.
3. Install the drivers in that package.
4. Reboot.
5. Flash with Arduino IDE (using the default esptool.)

Thanks for getting this resolved. Must be super annoying when one of your parts suppliers decides to break their drivers out of nowhere like this.

Terminal screen command mit: ctrl+a k schliessen
