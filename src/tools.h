#pragma once

#include <utility>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

#include "defs.h"

int Leggi_SinglePulse_xyz(std::list<Item>&points, DataSet *data1, int tot_ele, FILE *inputFile);
void printList(std::list<Item>&points);
void writeList(std::list<Item>&points, const char *filename);
void setItem(Item &n_it, real_ n, real_ e, real_ q, int identity, const std::pair<int, int>&c);
void buildMatriceSparsa(DataSet *data1, std::list<Item>&points, int rows, int col);
bool compare_index_then_value(Item& first, Item& second);
std::map<std::pair<int, int>, std::vector<real_>> list2map(std::list<Item>&point_list);
void write_map(std::map<std::pair<int, int>, std::vector<real_>>&my_map, const char *filename);
void fill_empty_cells(real_ *matrice_sparsa, int rows, int col);
void height_search(DataSet *data1, std::map<std::pair<int, int>, std::vector<real_>> &item_map, int rows, int col, int& max_density, unsigned char *density);
void terrain_search(DataSet *data1, std::map<std::pair<int, int>, std::vector<real_>> &item_map, int rows, int col, int& max_density, unsigned char *density);
void normal_height_search(DataSet *data1, std::map<std::pair<int, int>, std::vector<real_>> &item_map, int rows, int col, int& max_density, unsigned char *density);
