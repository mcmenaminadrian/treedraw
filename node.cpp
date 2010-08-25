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
	yco = -1;
	xco = -1;
	offset = 2;
	thread = false;
}

Node::Node(const char* str)
{
	value = string(str);
	left = -1;
	right = -1;
	black = true;
	yco = -1;
	xco = -1;
	offset = 2;
	thread = false;
}

void Node::setvalue(char* str)
{
	value = string(str);
}

const string Node::getvalue() const
{
	return value;
}

ostream& operator<<(ostream& os, const Tree& t)
{
	os << t.items.size() << endl;
	os << t.distance << endl;
	for (unsigned int l = 0; l < t.items.size(); l++)
	{
		Node* n = t.items[l];
		os << n->getvalue() << endl;
		os << n->left << endl;
		os << n->right << endl;
		os << n->black << endl;
		string name = n->otherdata;
		os << name.length() << endl;
		for (unsigned int k = 0; k < name.length(); k++)
			os << name[k]; 
		os << n->yco << endl;
		os << n->xco << endl;
		os << n->offset << endl;
		os << n->thread << endl;
	}
	return os;
}

istream& operator>>(istream& is, Tree& t)
{
	t.free();
	unsigned int k;
	is >> k;
	is >> t.distance;
	for (unsigned int i = 0; i < k; i++)
	{
		string val;
		is >> val;
		Node* n = new Node(val.c_str());
		is >> n->left;
		is >> n->right;
		is >> n->black;
		int r;
		is >> r;
		char xch;
		for (int y = 0; y < r; y++) {
			is >> xch;
			n->otherdata = n->otherdata + xch;
		}
		is >> n->yco;
		is >> n->xco;
		is >> n->offset;
		is >> n->thread;
		t.items.push_back(n);
	}
	return is;
}

Tree::Tree()
{
	distance = 2;
}

Tree::Tree(int d)
{
	distance = d;
}

void Tree::free()
{
	int i = items.size();
	while (i){
		delete items[i - 1];
		items.pop_back();
		i--;
	}
}

Tree::~Tree()
{
	free();
}

void Tree::calcpoints(Node* n, int level, Extreme& lmost, Extreme& rmost)
{
	Extreme rr, rl, lr, ll;
	int loffsum = 0;
	int roffsum = 0;
	n->yco = level;
	if (n->left != -1)
		calcpoints(items[n->left], level + 1, lr, ll);
	if (n->right != -1)
		calcpoints(items[n->right], level + 1, rr, rl);

	Node* left = NULL;
	Node* right = NULL;
	int ileft = n->left;
	if (ileft != -1)
		left = items[ileft];
	
	int iright = n->right;
	if (iright != -1)
		right = items[iright];

	if (iright == -1 && ileft == -1)
	{
		//leaf node most be most extreme
		lmost.n = n;
		lmost.offset = 0;
		lmost.level = level;
		rmost.n = n;
		rmost.offset = 0;
		rmost.level = level;
		return;
	}

	const int minsep = distance;
	int rootsep = minsep * 2;
	int cursep = rootsep;

	while (left && right) {
		if (cursep < minsep) {
			rootsep = rootsep + (minsep - cursep);
			cursep = minsep;
 		}

		if (left->right != -1) {
			loffsum = loffsum + left->offset;
			cursep = cursep - (left->offset + 1) / 2;
			ileft = left->right;
			left = items[left->right];
		}
		else
		{
			loffsum = loffsum - left->offset;
			if (left->left != -1) {
				cursep = cursep + (left->offset + 1) / 2;
				ileft = left->left;
				left = items[left->left];
			}
			else
				break;
		}

		if (right->left != -1 ) {
			roffsum = roffsum - right->offset;
			cursep = cursep - (right->offset + 1) / 2;
			iright = right->left;
			right = items[right->left];
		}
		else
		{
			roffsum = roffsum + right->offset;
			if (right->right != -1) {
				cursep = cursep + (right->offset + 1) / 2;
				iright = right->right;
				right = items[right->right];
			}
			else
				break;
		}
	}

	n->offset = rootsep;

	//update extreme descendants details
	if (rr.level > ll.level || n->left == -1)
	{
		lmost = rl;
		lmost.offset = lmost.offset + n->offset;
	}
	else {
		lmost = ll;
		lmost.offset = lmost.offset - n->offset;
	}

	if (lr.level > rr.level || n->right == -1)
	{
		rmost = lr;
		rmost.offset = rmost.offset - n->offset;
	}
	else {
		rmost = rr;
		rmost.offset = rmost.offset + n->offset;
	}

	//threading
	if (left != NULL && left != items[n->left])
	{
		rr.n->thread = true;
		rr.n->offset = abs((rr.offset + n->offset) - loffsum);
		if (loffsum - n->offset <= rr.offset)
			rr.n->left = ileft;
		else
			rr.n->right = ileft;
	}
	else if (right != NULL && right != items[n->right])
	{
		ll.n->thread = true;
		ll.n->offset = abs((ll.offset - n->offset) - roffsum);
		if (roffsum + n->offset >= ll.offset)
			ll.n->right = iright;
		else
			ll.n->left = iright;
	}
}

void Tree::fixpoints(Node* n, int x)
{
	n->xco = x;
	if (n->thread == true) {
		n->thread = false;
		n->right = -1;
		n->left = -1;
	}
	else {
		int disp = (n->offset + 1) / 2;
		if (n->left != -1)
			fixpoints(items[n->left], x - disp);
		if (n->right != -1)
			fixpoints(items[n->right], x + disp);
	}
}

void Tree::position()
{
	if (items.size() == 0)
		return;
	//post order traversal
	Extreme lhold, rhold;
	calcpoints(items[0], 0, lhold, rhold);
	//pre-order traversal
	fixpoints(items[0], 0);
}

int Tree::min(int x) const
{
	if (items[x]->left == -1)
		return items[x]->xco;
	min(items[x]->left);
}

int Tree::max(int x) const
{
	if (items[x]->right == -1)
		return items[x]->yco;
	max(items[x]->right);
}
