# AbortCount analysis with varying variables 1000-5000

import matplotlib.pyplot as plt
import os

# Data
variables = [1000, 2000, 3000, 4000, 5000]
BOCC_CTA = [2.759, 1.705, 1.267, 1.037, 0.823]
FOCC_CTA = [16.462, 3.495, 1.693, 1.195, 0.78]
FOCC_OTA = [1.736, 1.044, 0.767, 0.587, 0.488] # To be changed

# make a big plot
plt.figure(figsize=(16, 9))

# plot data
plt.plot(variables, BOCC_CTA, label='BOCC_CTA', marker='o', color='navy')
plt.plot(variables, FOCC_CTA, label='FOCC_CTA', marker='o', color='purple')
plt.plot(variables, FOCC_OTA, label='FOCC_OTA', marker='o', color='green')

# show grid lines
plt.grid(True)

plt.xlabel('number of data items')
plt.ylabel('Average aborts')
plt.title('Abort Count Analysis with Varying number of data items')
plt.legend()
script_name = os.path.splitext(os.path.basename(__file__))[0]
plt.savefig(f"{script_name}.png")
plt.show()