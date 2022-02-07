cc = gcc
CFLAGS = -Wall
target = 20161614.out
objects = 20161614.o
$(target): $(objects)
	$(cc) -o $(target) $(objects)
	
$(objects) : 20161614.h			

.PHONY : clean
clean : 
	rm $(target) $(objects)
