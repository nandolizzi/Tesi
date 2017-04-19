#include "tools.h"
#include "output_tools.h"

#include <Core>

extern Configurator laserRegioniConfig;

int  Leggi_SinglePulse_xyz(std::list<Item>&points, DataSet *data, int tot_ele, FILE *inputFile)
{
	int			punti_selezionati = 0, x = 0, y = 0;
	double			t1, t2, t3;
	double			tempXminTot, tempXmaxTot, tempYminTot, tempYmaxTot, tempZmin, tempZmax;
	double 			tempX, tempY, tempZ;
	int	j;
	int puntiButtati = 0;
	char point[1000];
	int colonne = 0;
	int punti = 0;

	tempXminTot = 1000000000;
	tempYminTot = 1000000000;
	tempXmaxTot = -1000;
	tempYmaxTot = -1000;
	tempZmin = 1000000000;
	tempZmax = -1000;

	fgets(point, 1000, inputFile);  //butto la prima riga


	/* tot_ele contava il numero di righe del file di dati => lo moltiplico per il numero di colonne del file*/

	for (j = 0; j < tot_ele * 3; j = j + 3)
	{
		colonne = VerificaPunto(point, inputFile);
		if (colonne == 3)
		{
			punti++;
			sscanf_s(point, "%lf %lf %lf", &t1, &t2, &t3);
			tempX = t1;    //  i_array[j]=coordinata Est=x
			tempY = t2;   //  i_array[j+1]=coordinata Nord=y
			tempZ = t3;	//  i_array[j+2]=coordinata z

			if (laserRegioniConfig.showAdditionalInfos)
			{
				tempXminTot = (tempX > tempXminTot ? tempXminTot : tempX);
				tempXmaxTot = (tempX < tempXmaxTot ? tempXmaxTot : tempX);
				tempYminTot = (tempY > tempYminTot ? tempYminTot : tempY);
				tempYmaxTot = (tempY < tempYmaxTot ? tempYmaxTot : tempY);
			}

			tempZmin = (tempZ > tempZmin ? tempZmin : tempZ);
			tempZmax = (tempZ < tempZmax ? tempZmax : tempZ);

			if (tempX >= data->LoLeftX  && tempX < data->UpRightX && tempY >= data->LoLeftY && tempY < data->UpRightY)
			{
				Item new_item;
				//si scaricano tutti i punti all'elemento di griglia minore
				x = (tempX - data->LoLeftX) / data->pelsX;
				y = (tempY - data->LoLeftY) / data->pelsX;

				/* Estrapolo i valori di riga e colonna della futura matrice grigliata */
				int col = x;
				int row = data->heightGrid - y - 1;


				/* Salvo i valori appena letti in una struct Item e li metto all'interno della lista.
				Faccio corrispondere id a punti selezionati, tale variabile aumenta di iterazione in iterazione. */
				setItem(new_item, tempX, tempY, tempZ, punti_selezionati, std::make_pair(row, col));
				points.push_back(new_item);
				punti_selezionati++;
			}
			else
				puntiButtati++;
		}
	}
	std::cout << "\n\tPunti raw totali: " << punti << "\n\tPunti buttati : " << puntiButtati << std::endl;
	//writeList(points, "prova_XY.txt");

	data->numPoints = punti_selezionati;
	if (laserRegioniConfig.showAdditionalInfos)
	{
		data->xminInput = (real_)tempXminTot;
		data->xmaxInput = (real_)tempXmaxTot;
		data->yminInput = (real_)tempYminTot;
		data->ymaxInput = (real_)tempYmaxTot;
	}
	data->zmin = (real_)tempZmin;
	data->zmax = (real_)tempZmax;

	return punti;
};

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

void write_list_cloud(std::list<Item>&points, const char *filename)
{
	FILE *fd = fopen(filename, "w");
	// Can't open the file

	if (!points.empty())
	{
		for (std::list<Item>::const_iterator iter = points.begin(); iter != points.end(); iter++)
		{
			fprintf(fd, "%lf %lf %lf\n", iter->nord, iter->est, iter->quota);
		}
	}
	else
		std::cout << "The List is empty" << std::endl;
	fclose(fd);
	//return true;
};

