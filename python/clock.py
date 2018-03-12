#! /usr/bin/python
from datetime import datetime,timedelta
import time
import colorsys
import math
import display
import accelerometer
import math

def SetAlarm(alarm,xl):
    if alarm['enabled']:
        alarm['enabled'] = False
        return
    doneSetting = False
    while (not doneSetting):
        a = xl.ReadAccelerations()
        doneSetting = abs(a[2])>0.5
        if (abs(a[1])<0.1):
            a[1] = 0
        angle = math.atan(a[1]/a[0])
        alarm['setTime'] += timedelta(seconds=480*angle**3)
        
        display.DrawTime(alarm['setTime'].hour,alarm['setTime'].minute,(0.,0.005,0))
        time.sleep(0.25)
    alarm['enabled'] = True



def runClock(cycles):
    alarm = {'enabled':False,
             'goingOff':False,
             'setTime':datetime.now()}
    xl = accelerometer.XL()
    n=-1
    brightness = 0.0015
    display.SetDotCorrection(1,1,1)
    t=0
    while (n<cycles):
        prevT=t
        t = datetime.now()
        if alarm['enabled'] and t.time() > alarm['setTime'].time() and prevT.time() < alarm['setTime'].time():
            alarm['goingOff'] = True
        
        cycleHours = 24
        cycleFrac = ((t.hour+t.minute/60.0+t.second/3600.0)%cycleHours)/cycleHours
        fsec = t.second+t.microsecond/1.0e6
        if alarm['goingOff'] and fsec%2<1:
            fgColor = (1,1,1)
        else:
            fgColor = colorsys.hsv_to_rgb(cycleFrac,1,brightness)
        colonColor = (0,0,0) if not alarm['enabled'] else (0.001,0.001,0.001)
        if alarm['goingOff']:
            if xl.Tap():
                alarm['goingOff'] = False
        else:
            if xl.DoubleTap():
                SetAlarm(alarm,xl)
        if xl.AmBeingShaken(duration=1):
            display.DrawIPAddr(reps=1)
        xl.ReadAccelerations()            
        display.DrawTime(t.hour,t.minute,fg=fgColor,colon=colonColor)
        time.sleep(1/60.0)
        if (cycles>0):
            n=n+1

if (__name__ == "__main__"):
    runClock(0)

    
