#include <iostream>
#include <cstdlib>
#include <string>
#include "tree.hpp"

using namespace std;

Node::Node()
{
	value = string("NULL");
	left = -1;
	right = -1;
	black = true;
	otherdata = NULL;
}

Node::Node(char* str)
{
	value = string(str);
	left = -1;
	right = -1;
	black = true;
	otherdata = NULL;
}

void Node::setvalue(char* str)
{
	value = string(str);
}

const string Node::getvalue() const
{
	return value;
}

Tree::~Tree()
{
	int i = items.size();
	while (i){
		delete items[i - 1];
		items.pop_back();
		i--;
	}
}

