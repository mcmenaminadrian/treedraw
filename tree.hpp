#include <string>
#include <vector>

using namespace std;

class Node
{
	public:
		Node();
		Node(const char*);
		const string getvalue() const;
		void setvalue(char*);
		int left;
		int right;
		bool black;
		string otherdata;
		//drawing data
		int yco;
		int xco;
		int offset;
		bool thread;
	private:
		string value;
};

class Extreme
{
	public:
		Node* n;
		int offset;
		int level;
		Extreme() {n = NULL; offset = level = 0;}
};

class Tree
{
	friend ostream& operator<<(ostream& os, const Tree& t);
	friend istream& operator>>(istream& is, Tree& t);
	public:
		Tree();
		Tree(int);
		void position();
		~Tree();
		vector<Node*> items;

	private:
		void calcpoints(Node*, int, Extreme&, Extreme&);
		void fixpoints(Node*, int);
		int distance;
		void free();
};


