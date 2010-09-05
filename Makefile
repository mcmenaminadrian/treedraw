all: treedraw

treedraw: main.cpp node.cpp node.hpp
	g++ -o treedraw -Wall main.cpp node.cpp -lxerces-c
