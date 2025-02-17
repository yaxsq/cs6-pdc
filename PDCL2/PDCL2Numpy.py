import time
import numpy as np

N = 1000  # Change this value to modify the matrix size

M1 = np.random.randint(0, 100, (N, N))
M2 = np.random.randint(0, 100, (N, N))
M3 = np.zeros((N, N), dtype=int)

def add_row_major():
    global M3
    for i in range(N):
        for j in range(N):
            M3[i, j] = M1[i, j] + M2[i, j]

def add_column_major():
    global M3
    for j in range(N):
        for i in range(N):
            M3[i, j] = M1[i, j] + M2[i, j]

start = time.time()
add_row_major()
print(f"Row Major Execution Time: {time.time() - start:.6f} seconds")

start = time.time()
add_column_major()
print(f"Column Major Execution Time: {time.time() - start:.6f} seconds")

start = time.time()
M3 = M1 + M2  # Direct addition
print(f"Direct Addition Execution Time: {time.time() - start:.6f} seconds")
