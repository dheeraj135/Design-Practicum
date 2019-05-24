import serial 
ser1 = serial.Serial('/dev/ttyACM0')
ser2 = serial.Serial('/dev/ttyACM1')
while 1:
    d1 = ser1.readline()
    d2 = ser2.readline()
    print("Data from 1: ",d1)
    print("Data from 2: ",d2)