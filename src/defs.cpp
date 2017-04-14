#include <iostream>
#include <string>
//#include <Core>
#include <vector>

#include "defs.h"
#include "const.h"
#include "tools.h"
#include "output_tools.h"
#include "gradient_tools.h"

//using namespace Eigen;
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

	data1->z = new real_[data1->widthGrid*data1->heightGrid];

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
	/* Commento le due inizializzazioni delle matrici perché le faccio in maniera diversa */
	char * paramError = NULL;

	short int			tipo;
	/* La prof li usava per il file del debug, per ora li commento. Se non necessito del debug li spengerò. */
	//char				*out_file = NULL, *tmp_out_file =NULL;
	//long int			i_dz = 0;	// Indice per Data1->dz

	int  tot_nodes;					//numero totale di righe nel file input
	long tot_grid_points;			//punti grd
	long int i_dz = 0;	// Indice per Data1->dz
	int colonne;
	errno_t err;
	FILE  *inputFile = new FILE;

	/* Effettuo un controllo per verificare i dati relativi al numero di righe e di colonne*/
	if ((paramError = validateCFGDataRAW()) != NULL)
		errore(PARAM_VALIDATION_ERROR, " NULLO o mancante ", paramError, TRUE);

	/* Non so bene perché ma copia il nome del file dati da param[] che è stata inizializzata attraverso
		il file di configurazione. */
	strcpy_s(nomeFileInput, 255, laserRegioniConfig.inputDataFileName);

	/* Dichiaro un vettore di tipo dataset con un numenro di elementi pari a righe per colonne. */
	vector <DataSet> dataset_vector(data1->heightGrid * data1->widthGrid);
	tipo = 0;
	char * nomeDaTastiera = (char*)filename;

	/* Effettuo un controllo sull'apertura del file dati.*/
	err = fopen_s(&inputFile, nomeDaTastiera, "r");
	if (err != 0)
		errore(FILE_OPENREAD_ERROR, laserRegioniConfig.inputDataFileName, FName, TRUE);

	rewind(inputFile);


	std::cout << "Width (min - max): " << data1->LoLeftX << "-" << data1->UpRightX << endl;
	std::cout << "Height (min - max): " << data1->LoLeftY << "-" << data1->UpRightY << endl;
	std::cout << "Matrice: " << data1->heightGrid << "x" << data1->widthGrid << "=" << data1->widthGrid*data1->heightGrid << endl;
	std::cout << "Grigliatura: " << data1->pelsX << endl;

	printf("\nInizio conteggio punti...");
	//nodi totali : tutti i punti presenti nel file raw
	tot_nodes = fileRows(inputFile);           
	/* Numero totale dei putni del grigliato. */
	tot_grid_points = data1->widthGrid * data1->heightGrid; 

	//ALLOCO SEMPRE IL VETTORE dz E POI RIMANE A ZERO NEL CASO DI UN SINGOLO IMPULSO

	for (int i = 0; i < dataset_vector.size(); i++)
		dataset_vector[i].dz;

	printf("\n\t\tPunti in input: %ld \n", tot_nodes);
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

	/* Effettuo la lettura del file dati.*/
	Leggi_SinglePulse_xyz(points, data1, tot_nodes, inputFile);
	fclose(inputFile);

	printf("\n\t\tPunti raw selezionati : %ld\n", data1->numPoints);

	if (data1->numPoints == 0) 
	{
		errore(NO_SELECTED_DATA_ERROR, " Punti Selezionati=0", FName, TRUE);

	}

	/* Costruisco la matrice sparsa... Per ora faccio solo la ricerca dei punti alti. */
	buildMatriceSparsa(data1, points, data1->heightGrid, data1->widthGrid);

	//riempie matrice sparsa... Non so se effettivamente mi serve, per ora l'ho riscritta.
	fill_empty_cells(data1->z, data1->heightGrid, data1->widthGrid);

	data1->Xg = (2 * data1->LoLeftX + data1->widthGrid * data1->pelsX) / 2;
	data1->Yg = (2 * data1->LoLeftY + data1->heightGrid * data1->pelsX) / 2;

	if(laserRegioniConfig.tipoOutputASCII == USCITA_ASCII_EN) ;
		export(data1);  //$ economia di variabili (dim)?

}

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

