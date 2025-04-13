# Commit Delay analysis with varying numTransactions 1000-5000

import matplotlib.pyplot as plt
import os
import numpy as np

# Data
numTransactions = [1000, 2000, 3000, 4000, 5000]
BTO = np.array([626.626+638.286+689.445, 670.255+649.154+665.652, 671.709+676.876+654.495, 664.918+670.096+665.916, 673.591+681.827+674.602])
MVTO = np.array([517.4+516.92+504.262, 504.753+513.212+520.899, 510.04+516.85+520.424, 520.936+521.82+514.434, 519.208+521.403+521.036])
MVTO_gc = np.array([537.394+506.681+517.026, 520.841+504.176+518.708, 510.955+516.525+517.025, 530.471+511.789+516.005, 521.584+504.202+519.562])
k_MVTO = np.array([506.646+496.782+520.215, 520.244+502.113+493.469, 522.213+505.018+529.711, 508.053+514.151+510.008, 513.558+506.501+513.693])

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
plt.ylabel('Average commit delay')
plt.title('Commit Delay Analysis with Varying numTransactions')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()