#! /usr/bin/python
from datetime import datetime
import time
import display
import math

# Make the color the time is displayed in change smoothly
# in a full cycle every 6 hours
# Draw the background black and the colon pale gray
while 1:
    t = datetime.now().time()
    brightness = 0.02
    cycleTime = 6.0
    hueAngle = 2.0*math.pi*(t.hour+t.minute/60.0+t.second/3600.0)/cycleTime
    fg1 = (math.sin(hueAngle),brightness*math.sin(hueAngle+2*math.pi/3.0),brightness*math.sin(hueAngle+4*math.pi/3.0))
    fgColor = [brightness/2.0*(x+1) for x in fg1]
    display.DrawTime(t.hour,t.minute,fgColor,(0,0,0),(0.001,0.001,0.001))
    time.sleep(1)
    
    
