all: treedraw

treedraw: main.cpp node.cpp node.hpp
	g++ -O2 -o treedraw -Wall main.cpp node.cpp -lxerces-c
