import random
import textwrap as tr
from FIFO import FIFO_sim
from LRU import LRU_sim
from OPT import OPT_sim

def main():
    #Generate and print the reference string.
    refstring = genReferenceString()
    print("Reference String:",tr.fill(str(refstring), width = 111))

    #List to store the results form each of the 30 runs
    #for each of the differenct algorithms.
    FIFO_faults = []
    LRU_faults = []
    OPT_faults = []
    
    #Running each simulated algorithm in range [1,31).
    #FIFO
    for x in range(1,31):
        temp = FIFO_sim(refstring, x)
        FIFO_faults.append(temp)
    #LRU
    for x in range(1,31):
        temp = LRU_sim(refstring, x)
        LRU_faults.append(temp)
    #OPT
    for x in range(1,31):
        temp = OPT_sim(refstring, x)
        OPT_faults.append(temp)

    #Print everything.
    print("FIFO Faults:", FIFO_faults)
    print("LRU Faults:", LRU_faults)
    print("OPT Faults:", OPT_faults)

'''
When called this function returns a int [] of size 100
with randomly generated integers in the range [0,49].
'''    
def genReferenceString():
    refString = [] 
    for x in range(100):
        num = random.randint(0,49)
        refString.append(num)
    return(refString)

#Entry point for the program3.py implementation.
if __name__ == '__main__':
    main()
