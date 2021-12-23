from typing import Counter
from Event import eventNode
class LinkedList:
    
    #Constructor for a linked-list of Event classes.
    def __init__(self):
        self.head = None
        
    #Allows the contents of the linked-list to be printed
    #to the console.
    def __str__(self):
        return str(self.__class__) + ": " + str(self.__dict__)
    
    #Adds a given Event class to the linked list in the proper
    #spot based upon the events time occurance.
    def addEvent(self, event):
        rover = self.head
        
        if (self.head == None):
            self.head = event
        else: 
            placeFound = False
            while placeFound == False:
                if rover == self.head and rover.time > event.time:
                    event.nextEvent = rover
                    self.head = event
                    placeFound = True   
                elif (rover.nextEvent == None):
                    rover.nextEvent = event
                    placeFound = True
                elif (rover.nextEvent.time > event.time):
                    event.nextEvent = rover.nextEvent
                    rover.nextEvent = event
                    placeFound = True
                rover = rover.nextEvent
                

    def getSize(self):
        rover = self.head
        count = 0
        if rover == None:
            return count
        else: 
            while rover != None:
                count = count + 1
                rover = rover.nextEvent
            return count
                    
    #Given an Event IN the linked-list it will look for the next
    #Event of the given type and remove it from the linked-list
    def removeEventType(self,event,eventType):
        rover = event
        eventFound = False
        while eventFound == False and rover.nextEvent is not None:
            if event.nextEvent.eventType == eventType:
                rover.nextEvent = rover.nextEvent.nextEvent
                eventFound = True
            rover = rover.nextEvent
            
                
            
        
