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
	offset = 2;
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
	offset = 2;
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

void Tree::calcpoints(Node* n, int level)
{
	n->yco = level;
	if (n->left != -1)
		calcpoints(items[n->left], level + 1 );
	if (n->right != -1)
		calcpoints(items[n->right], level + 1);

	Node* left = NULL;
	Node* right = NULL;
	int ileft = n->left;
	if (ileft != -1)
		left = items[ileft];
	
	int iright = n->right;
	if (iright != -1)
		right = items[iright];

	const int minsep = distance;
	int rootsep = minsep * 2;
	int cursep = rootsep;

	while (left && right) {
		if (cursep < minsep) {
			rootsep = rootsep + (minsep - cursep);
			cursep = minsep;
 		}

		if (left->right != -1) {
			cursep = cursep - (left->offset + 1) / 2;
			left = items[left->right];
		}
		else if (left->left != -1) {
			cursep = cursep + (left->offset + 1) / 2;
			left = items[left->left];
		}
		else
			break;

		if (right->left != -1 ) {
			cursep = cursep - (right->offset + 1) / 2;
			right = items[right->left];
		}
		else if (right->right != -1) {
			cursep = cursep + (right->offset + 1) / 2;
			right = items[right->right];
		}
		else
			break;
	}

	n->offset = rootsep;
}

void Tree::position()
{
	cout << "Node 0 has left " << items[0]->left << " and right " << items[0]->right << endl;
	if (items.size() == 0)
		return;
	//post order traversal
	calcpoints(items[0], 0);
	for (int x = 0; x<items.size() - 1; x++)
		cout << "NODE " << x << " has sib sep of " << items[x]->offset << " and is at level " << items[x]->yco << " with left child at " << items[x]->left << " and right child at " << items[x]->right << endl; 
}
