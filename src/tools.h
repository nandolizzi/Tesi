#pragma once

#include <utility>
#include <vector>
#include <algorithm>

#include "defs.h"

void printList(std::list<Item>&points);
void writeList(std::list<Item>&points, const char *filename);
void setItem(Item &n_it, float n, float e, float q, int identity, const std::pair<int, int>&c);
bool compare_index_then_value(Item& first, Item& second);
std::map<std::pair<int, int>, std::vector<float>> list2map(std::list<Item>&point_list);
void write_map(std::map<std::pair<int, int>, std::vector<float>>&my_map, const char *filename);
void fill_empty_cells(float *matrice_sparsa/*, int rows, int col*/);