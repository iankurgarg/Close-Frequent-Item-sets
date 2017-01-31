#include <iostream>
#include <list>
#include <fstream>
#include <stdlib.h>
#include "transaction.h"
#include "database.h"

//using namespace std;

Transaction *parse_database1(std::string file)
{
	std::fstream myfile;
	myfile.open (file.c_str());
	Transaction *start = new Transaction;
	Transaction *travel = start;
	int tid;
	std::list<std::string> *itemset ;
	std::string line;
	while(getline(myfile,line))
	{
		itemset = new std::list<std::string>();
		int space = line.find(" ");
		tid = atoi(line.substr(0,space).c_str());
		line = line.substr(space+1);
		int comma = line.find(",");
		while(comma != -1)
		{
			std::string x = line.substr(0,comma);
			itemset->push_back(x);
			line = line.substr(comma+1);
			comma = line.find(",");
		}
		itemset->push_back(line.substr(0,line.size()-1));
		travel->tid = tid;
		travel->itemset = itemset;
		travel->child = new Transaction;
		/*list<string>::iterator it;
		cout << travel->tid;
		for(it = (travel->itemset)->begin(); it!=(travel->itemset)->end(); it++)
		{
			cout <<  " " << (*it);
		}
		cout << endl;*/
		travel = travel->child;
	}
	myfile.close();
	/*list<string>::iterator it;
		cout << start->tid;
		for(it = (start->itemset)->begin(); it!=(start->itemset)->end(); it++)
		{
			cout <<  " " << (*it);
		}
		cout << endl;*/
	start = start->removeLast();
	return start;
}

Transaction *parse_database(std::string file)
{
	std::fstream myfile;
	myfile.open (file.c_str());
	Transaction *start = new Transaction;
	Transaction *travel = start;
	int tid;
	std::list<std::string> *itemset ;
	std::string line;
	while(getline(myfile,line))
	{
		itemset = new std::list<std::string>();
		line =  line.substr(0,line.size()-1);
		//~ std::cout << line;
		int space = line.find(" ");
		//tid = atoi(line.substr(0,space).c_str());
		//line = line.substr(space+1);
		//int comma = line.find(",");
		
		
		
		while(space != -1)
		{
			std::string x = line.substr(0,space);
			itemset->push_back(x);
			line = line.substr(space+1);
			space = line.find(" ");
		}
		itemset->push_back(line);
		//~ std::cout << itemset->size() << ":" << (itemset->back() == "834")  <<"\n";
		//~ std::cout << "Last Item " << line;
		travel->tid = 0;
		travel->itemset = itemset;
		travel->child = new Transaction;
		/*list<string>::iterator it;
		cout << travel->tid;
		for(it = (travel->itemset)->begin(); it!=(travel->itemset)->end(); it++)
		{
			cout <<  " " << (*it);
		}
		cout << endl;*/
		travel = travel->child;
	}
	myfile.close();
	/*list<string>::iterator it;
		cout << start->tid;
		for(it = (start->itemset)->begin(); it!=(start->itemset)->end(); it++)
		{
			cout <<  " " << (*it);
		}
		cout << endl;*/
	start = start->removeLast();
	return start;
}

std::map<std::string,int> fill_map(Transaction *head)
{
	std::map<std::string,int> frequency_map;
	Transaction *iter = head;
	while(iter)
	{
		//cout << "enter\n" ;
		std::list<std::string>::iterator it;
		for(it = (iter->itemset)->begin(); it!=(iter->itemset)->end(); it++)
		{
			//cout << *it << "\n";
			/*if (frequency_map.find(*it) == frequency_map.end()){
				cout << "   not found"<< "\n";
				frequency_map[*it] = 1;
			}
			else{
				cout << "   found"<< "\n";
				frequency_map[*it]++;
			}*/
			frequency_map[*it]++;
		}
		/*cout << "milk  " << frequency_map["milk"] << "\n";
		cout << "butter  " << frequency_map["butter"] << "\n";
		cout << "egg  " << frequency_map["egg"] << "\n";*/
		iter = iter->child;
	}
	return frequency_map;
}

void sort_only(std::map<std::string,int> frequency_map, item item_array[])
{
	int size_map = frequency_map.size();
	//~ item item_array[size_map];
	std::list<std::string> sorted_item_list;
	std::map<std::string,int>::iterator iter;
	int i = 0;
	for(iter = frequency_map.begin(); iter != frequency_map.end(); iter++)
	{
		//cout << iter->first << "  " << iter->second <<"\n";
		item_array[i].item_name = iter->first;
		item_array[i++].frequency = iter->second;
	}
	//cout << "completed\n";
	mergesort(item_array, 0, size_map-1);
}

StringList *sort_map(std::map<std::string,int> frequency_map)
{
	int size_map = frequency_map.size();
	StringList *result = new StringList;
	item item_array[size_map];
	sort_only(frequency_map, item_array);
	
	for(int i = size_map-1; i >=0 ; i--)
		result->add(item_array[i].item_name);
	
	return result;
}

StringList *get_frequency_list(std::map<std::string,int> frequency_map, int min_sup)
{
	int size_map = frequency_map.size();
	StringList *result = new StringList;
	item item_array[size_map];
	sort_only(frequency_map, item_array);
	
	for(int i = size_map-1; i >=0 ; i--)
	{
		if (item_array[i].frequency >= min_sup)
			result->add(item_array[i].item_name);
	}
	return result;
}

void mergesort(item *item_array, int low, int high)
{
	// check if low is smaller then high, if not then the array is sorted
	if(low < high)
	{
		// Get the index of the element which is in the middle
		int middle = low + (high - low) / 2;
		// Sort the left side of the array
		mergesort(item_array, low, middle);
		// Sort the right side of the array
		mergesort(item_array, middle + 1, high);
		// Combine them both
		merge(item_array, low, middle, high);
	}
}

void merge(item* item_array, int low, int middle, int high)
{
	item helper[high+1];
	// Copy both parts into the helper array
	for (int i = low; i <= high; i++)
	{
		helper[i] = item_array[i];
	}
	int i = low;
	int j = middle + 1;
	int k = low;
	// Copy the smallest values from either the left or the right side back
	// to the original array
	while (i <= middle && j <= high)
	{
		if (helper[i].frequency <= helper[j].frequency)
		{
			item_array[k] = helper[i];
			i++;
		}
		else
		{
			item_array[k] = helper[j];
			j++;
		}
		k++;
	}
	// Copy the rest of the left side of the array into the target array
	while (i <= middle)
	{
		item_array[k] = helper[i];
		k++;
		i++;
	}
	while(j<=high)
	{
		item_array[k] = helper[j];
		k++;
		j++;
	}
}

//~ int main()
//~ {
	//~ //fill_map(parse_database("database.txt"));
	//~ StringList *a1 = sort_map(fill_map(parse_database("database.txt")));
	//~ 
	//~ a1->print();
	//~ return 0;
//~ }

