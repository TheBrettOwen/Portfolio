class process:
    def __init__(self, procId, arrTime, burst, priority = 0,remBurTime = 0): #the chunk of 'priority' in the parameters is a default value if there isn't a value passed to it
        self.procId = procId
        self.arrTime = arrTime
        self.burstTime = burst
        self.cmpltTime = 0
        self.burstProgressTime = burst
        self.priority = priority
    def __str__(self):
        return str(self.__class__) + ": " + str(self.__dict__)
