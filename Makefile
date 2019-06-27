CC=g++
CCFLAGS=-std=c++11 -Wno-write-strings -O2 -fopenmp
objects:=data_reader.o timer.o solver.o solver_spfa.o solver_dijkstra.o solver_delta.o

%.o: %.cc %.h
	$(CC) -c -o $@ $< $(CCFLAGS)

serial: main.cc $(objects)
	$(CC) -o main main.cc $(objects) $(CCFLAGS)

all: serial

clean: 
	rm *.o
	rm main