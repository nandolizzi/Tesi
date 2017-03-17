#include "tools.h"

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
			fprintf(fd, "nord: %lf\t est: %lf\t quota: %lf\t id: %d\t row: %ld\t col: %ld\n", iter->nord, iter->est, iter->quota, iter->id, iter->coordinate.first, iter->coordinate.second);
			fprintf(fd, "\n");
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
		map_points[iterator->coordinate].push_back(iterator->quota);
	return map_points;
};