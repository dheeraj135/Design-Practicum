import datetime 
import serial
import csv
import math

di = 5

now = datetime.datetime.now()
fname = "../data/manual-"+now.strftime("%d-%m-%Y-%H-%M-%S")+".csv"

port = '/dev/ttyACM1'
ser = serial.Serial(port)
ser.flushInput()
ser.flushInput()
R = 10000
pi = math.pi
def process(v1,i2,do,di):
    rho = v1/i2*pi
    rho = rho*(do)*(do+di)/di
    return rho

def getReading(dist):
    ser.flushInput()
    rawData = ser.readline()
    print(rawData)
    rawData = rawData[0:len(rawData)-2].decode('utf-8')
    data = rawData.split()
    if len(data) != 2:
        return getReading(dist)
    v1 = int(data[0])*5.0/1023
    v2 = int(data[1])*5.0/1023
    print(v1,v2)
    i2 = v2/R
    return process(v1,i2,dist,di)

for i in range(5):
    print("Enter Distance between outer rods: ")
    dist = float(input())
    rho = 0
    ser.flushInput()
    for j in range(20):
        rho+=getReading(dist)
    rho/=20

    with open(fname,"a") as f:
        writer = csv.writer(f,delimiter=",")
        writer.writerow([rho,dist])
    