/*------------------------------------------------------------------------------------*\
Nome routine:
SegmentaInFalde1

Calcolo dell'intensità del gradiente e dell'orientamento con fusione di
2 partizioni shiftate di mezza ampiezza (se partizioni a 45° -> shift=22,5°:
l'output è la bitmap contenente la segmentazione basata sull'orientamento
del gradiente per TUTTA l'area


(aggiunta recente ancora da convalidare)
Calcolo delle discontinuità sulla base dell'orientamento del gradiente di punti con
intensità del gradiente elevate (laserRegioniConfig.sogliaGradContornoColmi)
l'output è:
- la bitmap contenete la segmentazione basata sull'orientamento del gradiente per punti
avente intensità del gradiente elevata
- file dxf delle linee estratte

Parametri:

<INPUT> DATA *Data	-	 Informazioni di elaborazione del progetto
<OUTPUT> unsigned char ** cnt	-	Immagine dell'orientamento dei gradienti

ritorna:

- la bitmap cnt che contiene la segmentazione secondo l'orientamento del gradiente

\*------------------------------------------------------------------------------------*/
void  SegmentaInFalde(DataSet *data1, unsigned char **cnt, real_ **graR, real_ **graC)
{
	const char * FName = "SegmentaInFalde1";
	/* Il numero degli elementi del vettore dipende dalla dimensione della matrice
		della quale voglio il kernel. (es. la prof usa 5 vome valori di riga e colonna 
		attraverso i quali fare i kernel quindi basterebbero vettori da 25). Versione iniziale da 81.*/
	real_ Hr[25], Hc[25], a[24], b[24];
	double shift;
	int i;
	int partitions;
	
	unsigned char *gra = new unsigned char[data1->widthGrid*data1->heightGrid];
	unsigned char *map1 = new unsigned char[data1->widthGrid*data1->heightGrid];
	unsigned char *map2 = new unsigned char[data1->widthGrid*data1->heightGrid];
	unsigned char *mapL = new unsigned char[data1->widthGrid*data1->heightGrid];
	long int *cnt1 = new long int[data1->widthGrid*data1->heightGrid];
	long int *cnt2 = new long int[data1->widthGrid*data1->heightGrid];

	const char * file_out_name_char = NULL;
	const char * file_palette_name_char = NULL;

	FILE *sgn;
	int lineeIMG;
	PLine **cls;
	long int tot_grid_points;


	tot_grid_points = data1->widthGrid*data1->heightGrid;

	/*************CALCOLO GRADIENTE **************************/
	build_kernel(Hr, Hc, 3);
	
	/* funzioni per applicare il filtro del kernel. La funzione, se andata a buon fine, restituisce un uno. */
	if (!kernelf(data1->z, *graR, Hr, 1, data1->widthGrid, data1->heightGrid, 3, 3))
		errore(ROUTINE_GENERIC_ERROR, "kernelf in R", FName, FALSE);
	if (!kernelf(data1->z, *graC, Hc, 1, data1->widthGrid, data1->heightGrid, 3, 3))
		errore(ROUTINE_GENERIC_ERROR, "kernelf in C", FName, FALSE);

	Gradiente(*graR, *graC, gra, data1->widthGrid, data1->heightGrid, data1->pelsX, data1->LoLeftX, data1->LoLeftY);

	if (laserRegioniConfig.tipoUscita >= LEVEL_3)
	{
		std::string file_out_name = makeExtension(laserRegioniConfig.projectName, SEGMINGRAD_EXT);
		file_out_name_char = file_out_name.c_str();
		if (fopen_s(&sgn, file_out_name_char, "wb") != NULL)
			errore(FILE_OPENWRITE_ERROR, (char*) file_out_name_char, FName, TRUE);

		if (laserRegioniConfig.paletteFileName != NULL)
		{
			std::string file_palette_name = makeExtension(laserRegioniConfig.paletteFileName, SEGMINFALDE_ACT);
			file_palette_name_char = file_palette_name.c_str();
		}
		HeaderWrPalette(sgn, data1->widthGrid, data1->heightGrid,(char*)file_palette_name_char);
		InvertiRaw2Bmp(gra, data1->heightGrid, data1->widthGrid, 1078, sgn);
		fclose(sgn);
	}
	delete gra;

	/*********CALCOLO ORIENTAMENTO DEL GRADIENTE*****************/
	partitions = build_partitions(a, b);

	if (!Teta(*graR, *graC, map1, a, laserRegioniConfig.sogliaGradOrientazione, 3, 3, data1->widthGrid, data1->heightGrid, partitions, 255))
		errore(ROUTINE_GENERIC_ERROR, "CalcolaGraTeta", FName, FALSE);
	if (!Teta(*graR, *graC, map2, b, laserRegioniConfig.sogliaGradOrientazione, 3, 3, data1->widthGrid, data1->heightGrid, partitions, 255))
		errore(ROUTINE_GENERIC_ERROR, "CalcolaGraTeta", FName, FALSE);

	conta(map1, cnt1, data1->widthGrid, data1->heightGrid, 255,1);
	conta(map2, cnt2, data1->widthGrid, data1->heightGrid, 255,2);

	//Fusione dei due partizionamenti shiftati: risultato in cnt!
	Fusione(cnt1, cnt2, map1, map2, *cnt, data1->widthGrid, data1->heightGrid);

	//stampa dei risultati della segmentazione caricati sulla bitmap (gloable) map - cnt  nel main

	if (laserRegioniConfig.tipoUscita >= LEVEL_1)
	{
		std::string file_out_name = makeExtension(laserRegioniConfig.projectName, SEGMINFALDE_EXT);
		const char *file_out_name_char = file_out_name.c_str();

		if (fopen_s(&sgn, file_out_name_char, "wb") != NULL)
			errore(FILE_OPENWRITE_ERROR, (char*)file_out_name_char, FName, TRUE);

		if (laserRegioniConfig.paletteFileName != NULL)
		{
			std::string file_palette_name = makeExtension(laserRegioniConfig.paletteFileName, SEGMINFALDE_ACT);
			file_palette_name_char = file_palette_name.c_str();
		}
		HeaderWrPalette(sgn, data1->widthGrid , data1-> heightGrid, (char*)file_palette_name_char);
		InvertiRaw2Bmp(*cnt, data1->heightGrid, data1->widthGrid, 1078, sgn);
		fclose(sgn);
	}

	delete map1;
	delete map2;
	delete mapL;
	delete cnt1;
	delete cnt2;
};