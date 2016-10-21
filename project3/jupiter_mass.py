from pylab import *
from numpy import zeros
from mpl_toolkits.mplot3d import Axes3D

# load data from textfile with positions
positions = loadtxt('positions.txt')
n = len(positions[:,0])/3

# create empty arrays
pos_sun = zeros((n, 3))
pos_earth = zeros((n, 3))
pos_jupiter = zeros((n, 3))


# fill arrays with positions
for i in range(n):
    #pos_sun[i,:]     = positions[3*i + 0, :]
    pos_earth[i,:]   = positions[3*i + 1, :]
    pos_jupiter[i,:] = positions[3*i + 2, :]



# plot the planet positions in the same plot
fig = figure()
ax = fig.add_subplot(111, projection='3d')
ax.plot(pos_sun[:,0], pos_sun[:,1], pos_sun[:,2], 'yo', label='Sun')
ax.plot(pos_earth[:,0], pos_earth[:,1], pos_earth[:,2], c='b', label='Earth orbit')
ax.plot(pos_jupiter[:,0], pos_jupiter[:,1], pos_jupiter[:,2], c='orange', label='Jupiter orbit')


ax.scatter(0, 0, 0, s=200, c='y')
ax.text(0, 0, 0, 'Sun')
ax.scatter(pos_earth[0,0], pos_earth[0,1], pos_earth[0,2], s=50, c='b')
ax.text(pos_earth[0,0], pos_earth[0,1], pos_earth[0,2], 'Earth')
ax.scatter(pos_jupiter[0,0], pos_jupiter[0,1], pos_jupiter[0,2], s=1000, c='orange')
ax.text(pos_jupiter[0,0], pos_jupiter[0,1], pos_jupiter[0,2], 'Jupiter')

#ax.set_title('Earth-Sun system')
ax.set_title(r'Jupiter with mass $M_{\odot}$')
#ax.set_title(r'Jupiter with mass $10M_{\odot}$')
#ax.set_title(r'Jupiter with mass $1000M_{\odot}$')
ax.set_xlabel(r'$x$', fontsize=20)
ax.set_ylabel(r'$y$', fontsize=20)
ax.set_zlabel(r'$z$', fontsize=20)

show()

# ask bruder for animations!!







