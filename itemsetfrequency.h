#include <fstream>
#include "list.h"

class ListInt {
	public:
		StringList *items;
		int support;
		ListInt();
		void print();
		void printInFile(std::ofstream *myfile);
};

class Itemsets {
	public:
		ListInt *itemset;
		Itemsets *next;
		Itemsets();
		Itemsets *add(ListInt *t);
		void addMultiple(Itemsets *t);
		void print();
		void printInFile(std::ofstream *myfile);
};
