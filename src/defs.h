#pragma once

#include <list>
#include <utility>

#include "config_file.h"
#include "const.h"
#include "parameters.h"


struct DataSet
{
	unsigned char *cont, *dz;
	long int widthGrid, heightGrid; /*Dimensione pixels griglia
									dati elaborata (solo per gli IMG è tutta la griglia)*/
	long int numPoints;
	float Xg, Yg;				//Coordinate baricentro
	float xminInput, xmaxInput, yminInput, ymaxInput;	//Estremi intera regione in 
	//input in coordinate cartografiche
	float zmin, zmax;			//Massime e minime quote
	// float Imax,Imin;
	float pelsX/*,pelsY*/;			//Passo della griglia (dimensione cella)
	float LoLeftX, LoLeftY;		//LoLeft di elaborazione dati in coordinate cartografiche
	float UpRightX, UpRightY;	//UpRight di elaborazione dati in coordinate cartografiche
	long int UpLeftRGrid, UpLeftCGrid, LoRightRGrid, LoRightCGrid; /*Coordinate pixel regione da processare
																   per dati in input grigliati: è possibile che
																   venga imposta tutta la finestra in input tramite
																   un altro parametro. Per i dati RAW vengono
																   calcolati dagli input.*/
	float *z;
};

struct Item
{
	float nord, est, quota;					/* Variabili che conterranno le coordinate spaziali (RAW). */
	int id;									/* Numero identificativo dell'elemento. */
	std::pair <int, int> coordinate;		// default constructor.
};

void setItem( Item &n_it, float n, float e, float q, int identity, const std::pair<int, int>&c);

int Config2Data(DataSet *data1);
void printData(DataSet *data1);
long int fileRows(FILE *inputFile);
int selezionaCaso(FILE *InFile);
char * validateCFGDataRAW();
void leggiDatiInput(const char *filename, DataSet *data1, std::list<Item>&points);
int Leggi_SinglePulse_xyz(std::list<Item>&points, DataSet *data1, int tot_ele, FILE *inputFile);
int VerificaPunto(char *str,FILE *InFile);
//void buildMatriceSparsa(DataSet *data1, list<Elemento>&points, int rows, int col);