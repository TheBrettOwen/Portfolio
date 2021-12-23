from EventsList import LinkedList
from Event import eventNode
from FCFS_sched import makeReport
from times_generator import genExp
from Process import process 

#Used for state.
ARR = 1
DEP = 2
PRE = 3
clock = 0.0
quantum = 0 
cpuIdle = True
readyQueueSize = 0
runningProc = None
eventList = LinkedList()
processQueue = []
totalProcesses = 10000 #set to 10000 after testing
departureCount = 0

#used for metrics
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
    global runningProc
    global readyQueueSize
    global quantum
    global processQueue
    global cpuIdle

    #Metrics
    global cpuIdleStart
    global cpuIdleEnd
    global cpuIdleTotalTime
    
    #print("foundEvent = arrEvent")
    if cpuIdle:
        cpuIdle = False
        cpuIdleEnd = clock
        cpuIdleTotalTime = cpuIdleTotalTime + (cpuIdleEnd-cpuIdleStart)

    if  event.process.burstProgressTime > quantum: #everything screws up here

        event.process.burstProgressTime = event.process.burstProgressTime - quantum
        preEvent = eventNode(quantum + clock, PRE, event.process, readyQueueSize)
        eventList.addEvent(preEvent)
        processQueue.append(event.process)

    elif event.process.burstProgressTime <= quantum:
    
        event.process.cmpltTime = clock + event.process.burstProgressTime

        runningProc = event.process
        depEvent = eventNode(event.process.cmpltTime, DEP, event.process ,readyQueueSize)
        eventList.addEvent(depEvent)
        
    else:
        readyQueueSize = readyQueueSize + 1
        event.readyNum = readyQueueSize  

def handleDeparture(event):
    global clock
    global cpuIdle
    global runningProc
    global readyQueueSize
    global processQueue
    global cpuIdleStart
    global departureCount
    global turnaroundSum
    global processTotalWaitTime

    #print("foundEvent = depEvent")
    processQueue.pop(0)
    departureCount = departureCount + 1
    #Metrics
    event.process.cmpltTime = clock + processQueue[0].burstProgressTime
    turnaroundSum = turnaroundSum + (event.process.cmpltTime - event.process.arrTime)
    
    processTotalWaitTime = processTotalWaitTime + (event.process.cmpltTime - event.process.arrTime - event.process.burstTime)

    #if Nothing in Queue
    if readyQueueSize == 0:
        cpuIdle = True
        cpuIdleStart = clock
        runningProc = None

    #if there's something in the queue
    else:
        readyQueueSize = readyQueueSize - 1
        event.readyNum = readyQueueSize
        if len(processQueue) !=0: 
            depEvent = eventNode(clock + processQueue[0].burstProgressTime, DEP, processQueue[0])
            eventList.addEvent(depEvent)
            runningProc = processQueue[0]
    
def handlePreempt(event):
    global clock
    global cpuIdle
    global runningProc
    global readyQueueSize
    global quantum
    global processQueue

    #print("foundEvent = preempt Event")
    processQueue.pop(0)
    #If quantum is greater than remaining burst time
    
    #if quantum is smaller than remaining burst time
    if  event.process.burstProgressTime > quantum: 
        
        event.process.burstProgressTime = event.process.burstProgressTime - quantum
        preEvent = eventNode(quantum + clock, PRE, event.process, readyQueueSize)
        eventList.addEvent(preEvent)
        processQueue.append(event.process)
        
    elif event.process.burstProgressTime <= quantum:
    
        event.process.cmpltTime = clock + event.process.burstProgressTime

        runningProc = event.process
        depEvent = eventNode(event.process.cmpltTime, DEP, event.process ,readyQueueSize)
        eventList.addEvent(depEvent)
    #if cpu is processing something else
    else:
        readyQueueSize = readyQueueSize + 1
        event.readyNum = readyQueueSize  

def makeReport(procsPerSec):
    global turnaroundSum
    global totalProcesses
    global cpuIdleTotalTime
    global processTotalWaitTime
    global clock

    turnaround = turnaroundSum/totalProcesses
    throughput = totalProcesses/clock
    cpuUtil = (1 - (cpuIdleTotalTime/clock)) * 100
    processTotalWaitTime = processTotalWaitTime/totalProcesses
    avgQueueLength = procsPerSec * processTotalWaitTime

    metrics = [turnaround, throughput, cpuUtil, avgQueueLength]
    #print("size of eventList", eventList.getSize())
    resetGlobals()
    return(metrics)

def resetGlobals():
    #State
    global clock
    global quantum
    global cpuIdle
    global readyQueueSize
    global runningProc 
    global eventList 
    global processQueue 
    global totalProcesses 
    global departureCount 
    #Metrics
    global turnaroundSum
    global finalclock
    global cpuIdleStart 
    global cpuIdleEnd
    global cpuIdleTotalTime
    global processTotalWaitTime
    #State
    clock = 0.0
    quantum = 0 
    cpuIdle = True
    readyQueueSize = 0
    runningProc = None
    eventList = LinkedList()
    processQueue = []
    totalProcesses = 10000 #set to 10000 after testing
    departureCount = 0
    #Metrics
    turnaroundSum = 0
    finalclock = 0
    cpuIdleStart = 0
    cpuIdleEnd = 0
    cpuIdleTotalTime = 0
    processTotalWaitTime = 0

def RR_sim(procsPerSec, burst, q):
    #Used for state.
    global quantum
    global clock
    global cpuIdle
    global runningProc
    global readyQueueSize
    global processQueue
    global departureCount
    global eventList
    quantum = q
    
    arrTime = 0
    #Initialize the event list
    for x in range(totalProcesses + int(0.25*totalProcesses)): 
        invBurst = 1/burst
        burstTime = genExp(invBurst)
        arrTime = arrTime + genExp(procsPerSec)
        newProc = process(x, arrTime, burstTime)
        arrEvent = eventNode(newProc.arrTime, ARR, newProc)
        eventList.addEvent(arrEvent)
        
    #initialize the ready queue
    currEvent = eventList.head
    while currEvent != None:
        processQueue.append(currEvent.process)
        currEvent = currEvent.nextEvent

    #print("real process queue at init")
    #for item in processQueue:
    #    print (item.arrTime)
    
    #CPU processes the processes
    while departureCount < totalProcesses:
        event = getNextEvent()
        #print(eventList.getSize())
        if event != None:
            clock = event.time
            case = event.eventType
            if case == ARR:
                handleArrival(event)
            elif case == DEP:
                #print("case Depart")
                handleDeparture(event)
            elif case == (PRE):
                #print("case preempt")
                handlePreempt(event)
        else:
            print("bad")
            break

    return(makeReport(procsPerSec))

  
