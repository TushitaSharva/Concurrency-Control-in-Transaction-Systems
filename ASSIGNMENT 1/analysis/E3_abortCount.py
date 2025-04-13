# AbortCount analysis with varying threads 2-32

import matplotlib.pyplot as plt
import os

# Data
numThreads = [2, 4, 8, 16, 32]
BOCC_CTA = [0.345, 0.793, 1.563, 2.86, 4.619]
FOCC_CTA = [0.242, 0.819, 3.085, 17.35, 405.632]
FOCC_OTA = [0.194, 0.511, 0.997, 1.764, 2.974] # To be changes

# make a big plot
plt.figure(figsize=(16, 9))

# plot data
plt.plot(numThreads, BOCC_CTA, label='BOCC_CTA', marker='o', color='navy')
plt.plot(numThreads, FOCC_CTA, label='FOCC_CTA', marker='o', color='purple')
plt.plot(numThreads, FOCC_OTA, label='FOCC_OTA', marker='o', color='green')

# show grid lines
plt.grid(True)

plt.xlabel('number of threads')
plt.ylabel('Average aborts')
plt.title('Abort Count Analysis with Varying number of threads')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()