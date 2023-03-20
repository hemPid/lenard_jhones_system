import matplotlib.pyplot as plt
import numpy as np

tick = []
energy = []
penergy = []
kenergy = []
"""
with open('logs/energy.txt', 'r') as f:
	for line in f:
		l = line.rstrip().split(", ")
		t_str = l[0].split(": ")
		e_str = l[1].split(": ")
		p_str = l[2].split(": ")
		k_str = l[3].split(": ")
		tick.append(float(t_str[1]))
		energy.append(float(e_str[1]))
		penergy.append(float(p_str[1]))
		kenergy.append(float(k_str[1]))


print(energy[0])
plt.plot(tick, energy)
plt.show()
plt.plot(tick, energy, tick, penergy, tick, kenergy)
#plt.ylim(-50,300)
plt.show()

"""
n= 0;
vels = []
vels_x = []
vels_y = []
vels_z = []

with open('logs/velocity.txt', 'r') as f:
	for line in f:
		if (line[0] == "n"):
			n = int(line.rstrip()[2:])
			print(n)
			continue;
		l = line.rstrip().split(" ")
		vels.append(float(l[1]))
		vels_x.append(float(l[2]))
		vels_y.append(float(l[3]))
		vels_z.append(float(l[4]))

vels = np.array(vels)
vels_x = np.array(vels_x)
vels_y = np.array(vels_y)
vels_z = np.array(vels_z)
"""
vels_x = vels_x * vels_x
vels_y = vels_y ** 2
vels_z = vels_z ** 2
"""
vels_x.sort()
vels_y.sort()
vels_z.sort()

print(*vels_x)

x_m = max(vels_x) ** 2
y_m = max(vels_y)
z_m = max(vels_z)

p = 50
#x
dv = max(vels_x)/n
v_x = np.linspace(0, x_m, p)
n_x = []

for x in v_x:
	n_x.append(0)
	for y in vels_x:
		if (y >= x ** 0.5) and (y <= x ** 0.5 + dv):
			n_x[len(n_x) - 1] += 1
	n_x[len(n_x) - 1] /= n

n_x = -1 * np.log(n_x)

plt.plot(v_x, n_x)
plt.show()