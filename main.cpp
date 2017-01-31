#include <iostream>
#include <stdlib.h>
#include "FPTree.h"
#include "database.h"

void findClosedFrequentItemsets(ListInt *X, Transaction *DB, StringList *f_list_complete, StringList *f_list, Itemsets *FCI, int min_sup);
bool check_fci (Itemsets *FCI, ListInt *new_fci, int min_sup);

void sort(Transaction *trans, StringList *f_list){
	if (trans == NULL)
		return;
	StringNode *temp = f_list->head;
	std::list<std::string> *new_itemset = new std::list<std::string>;
	while (temp!=NULL){
		
		if (trans->contains(temp->item))
			new_itemset->push_back(temp->item);
		temp = temp->next;
	}
	
	trans->itemset = new_itemset;
	
	if (trans->child != NULL){
		sort(trans->child, f_list);
	}
}


int main(int argc, char **argv){

	Transaction *db = parse_database(argv[1]);
	std::cout <<  "Database Parsed\n";
	StringList *f_list = sort_map(fill_map(db));
	std::cout <<  "Map  Filled\n";
	StringList *f_list_freq = get_frequency_list(fill_map(db), 2);
	std::cout <<  "Get Frequency List Done\n";
	sort(db, f_list);
	std::cout <<  "Database Sorted\n";
	FPTree *fptree = new FPTree;
	fptree->addDatabase(db, f_list);
	std::cout << "Number of Items: " << f_list->count() << "\n";
	std::cout <<  "FP Tree Made\n";
	//~ fptree->root = tn;
//	fptree->root->print();
//	std::cout << "\n\n";
	Transaction *t = fptree->conditionalDatabase("d");
	
	//~ std::cout << t->count();
	//~ std::cout << db->count();
	//~ t->print();
	
	StringList *x = sort_map(fill_map(t));
	
	//~ x->print();
	//~ FPTree *nfpt = new FPTree;
	//~ sort(t, x);
	//~ nfpt->addDatabase(t, x);
	//~ nfpt->root->print();
	//~ t = nfpt->conditionalDatabase("a");
	//~ t = nfpt->conditionalDatabase("c");
	
	//~ TreeNode *tempf = nfpt->root->find("f");
	//~ t = nfpt->conditionalDatabase("f");
	//~ t->print();
	//~ std::cout << "\n\n\n\n";
	//~ StringList *common = t->commonItemset(f_list);
//	common->print();
	//~ t->removeFromAll(common);
	//~ t = t->removeEmpty();
//	t->print();
	
	//~ StringList *test = new StringList;
	//~ test->add("a");
	Itemsets *FCI = new Itemsets;

	findClosedFrequentItemsets(new ListInt, db, f_list, f_list_freq, FCI, atoi (argv[2]));
	
	std::cout << "Closed Frequent Itemsets Mined\n";
	std::ofstream *myfile = new std::ofstream;
	myfile->open ("output.txt");
	FCI->printInFile(myfile);
	myfile->close();
	//~ std::cout << (FCI->itemset == NULL);
	//~ tn->print();
}

void findClosedFrequentItemsets(ListInt *X, Transaction *DB, StringList *f_list_complete, StringList *f_list, Itemsets *FCI, int min_sup){
	
	StringList *Y = DB->commonItemset(f_list);
//	DB->removeFromAll(Y);
//	DB = DB->removeEmpty();
	
	ListInt *Z = new ListInt;
	Z->items = Y->unionWith(X->items);
	if (DB != NULL)
		Z->support = DB->count();
	else
		Z->support = 0;
	
	if (check_fci(FCI, Z, min_sup)){
		//~ std::cout << "CFI -> ";Z->print();
		FCI->add(Z);
	}
	
	if (check_fci(FCI, X, min_sup)){	
		FCI->add(X);
	}
	
	FPTree *fptree = new FPTree;
	
	fptree->addDatabase(DB, f_list_complete);
	
	StringList *reverse_f_list = f_list->reverse();
	StringNode *temp = reverse_f_list->head;

	while (temp != NULL){		
		//~ std::cout << "--" << temp->item << " X: ";
		//~ X->items->print();
		Transaction *condDB = fptree->conditionalDatabase(temp->item);
		ListInt *iX = new ListInt;
		StringList *union_temp = new StringList;
		union_temp->add(temp->item);
		iX->items = X->items->unionWith(union_temp);
		iX->support = (condDB == NULL) ? 0 : condDB->count();
		condDB = condDB->removeEmpty();
		//~ iX->print();
		if (check_fci(FCI, iX, min_sup)){
			//~ iX->print();
			StringList *f_list_i = sort_map(fill_map(condDB));
			StringList *f_list_i_freq = get_frequency_list(fill_map(condDB), min_sup);
			sort(condDB, f_list_i);
			//~ Itemsets *iFCI = 
			findClosedFrequentItemsets(iX, condDB, f_list_i, f_list_i_freq, FCI, min_sup);
//			FCI->addMultiple(iFCI);
//			FCI->print();
		}
		temp = temp->next;
		
	}
	//~ std::cout << "check end\n";
	//~ return FCI;
}


bool check_fci (Itemsets *FCI, ListInt *new_fci, int min_sup){
	Itemsets *temp = FCI;
	if (new_fci == NULL || new_fci->support == 0 || new_fci->items == NULL || new_fci->items->head == NULL || new_fci->support < min_sup)
		return false;
	//~ std::cout << "check_fci:";
	//~ new_fci->print();
	//~ if (FCI->itemset != NULL){
		//~ temp->itemset->print();
	//~ }
	
	while (temp != NULL && temp->itemset != NULL){
		if ( new_fci->items->isSubsetOf(temp->itemset->items) && new_fci->support <= temp->itemset->support){
			//~ std::cout << "here\n";
			break;
		}
		temp = temp->next;
	}
	
	if (temp == NULL || temp->itemset == NULL){
		//~ std::cout << "here\n";
		return true;
	}
	else{
		//~ std::cout << "False\n";
		return false;
	}
}
