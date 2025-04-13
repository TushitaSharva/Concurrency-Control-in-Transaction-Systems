# Abort Count Analysis with k varying from 5-25

import matplotlib.pyplot as plt
import os
import numpy as np

# Data
k = [5, 10, 15, 20, 25]
BTO = np.array([1.077+1.083+1.187, 0.935+1.014+1.18, 1.045+1.08+1.055, 1.153+0.955+0.992, 0.437+1.008+1.115])
MVTO = np.array([0.413+0.433+0.441, 0.418+0.453+0.422, 0.452+0.465+0.376, 0.437+0.529+0.427, 0.481+0.439+0.464])
MVTO_gc = np.array([0.506+0.476+0.483, 0.396+0.493+0.511, 0.457+0.468+0.451, 0.46+0.418+0.452, 0.463+0.445+0.438])
k_MVTO = np.array([0.471+0.49+0.443, 0.494+0.432+0.485, 0.417+0.473+0.476, 0.435+0.45+0.422, 0.559+0.548+0.444])

# make a big plot
plt.figure(figsize=(16, 9))

# plot data
plt.plot(k, BTO/3, label='BTO', marker='o', color='navy')
plt.plot(k, MVTO/3, label='MVTO', marker='o', color='purple')
plt.plot(k, MVTO_gc/3, label='MVTO_gc', marker='o', color='red')
plt.plot(k, k_MVTO/3, label='k_MVTO', marker='o', color='green')

# show grid lines
plt.grid(True)

plt.xlabel('k value')
plt.ylabel('Average abort count')
plt.title('Abort Count Analysis with varying k value')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()