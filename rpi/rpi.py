import serial
import time
import csv

port = '/dev/ttyACM1'
R = 10

ser = serial.Serial(port)
ser.flushInput()

def process(v1,i2,do,di):
    return 0

def getReading():
    rawData = ser.readline()
    rawData = rawData[0:len(rawData)-2].decode('utf-8')
    data = rawData.split()
    if len(data) != 4:
        return -1
    v1 = int(data[0])
    v2 = int(data[1])
    i2 = v2/R
    disOut = float(data[2])
    disIn = float(data[3])
    rho = process(v1,i2,disOut,disIn)
    return (rho,disOut,disIn)

while(1):
    print(getReading())
