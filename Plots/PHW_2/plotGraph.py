import matplotlib.pyplot as plt

x = [1, 4, 16, 64, 256]
y = [2061.79, 1208.32, 1159.71, 1127.31, 1007.93]


plt.plot(x, y, 'bo-')
plt.title('Execution time (s) vs Number of threads')
plt.xlabel('Num of threads')
plt.ylabel('Execution time (s)')
plt.show()