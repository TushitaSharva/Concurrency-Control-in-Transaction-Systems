# CommitDelay analysis with varying variables 1000-5000

import matplotlib.pyplot as plt
import os

# Data
variables = [1000, 2000, 3000, 4000, 5000]
BOCC_CTA = [1477.96, 1064.74, 887.927, 806.398, 720.497]
FOCC_CTA = [6886.79, 1784.27, 1072.72, 869.178, 700.062]
FOCC_OTA = [1154.39, 864.707, 752.453, 666.405, 631.233]  # To be changed

# make a big plot
plt.figure(figsize=(16, 9))

# plot data
plt.plot(variables, BOCC_CTA, label='BOCC_CTA', marker='o', color='navy')
plt.plot(variables, FOCC_CTA, label='FOCC_CTA', marker='o', color='purple')
plt.plot(variables, FOCC_OTA, label='FOCC_OTA', marker='o', color='green')

# show grid lines
plt.grid(True)

plt.xlabel('number of data items')
plt.ylabel('Average Commit delay')
plt.title('Commit Delay Analysis with Varying number of data items')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()