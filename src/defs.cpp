#include <iostream>
#include <string>
#include <Core>
#include <vector>

#include "defs.h"
#include "const.h"
#include "tools.h"
#include "output_tools.h"

using namespace Eigen;
using namespace std;

#define tempMin 1000000000
#define tempMax -1000

extern Configurator laserRegioniConfig;

int Config2Data(DataSet *data1)
{
	if (strstr(laserRegioniConfig.projectName, ".prj") == NULL)
		strcat_s(laserRegioniConfig.projectName, strlen(".prj") + 1, ".prj");

	data1->UpLeftCGrid = 0;									//laserRegioniConfig.upLeftC;
	data1->UpLeftRGrid = 0;									//laserRegioniConfig.upLeftR;
	data1->LoRightCGrid = laserRegioniConfig.gridWidth;			//laserRegioniConfig.lowRightC;
	data1->LoRightRGrid = laserRegioniConfig.gridHeight;		//laserRegioniConfig.lowRightR;

	data1->widthGrid = laserRegioniConfig.gridWidth;
	data1->heightGrid = laserRegioniConfig.gridHeight;
	data1->pelsX /*= data1->pelsY */ = laserRegioniConfig.gridUnit;  // Usa due diverse variabili per x e y ma se sono le stesse potrei unificarle

	data1->LoLeftX = laserRegioniConfig.loLeftX;
	data1->LoLeftY = laserRegioniConfig.loLeftY;
	data1->UpRightX = data1->LoLeftX + (double)(data1->pelsX * data1->widthGrid);
	data1->UpRightY = data1->LoLeftY + (double)(data1->pelsX * data1->heightGrid);

	data1->z = new float[data1->widthGrid*data1->heightGrid];

	return SUCCESS;

}

void printData(DataSet *data1)
{
	std::cout << "Per ora niente" << std::endl;
	std::cout << "cont= " << data1->cont << " dz= " << data1->dz << std::endl;
	std::cout << "widthGrid= " << data1->widthGrid << " heightGrid= " << data1->heightGrid << std::endl;
	std::cout << "numPoints= " << data1->numPoints << std::endl;
	std::cout << "Xg= " << data1->Xg << " Yg= " << data1->Yg << std::endl;
	std::cout << "xminInput= " << data1->xminInput << " xmaxInput= " << data1->xmaxInput << " yminInput= " << data1->yminInput << " ymaxInput= " << data1->ymaxInput << std::endl;
	std::cout << "zmin= " << data1->zmin << " zmax= " << data1->zmax /*<< " Imax= " << data1->Imax << " Imin= " << data1->Imin */ << std::endl;
	std::cout << "pelsX= " << data1->pelsX/* << " pelsY= " << data1->pelsY*/ << std::endl;
	std::cout << "LoLeftX= " << data1->LoLeftX << " LoLeftY= " << data1->LoLeftY << " UpRightX= " << data1->UpRightX << " UpRightY= " << data1->UpRightY << std::endl;
	std::cout << "UpLeftRGrid= " << data1->UpLeftRGrid << " UpLeftCGrid= " << data1->UpLeftCGrid << " LoRightRGrid= " << data1->LoRightRGrid << " LoRightCGrid= " << data1->LoRightCGrid << std::endl;
};

/* Funzione che conta il numero di punti contenuti nel file dati di tipo .txt */
long int fileRows(FILE *inputFile)
{
	char trash[1000];
	long int punti = 0;

	while (fgets(trash, 1000, inputFile))
		punti++;

	return punti;
}

/*------------------------------------------------------------------------------------*\
	Nome routine:
	selezionaCaso

	Funzione che contando le sottostringhe di una riga del file dati riconosce se
	questo contiene dai inerenti a First Last o a un solo raggio.

	restituisce :	1 se caso solo un raggio
	2 se caso con First e Last.
	\*------------------------------------------------------------------------------------*/
