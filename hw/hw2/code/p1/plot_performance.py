import numpy as np, matplotlib.pyplot as plt

# taken from p1_results.txt
times1 = [1.43, 1.30, 0.87, 0.52, 0.32, 0.25]
times2  = [1.43, 0.77, 0.45, 0.28, 0.17, 0.13]
Sp1 = [times1[0]/t for t in times1]
Sp2 = [times1[0]/t for t in times2]
num_threads = [1, 2, 4, 8, 16, 32]

plt.figure()
plt.plot(num_threads, Sp1, label='With load imbalance')
plt.scatter(num_threads, Sp1, color='b')

plt.plot(num_threads, Sp2, label='Without load imbalance')
plt.scatter(num_threads, Sp2, color='orange')

plt.xlabel('# of threads')
plt.ylabel('time (s)')
plt.title('Speedup as a function of thread count')
plt.legend()
plt.grid()
plt.savefig('figure2_load_balance.png')
