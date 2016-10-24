from pylab import *
from numpy import zeros
from mpl_toolkits.mplot3d import Axes3D

# load data from textfile with positions
positions = loadtxt('positions_escape.txt')
NumPlanets = 2
n = len(positions[:,0])/NumPlanets

# create empty arrays
pos_sun = zeros((n, 3))
pos_toofun = zeros((n, 3))

# fill arrays with positions
for i in range(n):
    pos_toofun[i,:]   = positions[NumPlanets*i + 1, :]
    pos_sun[i,:]      = positions[NumPlanets*i + 0, :]


# plot the planet positions in the same plot
fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(pos_sun[:,0], pos_sun[:,1], pos_sun[:,2])
ax.plot(pos_toofun[:,0], pos_toofun[:,1], pos_toofun[:,2], 'blue')

ax.scatter(0, 0, 0, c='y', s=200)
ax.text(0, 0, 0, 'Sun')
ax.scatter(pos_toofun[0,0], pos_toofun[0,1], pos_toofun[0,2], c='b')
ax.text(pos_toofun[0,0], pos_toofun[0,1], pos_toofun[0,2], 'Too-fun-for-Sun')

ax.set_title('Random planet around the Sun')
ax.set_xlabel(r'$x$', fontsize=20)
ax.set_ylabel(r'$y$', fontsize=20)
ax.set_zlabel(r'$z$', fontsize=20)
show()
