import subprocess as sp
import sys
import matplotlib.pyplot as plt
import numpy as np

m = -0.5
s = 1.5
intervals = 100
samples = [1e2, 1e4, 1e5]

result = sp.run([sys.argv[1]], stdout=sp.PIPE).stdout
print(result.decode(encoding='UTF-8'))

# Expected histogram
for i in range(len(samples)):
    x = m + s * np.random.randn(int(samples[i]))
    plt.subplot(2,len(samples),i+1)
    plt.title('Expected\n(n=' + str(int(samples[i])) + ')')
    plt.xlabel('Number')
    plt.ylabel('Count')
    plt.hist(x, intervals, density=False, facecolor='g')

plt.show()