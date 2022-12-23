import matplotlib.pyplot as plt
import numpy as np


country0,x0,y0,z0 = np.loadtxt("class00.txt", unpack=True)
country1,x1,y1,z1 = np.loadtxt("class01.txt", unpack=True)
country2,x2,y2,z2 = np.loadtxt("class02.txt", unpack=True)
# country3,x3,y3,z3 = np.loadtxt("class03.txt", unpack=True)
# fcx,fcy,fcz = np.loadtxt("firstcentroid.txt", unpack=True)


fig = plt.figure()
ax = fig.add_subplot(projection='3d')
ax.set_xlabel('GDP')
ax.set_ylabel('Population Density')
ax.set_zlabel('Birth Rate')
ax.legend()
ax.scatter(x0, y0, z0, c="red")
ax.scatter(x1, y1, z1, c="blue")
ax.scatter(x2, y2, z2, c="orange")
# ax.scatter(x3, y3, z3, c="green")

# ax.scatter(fcx,fcy,fcz, c="black")
plt.show()