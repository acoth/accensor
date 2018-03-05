#! /usr/bin/python
from datetime import datetime
import time
import colorsys
import math
import display
import accelerometer

# Make the color the time is displayed in change smoothly
# in a full cycle every 6 hours
# Draw the background black and the colon pale gray
def runClock(cycles):
    n=-1
    brightness = 0.0015
    display.SetDotCorrection(1,1,1)
    while (n<cycles):
        t = datetime.now().time()
        cycleHours = 24
        cycleFrac = ((t.hour+t.minute/60.0+t.second/3600.0)%cycleHours)/cycleHours
        fgColor = colorsys.hsv_to_rgb(cycleFrac,1,brightness)
        fsec = t.second+t.microsecond/1.0e6
        colonColor = (0,0,0) if (t.second%2)==1 else fgColor 
        display.DrawTime(t.hour,t.minute,fg=fgColor,colon=colonColor,h24=False)
        time.sleep(1/60.0)
        if (cycles>0):
            n=n+1

#                    colonColor = colorsys.hsv_to_rgb(t.second/60.0,1,brightness)

#        colonColor = colorsys.hsv_to_rgb(fsec/60.0,0.9,brightness/4) 

if (__name__ == "__main__"):
    runClock(0)

    
