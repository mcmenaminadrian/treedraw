#include <string>
using namespace std;

class node
{
	public:
		node();
		node(char*);
		const string getvalue() const;
		void setvalue(char*);
		node* left;
		node* right;
	private:
		string value;
};

class tree
{
	public:
		tree(){root = NULL;}
		~tree();
		const node* getroot() const;
		void addnode(node*);

	private:
		node* root;
		void free(node*);
		void insertnode(node*, node*);
};
