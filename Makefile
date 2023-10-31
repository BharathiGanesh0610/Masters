SHELL = /bin/sh
CC = gcc -std=c99 
compops = -O3
linkops = -lm
objs = main.o get_input_eutectic.o Init_conf.o evolve.o Out_conf.o ran.o  
headers = Eutectic.h

%.o: %.c 
	$(CC) $(compops) -c $<

all: eutectoid.out
eutectoid.out: $(objs) $(headers) 
	$(CC) $(compops) -o eutectoid.out $(objs) $(linkops)

clean:
	-\rm *.o *.out
#End of the Makefile

