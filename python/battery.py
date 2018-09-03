#! /usr/bin/python
import argparse
import RPi.GPIO as GPIO

parser = argparse.ArgumentParser(description='Control whether battery power is enabled or disabled (airplane mode)')

parser.add_argument('-e','--enable',help='Enable battery charging/power',action='store_true')
parser.add_argument('-d','--disable','--airplane',help='Disable battery charging/power (activate airplane mode)',action='store_true')

args = parser.parse_args()

if (args.enable or args.disable):
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(37,GPIO.OUT)
    if args.disable:
        GPIO.output(37,0)
    else:
        GPIO.output(37,1)
        
    
    