int selezionaCaso(FILE *InFile)
{
	char str[250], PrecCar = '*';
	unsigned int numero_sottostr = 0, i = 0;

	fgets(str, 1000, InFile);//scarto la prima stringa 
	fgets(str, 1000, InFile);//Prendo una stringa intera

	for (i = 0; i < strlen(str); i++)
	{
		if ((str[i] == ' ' && PrecCar != ' ' && PrecCar != ',' && PrecCar != '*' && PrecCar != 9) ||
			(str[i] == ',' && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*' && PrecCar != 9) ||
			(str[i] == 9 && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*'  && PrecCar != ',' && PrecCar != 9) ||
			(str[i] == 10 && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*'  && PrecCar != ',' && PrecCar != 9))//separatori spazio o virgola
			numero_sottostr++;//Calcolo le sottostringhe
		PrecCar = str[i];
	}

	fseek(InFile, 0, SEEK_SET);

	return numero_sottostr; //Con Last e First
}

/*------------------------------------------------------------------------------------*\
	Nome routine:
	validateCFGDataRAW


	Esegue una verifica sulla presenza dei parametri per la lettura dei dati raw

	Return value:
	char *	nomeParamError	-	NULL se OK
	Nome parametro mancante se errore

	\*------------------------------------------------------------------------------------*/
char * validateCFGDataRAW()
{

	if (laserRegioniConfig.gridWidth == NONE)
		return "gridWidth";

	if (laserRegioniConfig.gridHeight == NONE)
		return "gridHeight";
	if (laserRegioniConfig.gridUnit == NONE)
		return "gridUnit";

	return NULL;
}



void  leggiDatiInput(const char *filename, DataSet *data1, list<Item>&points)
{
	char nomeFileInput[255] = "\0";
	const char * FName = "leggiDatiInput";
	/* Commento le due inizializzazioni delle matrici perch� le faccio in maniera diversa */
	//unsigned short   **MatrixInit;	//Matrice altezze temporanea e finale
	//struct elemento **CompleteMatrixInit = NULL;	//matrice di struct elemento temporanea
	char * paramError = NULL;

	short int			tipo;
	/* La prof li usava per il file del debug, per ora li commento. Se non necessito del debug li spenger�. */
	//char				*out_file = NULL, *tmp_out_file =NULL;
	//long int			i_dz = 0;	// Indice per Data1->dz
	long				celleVuote = 0;

	int  maxele;					//numero totale di righe nel file input
	long tot_grid_points;			//punti grd
	long int i_dz = 0;	// Indice per Data1->dz
	int colonne;
	errno_t err;
	FILE  *inputFile = new FILE;

	/* Effettuo un controllo per verificare i dati relativi al numero di righe e di colonne*/
	if ((paramError = validateCFGDataRAW()) != NULL)
		errore(PARAM_VALIDATION_ERROR, " NULLO o mancante ", paramError, TRUE);

	/* Non so bene perch� ma copia il nome del file dati da param[] che � stata inizializzata attraverso
		il file di configurazione. */
	strcpy_s(nomeFileInput, 255, laserRegioniConfig.inputDataFileName);

	/* Qua devo allocare due matrici, la MatrixInit e la CompleteMatrix... lui le chiama in una singola funzione perch� in realt�
		quella � una funzione che controlla l'allocazione di tali matrici(-> errore), quindi all'interno di quella richiama
		la funzione per allocarle entrambe.

		In realt� sembra che non mi serva la matrice CompleteMatrix... */

	/*MatrixXi MatrixInit;
	MatrixInit.resize( data1->heightGrid, data1->widthGrid);*/

	//std::vector <elemento> CompleteMatrixInit(Data1->heightGrid * Data1->widthGrid);
	vector <DataSet> dataset_vector(data1->heightGrid * data1->widthGrid);
	/*CompleteMatrixInit.resize(Data1->heightGrid * Data1->widthGrid);*/

	tipo = 0;
	//std::cout << laserRegioniConfig.inputDataFileName << endl;
	char * nomeDaTastiera = (char*)filename;
	//std::cout << nomeDaTastiera << endl;

	//err = fopen_s(&inputFile, "test5_3.txt", "r");
	err = fopen_s(&inputFile, nomeDaTastiera, "r");
	if (err != 0)
		errore(FILE_OPENREAD_ERROR, laserRegioniConfig.inputDataFileName, FName, TRUE);

	rewind(inputFile);

	printf("\nInizio conteggio punti...");
	maxele = fileRows(inputFile);           //maxele : tutti i punti presenti nel file raw

	tot_grid_points = (long int)((data1->widthGrid)*(data1->heightGrid));

	//ALLOCO SEMPRE IL VETTORE dz E POI RIMANE A ZERO NEL CASO DI UN SINGOLO IMPULSO

	for (int i = 0; i < dataset_vector.size(); i++)
		dataset_vector[i].dz;



	printf("\n\t\tPunti in input: %ld \n", maxele);
	printf("\t\tPunti Griglia: %ld \n", tot_grid_points);
	printf("\nInizio lettura dati RAW...%s\n", laserRegioniConfig.inputDataFileName);

	fseek(inputFile, 0, SEEK_SET);
	//lettura fileASCII

	colonne = selezionaCaso(inputFile);
	if (colonne != 3)
	{
		std::cout << "Error! The data file format is inappropriate" << endl;
		return;
	}

	Leggi_SinglePulse_xyz(points, data1, maxele, inputFile);
	fclose(inputFile);

	printf("\n\t\tPunti raw selezionati : %ld\n", data1->numPoints);

	std::cout << "Width (min - max): " << data1->xminInput << "-" << data1->xmaxInput << endl;
	std::cout << "Height (min - max): " << data1->yminInput << "-" << data1->ymaxInput << endl;
	std::cout << "Matrice: " << data1->heightGrid << "x" << data1->widthGrid << "=" << data1->widthGrid*data1->heightGrid << endl;
	std::cout << "Grigliatura: " << data1->pelsX << endl;

	if (data1->numPoints == 0) {
		errore(NO_SELECTED_DATA_ERROR, " Punti Selezionati=0", FName, TRUE);

	}
	buildMatriceSparsa(data1, points/*, data1->heightGrid, data1->widthGrid*/);

	//riempie matrice sparsa
	fill_empty_cells(data1->z/*, data1->heightGrid, data1->widthGrid*/);
	//Accresci(	Data1, Data1->heightGrid, Data1->widthGrid, Data1->pelsX);

	data1->Xg = (2 * data1->LoLeftX + data1->widthGrid * data1->pelsX) / 2;
	data1->Yg = (2 * data1->LoLeftY + data1->heightGrid * data1->pelsX) / 2;

	//if(laserRegioniConfig.tipoOutputASCII == USCITA_ASCII_EN) ;
	//	esporta(Data1);  //$ economia di variabili (dim)?

}

int  Leggi_SinglePulse_xyz(list<Item>&points, DataSet *data, int tot_ele, FILE *inputFile)
{
	int			punti_selezionati = 0, x = 0, y = 0;
	double			t1, t2, t3;
	double			tempXminTot = tempMin, tempXmaxTot = tempMax, tempYminTot = tempMin, tempYmaxTot = tempMax, tempZmin = tempMin, tempZmax = tempMax;
	double 			tempX, tempY, tempZ;
	long int		j;
	int puntiButtati = 0;
	char punto[1000];
	int colonne = 0;
	long int punti = 0;

	tempXminTot = 1000000000;
	tempYminTot = 1000000000;
	tempXmaxTot = -1000;
	tempYmaxTot = -1000;
	tempZmin = 1000000000;
	tempZmax = -1000;

	fgets(punto, 1000, inputFile);  //butto la prima riga


	/* tot_ele contava il numero di righe del file di dati => lo moltiplico per il numero di colonne del file*/

	for (j = 0; j < tot_ele * 3; j = j + 3)
	{
		colonne = VerificaPunto(punto, inputFile);
		if (colonne == 3)
		{
			punti++;
			sscanf_s(punto, "%lf %lf %lf", &t1, &t2, &t3);
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
				x = (long)((tempX - data->LoLeftX) / data->pelsX);
				y = (long)((tempY - data->LoLeftY) / data->pelsX);

				/* Estrapolo i valori di riga e colonna della futura matrice grigliata */
				int col = (int)x;
				int row = data->heightGrid - (int)y - 1;
				

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

	printf("\n\t\tPunti raw totali : %ld", punti);
	printf("\n\t\tPunti buttati : %ld", puntiButtati);
	//writeList(points, "prova_XY.txt");

	data->numPoints = punti_selezionati;
	if (laserRegioniConfig.showAdditionalInfos)
	{
		data->xminInput = (float)tempXminTot;
		data->xmaxInput = (float)tempXmaxTot;
		data->yminInput = (float)tempYminTot;
		data->ymaxInput = (float)tempYmaxTot;
	}
	data->zmin = (float)tempZmin;
	data->zmax = (float)tempZmax;

	return punti;
};

/*------------------------------------------------------------------------------------*\
	Nome routine:
	VerificaPunto

	Funzione che conta le sottostringhe di una riga del file dati
	- accetta come separatore sia punto che virgola
	- sostituisce gli spazi alle virgole nella stringa

	restituisce il numero di colonne
	\*------------------------------------------------------------------------------------*/
int VerificaPunto(char *str, FILE *InFile)
{
	char PrecCar = '*';
	unsigned int numero_sottostr = 0, i = 0;

	fgets(str, 1000, InFile);//Prendo una stringa intera

	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] == ',') str[i] = ' ';
		if ((str[i] == ' ' && PrecCar != ' ' && PrecCar != ',' && PrecCar != '*' && PrecCar != 9) ||
			(str[i] == ',' && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*' && PrecCar != 9) ||
			(str[i] == 9 && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*'  && PrecCar != ',' && PrecCar != 9) ||
			(str[i] == 10 && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*'  && PrecCar != ',' && PrecCar != 9))//separatori spazio o virgola
			numero_sottostr++;//Calcolo le sottostringhe
		PrecCar = str[i];
	}


	return numero_sottostr++;
};


void buildMatriceSparsa(DataSet *data1, list<Item>& points/*, int rows, int col*/)
{
	const char			*FName = "buildMatriceSparsa";
	int emptyCells = 0, m;
	int rows = data1->heightGrid;
	int col = data1->widthGrid;
	unsigned char *density = new unsigned char[data1->widthGrid*data1->heightGrid];
	float	delta;
	int MaxD = 0;
	int counter = 0;
	FILE *out_file;
	const char* file_palette = NULL;

	//writeList(points, "prova_sort.txt");
	points.sort(compare_index_then_value);
	//writeList(points, "prova_sort.txt");
	map<std::pair<int, int>, std::vector<float>> item_map;
	item_map = list2map(points);
	//write_map(item_map, "prova_map.txt");

	FILE *fd = fopen("prova_output.txt", "w");
	int tot_celle = rows*col;

	/*for (int i = 0; i < 5; ++i)   //scorre le righe
	{
	m = i *rows;
	for (int j = 0; j < 10; ++j)  //scorro le colonne
	{
	{
	for (int k = 0; k< item_map[std::make_pair(i, j)].size(); ++k)
	{
	std::pair<int, int> b = std::make_pair(i, j);
	std::cout << "mymap[" << i << "," << j << "](" << k << "): " << item_map[b].at(k) << std::endl;
	}
	}
	}
	}*/
	for (int i = 0; i < rows; ++i)   //scorre le righe
	{
		m = i *col;
		for (int j = 0; j < col; ++j)  //scorro le colonne	
		{
			/* Se non viene trovato alcun elemento nella cella della mappa allora la si setta nulla. */
			if (item_map.count(std::make_pair(i, j)) < 1/*item_map.find(std::make_pair(i, j)) == item_map.end()*/)
			{
				emptyCells++;
				data1->z[m + j] = QUOTA_BUCHI;
			}
			else
			{
				/* Altrimenti valuto immediatamente la lunghezza del vettore di indice (pair) ij */
				int vec_size = item_map[std::make_pair(i, j)].size();
				/* Se la dimensione del vettore � pari a 1 allora il valore
				appena letto viene passato al vettore z. */
				if (vec_size == 1)
				{
					data1->z[m + j] = item_map[std::make_pair(i, j)].back();
				}
				else
				{
					/* Altrimenti si valuta la differenza tra i due elementi con valore maggiore e valore minore. */
					delta = item_map[std::make_pair(i, j)].back() - item_map[std::make_pair(i, j)].front();
					/* Dato che il programma non legge un float in ingresso lo scrivo nel file config * 100,
					quindi sotto lo divido per 100 e lo casto. */
					float dislivello = (float)(laserRegioniConfig.dislivelloMatriceSparsa) / 100;
					/* Valuto il valore di delta rispetto al dislivello inserito nel file config. */
					if (delta > dislivello)
					{
						/* Se il delta � maggiore del dislivello allora  prendo l'ultimo elemento del vettore. */
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
							/* Se invece il numero di elelemti � dispari, faccio la somma dell'elemento precedente a quello che si trova
							a met� del vettore e dell'elemento che si trova proprio a met� del vettore diviso per due. */
							data1->z[m + j] = (item_map[std::make_pair(i, j)].at((vec_size - 1) / 2) + item_map[std::make_pair(i, j)].at((vec_size - 1) / 2 + 1)) / 2;
						}
					}
				}
				/* Per adesso ho aggiunto questa merda ma devo chiedere alla professoressa. */
				MaxD = vec_size > MaxD ? vec_size : MaxD;
				if (vec_size > 255) vec_size = 255;
				*(density + m + j) = (unsigned char)vec_size;
			}
			//std::cout << "dopo il sort!" << i << " " << j << endl;
		}
	}
	std::cout << "fatto build matrice sparsa... Maximum density: " << MaxD << endl;
	fprintf(fd, "celle totali: %d\ncelle vuote: %d\ncelle piene: %d\n", tot_celle, emptyCells, (tot_celle - emptyCells));
	//fprintf(fd, "LoLeftX: %f\tUpRightX: %f\tLoLeftY: %f\tUpRightY: %f\n", data1->LoLeftX, data1->UpRightX, data1->LoLeftY, data1->UpRightY);

	if (laserRegioniConfig.tipoUscita >= LEVEL_3)
	{
		/*Creo il nome del file di output*/
		string file_out_name = makeExtension(laserRegioniConfig.projectName, DENSITAPNT_EXT);
		const char *file_out_name_char = file_out_name.c_str();

		if (fopen_s(&out_file, file_out_name_char, "wb") != NULL)
			errore(FILE_OPENWRITE_ERROR, (char*)file_out_name_char, FName, TRUE);

		if (laserRegioniConfig.paletteFileName != NULL)
		{
			string nome_file_palette = makeExtension(laserRegioniConfig.paletteFileName, DENSITAPNT_ACT);
			file_palette = nome_file_palette.c_str();
		}
		HeaderWrPalette(out_file, rows, col, (char*)file_palette);
		InvertiRaw2Bmp(density, rows, col, 1078, out_file);
		fclose(out_file);
	}

	delete density;
	fclose(fd);
	return;
};