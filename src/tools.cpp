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