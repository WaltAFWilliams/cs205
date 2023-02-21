import numpy as np
import matplotlib.pyplot as plt

plt.figure()
x = np.array([1,2,4,7,16,32])
y = np.array([0.035, 0.103, 0.143, 0.193, 0.308, 0.478])
plt.scatter(x,y)
plt.grid()
plt.title('Performance vs thread count')
plt.show()


