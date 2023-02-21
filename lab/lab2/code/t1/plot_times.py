import numpy as np
import matplotlib.pyplot as plt


plt.figure()
x = np.array([1,2,4,8,16,28])
y = np.array([0.035, 0.103, 0.143, 0.193, 0.308, 0.478])
y2 = np.array([0.038, 0.0836, 0.118, 0.159, 0.187, 0.217])
y3 = np.array([0.0146, .035, .060, .055, .056, .062])
plt.plot(x,y, label='OpenMP Lock')
plt.plot(x,y2, label='OpenMP Critical')
plt.plot(x,y3, label='OpenMP Atomic')
plt.xlabel('number of threads')
plt.ylabel('t(s)')
plt.legend()
plt.grid()
plt.title('Performance vs thread count')
plt.show()
