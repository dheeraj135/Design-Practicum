import csv
import matplotlib.pyplot as plt
import sys

x = []
y = []
with open(sys.argv[1],'r') as f:
    reader = csv.reader(f)
    for row in reader:
        y.append(float(row[0]))
        x.append(float(row[1]))

plt.plot(x,y)
plt.show()