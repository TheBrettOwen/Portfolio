import sys
from FCFS_sched import FCFS_sim
from RR_sched import RR_sim
from SRTF_sched import SRTF_sim

def main():
    turnArray = []
    throughArray = []
    utilArray = []
    queueLengthArray = []

    try:
        algorithm = int(sys.argv[1])
        avgBurst = float(sys.argv[2])
        quantum = float(sys.argv[3])
    except:
        print("ERROR: INVALID PROGRAM INVOCATION")
        print("CALL:\'$ python<#> program2.py <schedule:int 1-3> <average burst time:float> <quantum:float>\'")
        exit(1)
    
    print("Get a coffee, you'll be here a while...")

    if algorithm == 1:
        for x in range(30):
            turnaround, throughput, cpuUtil, avgQueueLength = FCFS_sim(x+1, avgBurst)
            turnArray.append(turnaround)
            throughArray.append(throughput)
            utilArray.append(cpuUtil)
            queueLengthArray.append(avgQueueLength)
    elif algorithm == 2:
        for x in range(30):
            turnaround, throughput, cpuUtil, avgQueueLength = SRTF_sim(x+1, avgBurst)
            turnArray.append(turnaround)
            throughArray.append(throughput)
            utilArray.append(cpuUtil)
            queueLengthArray.append(avgQueueLength)
    elif algorithm == 3:
        for x in range(30):
            turnaround, throughput, cpuUtil, avgQueueLength = RR_sim(x+1, avgBurst, quantum)
            turnArray.append(turnaround)
            throughArray.append(throughput)
            utilArray.append(cpuUtil)
            queueLengthArray.append(avgQueueLength)
    print(len(turnArray),turnArray)
    print(len(throughArray),throughArray)
    print(len(utilArray),utilArray)
    print(len(queueLengthArray),queueLengthArray)
if __name__ == '__main__':
    main()
