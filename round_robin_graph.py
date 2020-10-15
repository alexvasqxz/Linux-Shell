
# 
#  round_robin_graph.py
#  
#  This program written in Python uses the round robin
#  process scheduling algorithm and displays the sequence
#  It also displays a graph that compares the average turn
#  around time in a quantum interval (between quantum_min and
#  quantum_max)
#
#  Link with the graph representing the average turnaround time
#  for the range from 1 quantum to 14 quantums (1-14 range):
#  https://drive.google.com/file/d/1e8UKX8h7zIANYKwcnFmFewkLxrzGc_2R/view
#
#   Created on 10/10/20
#   Copyright 2020 Gustavo Vasquez. All rights reserved
#
#           ___________________________________
#          |                                   |
#          |              WELCOME              |
#          |              TO THE               |
#          |            ROUND ROBIN            |
#          |       SCHEDULING ALGORITHM        |
#          |                                   |
#          |          -Gustavo Vasquez         |
#          |                                   |
#          |___________________________________|


from matplotlib import cm
import matplotlib.pyplot as plt

#////////////////////////////////////////
# This function will later be used to
# print the average turnaround time for
# every quantum of time along with the number
# of context switches each one made
#
#////////////////////////////////////////
def printQuantumsInfo():
    print ("Averageg Turnaround time for each quantum: ") 
    x = quantum_min_print
    for ta in turnaround_times:
    	print("For Quantum With value " + str(x) + ": " + str(ta))
    	x +=1

    print ("Context Switches per Quantum: ")
    cs = quantum_min_print
    for cont in context_switches:
    	print("For Quantum With value " + str(cs) + ": " + str(cont))
    	cs += 1


quantum_min = input("Enter the initial quantum (lower): ")
quantum_min_print = quantum_min
quantum_max = input("Enter the final quantum (greater): ")
quantums = []

context_switches = []
turnaround_times = []

processes =[2,3,4,12,8,5,6,1]
num_processes = len(processes)

# If the initial quantum is bigger than quantum_max then
# we cannot proceed with the function
if (quantum_min > quantum_max):
	print("Initial quantum's value must be less than final quantum's value")
	print("Please try again")
	exit()

# Round Robin Scheduling Algorithm
while quantum_min <= quantum_max:
    
    processes =[2,3,4,12,8,5,6,1]
    context_switch = 2
    context_switchess = 0
    execution_time = 0
    turnaround_time = 0.0

    i = 0
    quantums.append(quantum_min)

    while i < len(processes):

	# If the process takes less time than the
	# quantum time we won't have to add the 
	# context switch extra time
        if processes[i] <= quantum_min:
            print("process executed for Quantum: " + str(quantum_min))
            execution_time += processes[i]
            print("execution time " + str(execution_time))
        # If the process takes longer than the
        # quantum time then it will stop, we will use
        # the context switch and start the other process
        else:
            print("process interrupted")
            remain_time = processes[i] - quantum_min
            context_switchess += 1
            print("time process executed: "+ str(quantum_min))
            execution_time+=quantum_min
            execution_time+=context_switch
            print("execution time " + str(execution_time))
            processes.append(remain_time)

        print (processes[i:])
        i += 1
        print("-------------------------------")

    # The turnaround time is equal to the total execution time over the number of processes
    turnaround_time = float(execution_time)/float(num_processes)
    turnaround_times.append(turnaround_time)
    context_switches.append(context_switchess)
    quantum_min += 1

printQuantumsInfo()

y = turnaround_times
x = quantums

plt.plot(x, y)
plt.xlabel('Quantums')
plt.ylabel('Turnaround Time')

plt.show()
