#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <list>
#include <string>
#include "list.h"

class Transaction
{
public:
	int tid;
	std::list<std::string> *itemset;
	Transaction *child;

	Transaction();
	Transaction(int tid, std::list<std::string> *itemset);
	Transaction *removeLast();
	bool contains(std::string i);
	StringList *commonItemset(StringList *f_list);
	void removeFromAll(StringList *common);
	Transaction *removeEmpty();
	void print ();
	void printFirst();
	int count();
};

class item
{
	public:
		int frequency;
		std::string item_name;
};

#endif
