import ctypes
import socket
import fcntl
import struct
import time
import accelerometer

libDis = ctypes.cdll.LoadLibrary('../c-code/libdisplay.so')

pixelArray = ctypes.c_short*288

DigitPattern = {
    0:(0,1,1,1,1,0)+
      (1,0,0,0,0,1)+
      (0,1,1,1,1,0),
    1:(1,0,0,0,1,0)+
      (1,1,1,1,1,1)+
      (1,0,0,0,0,0),
    2:(1,1,0,0,1,0)+
      (1,0,1,0,0,1)+
      (1,0,0,1,1,0),
    3:(0,1,0,0,0,1)+
      (1,0,0,1,0,1)+
      (0,1,1,0,1,0),
    4:(0,0,0,1,1,1)+
      (0,0,0,1,0,0)+
      (1,1,1,1,1,1),
    5:(0,1,0,1,1,1)+
      (1,0,0,1,0,1)+
      (0,1,1,0,0,1),
    6:(0,1,1,1,1,0)+
      (1,0,0,1,0,1)+
      (0,1,1,0,0,1),
    7:(0,0,0,0,0,1)+
      (1,1,1,0,0,1)+
      (0,0,0,1,1,1),
    8:(0,1,1,0,1,0)+
      (1,0,0,1,0,1)+
      (0,1,1,0,1,0),
    9:(1,0,0,1,1,0)+
      (1,0,1,0,0,1)+
      (0,1,1,1,1,0),
    ' ':(0,0,0,0,0,0),
    ':':(0,2,0,0,2,0)}

StrPattern = {
    '0':DigitPattern[0]+DigitPattern[' '],
    '1':DigitPattern[1]+DigitPattern[' '],
    '2':DigitPattern[2]+DigitPattern[' '],
    '3':DigitPattern[3]+DigitPattern[' '],
    '4':DigitPattern[4]+DigitPattern[' '],
    '5':DigitPattern[5]+DigitPattern[' '],
    '6':DigitPattern[6]+DigitPattern[' '],
    '7':DigitPattern[7]+DigitPattern[' '],
    '8':DigitPattern[8]+DigitPattern[' '],
    '9':DigitPattern[9]+DigitPattern[' '],
    '.':(0,0,0,0,0,0)+
    (1,0,0,0,0,0)+
    (0,0,0,0,0,0)+
    (0,0,0,0,0,0),
    ' ':DigitPattern[' ']*4}

DigitPatternH12 = {
    0:(0,0,0,0,0,0)+
      (0,0,0,0,0,0),
    1:(1,1,1,1,1,1)+
      (0,1,0,0,0,0)}


def DrawNumber(number, fg, bg):
    digit3 = (number/1000) % 10
    digit2 = (number/100) %10
    digit1 = (number/10) %10
    digit0 = number % 10

    pixelArray = ctypes.c_short*288

    fgInt = [int(4095.99)*x for x in fg]
    bgInt = [int(4095.99)*x for x in bg]
    pixelPat = DigitPattern[digit0]+DigitPattern[' ']+DigitPattern[digit1]+DigitPattern[' ']+DigitPattern[' ']+DigitPattern[digit2]+DigitPattern[' ']+DigitPattern[digit3]
    colorPat = [fgInt[0] if x else bgInt[0] for x in pixelPat] + [fgInt[1] if x else bgInt[1] for x in pixelPat] + [fgInt[2] if x else bgInt[2] for x in pixelPat]
    pixels = pixelArray(*colorPat)
    libDis.WriteDisplay(pixels,ctypes.c_char('\2'))


    
def DrawTime(dt, fg, bg=(0,0,0), colon=(0,0,0), h24=True):
    h = dt.hour
    m = dt.minute
    fgInt = [int(4095.99*x) for x in fg]
    bgInt = [int(4095.99*x) for x in bg]
    cInt = [int(4095.99*x) for x in colon]

    m10 = (m/10) % 10
    m1 = m % 10

    if h24:
        h10 = (h/10) % 10
        h1 = h%10
        pixelsH = DigitPattern[h10]+DigitPattern[' ']+DigitPattern[h1]
        pixelsC = DigitPattern[':']+DigitPattern[':']
    else:
        h = ((h-1)%12)+1
        h10 = (h/10) % 10
        h1 = h%10
        pixelsH = DigitPatternH12[h10]+DigitPattern[' ']+DigitPattern[h1]
        pixelsC = DigitPattern[' ']+DigitPattern[':']+DigitPattern[' ']
        
    pixelsM = DigitPattern[m10]+DigitPattern[' ']+DigitPattern[m1]

    pixelList = [fg if x else bg for x in pixelsH] + [colon if x else bg for x in pixelsC] + [fg if x else bg for x in pixelsM]
    DrawPixels(pixelList)
    

def SetDotCorrection(r,g,b):
    rInt = int((2*r-1)*2048)
    gInt = int((2*g-1)*2048)
    bInt = int((2*r-1)*2048)
    dcs = pixelArray(*(([rInt]*96)+([gInt]*96)+[bInt]*96))
    libDis.WriteDisplay(dcs,ctypes.c_char('\3'))

def DrawMonochrome(pixmap,fg,bg):
    colorPix = [fg if x else bg for x in pixmap]
    DrawPixels(colorPix)

def DrawPixels(pixmap):
#    try:
#        a=DrawPixels.xl.ReadAccelerations()
#    except AttributeError:
#        DrawPixels.xl=accelerometer.XL()
#        a=DrawPixels.xl.ReadAccelerations()
#    if (a[0])<0:
#        pixmap.reverse()
    pixelsRed = [int(4095.99*x[0]) for x in pixmap]
    pixelsGreen = [int(4095.99*x[1]) for x in pixmap]
    pixelsBlue =  [int(4095.99*x[2]) for x in pixmap]
    pixels = pixelArray(*(pixelsRed+pixelsGreen+pixelsBlue))
    libDis.WriteDisplay(pixels,ctypes.c_char('\2'))
        
def ScrollString(s,fg=(0.01,0,0.01),bg=(0,0,0),timePerPixel=0.25,reps=1,pad=True):
    if pad:
        s = s+' '*4
    s=s*reps
    charList = [StrPattern[c] for c in s]
    pixList = [p for pm in charList for p in pm]
    offset = 0
    for offset in range(0,len(pixList)-95,6):
        DrawMonochrome(pixList[offset:(offset+96)],fg,bg)
        time.sleep(timePerPixel)
        
def DrawIPAddr(reps=3,fg=(0.01,0,0.01),bg=(0,0,0),timePerPixel=0.25,iface='wlan0'):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    ipStr = socket.inet_ntoa(fcntl.ioctl(s.fileno(),0x8915, struct.pack('256s', iface[:15]))[20:24])
    ScrollString(ipStr,fg=fg,bg=bg,reps=reps,timePerPixel=timePerPixel)
