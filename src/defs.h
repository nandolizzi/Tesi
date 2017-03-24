#pragma once

#include <list>
#include <utility>
#include <map>


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


int Config2Data(DataSet *data1);
void printData(DataSet *data1);
long int fileRows(FILE *inputFile);
int selezionaCaso(FILE *InFile);
char * validateCFGDataRAW();
void leggiDatiInput(const char *filename, DataSet *data1, std::list<Item>&points);
int VerificaPunto(char *str,FILE *InFile);
