# Commit Delay Analysis with varying read ratio

import matplotlib.pyplot as plt
import os
import numpy as np

# Data
readRatio = [0.5, 0.6, 0.7, 0.8, 0.9]
BTO = np.array([800.092+810.054+792.872, 744.516+735.275+749.264, 676.301+656.838+607.467, 597.585+582.504+612.334, 482.653+516.225+515.7])
MVTO = np.array([626.57+585.375+602.366, 537.058+540.022+558.628, 511.789+519.069+512.053, 471.155+476.023+486.53, 425.004+432.967+431.308])
MVTO_gc = np.array([600.791+600.981+620.443, 565.535+542.779+541.427, 516.186+525.053+499.418, 461.889+458.655+471.785, 434.406+428.027+433.721])
k_MVTO = np.array([587.873+582.278+605.991, 555.853+540.139+562.527, 507.129+503.656+512.277, 482.949+480.537+467.205, 425.199+437.328+429.196])

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
plt.ylabel('Average Commit Delay')
plt.title('Commit Delay Analysis with varying readRatio')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()