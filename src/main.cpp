#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <Core>
#include <list>

#include "input_validate.h"
#include "parameters.h"
#include "config_file.h"
#include "const.h"
#include "defs.h"
#include "output_tools.h"
//#include "gradient_tools.h"

using namespace std;


int main(int argc, char const *argv[])
{
	/* Variabile contenente i settaggi imposti tarmite il file di configurazione. */
	extern Configurator laserRegioniConfig;
	
	// inizializzo un intero di appoggio per non utilizzare argc.
	int n_par= argc;

	// Verifico che si sia inserito il giusto numero di parametri.
	if(!input_number_parameter( n_par))
		return 1;

	// Inizializzo un vettore di stringhe per copiare gli argomenti.
	std::vector<string> v;
	for (int i = 1; i < argc; i++) 
	{
		v.push_back(argv[i]);
	}
	// Creo due nuove variabili contenenti i nomi dei file passati da linea di comando.
	const char *new_argv_1 = v[0].c_str();
	const char *new_argv_2 = v[1].c_str();
	
	// Verifico che l'estensioni siano corrette.
	if(!data_extension( new_argv_1 ))
		return 1;

	if(!conf_extension( new_argv_2 ))
		return 1;
	
	cout << "The three file you passed were all correct" << endl;
	
	/* Inizializzo la variabile che conterrà la lista. */
	std::list<Item> raw_points, filtered_points;
	/* Inizializzo una variabile DataSet. */
	DataSet *prova= new DataSet;
	//printData(prova);
	/* Inizializzo la variabile utilizzata per la lettura del file di configurazione. */
	ConfigFile *file = new ConfigFile();
	
	//file -> printAllParameters();
	file -> load (new_argv_2);
	//file -> printAllParameters();
	Config2Data(prova);
	//printData(prova);
	
	leggiDatiInput(new_argv_1, prova, raw_points, filtered_points);
	writeBpw(laserRegioniConfig.projectName, prova);
	/*Devo capire bene come passare sta roba (se per riferimento o meno). */
	// Variabili utilizzate per il calcolo del gradiente.
	//Immagine degli orientamenti dei gradienti.
	unsigned char *pCnt = new unsigned char[prova->widthGrid*prova->heightGrid];
	real_ *pGraR = new real_[prova->widthGrid*prova->heightGrid];
	real_ *pGraC = new real_[prova->widthGrid*prova->heightGrid];
	SegmentaInFalde(prova, &pCnt, &pGraR, &pGraC);
	//pPLoc = MappaPianiLocali(&Data, ppCompleteMatrix);

	delete prova;
	delete file;
	delete pGraR;
	delete pGraC;
	cout << "Torno nel main" << endl;
	return 1;
}
