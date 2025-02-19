import matplotlib.pyplot as plt

import matplotlib.pyplot as plt

data = {
    1:  [(50000, 0.000461), (100000, 0.000509), (150000, 0.000981), (200000, 0.000561),
         (250000, 0.000775), (300000, 0.001456), (350000, 0.001562), (400000, 0.001844)],

    5:  [(50000, 0.000167), (100000, 0.000074), (150000, 0.000076), (200000, 0.000094),
         (250000, 0.000442), (300000, 0.001960), (350000, 0.000969), (400000, 0.000113)],

    10: [(50000, 0.000231), (100000, 0.000187), (150000, 0.000264), (200000, 0.000548),
         (250000, 0.000354), (300000, 0.000164), (350000, 0.000397), (400000, 0.000791)],

    15: [(50000, 0.000239), (100000, 0.000389), (150000, 0.000513), (200000, 0.000424),
         (250000, 0.000438), (300000, 0.000345), (350000, 0.000642), (400000, 0.000726)],

    20: [(50000, 0.000352), (100000, 0.000261), (150000, 0.000273), (200000, 0.000311),
         (250000, 0.000387), (300000, 0.000595), (350000, 0.000410), (400000, 0.000633)],

    25: [(50000, 0.000227), (100000, 0.000355), (150000, 0.000360), (200000, 0.000408),
         (250000, 0.000434), (300000, 0.000304), (350000, 0.000638), (400000, 0.000398)],

    30: [(50000, 0.000554), (100000, 0.000412), (150000, 0.000367), (200000, 0.000496),
         (250000, 0.000525), (300000, 0.000511), (350000, 0.000638), (400000, 0.000547)]
}


# Plot each thread count as a separate line
plt.figure(figsize=(10, 6))
for threads, values in data.items():
    x_vals = [point[0] for point in values]  # Array sizes
    y_vals = [point[1] for point in values]  # Execution times
    plt.plot(x_vals, y_vals, marker='o', label=f'Threads: {threads}')

# Labels and title
plt.xlabel("Vector Size")
plt.ylabel("Execution Time (seconds)")
plt.title("Execution Time vs Vector Size for Different Threads")
plt.legend()  # Show legend
plt.grid(True)

# Show the plot
# plt.show()

plt.savefig("exec_time_plot.png")  # Saves as an image