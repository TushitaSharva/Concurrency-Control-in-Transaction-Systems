# Abort Count Analysis with varying read ratio

import matplotlib.pyplot as plt
import os
import numpy as np

# Data
readRatio = [0.5, 0.6, 0.7, 0.8, 0.9]
BTO = np.array([1.624+1.637+1.61, 1.404+1.332+1.417, 1.11+1.004+0.886, 0.801+0.702+0.842, 0.335+0.442+0.476])
MVTO = np.array([0.948+0.795+0.834, 0.593+0.625+0.664, 0.515+0.517+0.474, 0.329+0.317+0.365, 0.129+0.141+0.161])
MVTO_gc = np.array([0.855+0.833+0.891, 0.695+0.597+0.583, 0.491+0.502+0.431, 0.287+0.272+0.302, 0.139+0.153+0.153])
k_MVTO = np.array([0.802+0.771+0.866, 0.657+0.574+0.696, 0.468+0.46+0.486, 0.362+0.342+0.276, 0.125+0.167+0.137])

# make a big plot
plt.figure(figsize=(16, 9))

# plot data
plt.plot(readRatio, BTO/3, label='BTO', marker='o', color='navy')
plt.plot(readRatio, MVTO/3, label='MVTO', marker='o', color='purple')
plt.plot(readRatio, MVTO_gc/3, label='MVTO_gc', marker='o', color='red')
plt.plot(readRatio, k_MVTO/3, label='k_MVTO', marker='o', color='green')

# show grid lines
plt.grid(True)

plt.xlabel('readRatio value')
plt.ylabel('Average abort count')
plt.title('Abort Count Analysis with varying readRatio')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()