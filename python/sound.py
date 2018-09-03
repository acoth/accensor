import pigpio

pi = pigpio.pi()

pi.set_PWM_frequency(18,800)


def BeepOn(duty=128):
    pi.set_PWM_dutycycle(18,duty)

def BeepOff(duty=0):
    pi.set_PWM_dutycycle(18,duty)

def BeepFreq(f):
    pi.set_PWM_frequency(18,f)
