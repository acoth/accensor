#! /usr/bin/python
from datetime import datetime
import time
import display
import colorsys
import math

# Make the color the time is displayed in change smoothly
# in a full cycle every 6 hours
# Draw the background black and the colon pale gray
def runClock(cycles):
    n=-1
    display.SetDotCorrection(0.5,0.5,0.5)
    while (n<cycles):
        t = datetime.now().time()
        brightness = 0.0015
        cycleHours = 24
        cycleFrac = ((t.hour+t.minute/60.0+t.second/3600.0)%cycleHours)/cycleHours
        fgColor = colorsys.hsv_to_rgb(cycleFrac,1,brightness)
        fsec = t.second+t.microsecond/1.0e6
        colonColor = (0,0,0) 
        display.DrawTime(t.hour,t.minute,fgColor, dimmer=1)
        time.sleep(1/60.0)
        if (cycles>0):
            n=n+1

#        colonColor = colorsys.hsv_to_rgb(fsec/60.0,0.9,brightness/4) 

if (__name__ == "__main__"):
    display.Initialize()
    runClock(0)
    display.Cleanup()
    
