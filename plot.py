#!/opt/epd-7.3-1-rh5-x86_64/bin/python

from pylab import*
from numpy import*
import sys
from datetime import datetime
startTime = datetime.now()
data = genfromtxt(sys.argv[1],skip_header=4)
index = data[:,0]
x = data[:,1]
y = data[:,2]
z = data[:,3]
vx = data[:,4]
vy = data[:,5]
vz = data[:,6]
V = 0.5*(vx**2 + vy**2 + vz**2)
print len(vx), sum(vx), sum(vy), sum(vz)
print sum(V)/len(V)

xLow = min(x)
xHi = max(x)
xlim(xLow, xHi)
yLow = min(y)
yHi = max(y)
ylim(yLow, yHi)
savefig("a.png")
#show()
#plot(x,y)
#show()
print ''
print 'Time taken by the program is :', datetime.now()-startTime 
