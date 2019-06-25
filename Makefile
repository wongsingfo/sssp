CC=g++
CCFLAGS=-std=c++11 -Wno-write-strings
objects:=data_reader.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CCFLAGS)
	
serial: main.cc $(objects)
	$(CC) -o main main.cc $(objects) $(CCFLAGS)

all: serial