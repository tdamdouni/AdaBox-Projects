# The Matrix Creator: IoT

_Captured: 2018-02-13 at 15:41 from [dzone.com](https://dzone.com/articles/the-matrix-creator-iot?edition=361106&utm_source=Zone%20Newsletter&utm_medium=email&utm_campaign=iot%202018-02-13)_

The Matrix Creator is an interesting multiple sensor hat that fits on a Raspberry Pi 3.

The first step is to connect it, which is a simple snap, no soldering required.

The specs are pretty impressive:

  * Xilinx Spartan 6 XC6SLX4 FPGA
  * Amtel Cortex-M3 ATSAM3S2 Microcontroller
  * 8 MEMS MP34DB02 audio sensor digital microphones
  * ST LSM9DS1 3D accelerometer, 3D gyroscope, 3d magnetometer IMU
  * ST HTS221 capacitive digital sensor for relative humidity and temperature
  * NXP MPL3115A2 precision pressure sensor with altimetry
  * Silicon Labs EM358X -- 2.4 GHz IEEE 802.15.4 Zigbee
  * Sigma Designs ZM5202 -- 868/908/921 MHz ZWave
  * Vishay TSOP573 -- carrier 38.0 kHz IR Receiver
  * Vishay VEML6070 UV light sensor
  * NXP PN512 NFC reader
  * Everloop 35 RGBW LEDs

It runs on Raspian lite and installs via:

![](https://community.hortonworks.com/storage/attachments/56504-matrixcreatorlit.jpg)

![](https://community.hortonworks.com/storage/attachments/56505-matrixcreatorside.png)

![](https://community.hortonworks.com/storage/attachments/56506-matrixcreatortop.jpg)

> _Our Apache NiFi flow for processing the three types of data:_

![](https://community.hortonworks.com/storage/attachments/56501-creatornifiprocessingflow.png)

> _Our versioned Apache NiFi and MiniFi flows:_

![](https://community.hortonworks.com/storage/attachments/56502-creatorflows.png)

> _We tail the three files produced by the three example Python sensor readers:_

![](https://community.hortonworks.com/storage/attachments/56503-matrixminififlow.png)

Both our MiniFi and Apache NiFi flows are very simple and documented above. As Python writes, tail the data from files, then send it from MiniFi to Apache NiFi, which separates the files into different flows for future processing. We could create schemas, convert to JSON, merge the feeds with JSON, and store them in three different data stores or more depending on what you want to do. This can be one on the edge or in Apache NiFi on a cluster. You could have MiniFi or NiFi trigger off specific values or ranges as the need arises. Or, like me, you can just store it for later use in your endless HDFS Data Lake.

## **Using Three Existing Examples**

Getting temperature, UV, and IMU values:
    
    
    python /home/pi/matrix-creator-malos/src/python_test/test_humidity.py 
    
    
        fh = open("/opt/demo/logs/humidity.log", "a")
    
    
        fh.writelines('{0}'.format(humidity_info))
    
    
    python /home/pi/matrix-creator-malos/src/python_test/test_uv.py 
    
    
    /opt/demo/logs/uv.log
    
    
    python /home/pi/matrix-creator-malos/src/python_test/test_imu.py
    
    
    /opt/demo/logs/imu.log
    
    
    /Volumes/seagate/Apps/minifi-toolkit-0.3.0/bin/config.sh transform $1 config.yml
    
    
    scp config.yml pi@192.168.1.197:/opt/demo/minifi-0.3.0/conf

## **Example Data**
