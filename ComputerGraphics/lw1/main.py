import matplotlib.pyplot as plt
import numpy as np


# добавить пометку осей(X, Y)
# task:
# a > 0, A <= t <= B < -1
# x = 3 * a * t * (1 + (t ** 3))
# y = 3 * a * (t ** 2) * (1 + (t ** 3))

def CheckConst(A, B):
    if(A > B or B >= -1): 
        exit()
    if(A <= B and B >= -1):
        exit()

print("A <= t <= B < -1")
A = int(input())
B = int(input())
CheckConst(A,B)
print("count of a, a > 0")
count = int(input())
all_a = []
while(count != 0):
    a = int(input())
    all_a.append(a)
    count -= 1
t = np.linspace(A, B, B - A + 1)
fig, ax = plt.subplots()
for a in all_a:
    # print(t)
    x = 3 * a * t * (1 + (t ** 3))
    y = 3 * a * (t ** 2) * (1 + (t ** 3))
    plt.plot(x, y, label="a = {}".format(a))
ax.grid()
ax.set_xlabel('X')
ax.set_ylabel('Y')
#plt.plot([0 for i in y], y, color="black")  #  X
#plt.plot(x, [0 for i in x], color="black")  #  Y
# plt.grid()                      
plt.legend(shadow=True)
plt.show()


