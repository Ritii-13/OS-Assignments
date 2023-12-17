import matplotlib
matplotlib.use('TkAgg')  # Use the TkAgg backend (or another suitable backend)
import matplotlib.pyplot as plt

# Define scheduling policies and priorities
scheduling_policies = ["SCHED_OTHER", "SCHED_RR", "SCHED_FIFO"]
colors = ['b', 'g', 'r']  # Blue, Green, Red

# Read the times from the text file
with open("process_times.txt", "r") as file:
    lines = file.readlines()
    times = [line.split(": ")[1].strip(" ms\n") for line in lines]

# Convert times to integers
times = [int(time) for time in times]

# Create a bar chart for time taken by each scheduling policy
plt.bar(scheduling_policies, times, color=colors)

# Set labels and title
plt.xlabel("Scheduling Policies")
plt.ylabel("Time to Complete (ms)")
plt.title("Execution Time for Different Scheduling Policies")

# Show the plot
plt.show()
