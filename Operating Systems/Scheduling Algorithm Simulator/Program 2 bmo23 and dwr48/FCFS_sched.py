from EventsList import LinkedList
from Event import eventNode
from times_generator import genExp
from Process import process
import random

#Used for state.
ARR = 1
DEP = 2
clock = 0.0
cpuIdle = True
readyQueueSize = 0
runningProc = None
eventList = LinkedList()
processQueue = []
totalProcesses = 10000 #set to 10000 after testing
departureCount = 0

#Used for metrics.
turnaroundSum = 0 #CALCULATED WRONG CURRENTLY
finalclock = 0
totalProcesses = 10000 #set to 10000 after testing
cpuIdleStart = 0
cpuIdleEnd = 0
cpuIdleTotalTime = 0
processTotalWaitTime = 0 #CALCULATED WRONG CURRENTLY

    
def getNextEvent():
    foundEvent = eventList.head
    while foundEvent != None:
        if foundEvent.time > clock:
            break
        foundEvent = foundEvent.nextEvent

    return foundEvent

def handleArrival(event):

    #Used for state.
    global clock
    global cpuIdle
    global runningProc
    global readyQueueSize
    
    #Used for metrics.
    global turnaroundSum
    global cpuIdleStart
    global cpuIdleEnd
    global cpuIdleTotalTime
    global processTotalWaitTime
    
    
    #print("foundEvent = arrEvent")
    if cpuIdle:
        cpuIdle = False
        #Metrics
        cpuIdleEnd = clock
        cpuIdleTotalTime = cpuIdleTotalTime +  (cpuIdleEnd - cpuIdleStart)

        event.process.cmpltTime = clock + event.process.burstTime
        #turnaroundSum = turnaroundSum + (event.process.cmpltTime - event.process.arrTime)

        runningProc = event.process
        depEvent = eventNode(clock + event.process.burstTime, DEP, event.process ,readyQueueSize)
        eventList.addEvent(depEvent)
        
    else:
        readyQueueSize = readyQueueSize + 1
        event.readyNum = readyQueueSize
        

def handleDeparture(event):

    #Used for state.
    global clock
    global cpuIdle
    global runningProc
    global readyQueueSize
    global departureCount
    #Metrics
    global cpuIdleStart
    global turnaroundSum
    global processTotalWaitTime

    departureCount = departureCount + 1

    #print("foundEvent = depEvent")
    processQueue.pop(0)
    turnaroundSum = turnaroundSum + (clock - event.process.arrTime)
    processTotalWaitTime = processTotalWaitTime + (clock - event.process.arrTime - event.process.burstTime)
    
    
    if readyQueueSize == 0:
        cpuIdle = True
        cpuIdleStart = clock
        runningProc = None
    else:
        readyQueueSize = readyQueueSize - 1
        event.readyNum = readyQueueSize
        if len(processQueue) != 0:
            depEvent = eventNode(clock + processQueue[0].burstTime, DEP, processQueue[0])
            eventList.addEvent(depEvent)
            runningProc = processQueue[0]

def resetGlobals():
    global clock
    global cpuIdle
    global readyQueueSize
    global runningProc 
    global eventList 
    global processQueue 
    global totalProcesses 
    global departureCount 
    global turnaroundSum
    global finalclock
    global cpuIdleStart 
    global cpuIdleEnd
    global cpuIdleTotalTime
    global processTotalWaitTime
    #state
    clock = 0.0
    cpuIdle = True
    readyQueueSize = 0
    runningProc = None
    eventList = LinkedList()
    processQueue = []
    totalProcesses = 10000 #set to 10000 after testing
    departureCount = 0

    #used for metrics
    turnaroundSum = 0
    finalclock = 0
    cpuIdleStart = 0
    cpuIdleEnd = 0
    cpuIdleTotalTime = 0
    processTotalWaitTime = 0

def FCFS_sim(procPerSec, burst):
    

    #Used for state.
    global clock
    global cpuIdle
    global runningProc

    #Used for Metric Calculation
    global totalProcesses
    global finalclock
    global cpuIdleTotalTime
    
    arrTime = 0
    #Initalize the event list
    for x in range(totalProcesses + int(0.25*totalProcesses)): 
        invBurst = 1/burst
        burstTime = genExp(invBurst)
        arrTime = arrTime + genExp(procPerSec)
        newProc = process(x, arrTime, burstTime)
        arrEvent = eventNode(newProc.arrTime, ARR, newProc)
        eventList.addEvent(arrEvent)
        
    #Initalize the process ready queue
    currEvent = eventList.head
    while currEvent != None:
        processQueue.append(currEvent.process)
        currEvent = currEvent.nextEvent
        
    #print("real process queue at initalization")
    #for item in processQueue:
    #   print (item.arrTime)

    
    while departureCount < totalProcesses:
        #print("=================================================================")
        event = getNextEvent()
        if event != None:
            clock = event.time
            case = event.eventType
            if case == ARR:
                handleArrival(event)
            
            elif case == DEP:
                handleDeparture(event)
                '''
            print("clock:",clock)
            print(event)
            print("actuall queue size:", len(processQueue))
            print("simulated queue size:", readyQueueSize)
            print("process in cpu:", runningProc)
            print("=================================================================\n\n\n")
               '''
        else:
            currEvent = eventList.head
            while currEvent != None: 
                print(currEvent)
                currEvent = currEvent.nextEvent
            break
    
    return(makeReport(procPerSec, burst))
    


    
def makeReport(procPerSec, burst):
    
    global turnaroundSum
    global totalProcesses
    #global finalclock
    global cpuIdleTotalTime
    global processTotalWaitTime
    global clock
    turnaround = turnaroundSum/totalProcesses
    throughput = totalProcesses/clock
    cpuUtil = (1 - (cpuIdleTotalTime/clock)) * 100
    processTotalWaitTime = processTotalWaitTime/totalProcesses
    
    # Equation for wait time is turnaround time is turnaround time - burst time, so I calculate total wait time and divide it all by final time. 
    # Equation for queue length is Lambda (the same one that we pass, processes per second) * average wait time
    avgQueueLength = procPerSec * processTotalWaitTime 
    #print("Turnaround: ", turnaround)
    #print("Throughput:", throughput)
    #print("cpuIdleTotalTime",cpuIdleTotalTime)
    #print("CPU Utilization:", cpuUtil)
    #print("AVG. Queue Length:", avgQueueLength) 
    metrics = [turnaround, throughput, cpuUtil, avgQueueLength]
    resetGlobals()
    return(metrics)

