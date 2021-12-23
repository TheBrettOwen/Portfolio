def FIFO_sim(refstring, framesAvailable):
    #A copy of the reference string. Not using the copy function returns a
    #pointer to the ref-string from program3.py.
    tempRefString = refstring.copy() 
    freeFrames = [] #A List to store the changing state of the free frams.
    pageFaults = 0 #Page fault counter.

    #The while-loop will run until the reference string has been fully emptied
    #of all elements.
    while (len(tempRefString) > 0):
         #Case:the page is already in the loaded in a frame.
        if(freeFrames.count(tempRefString[0]) > 0):
            tempRefString.pop(0)
        #Case:the page is not loaded in a frame and there is an available frame.    
        elif (len(freeFrames) < framesAvailable):
            freeFrames.append(tempRefString[0])
            tempRefString.pop(0)
            pageFaults += 1
        #Case:the page is not loaded in a frame and there is no free frame.    
        else:
            freeFrames.pop(0) #Evict the first page in the first frame. 
            freeFrames.append(tempRefString[0])
            tempRefString.pop(0)
            pageFaults += 1

    return(pageFaults)
