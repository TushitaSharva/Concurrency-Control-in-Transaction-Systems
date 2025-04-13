# AbortCount analysis with varying numTransactions 1000-5000

import matplotlib.pyplot as plt
import os
import numpy as np

# Data
numTransactions = [1000, 2000, 3000, 4000, 5000]
BTO = np.array([1.145+0.962+1.167, 1.1065+1.001+1.044, 1.08+1.097+1.02233, 1.069+1.081+1.0685, 1.0974+1.124+1.1076])
MVTO = np.array([0.475+0.506+0.452, 0.4235+0.4775+0.505, 0.462+0.484+0.505333, 0.493+0.522+0.4825, 0.496+0.505+0.5116])
MVTO_gc = np.array([0.57+0.441+0.502, 0.499+0.4475+0.4955, 0.466+0.484+0.487667, 0.542+0.47175+0.48325, 0.517+0.4384+0.4964])
k_MVTO = np.array([0.443+0.424+0.476, 0.505+0.45+0.41, 0.493+0.454667+0.54, 0.463+0.48625+0.4655, 0.484+0.4472+0.4804])

# make a big plot
plt.figure(figsize=(16, 9))

# plot data
plt.plot(numTransactions, BTO/3, label='BTO', marker='o', color='navy')
plt.plot(numTransactions, MVTO/3, label='MVTO', marker='o', color='purple')
plt.plot(numTransactions, MVTO_gc/3, label='MVTO_gc', marker='o', color='red')
plt.plot(numTransactions, k_MVTO/3, label='k_MVTO', marker='o', color='green')

# show grid lines
plt.grid(True)

plt.xlabel('total number of transactions')
plt.ylabel('Average aborts')
plt.title('Abort Count Analysis with Varying numTransactions')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()