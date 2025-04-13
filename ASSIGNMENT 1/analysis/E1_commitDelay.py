# Commit Delay analysis with varying numTransactions 1000-5000

import matplotlib.pyplot as plt
import os

# Data
numTransactions = [1000, 2000, 3000, 4000, 5000]
BOCC_CTA = [1480.63, 1511.2, 1550.07, 1529.35, 1516.8]
FOCC_CTA = [7371.25, 7757.13, 7677.16, 7864.68, 7914.82]
FOCC_OTA = [1151.37, 1163.22, 1183.74, 1181.82, 1196.11] # To be changes

# make a big plot
plt.figure(figsize=(16, 9))

# plot data
plt.plot(numTransactions, BOCC_CTA, label='BOCC_CTA', marker='o', color='navy')
plt.plot(numTransactions, FOCC_CTA, label='FOCC_CTA', marker='o', color='purple')
plt.plot(numTransactions, FOCC_OTA, label='FOCC_OTA', marker='o', color='green')

# show grid lines
plt.grid(True)

plt.xlabel('total number of transactions')
plt.ylabel('Average commit delay')
plt.title('Commit Delay Analysis with Varying numTransactions')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()