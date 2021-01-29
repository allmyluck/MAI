import matplotlib as mpl
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np
import math as func

fig = plt.figure()
ax = plt.axes(projection='3d')
print("R:")
R = float(input())
print("amount")
n = int(input())
print("Center of pyramid(x,y)")
center_x = float(input())
center_y = float(input())
print("z(begin):")
z_begin  = float(input())
print("z(end):")
z_max = float(input())
print("z(fact):")
z_fact = float(input())
k = 1 - float(abs((z_fact - z_begin) / (z_max - z_begin)))
# print(k)
x_v = list()
y_v = list()
z_v = list()
x_f = list()
y_f = list()
i = 0
while i <= n:
    angle = (2 * func.pi * i) / n;
    x = R * func.cos(angle) + center_x
    y = R * func.sin(angle) + center_y
    x_v.append(x)
    y_v.append(y)
    z_v.append(z_begin)
    x_v.append((R * k * func.cos(angle) + center_x))
    y_v.append((R * k * func.sin(angle) + center_y))
    z_v.append(z_fact)
    x_f.append((R * k * func.cos(angle) + center_x))
    y_f.append((R * k * func.sin(angle) + center_y))
    if(i > 0) :
        x_v.append(x_f[i - 1])
        y_v.append(y_f[i - 1])
        z_v.append(z_fact)
        x_v.append(x_f[i])
        y_v.append(y_f[i])
        z_v.append(z_fact)
    x_v.append(R * func.cos(angle) + center_x)
    y_v.append(R * func.sin(angle) + center_y)
    z_v.append(z_begin)
    i += 1 
    
ax.plot(x_v, y_v, z_v, label='circle1', color='black')
plt.xlabel('X')
plt.ylabel('Y')
plt.show()