#include <iostream>
#include "list.h"

StringNode::StringNode(){
	item = "";
	next = NULL;
}

int StringList::find (std::string i){
	int j = 0;
	StringNode *temp = head;
	while (temp != NULL && temp->item != i){
		j++;
		temp = temp->next;
	}
	if (temp == NULL)
		return -1;
	return j;
}

StringList::StringList() {
	head = NULL;
}

int StringList::count(){
	StringNode *temp = head;
	int x = 0;
	while(temp != NULL){
		x++;
		temp = temp->next;
	}
	return x;
}

StringList *StringList::reverse(){
	StringList *ret = new StringList;
	StringNode *temp = head;
	while (temp!= NULL){
		ret->addAtStart(temp->item);
		temp = temp->next;
	}
	return ret;
}

void StringList::add(std::string i) {
	StringNode *insert = new StringNode;
	insert->item = i;
	StringNode *temp = head;
	if (head == NULL){
		head = insert;
	}
	else{
		while (temp->next != NULL){
			temp = temp->next;
		}
		temp->next = insert;
	}
}

void StringList::addAtStart(std::string i){
	StringNode *insert = new StringNode;
	insert->item = i;
	StringNode *temp = head;
	if (head == NULL){
		head = insert;
	}
	else{
		insert->next = head;
		head = insert;
	}
}

void StringList::removefirst(){
	if (head!=NULL)
		head = head->next;
}

void StringList::print(){
	StringNode *temp = head;
	while (temp != NULL){
		std::cout << temp->item << ",";
		temp = temp->next;
	}
	std::cout << "\n";
}

StringList *StringList::unionWith(StringList *Y){
	StringList *result = new StringList;
	
	StringNode *temp1 = this->head;
	while (temp1 != NULL){
		result->add(temp1->item);
		temp1 = temp1->next;
	}
	
	temp1 = NULL;
	
	if (Y !=NULL)
		temp1 = Y->head;
	
	while (temp1 != NULL){
		result->add(temp1->item);
		temp1 = temp1->next;
	}
	
	return result;
}

bool StringList::isSubsetOf(StringList *Y){
	if (Y == NULL)
		return false;
		
	StringNode *temp1 = this->head;
	while (temp1 != NULL){
		if ( Y->find(temp1->item) == -1)
			break;
		temp1 = temp1->next;
	}
	if (temp1 == NULL)
		return true;
	
	return false;
}
