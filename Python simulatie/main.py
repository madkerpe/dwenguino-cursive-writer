import math

def ms(s):
    return s*10**(-3)

def angle_to_pulse_duration(hoek):
    
    LL = ms(0.7)
    RL = ms(2.3)

    return hoek*(RL - LL)/180 + LL

def pulse_duration_to_treshold(piekbreedte):
    FK = 16*10**6
    PRESC = 256

    return FK*piekbreedte/PRESC


def position_to_angle(x, y, l1, l2):
    d = math.sqrt(x**2 + y**2) #afstand tussen pen en oorsprong


    temp1 = (l1**2 + d**2 - l2**2)/(2*l1*d)
    hoek1 = math.acos(temp1) + math.atan(y/x)
    hoek1 = radians_to_degrees(hoek1)

    temp2 = (l1**2 + l2**2 - d**2)/(2*l1*l2)
    hoek2 = math.acos(temp2)
    hoek2 = radians_to_degrees(hoek2)

    return (hoek1, hoek2)

def radians_to_degrees(h):
    return h*180/math.pi



def position_to_treshold(x,y):

    hoek1, hoek2 = position_to_angle(x, y, 14, 14)
    piek1, piek2 = angle_to_pulse_duration(hoek1), angle_to_pulse_duration(hoek2)
    treshold1, treshold2 = pulse_duration_to_treshold(piek1), pulse_duration_to_treshold(piek2)

    return (int(treshold1), int(treshold2))

def angle_to_treshold(hoek):
    return pulse_duration_to_treshold(angle_to_pulse_duration(hoek))

class BP(object):
    def __init__(self, P0, P1, P2):
        self.P0 = P0
        self.P1 = P1
        self.P2 = P2

    def calculate_x(self, t):
        return self.P0[0]*(1-t)**2 + 2*(1-t)*t*self.P1[0] + self.P2[0]*t**2

    def calculate_y(self, t):
        return self.P0[1]*(1-t)**2 + 2*(1-t)*t*self.P1[1] + self.P2[1]*t**2

if __name__ == "__main__":
    
    vierkant = [[(14, 10), (16, 10), (18, 10)],[(18, 10), (18,12), (18,14)],[(18,14),(16,14),(14,14)],[(14,14),(14,12),(14,10)]]
    
    coordinaten_lijst = []
    treshold_lijst = []

    for bp_parameters in vierkant:
        bp = BP(bp_parameters[0], bp_parameters[1], bp_parameters[2])

        for t in range(11):
            t = t/10
            print(t)

            coordinaten_lijst.append((bp.calculate_x(t), bp.calculate_y(t)))

    print(coordinaten_lijst)

    for coordinaat in coordinaten_lijst:
        print(position_to_treshold(coordinaat[0], coordinaat[1]))
        treshold_lijst.append(position_to_treshold(coordinaat[0], coordinaat[1]))


    file = open("output.txt", 'w')
    
    ocb = str('{')
    ccb = str('}')

    file.write(ocb)
    for koppel in treshold_lijst:
        file.write(ocb + str(koppel[0]) + str(",") + str(koppel[1]) + ccb + str(","))
    file.write(ccb)

    file.close()

        