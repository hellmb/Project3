from pylab import *
from numpy import zeros
from mpl_toolkits.mplot3d import Axes3D

# load data from textfile with positions
angle_time = loadtxt('perihelion_angle_GR.txt')
#angle_time = loadtxt('perihelion_angle_pure.txt')
n = len(angle_time)/2


# create empty arrays
angle = zeros(n)
init_time = zeros(n)

# fill arrays with positions
for i in range(n):
    angle[i] = angle_time[2*i + 0]
    init_time[i]  = angle_time[2*i + 1] 

# time step
dt = 1e-8
# calculating Mercury years
time = init_time * dt
# calculating angle in arc seconds
arcsec = angle * (3600 * 180)/pi 

print arcsec[-1]


plot(time, arcsec)
title('Perihelion precession of Mercury')
xlabel('Mercury year', fontsize=13)
ylabel(r'$\theta_p$ in arc seconds', fontsize=13)
grid()

show()