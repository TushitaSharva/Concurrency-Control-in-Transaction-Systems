# CommitDelay analysis with varying variables 1000-5000

import matplotlib.pyplot as plt
import os
import numpy as np

# Data
variables = [1000, 2000, 3000, 4000, 5000]
BTO = np.array([660.348+661.456+676.455, 496.299+507.644+492.086, 455.173+452.081+445.624, 443.98+440.186+435.168, 425.863+423.935+422.888])
MVTO = np.array([513.161+493.473+525.036, 446.117+448.869+461.321, 418.446+429.117+426.712, 416.492+416.976+417.907, 407.389+411.496+411.87])
MVTO_gc = np.array([522.893+537.007+511.306, 437.813+448.158+433.142, 428.975+423.486+425.249, 424.127+420.449+416.682, 420.83+419.744+414.599])
k_MVTO = np.array([528.893+522.4+519.295, 438.614+452.128+440.053, 417.285+425.884+418.143, 421.552+413.728+409.608, 416.809+412.047+416.193])

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
plt.ylabel('Average Commit delay')
plt.title('Commit Delay Analysis with Varying number of data items')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()