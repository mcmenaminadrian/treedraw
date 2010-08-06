all: treedraw

treedraw: main.cpp redblackSAX.hpp node.cpp redblackSAX.cpp
	g++ -o treedraw -Wall main.cpp node.cpp redblackSAX.cpp -lxerces-c
