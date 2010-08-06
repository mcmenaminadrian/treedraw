#include <iostream>
#include <cstdlib>
#include <string>
#include "tree.hpp"

using namespace std;

node::node()
{
	value = string("");
	left = NULL;
	right = NULL;
}

node::node(char* str)
{
	value = string(str);
	left = NULL;
	right = NULL;
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
	free(root);
}

const node* tree::getroot() const
{
	return root;
}

void tree::free(node* n)
{
	if (n == NULL)
		return;
	free(n->left);
	free(n->right);
	delete n;
	n = NULL;
}

void tree::addnode(node* n)
{
	if (root == NULL)
		root = n;
	else
		insertnode(n, root);
}

void tree::insertnode(node* n, node* tn)
{
	int nv;
	nv = atoi(n->getvalue().c_str());
	int tv;
	tv = atoi(tn->getvalue().c_str());
	if (nv < tv) {
		if (tn->left == NULL){
			tn->left = n;
			return;
		}
		else {
			insertnode(n, tn->left);
			return;
		}
	}
	else {
		if (tn->right == NULL) {
			tn->right = n;
			return;
		}
		else {
			insertnode(n, tn->right);
			return;
		}
	}
}
