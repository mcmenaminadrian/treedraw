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
		int yco;
		int xco;
	private:
		string value;
};

class Tree
{
	public:
		~Tree();
		vector<Node*> items;
};
