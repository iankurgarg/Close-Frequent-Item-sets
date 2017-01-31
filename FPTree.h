#include <string>
#include "transaction.h"
#include "itemsetfrequency.h"
#include "list.h"

class TreeNode;

class List {
	public:
		TreeNode *a;
		List *next;
		List();
	
};

class Nodes {
	public:
		List *head;
		Nodes();
		void print();
};

class TreeNode {
	public:
		std::string item;
		int count;
		TreeNode *parent;
		Nodes *children;
		TreeNode *link;
		
		TreeNode();
		TreeNode(std::string i, int c);
		
		TreeNode *find(std::string i);
		TreeNode *addChild (std::string item, StringList *f_list);
		TreeNode *addTransaction(StringList *transaction, StringList *f_list);
		void print();
		int numberContainingItem(std::string i);
		void transactionContaining(std::string i);
		
	private:
		TreeNode *findInLeftSiblings(std::string i);
		TreeNode *findInRightSiblings(std::string i);
		TreeNode *findAhead(std::string i);
		TreeNode *findBefore(std::string i);
};

class FPTree {
	public:
		TreeNode *root;
		void addDatabase(Transaction *db, StringList *f_list);
		Transaction *conditionalDatabase(std::string i);
		FPTree();
		
	private:
		StringList *toStringList(std::list<std::string> *x);
};
