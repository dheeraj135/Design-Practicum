import serial
import time
import csv

ser = serial.Serial('/dev/ttyACM0')
ser.flushInput()

i = input()
j = input()
i = int(i)
j = int(j)
while True:
    try:
        ser_bytes = ser.readline()
        ser_bytes2 = ser.readline()
        decoded_bytes = float(ser_bytes[0:len(ser_bytes)-2].decode("utf-8"))
        decoded_bytes2 = float(ser_bytes2[0:len(ser_bytes)-2].decode("utf-8"))
        decoded_bytes = decoded_bytes*5.0/1023;
        decoded_bytes2 = decoded_bytes2*5.0/1023;
        print(decoded_bytes)
        print(decoded_bytes2)
        with open("test_data.csv","a") as f:
            writer = csv.writer(f,delimiter=",")
            writer.writerow([time.time(),i,j,decoded_bytes,decoded_bytes2])
    except:
        print("Keyboard Interrupt")
        break