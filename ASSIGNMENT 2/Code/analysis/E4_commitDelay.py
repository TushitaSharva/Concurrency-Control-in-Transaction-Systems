# Commit delay Analysis with k varying from 5-25

import matplotlib.pyplot as plt
import os
import numpy as np

# Data
k = [5, 10, 15, 20, 25]
BTO = np.array([664.174+674.873+705.722, 624.935+657.293+700.501, 660.03+672.725+664.595, 688.973+638.522+653.081, 660.993+653.828+678.076])
MVTO = np.array([492.306+505.557+505.569, 494.376+509.438+505.844, 505.16+513.802+489.147, 501.84+525.747+504.62, 508.762+505.454+513.351])
MVTO_gc = np.array([512.248+508.861+509.133, 491.646+515.762+520.119, 511.116+513.453+505.505, 507.785+495.678+508.512, 512.189+503.646+500.732])
k_MVTO = np.array([513.224+511.987+506.208, 515.851+502.131+516.091, 495.776+514.738+513.268, 501.148+514.106+499.459, 535.927+533.26+508.34])

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
plt.ylabel('Average commit delay')
plt.title('Commit Delay Analysis with varying k value')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()