import ctypes

lib = ctypes.cdll.LoadLibrary('../c-code/libaccelerometer.so')

def WriteReg(reg,val):
    lib.WriteReg(ctypes.c_char(chr(reg)),ctypes.c_char(chr(val)))
    
def ReadReg(reg):
    return(lib.ReadReg(ctypes.c_char(chr(reg))))

def ReadAccelerations():
    aType = ctypes.c_float*3
    a = aType(0,0,0)
    lib.ReadAccelerations(a)
    return(list(a))

WriteReg(29,4) #Tap Threshold of +/-0.25g
WriteReg(30,0) #No X offset adjust
WriteReg(31,0) #No X offset adjust
WriteReg(32,0) #No X offset adjust
WriteReg(33,255) #160ms max time for a tap
WriteReg(42,7) #Enable all axes for tap
WriteReg(44,10) #Set data rate to 100Hz
WriteReg(45,8) #Turn on accelerometer
WriteReg(46,64) #turn on single-tap interrupts
WriteReg(47,0) #direct all interrupts to pin 1
WriteReg(49,15) #Set data format to full resolution
