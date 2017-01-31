#ifndef DATABASE_H
#define DATABASE_H
#include "list.h"
#include "transaction.h"
#include <string>
#include <map>

void mergesort(item *item_array, int low, int high);
void merge(item* item_array, int low, int middle, int high);
Transaction *parse_database(std::string file);
std::map<std::string,int> fill_map(Transaction *head);

void sort_only(std::map<std::string,int> frequency_map, item item_array[]);
StringList *sort_map(std::map<std::string,int> frequency_map);
StringList *get_frequency_list(std::map<std::string,int> frequency_map, int min_sup);

#endif
