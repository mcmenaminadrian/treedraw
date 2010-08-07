#include <iostream>
#include <cstdlib>
#include <string>
#include "tree.hpp"

using namespace std;

node::node()
{
	value = string("");
	left = -1;
	right = -1;
	otherdata = NULL;
}

node::node(char* str)
{
	value = string(str);
	left = -1;
	right = -1;
	otherdata = NULL;
}

void node::setvalue(char* str)
{
	value = string(str);
}

const string node::getvalue() const
{
	return value;
}

tree::~tree()
{
	int i = items.size();
	while (i){
		delete items[i - 1];
		items.pop_back();
		i--;
	}
}

