def LRU_sim(refstring, framesAvailable):
    #A copy of the reference string. Not using the copy function returns a
    #pointer to the ref-string from program3.py.
    tempRefString = refstring.copy()
    freeFrames = [] #A List to store the changing state of the free frames.
    pageFaults = 0 #Page fault counter.

    #Works the same as FIFO but, when a page hit occurs, it instead pops the page
    #hit element in the frames list and appends it to the end of the frames List.
    while (len(tempRefString) > 0):
        #Case:the page is already in the loaded in a frame.
        if(freeFrames.count(tempRefString[0]) > 0):
            freeFrames.remove(tempRefString[0]) #Remove the page hit element.
            #Append the page hit element to the end of the free frames List.
            freeFrames.append(tempRefString[0]) 
            tempRefString.pop(0)
        #Case:the page is not loaded in a frame and there is an available frame.    
        elif (len(freeFrames) < framesAvailable):
            freeFrames.append(tempRefString[0])
            tempRefString.pop(0)
            pageFaults += 1
        #Case:the page is not loaded in a frame and there is no free frame.    
        else:
            freeFrames.pop(0)
            freeFrames.append(tempRefString[0])
            tempRefString.pop(0)
            pageFaults += 1

    return(pageFaults)
    
