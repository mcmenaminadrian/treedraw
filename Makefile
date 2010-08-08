all: treedraw

treedraw: main.cpp node.cpp
	g++ -o treedraw -Wall main.cpp node.cpp -lxerces-c
