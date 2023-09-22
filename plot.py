import matplotlib.pyplot as plt

# Read the statistics data from the file and handle invalid values
with open('stat_values.txt', 'r') as file:
    stat_data = []
    for line in file:
        stripped_line = line.strip()
        if stripped_line not in ["-1.#IND00", "-1.#INF00", '-1.#INF00000000000e+000', "1.#INF00000000000e+000"]:
            try:
                stat_data.append(float(stripped_line))
            except ValueError:
                pass
                # print(f"Skipping invalid value: {stripped_line}")

# Create a list of x values based on the length of stat_data
x = [i for i in range(1, len(stat_data) + 1)]

# Create a line graph
plt.plot(x, stat_data, color='blue')
plt.xlabel('Iteration')
plt.ylabel('Difference')
plt.title('Difference (Line Graph)')

# Set the x-axis ticks to integer values
plt.xticks(x)

# Show the plot
plt.show()