void setItem(Item &n_it, real_ n, real_ e, real_ q, int identity, const std::pair<int, int>& c)
{
	n_it.nord = n;
	n_it.est = e;
	n_it.quota = q;
	n_it.id = identity;
	n_it.coordinate = c;
};

void buildMatriceSparsa(DataSet *data1, std::list<Item>& points, std::list<Item>& filt_points, int rows, int col)
{
	const char			*FName = "buildMatriceSparsa";
	long int emptyCells = 0, m;
	unsigned char *density = new unsigned char[data1->widthGrid*data1->heightGrid];
	for (size_t i = 0; i < (data1->widthGrid*data1->heightGrid); i++)
	{
		density[i] = 0;
	}
	real_	delta;
	int MaxD = 0;			//Densità massima
	int counter = 0;
	FILE *out_file;
	const char* file_palette_name_char = NULL;

	std::cout << "nome file palette: " << laserRegioniConfig.paletteFileName << std::endl;

	points.sort(compare_index_then_value);
	//writeList(points, "prova_sort.txt");

	/* Dichiaro una mappa con un pair (di coordinate), come chiave ed il valore della quota. */
	std::map<std::pair<int, int>, std::vector<real_>> item_map;
	/* Immetto la lista nella mappa. */
	item_map = list2map(points);
	//write_map(item_map, "prova_map.txt");

	//FILE *fd = fopen("prova_output.txt", "w");
	int tot_celle = rows*col;

	std::cout << "\ndislivelloMatriceSparsa: " << laserRegioniConfig.dislivelloMatriceSparsa << std::endl;
	std::cout << "altezza da terreno: " << laserRegioniConfig.altezzaDaTerreno << std::endl;
	if (laserRegioniConfig.tipoRicerca == TIPORICERCA_EDIFICI)
	{
		height_search(data1, item_map, rows, col, MaxD, density);
	}
	else if (laserRegioniConfig.tipoRicerca == TIPORICERCA_DTM)
	{
		terrain_search(data1, item_map, rows, col, MaxD, density);
	}
	else if (laserRegioniConfig.tipoRicerca == TIPORICERCA_ALT_TERRENO)
	{	
		//int pippo = 0;
		real_ *z_temp = new real_[tot_celle];

		terrain_search(data1, item_map, rows, col, MaxD, density);
		for (size_t i = 0; i < (data1->widthGrid*data1->heightGrid); i++)
		{
			z_temp[i] = data1->z[i];
		}

		height_search(data1, item_map, rows, col, MaxD, density);
		
		for (size_t i = 0; i < (data1->widthGrid*data1->heightGrid); ++i)
		{
			data1->z[i] = data1->z[i] - z_temp[i];
			if (data1->z[i] < laserRegioniConfig.altezzaDaTerreno)
			{
				data1->z[i] = 0;
			}
			/*else
				pippo++;*/
		}
		
		std::cout << "fatto build matrice sparsa... Maximum density: " << MaxD << " tot celle diverse da zero: " /*<< pippo*/ << std::endl;

		delete z_temp;
	}
	std::cout << "fatto build matrice sparsa... Maximum density: " << MaxD << std::endl;
	//fprintf(fd, "celle totali: %d\ncelle vuote: %d\ncelle piene: %d\n", tot_celle, emptyCells, (tot_celle - emptyCells));
	
	if (laserRegioniConfig.tipoUscita >= LEVEL_3)
	{
		/*Creo il nome del file di output*/
		std::string file_out_name = makeExtension(laserRegioniConfig.projectName, DENSITAPNT_EXT);
		const char *file_out_name_char = file_out_name.c_str();

		if (fopen_s(&out_file, file_out_name_char, "wb") != NULL)
			errore(FILE_OPENWRITE_ERROR, (char*)file_out_name_char, FName, TRUE);

		if (laserRegioniConfig.paletteFileName != NULL)
		{
			std::string file_palette_name = makeExtension(laserRegioniConfig.paletteFileName, DENSITAPNT_ACT);
			file_palette_name_char = file_palette_name.c_str();
		}
		HeaderWrPalette(out_file, col, rows, (char*)file_palette_name_char);
		InvertiRaw2Bmp(density, rows, col, 1078, out_file);
		fclose(out_file);
	}

	write_elaborated_points(points, filt_points, data1, rows, col);

	delete density;
	//fclose(fd);
	
	return;
};

