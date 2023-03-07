import numpy as np
import matplotlib.pyplot as plt

# Define the roofline models for processors A and B
A_peak_flops = 80  # peak floating-point performance for processor A (GFLOPS/s)
A_peak_mem_bw = 30  # peak memory bandwidth for processor A (GB/s)
A_ridge_point = 2.667  # operational intensity at the ridge point for processor A

B_peak_flops = 4096  # peak floating-point performance for processor B (GFLOPS/s)
B_peak_mem_bw = 80  # peak memory bandwidth for processor B (GB/s)
B_ridge_point = 51.2  # operational intensity at the ridge point for processor B

# Define the x-axis values for the roofline graph (operational intensity)
x = np.logspace(-1, 4)

# Define the y-axis values for the roofline graph (operational performance)
yA = np.minimum(A_peak_mem_bw * x, A_peak_flops)  # processor A
yB = np.minimum(B_peak_mem_bw * x, B_peak_flops)  # processor B

# Create the roofline graph
fig, ax = plt.subplots()
ax.loglog(x, yA, 'b', label='Processor A')
ax.loglog(x, yB, 'orange', label='Processor B')
ax.set_xlabel('Operational Intensity (FLOPs/Byte)')
ax.set_ylabel('Operational Performance (GFLOPs/s)')
ax.set_xlim(x[0], x[-1])
ax.grid()
ax.set_ylim(1e-1, 1e4)

ax.grid(True)
# Add legend to the graph
ax.legend()

#plt.savefig("roofline.png")
plt.show()
