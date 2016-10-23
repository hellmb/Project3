from pylab import *
from numpy import zeros
from mpl_toolkits.mplot3d import Axes3D
import matplotlib


#n = 1000

# load data from textfile with positions
positions = loadtxt('positions_system.txt')
NumPlanets = 10
n = len(positions[:,0])/NumPlanets
print len(positions[:,0])/NumPlanets


# create empty arrays
pos_sun = zeros((n, 3))
pos_mercury = zeros((n, 3))
pos_venus = zeros((n, 3))
pos_earth = zeros((n, 3))
pos_mars = zeros((n, 3))
pos_jupiter = zeros((n, 3))
pos_saturn = zeros((n, 3))
pos_uranus = zeros((n, 3))
pos_neptune = zeros((n, 3))
pos_pluto = zeros((n, 3))

# fill arrays with positions
for i in range(n):
    pos_sun[i,:]     = positions[NumPlanets*i + 0, :]
    pos_mercury[i,:] = positions[NumPlanets*i + 1, :]
    pos_venus[i,:]   = positions[NumPlanets*i + 2, :]
    pos_earth[i,:]   = positions[NumPlanets*i + 3, :]
    pos_mars[i,:]    = positions[NumPlanets*i + 4, :]
    pos_jupiter[i,:] = positions[NumPlanets*i + 5, :]
    pos_saturn[i,:]  = positions[NumPlanets*i + 6, :]
    pos_uranus[i,:]  = positions[NumPlanets*i + 7, :]
    pos_neptune[i,:] = positions[NumPlanets*i + 8, :]
    pos_pluto[i,:] 	 = positions[NumPlanets*i + 9, :]

# split lists for inner planets
half = len(pos_sun[:,0])/6
print len(pos_mercury[:half, 0])


# plot the planet positions in the same plot
fig = figure()
ax1 = fig.add_subplot(2, 1, 1, projection='3d')
ax1.plot(pos_sun[:,0], pos_sun[:,1], pos_sun[:,2])
ax1.plot(pos_mercury[:half,0], pos_mercury[:half,1], pos_mercury[:half,2])
ax1.plot(pos_venus[:half,0], pos_venus[:half,1], pos_venus[:half,2])
ax1.plot(pos_earth[:half,0], pos_earth[:half,1], pos_earth[:half,2])
ax1.plot(pos_mars[:half,0], pos_mars[:half,1], pos_mars[:half,2])

ax2 = fig.add_subplot(2, 1, 2, projection='3d')
ax2.plot(pos_jupiter[:,0], pos_jupiter[:,1], pos_jupiter[:,2])
ax2.plot(pos_saturn[:,0], pos_saturn[:,1], pos_saturn[:,2])
ax2.plot(pos_uranus[:,0], pos_uranus[:,1], pos_uranus[:,2])
ax2.plot(pos_neptune[:,0], pos_neptune[:,1], pos_neptune[:,2])
ax2.plot(pos_pluto[:,0], pos_pluto[:,1], pos_pluto[:,2])


ax1.scatter(pos_sun[0,0], pos_sun[0,1], pos_sun[0,2], s=200, c='gold')
ax1.text(pos_sun[0,0], pos_sun[0,1], pos_sun[0,2], 'Sun')

ax1.scatter(pos_mercury[0,0], pos_mercury[0,1], pos_mercury[0,2], s=10, c='darkslategrey')
ax1.text(pos_mercury[0,0], pos_mercury[0,1], pos_mercury[0,2], 'Mercury')

ax1.scatter(pos_venus[0,0], pos_venus[0,1], pos_venus[0,2], s=30, c='goldenrod')
ax1.text(pos_venus[0,0], pos_venus[0,1], pos_venus[0,2], 'Venus')

ax1.scatter(pos_earth[0,0], pos_earth[0,1], pos_earth[0,2], s=50, c='b')
ax1.text(pos_earth[0,0], pos_earth[0,1], pos_earth[0,2], 'Earth')

ax1.scatter(pos_mars[0,0], pos_mars[0,1], pos_mars[0,2], s=20, c='r', alpha=0.7)
ax1.text(pos_mars[0,0], pos_mars[0,1], pos_mars[0,2], 'Mars')

ax2.scatter(pos_jupiter[0,0], pos_jupiter[0,1], pos_jupiter[0,2], s=100, c='orange')
ax2.text(pos_jupiter[0,0], pos_jupiter[0,1], pos_jupiter[0,2], 'Jupiter')

ax2.scatter(pos_saturn[0,0], pos_saturn[0,1], pos_saturn[0,2], s=90, c='y')
ax2.text(pos_saturn[0,0], pos_saturn[0,1], pos_saturn[0,2], 'Saturn')

ax2.scatter(pos_uranus[0,0], pos_uranus[0,1], pos_uranus[0,2], s=90, c='b', alpha=0.5)
ax2.text(pos_uranus[0,0], pos_uranus[0,1], pos_uranus[0,2], 'Uranus')

ax2.scatter(pos_neptune[0,0], pos_neptune[0,1], pos_neptune[0,2], s=90, c='g', alpha=0.7)
ax2.text(pos_neptune[0,0], pos_neptune[0,1], pos_neptune[0,2], 'Neptune')

ax2.scatter(pos_pluto[0,0], pos_pluto[0,1], pos_pluto[0,2], s=10, c='grey')
ax2.text(pos_pluto[0,0], pos_pluto[0,1], pos_pluto[0,2], 'Pluto')

ax1.set_title('Planets around the Sun')
ax1.set_xlabel(r'$x$', fontsize=20)
ax1.set_ylabel(r'$y$', fontsize=20)
ax1.set_zlabel(r'$z$', fontsize=20)

ax2.set_xlabel(r'$x$', fontsize=20)
ax2.set_ylabel(r'$y$', fontsize=20)
ax2.set_zlabel(r'$z$', fontsize=20)

show()







