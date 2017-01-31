#include "transaction.h"
#include <iostream>

Transaction::Transaction(){
	tid = 0;
	itemset = new std::list<std::string>;
	child = NULL;
}

Transaction::Transaction(int tid, std::list<std::string> *itemset) {
	this->tid = tid;
	this->itemset = itemset;
	child = NULL;
}

Transaction *Transaction::removeLast(){
	if (child == NULL)
		return NULL;
	else {
		child = child->removeLast();
	}
}


void Transaction::print(){
	
	printFirst();
	if (child!=NULL)
		child->print();
}

void Transaction::printFirst(){
	std::list<std::string>::iterator it;
	for (it = itemset->begin(); it !=itemset->end();it++){
		std::cout << *it << ",";
	}
	std::cout << "\n";
}

bool Transaction::contains(std::string i){
	std::list<std::string>::iterator it;
	for (it = itemset->begin(); it !=itemset->end();it++){
		if (*it == i)
			return true;
	}
	return false;
}

StringList *Transaction::commonItemset(StringList *f_list){
	if (f_list == NULL)
		return NULL;
	StringNode *temp = f_list->head;
	StringList *result = new StringList;
	Transaction *root = this;
	while(temp!=NULL){
		root = this;
		while (root != NULL && root->contains(temp->item)){
			root = root->child;
		}
		if (root == NULL){
			result->add(temp->item);
		}
		temp = temp->next;
	}
	return result;
}

void Transaction::removeFromAll(StringList *common){
	Transaction *temp = this;
	if (common == NULL)
		return;
	StringNode *temp2 = common->head;
	while (temp2 != NULL){
		temp = this;
		while (temp != NULL){
			temp->itemset->remove(temp2->item);
			temp = temp->child;
		}
		temp2 = temp2->next;
	}
}

Transaction *Transaction::removeEmpty(){
	Transaction *temp = this;
	Transaction *result = new Transaction;
	Transaction *ret = result;
	while (temp != NULL){
		if (!temp->itemset->empty()){
			result->tid = temp->tid;
			result->itemset = temp->itemset;
			result->child = new Transaction;
			result = result->child;
		}
		temp = temp->child;
	}
	return ret->removeLast();
}

int Transaction::count(){
	if (child==NULL)
		return 1;
	else{
		return 1 + child->count();
	}
}

