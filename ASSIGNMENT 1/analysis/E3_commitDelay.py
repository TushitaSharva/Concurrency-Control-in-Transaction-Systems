# Commit Delay analysis with varying threads 2-32

import matplotlib.pyplot as plt
import os

# Data
numThreads = [2, 4, 8, 16, 32]
BOCC_CTA = [529.258, 710.67, 1017.24, 1523.08, 2216.44]
FOCC_CTA = [491.749, 725.694, 1611.06, 7255.1, 160119]
FOCC_OTA = [487.202, 619.221, 827.36, 1169.81, 1862.3] # To be changes

# make a big plot
plt.figure(figsize=(16, 9))

# plot data
plt.plot(numThreads, BOCC_CTA, label='BOCC_CTA', marker='o', color='navy')
plt.plot(numThreads, FOCC_CTA, label='FOCC_CTA', marker='o', color='purple')
plt.plot(numThreads, FOCC_OTA, label='FOCC_OTA', marker='o', color='green')

# show grid lines
plt.grid(True)

plt.xlabel('number of threads')
plt.ylabel('Average commit delay')
plt.title('Commit Delay Analysis with Varying number of threads')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()