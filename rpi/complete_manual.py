import matplotlib.pyplot as plt 
from math import pi
di = 5
x = []
y = []

def process(v,i,do,di):
	rho = v/i*pi*do*(do+di)/di
	return rho


for i in range(7):
	print("Enter V,I,d: ")
	v = int(input())*5.0/1023
	i = (int(input())*5.0/1023)/10000
	do = int(input())
	rho = process(v,i,do,di)
	x.append(do)
	y.append(rho)

plt.plot(x,y)
plt.show()