/* Funzione per cercare le altezze totali. */
void height_search(DataSet *data1, std::map<std::pair<int, int>, std::vector<real_>> &item_map, int rows, int col, int& max_density, unsigned char *density)
{
	long int empty_cells = 0, m;
	for (int i = 0; i < rows; ++i)   //scorre le righe
	{
		m = i *col;
		for (int j = 0; j < col; ++j)  //scorro le colonne	
		{
			/* Se non viene trovato alcun elemento nella cella della mappa allora la si setta nulla. */
			if (item_map.count(std::make_pair(i, j)) < 1/*item_map.find(std::make_pair(i, j)) == item_map.end()*/)
			{
				empty_cells++;
				data1->z[m + j] = QUOTA_BUCHI;
			}
			else
			{
				/* Altrimenti valuto immediatamente la lunghezza del vettore di indice (pair) ij */
				int vec_size = item_map[std::make_pair(i, j)].size();
				/* Se la dimensione del vettore è pari a 1 allora il valore
				appena letto viene passato al vettore z. */
				if (vec_size == 1)
				{
					data1->z[m + j] = item_map[std::make_pair(i, j)].back();
				}
				else
				{
					/* Altrimenti si valuta la differenza tra i due elementi con valore maggiore e valore minore. */
					real_ delta = item_map[std::make_pair(i, j)].back() - item_map[std::make_pair(i, j)].front();
					/* confronto il valore delta con il dislivello matrice sparsa settato con il file config*/
					real_ dislivello = (real_)laserRegioniConfig.dislivelloMatriceSparsa;
					/* Valuto il valore di delta rispetto al dislivello inserito nel file config. */
					if (delta > dislivello)
					{
						/* Se il delta è maggiore del dislivello allora  prendo l'ultimo elemento del vettore. */
						data1->z[m + j] = item_map[std::make_pair(i, j)].back();
					}
					else
					{
						if (vec_size % 2)
						{
							/* Altrimenti, se il vettore contiene un numero pari di elelenti, prendo l'elemento che si trova al centro.*/
							data1->z[m + j] = item_map[std::make_pair(i, j)].at((vec_size - 1) / 2);
						}
						else
						{
							/* Se invece il numero di elelemti è dispari, faccio la somma dell'elemento precedente a quello che si trova
							a metà del vettore e dell'elemento che si trova proprio a metà del vettore diviso per due. */
							data1->z[m + j] = (item_map[std::make_pair(i, j)].at((vec_size - 1) / 2) + item_map[std::make_pair(i, j)].at((vec_size - 1) / 2 + 1)) / 2;
						}
					}
				}
				/* Per adesso ho aggiunto questo pezzo ma devo chiedere alla professoressa. */
				max_density = vec_size > max_density ? vec_size : max_density;
				if (vec_size > 255) vec_size = 255;
				*(density + m + j) = (unsigned char)vec_size;
			}
		}
	}
	std::cout << "fatto build matrice sparsa... Maximum density: " << max_density << std::endl;
};

