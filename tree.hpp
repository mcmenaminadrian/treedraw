#include <string>
#include <vector>

using namespace std;

class Node
{
	public:
		Node();
		Node(char*);
		const string getvalue() const;
		void setvalue(char*);
		int left;
		int right;
		bool black;
		void* otherdata;
		//drawing data
		int yco;
		int xco;
		int offset;
	private:
		string value;
};

class Tree
{
	public:
		Tree();
		Tree(int);
		void position();
		~Tree();
		vector<Node*> items;

	private:
		void calcpoints(Node*, int);
		int distance;
};
