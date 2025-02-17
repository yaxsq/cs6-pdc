import time
import random

N = 1000  # Change this value to modify the matrix size

M1 = [[random.randint(0, 100) for _ in range(N)] for _ in range(N)]
M2 = [[random.randint(0, 100) for _ in range(N)] for _ in range(N)]
M3 = [[0] * N for _ in range(N)]

def add_row_major():
    for i in range(N):
        for j in range(N):
            M3[i][j] = M1[i][j] + M2[i][j]

def add_column_major():
    for j in range(N):
        for i in range(N):
            M3[i][j] = M1[i][j] + M2[i][j]

def direct_addition():
    global M3
    M3 = [[M1[i][j] + M2[i][j] for j in range(N)] for i in range(N)]

start = time.time()
add_row_major()
print(f"Row Major Execution Time: {time.time() - start:.6f} seconds")

start = time.time()
add_column_major()
print(f"Column Major Execution Time: {time.time() - start:.6f} seconds")

start = time.time()
direct_addition()
print(f"Direct Addition Execution Time: {time.time() - start:.6f} seconds")
