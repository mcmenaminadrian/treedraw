all: treeview

treeview: main.cpp redblackSAX.hpp redblackSAX.cpp
	g++ -o treeview -Wall main.cpp redblackSAX.cpp -lxerces-c
