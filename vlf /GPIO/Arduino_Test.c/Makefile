CC = g++

CFLAGS = -w -Wall -O2
SRCS = Arduino_Test.c -lwiringPi

PROG = test

OPENCV = `pkg-config --cflags --libs opencv`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
	
	$(./PROG)
