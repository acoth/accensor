all:
	gcc -c -fpic display.c interface.c
	gcc -pthread -shared -o libdisplay.so display.o interface.o
