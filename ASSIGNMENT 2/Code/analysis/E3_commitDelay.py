# Commit Delay analysis with varying threads 2-32

import matplotlib.pyplot as plt
import os
import numpy as np

# Data
numThreads = [2, 4, 8, 16, 32]
BTO = np.array([400.902+407.663+404.269, 423.845+433.626+434.903, 494.566+490.995+483.605, 679.948+692.62+654.102, 1636.04+1501.25+1450.72])
MVTO = np.array([404.649+398.216+404.532, 410.835+420.949+419.767, 436.209+431.362+430.496, 493.914+528.935+528.422, 739.98+667.06+719.106])
MVTO_gc = np.array([404.328+401.23+402.629, 414.264+413.372+419.316, 446.507+439.334+443.055, 500.873+504.1+511.616, 739.782+738.525+707.383])
k_MVTO = np.array([401.328+398.054+397.431, 421.707+411.149+414.375, 431.034+442.201+453.609, 509.646+521.012+516.159, 731.699+807.739+670.931])

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
plt.ylabel('Average commit delay')
plt.title('Commit Delay Analysis with Varying number of threads')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()