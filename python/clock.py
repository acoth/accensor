#! /usr/bin/python
from datetime import datetime,timedelta
import time
import colorsys
import math
import display
import accelerometer
import math
import sound

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
        alarm['setTime'] += timedelta(seconds=150*angle**3)
        t=datetime.now()
        fsec = t.second+t.microsecond/1.0e6
        display.DrawTime(alarm['setTime'],colorsys.hsv_to_rgb((fsec%4/4),1,0.005))
        time.sleep(0.1)
    alarm['enabled'] = True



def runClock(cycles):
    alarm = {'enabled':False,
             'goingOff':False,
             'setTime':datetime.now()}
    sunset = {'enabled':False,
              'setTime': datetime.now()}
    xl = accelerometer.XL()
    n=-1
    brightness = 0.001
    display.SetDotCorrection(1,1,1)
    t=datetime.now()-timedelta(0,61,0)
    redraw=True
    while (n<cycles):
        redraw=True
        prevT=t
        t = datetime.now()
        if t.minute != prevT.minute:
            redraw=True
        if alarm['goingOff']:
            redraw=True
            
            if xl.Tap():
                alarm['goingOff'] = False
        else:
            dummy=3
            #            time.sleep(0.001)
            if xl.Int():
                if xl.DoubleTap():
                    time.sleep(0.5)
                    if xl.DoubleTap():
                        time.sleep(0.5)
                        if xl.DoubleTap():
                            display.DrawIPAddr(reps=1)
                        else:
                            SetAlarm(sunset,xl)
                            redraw=True
                    else:
                        SetAlarm(alarm,xl)
                        redraw = True
        if alarm['enabled'] and t.time() > alarm['setTime'].time() and prevT.time() < alarm['setTime'].time():
            alarm['goingOff'] = True
        
        cycleHours = 24
        cycleFrac = ((t.hour+t.minute/60.0+t.second/3600.0)%cycleHours)/cycleHours
        fsec = t.second+t.microsecond/1.0e6
        if alarm['goingOff']:
            fgColor = (0,1,0)
            bgColor = (1,1,1) if fsec%1.0<0.5 else (0,0,0)
            if (fsec%1.0)<0.25:
                sound.BeepOn()
            else:
                sound.BeepOff()
        else:
            bgColor = (0,0,0)
            if t.hour<4:
                fgColor = (3./4096,0,0)
            if t.hour>=4 and t.hour<8:
                fgColor = (2./4096,2./4096,0)
            if t.hour>=8 and t.hour<12:
                fgColor = (0/4096,6./4096,0)
            if t.hour>=12 and t.hour<16:
                fgColor = (0/4096,5./4096,5./4096)
            if t.hour>=16 and t.hour<20:
                fgColor = (0/4096,0/4096,8./4096)
            if t.hour>=20:
                fgColor = (2./4096,0,2./4096)
                
        colonColor = (0,0,0) if not alarm['enabled'] else (.0005,0.0005,0.0005)
#        xl.ReadAccelerations()            
        if (redraw):
            display.DrawTime(t,fg=fgColor,bg=bgColor,colon=colonColor)
            redraw = False
        time.sleep(1/10.0)
        if (cycles>0):
            n=n+1

if (__name__ == "__main__"):
    runClock(0)

    
