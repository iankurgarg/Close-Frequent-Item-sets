#ifndef LIST_H
#define LIST_H

#include <string>

class StringNode {
	public:
		std::string item;
		StringNode *next;
		StringNode();
};

class StringList {
	public:
		StringNode *head;
		int find(std::string i);
		void add(std::string i);
		void addAtStart(std::string i);
		void removefirst();
		void print();
		int count();
		StringList *unionWith(StringList *Y);
		bool isSubsetOf(StringList *Y);
		StringList();
		StringList *reverse();
};

#endif
