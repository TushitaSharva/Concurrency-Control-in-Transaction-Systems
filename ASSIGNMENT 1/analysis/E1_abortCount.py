# AbortCount analysis with varying numTransactions 1000-5000

import matplotlib.pyplot as plt
import os

# Data
numTransactions = [1000, 2000, 3000, 4000, 5000]
BOCC_CTA = [2.742, 2.836, 2.931, 2.8845, 2.8656]
FOCC_CTA = [17.71, 18.586, 18.3253, 18.8272, 18.993]
FOCC_OTA = [1.755, 1.782, 1.803, 1.808, 1.827] # To be changes

# make a big plot
plt.figure(figsize=(16, 9))

# plot data
plt.plot(numTransactions, BOCC_CTA, label='BOCC_CTA', marker='o', color='navy')
plt.plot(numTransactions, FOCC_CTA, label='FOCC_CTA', marker='o', color='purple')
plt.plot(numTransactions, FOCC_OTA, label='FOCC_OTA', marker='o', color='green')

# show grid lines
plt.grid(True)

plt.xlabel('total number of transactions')
plt.ylabel('Average aborts')
plt.title('Abort Count Analysis with Varying numTransactions')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()