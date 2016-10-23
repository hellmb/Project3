from pylab import *
from numpy import zeros
from mpl_toolkits.mplot3d import Axes3D

# load data from textfile with positions
positions = loadtxt('positions.txt')
NumPlanets = 2
n = len(positions[:,0])/NumPlanets

# create empty arrays
pos_sun = zeros((n, 3))
pos_earth = zeros((n, 3))


# fill arrays with positions
for i in range(n):
    pos_sun[i,:]     = positions[NumPlanets*i + 0, :]
    pos_earth[i,:] = positions[NumPlanets*i + 1, :]


# plot the planet positions in the same plot
fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(pos_sun[:,0], pos_sun[:,1], pos_sun[:,2])
ax.plot(pos_earth[:,0], pos_earth[:,1], pos_earth[:,2], 'blue')

ax.scatter(0, 0, 0, s=500, c='y')
ax.text(0, 0, 0, 'Sun')
ax.scatter(pos_earth[0,0], pos_earth[0,1], pos_earth[0,2], s=100, c='blue')
ax.text(pos_earth[0,0], pos_earth[0,1], pos_earth[0,2], 'Earth')

ax.set_title(r'Earth-Sun system')
ax.set_xlabel(r'$x$', fontsize=20)
ax.set_ylabel(r'$y$', fontsize=20)
ax.set_zlabel(r'$z$', fontsize=20)

show()

