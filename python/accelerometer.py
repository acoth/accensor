import ctypes
import time

class XL:
    lib = ctypes.cdll.LoadLibrary('../c-code/libaccelerometer.so')

    def __init__(self):
        self.WriteReg(29,32) #Tap Threshold of 2g
        self.WriteReg(30,0) #No X offset adjust
        self.WriteReg(31,0) #No Y offset adjust
        self.WriteReg(32,0) #No Z offset adjust
        self.WriteReg(33,255) #160ms max time for a tap
        self.WriteReg(34,128) #min required separation between taps
        self.WriteReg(35,255) #max window for second tap
        self.WriteReg(42,7) #Enable all axes for tap
        self.WriteReg(44,10) #Set data rate to 100Hz
        self.WriteReg(45,8) #Turn on accelerometer
        self.WriteReg(46,96) #turn on both tap interrupts
        self.WriteReg(47,0) #direct all interrupts to pin 1
        self.WriteReg(49,15) #Set data format to full resolution
        self.ReadReg(48)
        self.dataLog = []
    
    def WriteReg(self,reg,val):
        self.lib.WriteReg(ctypes.c_char(chr(reg)),ctypes.c_char(chr(val)))
    
    def ReadReg(self,reg):
        return(self.lib.ReadReg(ctypes.c_char(chr(reg))))

    def ReadAccelerations(self):
        aType = ctypes.c_float*3
        a = aType(0,0,0)
        self.lib.ReadAccelerations(a)
        aList = list(a)
        self.LogAccel(aList)
        return(aList)

    def LogAccel(self,a):
        t = time.time()
        self.dataLog = filter(lambda x: (t-x[0])<3,self.dataLog)
        self.dataLog.append((t,a))

    def AmBeingShaken(self,threshold=2,duration=1,sampling=0.25):
        meanAccel = reduce(lambda x,y: (x[0]+y[1][0]/len(self.dataLog),x[1]+y[1][1]/len(self.dataLog),x[2]+y[1][2]/len(self.dataLog)),self.dataLog,(0.,0.,0.))
        varianceMag = map(lambda x: (x[0],sum([(x[1][n]-meanAccel[n])**2 for n in range(3)])),self.dataLog);
        tOverThresh = [x[0] for x in varianceMag if x[1]>threshold]
        for sind in range(int(duration/sampling)+1):
            timeSeps = [abs(self.dataLog[0][0]-t) for t in tOverThresh]
            if len(timeSeps)==0 or min(timeSeps)>sampling/2.0:
                return False
        return True

    def Tap(self):
        return (self.ReadReg(48)&64)>0

    def DoubleTap(self):
        return (self.ReadReg(48)&32)>0
    
