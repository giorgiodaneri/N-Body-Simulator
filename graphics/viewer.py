import numpy as np
from matplotlib import pyplot as plt
import matplotlib.animation
import pandas as pd


# array a size must be equal to N*Npart, where N is how many timestep you want and N_part the # of particles

N = 15
N_part = 10

#To have random numbers
a = np.random.rand(N*N_part, 3)*5

#print(a)

#a = np.array([[1,2,3],[2,3,4],[3,4,5],[4,5,6],[5,6,7],[7,6,5],[6,5,4],[5,4,3],[4,3,2],[3,2,1],[4,3,7],[8,6,2],[6,2,8],[7,6,2],[5,3,6]])


"""
a =
[1,2,3
2,3,4
3,4,5
4,5,6
etc]

t timespan
"""

t = np.array([np.ones(N_part)*i for i in range(N)]).flatten()
df = pd.DataFrame({"time": t ,"x" : a[:,0], "y" : a[:,1], "z" : a[:,2]})

def update_graph(num):
    data=df[df['time']==num]
    graph._offsets3d = (data.x, data.y, data.z)
    title.set_text('N-Body particle simulator, time={}'.format(num))


fig = plt.figure(figsize=(8,8))
ax = fig.add_subplot(111, projection='3d')
title = ax.set_title('N-Body particle simulator')

data=df[df['time']==0]
graph = ax.scatter(data.x, data.y, data.z)

ani = matplotlib.animation.FuncAnimation(fig, update_graph, (N-1),
                               interval=200, blit=False)

ani.save("N-Body-simulator.mp4")