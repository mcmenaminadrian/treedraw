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
	yco = -1;
	xco = -1;
}

Node::Node(char* str)
{
	value = string(str);
	left = -1;
	right = -1;
	black = true;
	otherdata = NULL;
	yco = -1;
	xco = -1;
}

void Node::setvalue(char* str)
{
	value = string(str);
}

const string Node::getvalue() const
{
	return value;
}

Tree::Tree()
{
	distance = 2;
}

Tree::Tree(int d)
{
	distance = d;
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

void Tree::calcpoints(Node* n, int level, Node* leftmost, Node* rightmost)
{
	n->yco = level;
	if (n->left != -1)
		calcpoints(items[n->left], level + 1, n, rightmost);
	if (n->right != -1)
		calcpoints(items[n->right], level + 1, leftmost, n);

	if (!n->left && !n->right) {
	}}	


void Tree::position()
{
	if (items.size() == 0)
		return;
	//post order traversal
	calcpoints(items[0], 0, items[0], items[0]);
}
