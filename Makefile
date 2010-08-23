all: treedraw

treedraw: main.cpp node.cpp tree.hpp
	g++ -o treedraw -Wall main.cpp node.cpp -lxerces-c
