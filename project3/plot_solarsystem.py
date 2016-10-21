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


# plot the planet positions in the same plot
fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(pos_sun[:,0], pos_sun[:,1], pos_sun[:,2])
ax.plot(pos_mercury[:,0], pos_mercury[:,1], pos_mercury[:,2])
ax.plot(pos_venus[:,0], pos_venus[:,1], pos_venus[:,2])
ax.plot(pos_earth[:,0], pos_earth[:,1], pos_earth[:,2])
ax.plot(pos_mars[:,0], pos_mars[:,1], pos_mars[:,2])
ax.plot(pos_jupiter[:,0], pos_jupiter[:,1], pos_jupiter[:,2])
ax.plot(pos_saturn[:,0], pos_saturn[:,1], pos_saturn[:,2])
ax.plot(pos_uranus[:,0], pos_uranus[:,1], pos_uranus[:,2])
ax.plot(pos_neptune[:,0], pos_neptune[:,1], pos_neptune[:,2])
ax.plot(pos_pluto[:,0], pos_pluto[:,1], pos_pluto[:,2])

'''
ax.scatter(pos_sun[0,0], pos_sun[0,1], pos_sun[0,2], s=200, c='gold')
ax.text(pos_sun[0,0], pos_sun[0,1], pos_sun[0,2], 'Sun')

ax.scatter(pos_venus[0,0], pos_venus[0,1], pos_venus[0,2], s=20, c='goldenrod')
ax.text(pos_venus[0,0], pos_venus[0,1], pos_venus[0,2], 'Mars')

ax.scatter(pos_earth[0,0], pos_earth[0,1], pos_earth[0,2], s=50, c='b')
ax.text(pos_earth[0,0], pos_earth[0,1], pos_earth[0,2], 'Earth')

ax.scatter(pos_mars[0,0], pos_mars[0,1], pos_mars[0,2], s=20, c='r', alpha=0.7)
ax.text(pos_mars[0,0], pos_mars[0,1], pos_mars[0,2], 'Mars')

ax.scatter(pos_jupiter[0,0], pos_jupiter[0,1], pos_jupiter[0,2], s=100, c='orange')
ax.text(pos_jupiter[0,0], pos_jupiter[0,1], pos_jupiter[0,2], 'Jupiter')

ax.scatter(pos_saturn[0,0], pos_saturn[0,1], pos_saturn[0,2], s=100, c='y')
ax.text(pos_saturn[0,0], pos_saturn[0,1], pos_saturn[0,2], 'Saturn')

ax.scatter(pos_uranus[0,0], pos_uranus[0,1], pos_uranus[0,2], s=100, c='b', alpha=0.5)
ax.text(pos_uranus[0,0], pos_uranus[0,1], pos_uranus[0,2], 'Uranus')

ax.scatter(pos_neptune[0,0], pos_neptune[0,1], pos_neptune[0,2], s=100, c='g', alpha=0.7)
ax.text(pos_neptune[0,0], pos_neptune[0,1], pos_neptune[0,2], 'Neptune')

ax.scatter(pos_pluto[0,0], pos_pluto[0,1], pos_pluto[0,2], s=100, c='grey')
ax.text(pos_pluto[0,0], pos_pluto[0,1], pos_pluto[0,2], 'Pluto')
'''
#ax.set_title('Earth-Sun system')
ax.set_title('Planets around the Sun')
ax.set_xlabel(r'$x$', fontsize=20)
ax.set_ylabel(r'$y$', fontsize=20)
ax.set_zlabel(r'$z$', fontsize=20)

#ax.legend()
show()







