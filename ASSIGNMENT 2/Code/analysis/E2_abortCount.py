# AbortCount analysis with varying variables 1000-5000

import matplotlib.pyplot as plt
import os
import numpy as np

# Data
variables = [1000, 2000, 3000, 4000, 5000]
BTO = np.array([1.077+1.038+1.111, 0.413+0.407+0.371, 0.235+0.23+0.194, 0.189+0.176+0.153, 0.116+0.123+0.104])
MVTO = np.array([0.465+0.406+0.495, 0.185+0.185+0.246, 0.107+0.142+0.121, 0.099+0.089+0.093, 0.063+0.087+0.073])
MVTO_gc = np.array([0.529+0.569+0.455, 0.163+0.22+0.157, 0.122+0.117+0.126, 0.107+0.085+0.074, 0.068+0.062+0.076])
k_MVTO = np.array([0.515+0.496+0.493, 0.213+0.222+0.188, 0.104+0.129+0.103, 0.108+0.085+0.077, 0.064+0.066+0.069])

# make a big plot
plt.figure(figsize=(16, 9))

# plot data
plt.plot(variables, BTO/3, label='BTO', marker='o', color='navy')
plt.plot(variables, MVTO/3, label='MVTO', marker='o', color='purple')
plt.plot(variables, MVTO_gc/3, label='MVTO_gc', marker='o', color='red')
plt.plot(variables, k_MVTO/3, label='k_MVTO', marker='o', color='green')

# show grid lines
plt.grid(True)

plt.xlabel('number of data items')
plt.ylabel('Average aborts')
plt.title('Abort Count Analysis with Varying number of data items')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()