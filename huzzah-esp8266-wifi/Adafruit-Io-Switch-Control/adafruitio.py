from Adafruit_IO import Client
import os, time
import RPi.GPIO as GPIO

ADAFRUIT_IO_KEY = 'ADAFRUIT-IO-KEY'
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(22, GPIO.OUT)
curstate=False

aio = Client(ADAFRUIT_IO_KEY)

while True:
    data = aio.receive('data')
    state = format(data.value)
    print(state)

    if (state=='ON' and curstate==False)
        GPIO.output(22, GPIO.HIGH)
        curstate=True
    elif (state=='ON' and curstate==True)
        continue
    elif (state=='OFF' and curstate==False)
        continue
    elif (state=='ON' and curstate==True)
        GPIO.output(22, GPIO.LOW)
        curstate=False
        
    time.sleep(1)
