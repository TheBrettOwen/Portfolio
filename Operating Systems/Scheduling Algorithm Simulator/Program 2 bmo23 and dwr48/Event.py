class eventNode:
    def __init__(self, time = 0, eventType = 1, proc = None, readyNum = 0):
        self.time = time
        self.eventType = eventType
        self.nextEvent = None # 1 = Arrival, 2 = departure, 3 = Preempt event
        #proc represents the process arriving, departing, or being
        #preempted.
        self.process = proc
        #The number of processes in the ready a the moment of this
        #event.
        self.readyNum = readyNum
        
    def __str__(self):
        return str(self.__class__) + ": " + str(self.__dict__)
