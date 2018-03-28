import math

def ms(s):
    return s*10**(-3)

def piekbreedte(hoek):
    
    LL = ms(0.7)
    RL = ms(2.3)

    return hoek*(RL - LL)/180 + LL

def treshold(piekbreedte):
    
    LL = ms(0.7)
    RL = ms(2.3)
    FK = 16*10**6
    PRESC = 256

    return FK*piekbreedte/PRESC


def hoekify(x, y, l1, l2):
    d = math.sqrt(x**2 + y**2) #afstand tussen pen en oorsprong


    temp1 = (l1**2 + d**2 - l2**2)/(2*l1*d)
    hoek1 = math.acos(temp1) + math.atan(y/x)
    hoek1 = degrees(hoek1)

    temp2 = (l1**2 + l2**2 - d**2)/(2*l1*l2)
    hoek2 = math.acos(temp2)
    hoek2 = degrees(hoek2)

    return (hoek1, hoek2)

def degrees(h):
    return h*180/math.pi



def bepaal_treshold(x,y):

    hoek1, hoek2 = hoekify(x, y, 14, 14)
    piek1, piek2 = piekbreedte(hoek1), piekbreedte(hoek2)
    treshold1, treshold2 = treshold(piek1), treshold(piek2)

    return (treshold1, treshold2)
    
    