#!/bin/sh
cd /home/pi/accensor/python
killall clock.py
./displayoff.py
./battery.py --disable
