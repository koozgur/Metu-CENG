CC=g++
CFLAGS=-c -ansi -Wall -Wconversion -pedantic-errors -O0

all: main

ObjLoader.o: ObjLoader.cpp ObjLoader.h Structs.h
	$(CC) $(CFLAGS) -o ObjLoader.o ObjLoader.cpp

MeshGraph.o: MeshGraph.cpp MeshGraph.h Structs.h BinaryHeap.h
	$(CC) $(CFLAGS) -o MeshGraph.o MeshGraph.cpp

BinaryHeap.o: BinaryHeap.cpp BinaryHeap.h
	$(CC) $(CFLAGS) -o BinaryHeap.o BinaryHeap.cpp

Main.o: main.cpp MeshGraph.h Structs.h BinaryHeap.h Structs.h
	$(CC) $(CFLAGS) Main.o main.cpp

main: BinaryHeap.o MeshGraph.o ObjLoader.o main.o
	$(CC) BinaryHeap.o MeshGraph.o ObjLoader.o main.o -o main

clean:
	rm *o
	rm main