import random
import math

def uRand():
    return(random.uniform(0.1,1))

def genExp(expLambda):
    x = 0.0
    u = 0.0
    while x == 0:
        u = uRand()
        x = (-1/expLambda) * math.log(u)
    return(x)
