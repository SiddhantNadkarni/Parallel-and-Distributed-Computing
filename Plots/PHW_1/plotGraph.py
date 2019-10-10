import matplotlib.pyplot as plt
import numpy as np

def plotGraph(x, y, title, xLabel, yLabel):
	plt.plot(x, y, 'ro-')
	plt.ylabel(yLabel)
	plt.xlabel(xLabel)
	plt.title(title)
	plt.show()

typeMatrix = ['naive', 'block 4', 'block 8', 'block 16']
timeTaken = [2061.79, 640.81, 590.56, 532.313]
performanceFlops = [66.66, 214.47, 232.72, 258.641]

plotGraph(typeMatrix, timeTaken, 'Time taken (s) vs Type of Matrix Multiplication', 'Type of Matrix Multiplication', 'Time taken in seconds')
plotGraph(typeMatrix, performanceFlops, 'Performance (MFLOPS per sec) vs Type of Matrix Multiplication', 'Type of Matrix Multiplication', 'MFLOPS per sec')
