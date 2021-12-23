#RUN THIS FILE TO SEE AN EXAMPLE CASE OF AN INCORRECT EXECUATION (I THINK).
def LRU_sim(refstring, framesAvailable):
    tempRefString = refstring.copy()
    freeFrames = []
    pageFaults = 0
    
    #Works the same as FIFO but pop the element and add to the end of the queue if there isn't a page fault
    '''
    Dylan's notes: I agree with the sentence above. The element in question needs to be removed and added to the
    end of the freeFrams list. But I think the implmentation below for the first if block does not work as intended.
    the value needing to be removed will not be removed in certain cases. See comments below to understand what I 
    think the implementation might need to be.
    '''
    while (len(tempRefString) > 0):
        print("========================================")
        print("page:", tempRefString[0])
        if(freeFrames.count(tempRefString[0]) > 0):
            freeFrames.remove(tempRefString[0])   #I think temp is not needed and this line should just be freeFrames.remove(tempRefString[0])
            freeFrames.append(tempRefString[0])     #This line then should be freeFrames.append(tempRefString[0])
            tempRefString.pop(0)                            #FIXME add all that right here
            print("Frames:", freeFrames)
        elif (len(freeFrames) < framesAvailable):
            freeFrames.append(tempRefString[0])
            tempRefString.pop(0)
            pageFaults += 1
            print("Frames:", freeFrames)
        else:
            freeFrames.pop(0)
            freeFrames.append(tempRefString[0])
            tempRefString.pop(0)
            pageFaults += 1
            print("Frames:", freeFrames)
            
    print("========================================")
    print("Page Faults:", pageFaults)
    print("Final Frames:", freeFrames)
    return(0)

#ch10VM.pptx slide 10.34 (The results for this implementation do not match the slides)
LRU_sim([7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1],3)
