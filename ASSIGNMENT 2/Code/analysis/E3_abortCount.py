# AbortCount analysis with varying threads 2-32

import matplotlib.pyplot as plt
import os
import numpy as np

# Data
numThreads = [2, 4, 8, 16, 32]
BTO = np.array([0.036+0.038+0.051, 0.106+0.142+0.147, 0.372+0.338+0.31, 1.118+1.173+1.029, 5.595+4.874+4.767])
MVTO = np.array([0.031+0.019+0.027, 0.074+0.084+0.085, 0.171+0.147+0.146, 0.42+0.523+0.531, 1.563+1.236+1.464])
MVTO_gc = np.array([0.028+0.018+0.022, 0.07+0.066+0.08, 0.211+0.183+0.191, 0.43+0.464+0.466, 1.568+1.543+1.413])
k_MVTO = np.array([0.029+0.023+0.024, 0.097+0.076+0.084, 0.144+0.179+0.212, 0.467+0.493+0.463, 1.514+1.822+1.242])

# make a big plot
plt.figure(figsize=(16, 9))

# plot data
plt.plot(numThreads, BTO/3, label='BTO', marker='o', color='navy')
plt.plot(numThreads, MVTO/3, label='MVTO', marker='o', color='purple')
plt.plot(numThreads, MVTO_gc/3, label='MVTO_gc', marker='o', color='red')
plt.plot(numThreads, k_MVTO/3, label='k_MVTO', marker='o', color='green')

# show grid lines
plt.grid(True)

plt.xlabel('number of threads')
plt.ylabel('Average aborts')
plt.title('Abort Count Analysis with Varying number of threads')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()