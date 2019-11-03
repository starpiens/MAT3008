import subprocess as sp
import sys
import matplotlib.pyplot as plt
import numpy as np

a = -3
b = 2
m = -0.5
s = 1.5
intervals = 100
samples = [100, 10000, 100000]

# Uniform distribution
def draw_uniform():
    # By Numpy
    for i in range(len(samples)):
        x = np.random.uniform(-3, 2, samples[i])
        plt.subplot(2, len(samples), i+1)
        plt.title('By NumPy\n(n=' + str(samples[i]) + ')')
        plt.xlabel('X')
        plt.ylabel('Probability Density')
        plt.hist(x, intervals, density=True, facecolor='xkcd:rose')

    # By NR
    for i in range(len(samples)):
        result = sp.run([sys.argv[1], str(samples[i]), 'uniform'], stdout=sp.PIPE)
        result = result.stdout.decode(encoding='UTF-8')
        x = [float(j) * (b-a) + a for j in result.split()]
        plt.subplot(2, len(samples), len(samples)+i+1)
        plt.title('By NR\n(n=' + str(samples[i]) + ')')
        plt.xlabel('X')
        plt.ylabel('Probability Density')
        plt.hist(x, intervals, density=True, facecolor='xkcd:blue green')

# Gaussian distribution
def draw_gaussian():
    # By Numpy
    for i in range(len(samples)):
        x = m + s * np.random.randn(samples[i])
        plt.subplot(2, len(samples), i+1)
        plt.title('By NumPy\n(n=' + str(samples[i]) + ')')
        plt.xlabel('X')
        plt.ylabel('Probability Density')
        plt.hist(x, intervals, density=True, facecolor='xkcd:rose')

    # By NR
    for i in range(len(samples)):
        result = sp.run([sys.argv[1], str(samples[i]), 'gaussian'], stdout=sp.PIPE)
        result = result.stdout.decode(encoding='UTF-8')
        x = [float(j) * s + m for j in result.split()]
        plt.subplot(2, len(samples), len(samples)+i+1)
        plt.title('By NR\n(n=' + str(samples[i]) + ')')
        plt.xlabel('X')
        plt.ylabel('Probability Density')
        plt.hist(x, intervals, density=True, facecolor='xkcd:blue green')

plt.figure(1, figsize=(10, 6))
draw_uniform()
plt.figure(2, figsize=(10, 6))
draw_gaussian()
plt.show()