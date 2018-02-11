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
    while (n<cycles):
        t = datetime.now().time()
        brightness = 0.02
        cycleHours = 6
        cycleFrac = ((t.hour+t.minute/60.0+t.second/3600.0)%cycleHours)/cycleHours
        fgColor = colorsys.hsv_to_rgb(cycleFrac,1,brightness)
        fsec = t.second+t.microsecond/1.0e6
        colonColor = colorsys.hsv_to_rgb(fsec/60.0,1,brightness/4*(math.sin(2*math.pi*fsec/8.0)+1)) 
        display.DrawTime(t.hour,t.minute,fgColor,(0,0,0),colonColor)
        time.sleep(1/60.0)
        if (cycles>0):
            n=n+1
        
if (__name__ == "__main__"):
    runClock(0)
    
