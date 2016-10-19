from pylab import *
from numpy import zeros
from mpl_toolkits.mplot3d import Axes3D
import sys

n = 100

positions = loadtxt(filename)


k_list = []


pos_sun = zeros((n/2, 3))
pos_earth = zeros((n/2, 3))


for i in range(n-1):
	j = i + 1
	k = i + j

	if k > n-1:
		break

	k_list.append(k)


for i in range(len(k_list)):
	for j in range(3):
		k = k_list[i]
		pos_earth[i, j] = positions[k][j]

# printing x cooridinates
#print pos_earth[:,0]
print pos_earth[:,0]
#print k_list


fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(pos_sun[:,0], pos_sun[:,1], pos_sun[:,2], 'yo', label='Sun')
ax.plot(pos_earth[:,0], pos_earth[:,1], pos_earth[:,2], label='Earth orbit')
ax.legend()
show()









