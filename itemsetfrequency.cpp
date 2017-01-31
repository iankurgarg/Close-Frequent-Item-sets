#include <iostream>
#include "itemsetfrequency.h"

ListInt::ListInt(){
	items = new StringList;
	support = 0;
}

void ListInt::printInFile(std::ofstream *myfile){
	
//	myfile << "Writing this to a file.\n";
	
	StringNode *temp = items->head;
	while (temp != NULL){
		*myfile << temp->item << ",";
		temp = temp->next;
	}
	*myfile << " : " << support << "\n";
}

void ListInt::print(){
	
//	myfile << "Writing this to a file.\n";
	
	StringNode *temp = items->head;
	while (temp != NULL){
		std::cout << temp->item << ",";
		temp = temp->next;
	}
	std::cout << " : " << support << "\n";
}

Itemsets::Itemsets(){
	itemset = NULL;
	next = NULL;
}

Itemsets *Itemsets::add(ListInt *t){
	
	Itemsets *temp = this;
	if (itemset == NULL){
		this->itemset = new ListInt;
		itemset->items = t->items;
		itemset->support = t->support;
		return this;
	}
	else{
		//~ t->print();
		
		while (temp->next != NULL){
			temp = temp->next;
		}
		temp->next = new Itemsets;
		temp->next->itemset = t;
	}
	return this;
}

void Itemsets::addMultiple(Itemsets *t){
	if (itemset == NULL){
		itemset = t->itemset;
		next = t->next;
	}
	Itemsets *temp = this;
	
	while (temp->next != NULL){
		std::cout << "Check\n";
		temp = temp->next;
	}
	temp->next = t;
	
	//~ std::cout << "Check\n";
}

void Itemsets::print(){

	if (itemset != NULL){
		itemset->print();
	}
	if (next != NULL){
		next->print();
	}
}

void Itemsets::printInFile(std::ofstream *myfile){

	if (itemset != NULL){
		itemset->printInFile(myfile);
	}
	if (next != NULL){
		next->printInFile(myfile);
	}
}
