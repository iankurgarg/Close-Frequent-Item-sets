#include <iostream>
#include "FPTree.h"

ListInt *getAncestorPath(TreeNode *t);

TreeNode::TreeNode() {
	item = "";
	count = -1;
	parent = NULL;
	children = new Nodes;
	link = NULL;
}

TreeNode::TreeNode(std::string i, int c) {
	item = i;
	count = c;
	parent = NULL;
	children = new Nodes;
	link = NULL;
}

TreeNode *TreeNode::addChild (std::string i, StringList *f_list){
	if (children->head == NULL) {
		children->head = new List;
		TreeNode *insert = new TreeNode(i, 1);		
		
		TreeNode *x = findBefore(i);
		TreeNode *y = findAhead(i);
		if (x != NULL) {
			while (x->link != NULL && x->link != y){
				x = x->link;
			}
			insert->link = x->link;
			x->link = insert;
		}
		else {
			insert->link = y;
		}
		
		insert->parent = this;
		children->head->a = insert;
		
		return children->head->a;
	}
	else {
		List *temp = children->head;
		
		while (temp->next != NULL && f_list->find(temp->next->a->item) < f_list->find(i)){			
			temp = temp->next;
		}

		if (temp->a->item == i){
			temp->a->count++;
			return temp->a;
		}
		else if (f_list->find(temp->a->item) > f_list->find(i)){
			List *insert = new List;
			insert->a = new TreeNode(i, 1);
			TreeNode *x = temp->a->findBefore(i);
			TreeNode *y = temp->a->findAhead(i);
			
			if (x != NULL){
				while (x->link != NULL && x->link != y){
					x = x->link;
				}
				insert->a->link = x->link;
				x->link = insert->a;
				insert->next = temp;
				insert->a->parent = this;
				children->head = insert;
			}
			else {
				insert->a->link = y;
				insert->next = temp;
				insert->a->parent = this;
				children->head = insert;
			}
			return insert->a;
		}
		else if (temp->next != NULL && temp->next->a->item == i) {
			temp->next->a->count++;
			return temp->next->a;
		}
		else {
			List *insert = new List;
			insert->a = new TreeNode(i, 1);
			TreeNode *x = temp->a->findBefore(i);
			if (x == NULL)
				x = temp->a->find(i);
			TreeNode *y = temp->a->findAhead(i);
			
			if (x != NULL){
				while (x->link != NULL && x->link != y){
					x = x->link;
				}
				insert->a->link = x->link;
				x->link = insert->a;
				insert->next = temp->next;
				insert->a->parent = this;
				temp->next = insert;
				
			}
			else {
				insert->a->link = y;
				insert->next = temp->next;
				insert->a->parent = this;
				temp->next = insert;
			}
			return temp->next->a;
		}
	}
}


List::List() {
	a = NULL;
	next = NULL;
}


Nodes::Nodes(){
	head = NULL;
}

void Nodes::print(){
	List *temp = head;
	while (temp != NULL){
		std::cout << temp->a->item << ":" << temp->a->count << ", ";
		temp = temp->next;
	}
	std::cout << "\n";
}

TreeNode *TreeNode::find(std::string i){

	TreeNode *found = NULL;
	if (item == i){
		return this;
	}
	else if (children->head != NULL){
		
		List *temp = children->head;
		while (temp != NULL){
			if (temp->a != NULL)
				found = temp->a->find(i);
			if (found != NULL)
				return found;
			temp = temp->next;
		}
		
	}
	return NULL;
}

TreeNode *TreeNode::findInLeftSiblings(std::string i){
	
	if (parent == NULL){
		return NULL;
	}
	
	List *temp = parent->children->head;
	TreeNode *found = NULL;
	while (temp->a != this){
		found = temp->a->find(i);
			if (found != NULL)
				break;
		temp = temp->next;
	}
	
	return found;
}

TreeNode *TreeNode::findBefore(std::string i){
	TreeNode *found = findInLeftSiblings(i);	
	if (found == NULL && parent != NULL){
		found = parent->findBefore(i);
	}
	return found;
}

TreeNode *TreeNode::findInRightSiblings(std::string i){
	
	if (parent == NULL){		
		return NULL;
	}
	List *temp = parent->children->head;

	while (temp->a->item != this->item){
		temp = temp->next;
	}

	TreeNode *found = NULL;

	temp = temp->next;
	
	while (temp != NULL){
		found = temp->a->find(i);
		if (found != NULL)
			break;
		temp = temp->next;
	}
	return found;
}

TreeNode *TreeNode::findAhead(std::string i){
	TreeNode *found = findInRightSiblings(i);	
	if (found == NULL && parent != NULL){
		found = parent->findAhead(i);
	}
	return found;
}

TreeNode *TreeNode::addTransaction(StringList *transaction, StringList *f_list){
	TreeNode *x = addChild(transaction->head->item, f_list);
	StringList *rem = new StringList;
	if (transaction->head->next != NULL){
		rem->head = transaction->head->next;
		x->addTransaction(rem, f_list);
	}
	return NULL;
}

void TreeNode::print(){
	if (this->count != -1)
		std::cout << this->item << ":" << count << ", ";
	if (children == NULL)
		return;
	List *temp = children->head;
	while (temp != NULL){
		temp->a->print();
		temp = temp->next;
	}
	if (children->head == NULL)
		std::cout << '\n';
}


int TreeNode::numberContainingItem(std::string i){	
	TreeNode *x = find(i);
	int number = 0;
	while (x != NULL){
		x = x->link;
		number++;
	}
	return number;
}

void TreeNode::transactionContaining(std::string i){	
	TreeNode *x = find(i);
	int number = 0;

	while (x!=NULL){
		ListInt *temp = getAncestorPath(x);
		number++;
		x = x->link;
	}
}

ListInt *getAncestorPath(TreeNode *t){
	ListInt *itemset = new ListInt;
	itemset->support = t->count; 
	t = t->parent;
	while (t!=NULL && t->parent != NULL){
		itemset->items->addAtStart(t->item);
		t = t->parent;
	}
	return itemset;
}

void FPTree::addDatabase(Transaction *db, StringList *f_list) {
	
	while (db !=NULL) {
		root->addTransaction(toStringList(db->itemset), f_list);
		db = db->child;
	}
}

StringList *FPTree::toStringList(std::list<std::string> *x){
	StringList *l = new StringList;

	for (std::list<std::string>::iterator it=x->begin(); it != x->end(); ++it)
		l->add(*it);
	
	return l;
}

Transaction *FPTree::conditionalDatabase (std::string i){
	TreeNode *x = root->find(i);
	Transaction *db = new Transaction;
	int j = 0;
	Transaction *frdb = db;
	while (x!=NULL){
		ListInt *temp = getAncestorPath(x);
		for (j = 0; j < temp->support; j++){
			StringNode *save = temp->items->head;
			while (save != NULL){
				db->itemset->push_back(save->item);
				save = save->next;
			}
			db->child = new Transaction;
			db = db->child;
		}
		x = x->link;
	}
	
	return frdb->removeLast();
}

FPTree::FPTree(){
	root = new TreeNode;
}