/* Funzione per la ricerca del terreno. */
void terrain_search(DataSet *data1, std::map<std::pair<int, int>, std::vector<real_>> &item_map, int rows, int col, int& max_density, unsigned char *density)
{
	long int empty_cells = 0, m;
	for (int i = 0; i < rows; ++i)   //scorre le righe
	{
		m = i *col;
		for (int j = 0; j < col; ++j)  //scorro le colonne	
		{
			/* Se non viene trovato alcun elemento nella cella della mappa allora la si setta nulla. */
			if (item_map.count(std::make_pair(i, j)) < 1)
			{
				empty_cells++;
				data1->z[m + j] = QUOTA_BUCHI;
			}
			else
			{
				/* Altrimenti valuto immediatamente la lunghezza del vettore di indice (pair) ij */
				int vec_size = item_map[std::make_pair(i, j)].size();
				/* Se la dimensione del vettore è pari a 1 allora il valore
				appena letto viene passato al vettore z. */
				if (vec_size == 1)
				{
					data1->z[m + j] = item_map[std::make_pair(i, j)].front();
				}
				else
				{
					/* Altrimenti si valuta la differenza tra i due elementi con valore maggiore e valore minore. */
					real_ delta = item_map[std::make_pair(i, j)].back() - item_map[std::make_pair(i, j)].front();
					/* confronto il valore delta con il dislivello matrice sparsa settato con il file config*/
					real_ dislivello = (real_)laserRegioniConfig.dislivelloMatriceSparsa;
					/* Valuto il valore di delta rispetto al dislivello inserito nel file config. */
					if (delta > dislivello)
					{
						/* Se il delta è maggiore del dislivello allora  prendo l'ultimo elemento del vettore. */
						data1->z[m + j] = item_map[std::make_pair(i, j)].front();
					}
					else
					{
						if (vec_size % 2)
						{
							/* Altrimenti, se il vettore contiene un numero pari di elelenti, prendo l'elemento che si trova al centro.*/
							data1->z[m + j] = item_map[std::make_pair(i, j)].at((vec_size - 1) / 2);
						}
						else
						{
							/* Se invece il numero di elelemti è dispari, faccio la somma dell'elemento precedente a quello che si trova
							a metà del vettore e dell'elemento che si trova proprio a metà del vettore diviso per due. */
							data1->z[m + j] = (item_map[std::make_pair(i, j)].at((vec_size - 1) / 2) + item_map[std::make_pair(i, j)].at((vec_size - 1) / 2 + 1)) / 2;
						}
					}
				}
				/* Per adesso ho aggiunto questo pezzo ma devo chiedere alla professoressa. */
				max_density = vec_size > max_density ? vec_size : max_density;
				if (vec_size > 255) vec_size = 255;
				*(density + m + j) = (unsigned char)vec_size;
			}
		}
	}
	std::cout << "fatto build matrice sparsa... Maximum density: " << max_density << std::endl;
};


/* Funzione per compiere il sort. Organizza la lista in base all'indice. In caso di stesso indice
	l'ordina a valori crescenti di quota. */
bool compare_index_then_value(Item& first, Item& second)
{
	return ((first.coordinate.first < second.coordinate.first) || (first.coordinate.first == second.coordinate.first && first.coordinate.second < second.coordinate.second) || (first.coordinate.first == second.coordinate.first && first.coordinate.second == second.coordinate.second && first.quota < second.quota));
};

/* Funzione per il find in base agli indici di riga e di colonna.

	Copio i valori di quota e coordinate dell'eventuale elemento trovato e lo cancello dalla lista.
	In uscita restituirò l'elemento copia nel caso in cui lo si è trovato, altrimenti l'elemento con il valore di quota
	fissato a -1. */
Item Find(std::pair<int, int> coord, std::list <Item>& my_list)
{
	Item point;
	//point.quota = NOT_FOUND;

	if (!my_list.empty())
	{
		//std::cout << "la lista temp non risulta vuota" << std::endl;
		for (std::list<Item>::const_iterator iter = my_list.begin(); iter != my_list.end(); ++iter)
		{
			if (coord.first == iter->coordinate.first && coord.second == iter->coordinate.second /*&& iter->quota != NOT_FOUND*/)
			{
				//std::cout << "trovo l'elemento: "<< iter->coordinate.first << " " << iter->coordinate.second <<" id: "<< iter->id << std::endl;
				point.coordinate = iter->coordinate;
				point.est = iter->est;
				point.nord = iter->nord;
				point.quota = iter->quota;
				point.id = iter->id;

				my_list.erase(iter);
				//for (std::list<Item>::const_iterator it = my_list.begin(); it < fine; ++ it)
				//{
				//	my_list.erase(it);
				//}

				return point;
			}
		}
		point.quota = NOT_FOUND;
		return point;
	}
	else
	{
		std::cout << "la lista temp è vuota" << std::endl;
	}
	
};


