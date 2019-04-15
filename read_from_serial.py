import serial
import time
import csv
import sys

def read_from_serial(a,b,depth,filename = "test_runs/sample.csv",port='/dev/ttyACM0',sample=100):
    ser = serial.Serial(port)
    ser.flushInput()
    curr_sample = 0
    while curr_sample<sample:
        curr_sample+=1
        try:
            ser_bytes = ser.readline()
            data = str(ser_bytes)[2:-3].split()
            data = list(map(float, data))
            data.append(a)
            data.append(b)
            data.append(depth)
            print(data)
            with open(filename,"a") as f:
                writer = csv.writer(f,delimiter=",")
                writer.writerow(data)
        except:
            print("Interpretation error!")
            break

if __name__=='__main__':
    if(len(sys.argv)<4 or len(sys.argv)>7):
        print("Usage: python3 "+sys.argv[0]+" a b depth (filename port samples)")
        exit(0)
    a = float(sys.argv[1])
    b = float(sys.argv[2])
    depth = float(sys.argv[3])
    if(len(sys.argv)==4):
        read_from_serial(a,b,depth,sample=10)
    elif(len(sys.argv)==5):
        read_from_serial(a,b,depth,filename=sys.argv[4])
    elif len(sys.argv)==6:
        read_from_serial(a,b,depth,filename=sys.argv[4],port=sys.argv[5])
    else:
        read_from_serial(a,b,depth,sys.argv[4],sys.argv[5],int(sys.argv[6]))