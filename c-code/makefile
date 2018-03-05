all:
	gcc -c -fpic display.c interface.c accelerometer.c
	gcc -shared -o libdisplay.so display.o interface.o
	gcc -shared -o libaccelerometer.so accelerometer.o interface.o
