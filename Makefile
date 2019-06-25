CC=g++
CCFLAGS=-std=c++11 -Wno-write-strings
objects:=data_reader.o timer.o solver.o solver_spfa.o solver_dijkstra.o

%.o: %.cc
	$(CC) -c -o $@ $< $(CCFLAGS)

serial: main.cc $(objects)
	$(CC) -o main main.cc $(objects) $(CCFLAGS)

all: serial