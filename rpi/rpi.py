import serial
import time
import csv
import math
import os
import datetime
pi = math.pi
port = '/dev/ttyACM0'
R = 10

ser = serial.Serial(port)
ser.flushInput()
now = datetime.datetime.now()
fname = "../data/manual-"+now.strftime("%d-%m-%Y-%H-%M-%S")+".csv"

def process(v1,i2,do,di):
    rho = v1/i2*pi
    rho = rho*(do)*(do+di)/di
    return rho

def getReading():
    rawData = ser.readline()
    rawData = rawData[0:len(rawData)-2].decode('utf-8')
    data = rawData.split()
    if len(data) != 4:
        return (-1,-1)
    v1 = int(data[0])
    v2 = int(data[1])
    i2 = v2/R
    disOut = float(data[2])
    disIn = float(data[3])
    rho = process(v1,i2,disOut,disIn)
    return (rho,disOut)

ser.write(b'go ahead!\n')

for i in range(5):
    rho = 0
    disOut = 0
    ser.flushInput()
    for j in range(20):
        (y1,x1)=getReading()
        rho+=y1
        disOut+=x1
    rho/=20
    disOut/=20

    with open(fname,"a") as f:
        writer = csv.writer(f,delimiter=",")
        writer.writerow([rho,disOut])

os.system("python3 plot_from_csv.py "+fname)