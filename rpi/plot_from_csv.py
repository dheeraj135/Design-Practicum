import csv
import matplotlib.pyplot as plt
import sys
import numpy as np

x = []
y = []
with open(sys.argv[1],'r') as f:
    reader = csv.reader(f)
    for row in reader:
        y.append(float(row[0]))
        x.append(float(row[1]))

x = np.array(x)
y = np.array(y)
z = np.polyfit(x,y,4)
x = np.linspace(25,45,256,endpoint=True)
y = (z[4]+(z[3]+z[2]*x+z[1]*x*x+z[0]*x*x*x)*x)
# for i in range(4):
#     y = y*x+z[3-i]
plt.plot(x/2,y)
plt.show()