/* Funzione per l'immagazzinamento della lista all'interno di una mappa.
	Tale mappa avrà come chiave il pair contenente gli indici di riga e colonna della futura matrice 
	e come valore il vettore contenente tutti gli elementi copntraddistinti dallo stesso indice di riga e colonna.*/
std::map<std::pair<int, int>, std::vector<real_>> list2map(std::list<Item>&point_list)
{
	std::map<std::pair<int, int>, std::vector<real_>> map_points;
	for (std::list<Item>::const_iterator iterator = point_list.begin(); iterator != point_list.end(); ++iterator)
	{
		map_points[iterator->coordinate].push_back(iterator->quota);
	}
	return map_points;
};

void write_map(std::map<std::pair<int, int>, std::vector<real_>>&my_map, const char *filename)
{
	FILE *fd = fopen(filename, "w");
	// Can't open the file
	if (!my_map.empty())
	{
		for (std::map<std::pair<int, int>, std::vector<real_>>::const_iterator iterator = my_map.begin(); iterator != my_map.end(); ++iterator)
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

void fill_empty_cells(real_ *matrice_sparsa, int rows, int col)
{
	std::cout << "Costruzione della matrice completa" << std::endl;
	int vec_size = 0;
	real_ delta = 0.00;
	//int rows = laserRegioniConfig.gridHeight;
	//int col = laserRegioniConfig.gridWidth;

	typedef Eigen:: Matrix <real_, Eigen::Dynamic, Eigen::Dynamic > MatrixXr;
	MatrixXr temp(rows, col);

	for (int i = 0; i < rows*col; ++i)
	{
		temp(i)= matrice_sparsa[i];
	}

	for (int i = 1; i < rows-1; ++i)
	{
		for (int j = 1; j < col-1; ++j)
		{
			if (matrice_sparsa [i*col + j] == QUOTA_BUCHI)
			{
				std::vector <real_> neighbors;
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
					real_ dislivello = (real_)(laserRegioniConfig.dislivelloMatriceSparsa) / 100;
					if (delta < dislivello)
					{
						/*if (vec_size % 2)   matrice_sparsa[i* col + j ] = neighbors[vec_size/2.0];
						else          matrice_sparsa[i* col + j] = (neighbors[vec_size / 2] + neighbors[vec_size / 2 - 1]) / 2.0;*/
						if (vec_size % 2)   temp(i* col + j) = neighbors[vec_size / 2.0];
						else          temp(i* col + j) = (neighbors[vec_size / 2] + neighbors[vec_size / 2 - 1]) / 2.0;
					}
					else
					{
						if (laserRegioniConfig.tipoRicerca == TIPORICERCA_EDIFICI)
							temp(i* col + j) = neighbors[vec_size / 2];
						else
							temp(i* col + j) = neighbors[vec_size / 2-1];
					}

				}
				neighbors.clear();
			}
		}
	}
	
	for (int i = 0; i < rows*col ; ++i)
	{
		matrice_sparsa[i] = temp(i);
	}
	std::cout << "Fine!!" << std::endl;
	return;
}

void write_elaborated_points(std::list <Item> starting_point, std::list<Item> new_list, DataSet *data1, int rows, int col)
{
	Item point;
	setItem(point,0 , 0 , 0 , 0, std::make_pair(0, 0));
	
	std::list<Item> temp;
	temp = starting_point;
	std::list<Item>::const_iterator iter = temp.begin();

	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < col; ++j)
		{
			//std::cout << "no problema!" << std::endl;
			if (data1->z[i*col + j] != 0)
			{
				//std::cout << "i: " << i << " j: " << j << std::endl;
				while (point.quota != NOT_FOUND)
				{
					point = Find(std::make_pair(i, j), temp);
					if (point.quota != NOT_FOUND)
						new_list.push_back(point);
				}
				//std::cout << "PROBLEMA_ANCORA_MAGGIORE: "<< i << " " << j << std::endl;
				point.quota = 0;
				//std::cout << "PROBLEMA_MAGGIORE: "<< i << " " << j  << std::endl;
				//continue;
				//std::cout << "PROBLEMA" << std::endl;
			}
		}
	}
	write_list_cloud(new_list, "prova_nuvola_punti_1.txt");
	return;
};