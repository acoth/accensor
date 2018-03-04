import ctypes

libDis = ctypes.cdll.LoadLibrary('../c-code/libdisplay.so')

pixelArray = ctypes.c_short*288

DigitPattern = {
    0:(0,1,1,1,1,0)+
      (1,0,0,0,0,1)+
      (0,1,1,1,1,0),
    1:(0,0,0,0,0,1)+
      (1,1,1,1,1,1)+
      (0,1,0,0,0,1),
    2:(0,1,1,0,0,1)+
      (1,0,0,1,0,1)+
      (0,1,0,0,1,1),
    3:(0,1,0,1,1,0)+
      (1,0,1,0,0,1)+
      (1,0,0,0,1,0),
    4:(1,1,1,1,1,1,)+
      (0,0,1,0,0,0)+
      (1,1,1,0,0,0),
    5:(1,0,0,1,1,0)+
      (1,0,1,0,0,1)+
      (1,1,1,0,1,0),
    6:(1,0,0,1,1,0)+
      (1,0,1,0,0,1)+
      (0,1,1,1,1,0),
    7:(1,1,1,0,0,0)+
      (1,0,0,1,1,1)+
      (1,0,0,0,0,0),
    8:(0,1,0,1,1,0)+
      (1,0,1,0,0,1)+
      (0,1,0,1,1,0),
    9:(0,1,1,1,1,0)+
      (1,0,0,1,0,1)+
      (0,1,1,0,0,1),
    ' ':(0,0,0,0,0,0),
    ':':(0,2,0,0,2,0)}


def Initialize(mode=0):
    libDis.Initialize(ctypes.c_char(chr(mode)))

def Cleanup():
    libDis.Cleanup()

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


def DrawTime(h,m, fg, dimmer=1, bg=(0,0,0), colon=(0,0,0)):
    h10 = (h/10) % 10
    h1 = h%10
    m10 = (m/10) % 10
    m1 = m % 10


    fgInt = [int(4095.99*x) for x in fg]
    bgInt = [int(4095.99*x) for x in bg]
    cInt = [int(4095.99*x) for x in colon]
    pixelsH = DigitPattern[h1]+DigitPattern[' ']+DigitPattern[h10]
    pixelsC = DigitPattern[':']+DigitPattern[':']
    pixelsM = DigitPattern[m1]+DigitPattern[' ']+DigitPattern[m10]

    pixelsMRed = [fgInt[0] if x else bgInt[0] for x in pixelsM]
    pixelsCRed = [cInt[0] if x else bgInt[0] for x in pixelsC]
    pixelsHRed = [fgInt[0] if x else bgInt[0] for x in pixelsH]
    pixelsRed = pixelsMRed+pixelsCRed+pixelsHRed
    
    pixelsMGreen = [fgInt[1] if x else bgInt[1] for x in pixelsM]
    pixelsCGreen = [cInt[1] if x else bgInt[1] for x in pixelsC]
    pixelsHGreen = [fgInt[1] if x else bgInt[1] for x in pixelsH]
    pixelsGreen = pixelsMGreen+pixelsCGreen+pixelsHGreen

    pixelsMBlue = [fgInt[2] if x else bgInt[2] for x in pixelsM]
    pixelsCBlue = [cInt[2] if x else bgInt[2] for x in pixelsC]
    pixelsHBlue = [fgInt[2] if x else bgInt[2] for x in pixelsH]
    pixelsBlue = pixelsMBlue+pixelsCBlue+pixelsHBlue
    
    pixels = pixelArray(*(pixelsRed+pixelsGreen+pixelsBlue))
    libDis.WriteDisplay(pixels,ctypes.c_short(int(65535*dimmer)),ctypes.c_char('\2'))

def SetDotCorrection(r,g,b):
    rInt = int((2*r-1)*2048)
    gInt = int((2*g-1)*2048)
    bInt = int((2*r-1)*2048)
    dcs = pixelArray(*(([rInt]*96)+([gInt]*96)+[bInt]*96))
    libDis.WriteDisplay(dcs,ctypes.c_char('\3'))
    
    
