import sys
def OPT_sim(refstring, framesAvailable):
    #copy of the reference string. Not using the copy function returns a
    #pointer to the ref-string from program3.py.
    tempRefString = refstring.copy() 
    freeFrames = [] #A List to store the changing state of the free frames.
    pageFaults = 0  #Page fault counter.

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
            #A tuple with values (page number, next page number ref-string index)
            evictee = (None, -sys.maxsize - 1) 
            #Search for which frame in the frames list will not be used for the
            #longest period of time, i.e has the largest index in the ref-string.
            for i in freeFrames:
                try:
                    pageIndex = tempRefString.index(i)
                    if (evictee[1] < pageIndex):
                        evictee = (i, pageIndex)
                except ValueError:
                    evictee = (i, None)
                    break
            freeFrames.remove(evictee[0])
            freeFrames.append(tempRefString[0])
            tempRefString.pop(0)
            pageFaults += 1
                  
    return(pageFaults)
