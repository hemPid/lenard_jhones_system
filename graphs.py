import matplotlib.pyplot as plt
import numpy as np

tick = []
energy = []

with open('energy.txt', 'r') as f:
	for line in f:
		l = line.rstrip().split(" ")
		tick.append(float(l[1]))
		energy.append(float(l[3]))


print(energy[0])
plt.plot(tick, energy)
plt.show()