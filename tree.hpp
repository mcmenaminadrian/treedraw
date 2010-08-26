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
		int max(int) const;
		int min(int) const;
		int maxdepth(int) const;
		ostream& output_svg(ostream& os) const;

	private:
		void draw_next_line(ostream&, int, int, int, const int) const;
		void draw_next_node(ostream&, int, const int) const;
		void calcpoints(Node*, int, Extreme&, Extreme&);
		void fixpoints(Node*, int);
		int distance;
		void free();
};


