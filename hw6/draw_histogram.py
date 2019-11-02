import subprocess as sp
import sys
import matplotlib.pyplot as plt
import numpy as np

a = -3
b = 2
m = -0.5
s = 1.5
intervals = 100
samples = [1e2, 1e4, 1e5]

result = sp.run([sys.argv[1]], stdout=sp.PIPE)
result = result.stdout.decode(encoding='UTF-8')
print(result)


plt.figure(1, figsize=(10, 6))

# Expected histogram
for i in range(len(samples)):
    x = np.random.uniform(-3, 2, int(samples[i]))
    plt.subplot(2, len(samples), i+1)
    plt.title('Expected\n(n=' + str(int(samples[i])) + ')')
    plt.xlabel('Number')
    plt.ylabel('Count')
    plt.hist(x, intervals, density=False, facecolor='xkcd:rose')

# Actual histogram
for i in range(len(samples)):
    x = np.random.uniform(-3, 2, int(samples[i])+i+1)
    plt.subplot(2, len(samples), len(samples)+i+1)
    plt.title('Actual\n(n=' + str(int(samples[i])) + ')')
    plt.xlabel('Number')
    plt.ylabel('Count')
    plt.hist(x, intervals, density=False, facecolor='xkcd:blue green')


plt.figure(2, figsize=(10, 6))

# Expected histogram
for i in range(len(samples)):
    x = m + s * np.random.randn(int(samples[i]))
    plt.subplot(2, len(samples), i+1)
    plt.title('Expected\n(n=' + str(int(samples[i])) + ')')
    plt.xlabel('Number')
    plt.ylabel('Count')
    plt.hist(x, intervals, density=False, facecolor='xkcd:rose')

# Actual histogram
for i in range(len(samples)):
    x = m + s * np.random.randn(int(samples[i]))
    plt.subplot(2, len(samples), len(samples)+i+1)
    plt.title('Actual\n(n=' + str(int(samples[i])) + ')')
    plt.xlabel('Number')
    plt.ylabel('Count')
    plt.hist(x, intervals, density=False, facecolor='xkcd:blue green')

plt.show()