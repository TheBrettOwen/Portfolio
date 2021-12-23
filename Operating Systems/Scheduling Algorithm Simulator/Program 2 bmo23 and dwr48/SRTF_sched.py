import heapq as hp
from EventsList import LinkedList
from Event import eventNode
from times_generator import genExp
from Process import process 

#Used for state.
ARR = 1
DEP = 2
PRE = 3
clock = 0.0
cpuIdle = True
readyQueueSize = 0
runningProc = None
eventList = LinkedList()
processQueue = []
departureCount = 0

#Used for metrics.
turnaroundSum = 0 
finalclock = 0
totalProcesses = 20 #set to 10000 after testing
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
    global turnaroundSum

    #Used for metrics.
    global cpuIdleStart
    global cpuIdleEnd
    global cpuIdleTotalTime
    global processTotalWaitTime
    
    #print("foundEvent = arrEvent")
    #print("burst Time", event.process.burstTime)
    if cpuIdle:
        cpuIdle = False
        #Metrics
        cpuIdleEnd = clock
        cpuIdleTotalTime = cpuIdleTotalTime +  (cpuIdleEnd - cpuIdleStart)
        #Update simulation.
        event.process.cmpltTime = clock + event.process.burstProgressTime
        runningProc = (clock, event.process)
        depEvent = eventNode(clock + event.process.burstProgressTime, DEP, event.process ,readyQueueSize)
        eventList.addEvent(depEvent)
        
    else:
        #This currentlty arriving process, if run on the cpu at this moment, will finish faster
        #then what is currently running on the cpu.
        #The scheduled departure event for the currently running process
        #must be rolled back.
        if (clock + event.process.burstTime) < runningProc[1].cmpltTime:
            #Roll back the speculative departure event, because of preemption.
            eventList.removeEventType(event,DEP)
            #Schedule a preempt event.
            event.process.cmpltTime = clock + 0.00000000000001 + event.process.burstProgressTime
            preEvent = eventNode(clock + 0.00000000000001, PRE, event.process, readyQueueSize)
            eventList.addEvent(preEvent)
        else:    
            readyQueueSize = readyQueueSize + 1
            event.readyNum = readyQueueSize
        

def handleDeparture(event):

    #print("complete time:",event.process.cmpltTime)
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

    #print("foundEvent = depEvent")
    departureCount = departureCount + 1
    tempProc = hp.heappop(processQueue)
    turnaroundSum = turnaroundSum + ((clock + tempProc[1].burstProgressTime) - event.process.arrTime)
    processTotalWaitTime = processTotalWaitTime + ((clock + tempProc[1].burstProgressTime)  - event.process.arrTime - event.process.burstTime)
    
    if readyQueueSize == 0:
        cpuIdle = True
        cpuIdleStart = clock
        runningProc = None
    else:
        readyQueueSize = readyQueueSize - 1
        event.readyNum = readyQueueSize
        if len(processQueue) != 0:
            procTup = hp.heappop(processQueue)
            depEvent = eventNode(clock + procTup[1].burstProgressTime, DEP, procTup[1])
            eventList.addEvent(depEvent)
            procTup[1].cmpltTime = clock + procTup[1].burstProgressTime
            runningProc = (clock,procTup[1])
            hp.heappush(processQueue,procTup)

def handlePreemption(event):
    #Used for state.
    global clock
    global cpuIdle
    global runningProc
    global readyQueueSize
    global turnaroundSum

    #Used for metrics.
    global cpuIdleStart
    global cpuIdleEnd
    global cpuIdleTotalTime
    global processTotalWaitTime
    #print("foundEvent = preEvent")
    
    runningProc[1].burstProgressTime = runningProc[1].burstProgressTime - (clock - runningProc[0])
    hp.heappop(processQueue)
    hp.heappush(processQueue, (runningProc[1].burstProgressTime, runningProc[1]))
    readyQueueSize = readyQueueSize + 1
    event.readyNum= readyQueueSize
    depEvent = eventNode(clock + event.process.burstProgressTime, DEP, event.process, readyQueueSize)
    eventList.addEvent(depEvent)
    
def resetGlobals():
    global clock
    global quantum
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
    quantum = 0 
    cpuIdle = True
    readyQueueSize = 0
    runningProc = None
    eventList = LinkedList()
    processQueue = []
    totalProcesses = 20 #set to 10000 after testing
    departureCount = 0

    #used for metrics
    turnaroundSum = 0
    finalclock = 0
    cpuIdleStart = 0
    cpuIdleEnd = 0
    cpuIdleTotalTime = 0
    processTotalWaitTime = 0    
    
def SRTF_sim(procsPerSec, burst):

    #Used for state.
    global clock
    global cpuIdle
    global runningProc
    global departureCount
    
    #Used for Metric Calculation
    global totalProcesses
    global finalclock
    global cpuIdleTotalTime
    
    #Initalize the event list
    arrTime = 0
    #Initialize the event list
    for x in range(totalProcesses + int(0.25*totalProcesses)): 
        invBurst = 1/burst
        burstTime = genExp(invBurst)
        arrTime = arrTime + genExp(procsPerSec)
        newProc = process(x, arrTime, burstTime)
        arrEvent = eventNode(newProc.arrTime, ARR, newProc)
        eventList.addEvent(arrEvent)
        
    #Initalize the process ready queue
    currEvent = eventList.head
    while currEvent != None:
        processQueue.append((currEvent.process.burstProgressTime,currEvent.process))
        currEvent = currEvent.nextEvent
    hp.heapify(processQueue)

    '''
    print("real process queue at initalization")
    for item in processQueue:
        print (item[1].arrTime)
    '''
    
    while departureCount < totalProcesses:
        #print("=================================================================")
        event = getNextEvent()
        if event != None:
            print("pre-clock:",clock)
            clock = event.time
            print("post-clock:",clock)
            case = event.eventType
            if case == ARR:
                print("ARR")
                handleArrival(event)
            
            elif case == DEP:
                print("DEP")
                handleDeparture(event)
                
            elif case == PRE:
                print("PRE")
                handlePreemption(event)
                
            '''
            print(event)
            print("actuall queue size:", len(processQueue))
            print("simulated queue size:", readyQueueSize)
            print("process in cpu:", runningProc)
            print("=================================================================\n\n\n")
            '''
        else:
            print(clock)
            print("bad")
            currEvent = eventList.head
            while currEvent != None:
                print("event:",currEvent)
                print("proccess:",currEvent.process)
                print()
                print()
                currEvent = currEvent.nextEvent
            print(departureCount)
        
            break


    return(makeReport(procsPerSec, burst))

    
   
def makeReport(procPerSec, burst):
    global turnaroundSum
    global totalProcesses
    global cpuIdleTotalTime
    global processTotalWaitTime
    turnaround = turnaroundSum/totalProcesses
    throughput = totalProcesses/clock
    cpuUtil = (1 - (cpuIdleTotalTime/clock)) * 100
    processTotalWaitTime = processTotalWaitTime/totalProcesses
    
    # Equation for wait time is turnaround time is turnaround time - burst time, so I calculate total wait time and divide it all by final time. 
    # Equation for queue length is Lambda (the same one that we pass, processes per second) * average wait time
    avgQueueLength = procPerSec * processTotalWaitTime 
    metrics = [turnaround, throughput, cpuUtil, avgQueueLength]
    '''
    print("Turnaround: ", turnaround)
    print("Throughput:", throughput)
    print("CPU Utilization:", cpuUtil)
    print("AVG. Queue Length:", avgQueueLength)
    '''
    resetGlobals()
    return(metrics)
