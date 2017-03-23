#include "tools.h"

extern Configurator laserRegioniConfig;

void printList(std::list<Item>&points)
{
	std::cout << "List:\n" << std::endl;

	/* Si verifica se la lista è vuota o meno. */
	if (!points.empty())
	{
		/* Mi muovo all'interno della lista dal primo all'ultimo membro. */
		for (std::list<Item>::const_iterator iter = points.begin(); iter != points.end(); iter++)
		{
			/* Stampo a video gli attributi dell'elemento della lista. */
			std::cout << iter->nord << " " << iter->est << " " << iter->quota << " " << iter->id << " ";
			std::cerr << iter->coordinate.first << " " << iter->coordinate.second << std::endl;
		}
	}
	else
		std::cout << "The List is empty" << std::endl;
}

void writeList(std::list<Item>&points, const char *filename)
{
	FILE *fd = fopen(filename, "w");
	// Can't open the file

	if (!points.empty())
	{
		for (std::list<Item>::const_iterator iter = points.begin(); iter != points.end(); iter++)
		{
			/* Acquisisco i valori del nodo della lista. */
			/*double nord = temp->_element.getNord();
			double est = temp->_element.getEst();
			double value = temp->_element.getValue();
			int id = temp->_element.getId();
			int row = temp->_element.getRow();
			int col = temp->_element.getCol();*/
			//fprintf(fd, "nord: %lf\t est: %lf\t quota: %lf\t id: %d\t row: %ld\t col: %ld\n", iter->nord, iter->est, iter->quota, iter->id, iter->coordinate.first, iter->coordinate.second);
			fprintf(fd, "nord: %lf\t est: %lf\t quota: %lf\t riga: %d\t colonna: %d\n", iter->nord, iter->est, iter->quota, iter->coordinate.first, iter->coordinate.second);
			//fprintf(fd, "\n");
		}
	}
	else
		std::cout << "The List is empty" << std::endl;
		fclose(fd);
	//return true;
}

void setItem(Item &n_it, float n, float e, float q, int identity, const std::pair<int, int>& c)
{
	n_it.nord = n;
	n_it.est = e;
	n_it.quota = q;
	n_it.id = identity;
	n_it.coordinate = c;
};

/* Funzione per compiere il sort. Organizza la lista in base all'indice. In caso di stesso indice
	l'ordina a valori crescenti di quota. */
bool compare_index_then_value(Item& first, Item& second)
{
	return ((first.coordinate.first < second.coordinate.first) || (first.coordinate.first == second.coordinate.first && first.coordinate.second < second.coordinate.second) || (first.coordinate.first == second.coordinate.first && first.coordinate.second == second.coordinate.second && first.quota < second.quota));
};

/* Funzione per l'immagazzinamento della lista all'interno di una mappa.
	Tale mappa avrà come chiave il pair contenente gli indici di riga e colonna della futura matrice 
	e come valore il vettore contenente tutti gli elementi copntraddistinti dallo stesso indice di riga e colonna.*/
std::map<std::pair<int, int>, std::vector<float>> list2map(std::list<Item>&point_list)
{
	std::map<std::pair<int, int>, std::vector<float>> map_points;
	for (std::list<Item>::const_iterator iterator = point_list.begin(); iterator != point_list.end(); ++iterator)
	{
		map_points[iterator->coordinate].push_back(iterator->quota);
	}
	return map_points;
};

void write_map(std::map<std::pair<int, int>, std::vector<float>>&my_map, const char *filename)
{
	FILE *fd = fopen(filename, "w");
	// Can't open the file
	if (!my_map.empty())
	{
		for (std::map<std::pair<int, int>, std::vector<float>>::const_iterator iterator = my_map.begin(); iterator != my_map.end(); ++iterator)
		{
			/*std::pair<int, int> c = std::make_pair(iterator->first, iterator->second);
			int	size = my_map[iterator->first].size();
			for (int i = 0; i < size; ++i)
			{*/
				fprintf(fd, "riga: %d\t colonna: %d\n", iterator->first, iterator->second);
			//}
		}
	}
	else
		std::cout << "The Map is empty" << std::endl;
	fclose(fd);
};


void fill_empty_cells(float *matrice_sparsa/*, int rows, int col*/)
{
	std::cout << "Costruzione della matrice completa" << std::endl;
	int vec_size = 0;
	float delta = 0.00;
	int rows = laserRegioniConfig.gridHeight;
	int col = laserRegioniConfig.gridWidth;

	for (int i = 1; i < rows-1; ++i)
	{
		for (int j = 1; j < col-1; ++j)
		{
			if (matrice_sparsa [i*col + j] == QUOTA_BUCHI)
			{
				std::vector <float> neighbors;
				for (int k = -1; k <= 1; ++k)
				{
					for (int l = -1; l <= 1; ++l)
					{
						if ( k * l == 0 && k == l )
						{
							continue;
						}
						else
						{
							if (matrice_sparsa[(i + k)*col + j + l] != QUOTA_BUCHI)
							{
								neighbors.push_back(matrice_sparsa[((i + k)*col) + j + l]);
							}
						}
					}
				}
				vec_size = neighbors.size();
				if (vec_size > 1)
				{
					std::sort(neighbors.begin(), neighbors.end());
					delta = neighbors.end() - neighbors.begin();
					/* Dato che il programma non legge un float in ingresso lo scrivo nel file config * 100,
					quindi sotto lo divido per 100 e lo casto. */
					float dislivello = (float)(laserRegioniConfig.dislivelloMatriceSparsa) / 100;
					if (delta < dislivello)
					{
						if (vec_size % 2)   matrice_sparsa[i* col + j ] = neighbors[vec_size/2.0];
						else          matrice_sparsa[i* col + j] = (neighbors[vec_size / 2] + neighbors[vec_size / 2 - 1]) / 2.0;
					}
					else
					{
						if (laserRegioniConfig.tipoRicerca == TIPORICERCA_EDIFICI)
							matrice_sparsa[i* col + j] = neighbors[vec_size / 2];
						else
							matrice_sparsa[i* col + j] = neighbors[vec_size / 2-1];
					}

				}
				neighbors.clear();
			}
		}
	}
	std::cout << "Fine!!" << std::endl;
	return;
}
