#include <string>
#include <vector>

using namespace std;

class node
{
	public:
		node();
		node(char*);
		const string getvalue() const;
		void setvalue(char*);
		int left;
		int right;
		void* otherdata;
	private:
		string value;
};

class tree
{
	public:
		~tree();
		vector<node*> items;
};
