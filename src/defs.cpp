#include <iostream>
#include <string>

#include "defs.h"
#include "const.h"

int Config2Data(DataSet *data1)
{
	extern Configurator laserRegioniConfig;

	if (strstr(laserRegioniConfig.projectName, ".prj") == NULL)
		strcat_s(laserRegioniConfig.projectName, strlen(".prj")+1,".prj");
	
	data1->UpLeftCGrid  = 0;									//laserRegioniConfig.upLeftC;
	data1->UpLeftRGrid  = 0;									//laserRegioniConfig.upLeftR;
	data1->LoRightCGrid = laserRegioniConfig.gridWidth;			//laserRegioniConfig.lowRightC;
	data1->LoRightRGrid = laserRegioniConfig.gridHeight;		//laserRegioniConfig.lowRightR;

	data1->widthGrid    = laserRegioniConfig.gridWidth;
	data1->heightGrid   = laserRegioniConfig.gridHeight;
	data1->pelsX = data1->pelsY = laserRegioniConfig.gridUnit;  // Usa due diverse variabili per x e y ma se sono le stesse potrei unificarle

	data1->LoLeftX      = laserRegioniConfig.loLeftX;
	data1->LoLeftY      = laserRegioniConfig.loLeftY;
	data1->UpRightX     = data1->LoLeftX + (double)(data1->pelsX * data1->widthGrid);
	data1->UpRightY     = data1->LoLeftY + (double)(data1->pelsY * data1->heightGrid);

	return SUCCESS;
	
}

void printData(DataSet *data1)
{
	std::cout <<"Per ora niente"<< std::endl;
	std::cout << "cont= " << data1->cont << " dz= "<< data1->dz << std::endl;
	std::cout << "widthGrid= " << data1->widthGrid << " heightGrid= " << data1->heightGrid << std::endl;
	std::cout << "numPoints= " << data1->numPoints << std::endl;
	std::cout << "Xg= " << data1->Xg << " Yg= " << data1->Yg << std::endl;
	std::cout << "xminInput= "<< data1->xminInput << " xmaxInput= " << data1->xmaxInput << " yminInput= " << data1->yminInput << " ymaxInput= " << data1->ymaxInput << std::cout;
	std::cout << "zmin= " << data1->zmin << " zmax= " << data1->zmax << " Imax= " << data1->Imax << " Imin= " << data1->Imin << std::endl;
	std::cout << "pelsX= " << data1->pelsX << " pelsY= " << data1->pelsY << std::endl;
	std::cout << "LoLeftX= " << data1->LoLeftX << " LoLeftY= " << data1->LoLeftY << " UpRightX= " << data1->UpRightX << " UpRightY= " << data1->UpRightY << std::endl;
	std::cout << "UpLeftRGrid= " << data1->UpLeftRGrid << " UpLeftCGrid= " << data1->UpLeftCGrid << " LoRightRGrid= " << data1->LoRightRGrid << " LoRightCGrid= " << data1->LoRightCGrid << std::endl;
};

/* Funzione che conta il numero di punti contenuti nel file dati di tipo .txt */
long int fileRows(FILE *inputFile)
{
  char trash[1000];
  long int punti = 0;

  while( fgets( trash, 1000, inputFile) )
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
	char str[250],PrecCar='*';
	unsigned int numero_sottostr=0,i=0;

	fgets(str,1000,InFile);//scarto la prima stringa 
	fgets(str,1000,InFile);//Prendo una stringa intera

	for ( i = 0; i < strlen(str) ; i++)
	{
		if( (str[i] == ' ' && PrecCar != ' ' && PrecCar != ',' && PrecCar != '*' && PrecCar != 9) || 
			(str[i] == ',' && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*' && PrecCar != 9) ||
			(str[i] == 9  && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*'  && PrecCar != ',' && PrecCar != 9) || 
			(str[i] == 10 && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*'  && PrecCar != ',' && PrecCar != 9))//separatori spazio o virgola
			numero_sottostr++;//Calcolo le sottostringhe
		PrecCar = str[i];
	}

	fseek(InFile,0,SEEK_SET);

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
	extern Configurator laserRegioniConfig;

	if (laserRegioniConfig.gridWidth == NONE)
		return "gridWidth";

	if (laserRegioniConfig.gridHeight == NONE)
		return "gridHeight";
	if (laserRegioniConfig.gridUnit == NONE)
		return "gridUnit";

	return NULL;
}



void  leggiDatiInput(const char *filename, DataSet *Data1/*,struct elemento ***CompleteMatrix*/)
{
	extern Configurator laserRegioniConfig;
	char nomeFileInput[255]="\0";
	const char * FName = "leggiDatiInput";
	unsigned short   **MatrixInit;	//Matrice altezze temporanea e finale
	struct elemento **CompleteMatrixInit = NULL;	//matrice di struct elemento temporanea
	char * paramError = NULL;

	short int			tipo;
	//char				*out_file = NULL, *tmp_out_file =NULL;
	//long int			i_dz = 0;	// Indice per Data1->dz
	long				celleVuote = 0;

	long  maxele;  //numero totale di righe nel file input
	long punti; //punti grd
	long punti_selezionati;
    int colonne;
	errno_t err;
	FILE  *inputFile= new FILE;

	if ((paramError = validateCFGDataRAW()) != NULL)
		errore(PARAM_VALIDATION_ERROR, " NULLO o mancante ", paramError, TRUE);
	
	strcpy_s(nomeFileInput, 255,laserRegioniConfig.inputDataFileName);

	/* Qua devo allocare due matrici, la MatrixInit e la CompleteMatrix... lui le chiama in una singola funzione perché in realtà
		quella è una funzione che controlla l'allocazione di tali matrici(-> errore), quindi all'interno di quella richiama 
		la funzione per inizializzarle entrambe*/

	//allocaMatriciDati( &MatrixInit, CompleteMatrix, Data1->heightGrid, Data1->widthGrid );  QUA DEVO RIMETTERE LA FUNZIONE!!!!!!!!!! 

	//tipo = 0;
  std::cout << laserRegioniConfig.inputDataFileName<< std::endl;
  char * nomeDaTastiera= (char*) filename;
  std::cout << nomeDaTastiera<< std::endl;
  
  //err = fopen_s(&inputFile, "test5_3.txt", "r");
  err = fopen_s(&inputFile, nomeDaTastiera, "r");
	if (err != 0)
			errore(FILE_OPENREAD_ERROR, laserRegioniConfig.inputDataFileName, FName, TRUE);
	  
	std::cout << "Arrivo dopo l'err"<< std::endl;
	
	rewind(inputFile);

	printf("\nInizio conteggio punti...");
	maxele = fileRows(inputFile);           //maxele : tutti i punti presenti nel file raw

	punti = (long int)((Data1->widthGrid)*(Data1->heightGrid));

	//ALLOCO SEMPRE IL VETTORE dz E POI RIMANE A ZERO NEL CASO DI UN SINGOLO IMPULSO
	/*	if((Data1->dz = (unsigned char *)calloc( punti , sizeof(unsigned char))) == NULL) 
			errore(MEMORY_ALLOCATION_ERROR,"data.dz",FName,TRUE);
			QUA DEVO RIMETTERE LA FUNZIONE!!!!!!!!!!											*/

	printf("\n\t\tPunti in input: %ld \n",maxele);
	printf("\t\tPunti Griglia: %ld \n",punti);
	printf("\nInizio lettura dati RAW...%s", laserRegioniConfig.inputDataFileName);

	fseek(inputFile,0,SEEK_SET);
	//lettura fileASCII
   
	colonne = selezionaCaso(inputFile);
	std::cout << "Il numero di colonne risulta pari a: " << colonne << std::endl;

	/*switch(laserRegioniConfig.tipoLastFirst)
		{
	case TIPO_LF_1SOLO:      //X Y Z    colonne: 3
		if(colonne == 3)	Leggi_SinglePulse_xyz( * CompleteMatrix,Data1,maxele,inputFile);
		else 	            errore(ERROR_DATA_FORMAT, laserRegioniConfig.inputDataFileName, FName, TRUE);
		break;
	case TIPO_LF_1SOLO_INTENSITA:      //X Y Z I    colonne 4
		if(colonne == 4)    Leggi_SinglePulse_xyzi( * CompleteMatrix,Data1,maxele,inputFile); //DATI X Y Z I
		else 	            errore(ERROR_DATA_FORMAT, laserRegioniConfig.inputDataFileName, FName, TRUE);
		break;
	case TIPO_LF_LASTFIRST_INSIEME_NOTEMPO:     //CODICE X Y Z I (senza Tempo...solo stromboli 2006) colonne 5
		if(colonne == 5)    Leggi_Pulse_tcxyzi( * CompleteMatrix,Data1,maxele,inputFile);   //LETTURA DATI TEMPO CODICE X Y Z I
		else 	            errore(ERROR_DATA_FORMAT, laserRegioniConfig.inputDataFileName, FName, TRUE);
		break;
	case TIPO_LF_LASTFIRST_INSIEME:    //TEMPO CODICE X Y Z I   colonne 6
		if(colonne == 6)    Leggi_Pulse_tcxyzi( * CompleteMatrix,Data1,maxele,inputFile);   //LETTURA DATI TEMPO CODICE X Y Z I
		else 	            errore(ERROR_DATA_FORMAT, laserRegioniConfig.inputDataFileName, FName, TRUE);
		break;
	case TIPO_LF_LASTFIRST:     //XL YL ZL IL XF YF ZF IF              (pavia optech)   colonne 8
		if(colonne == 8)    Leggi_LastFirstPulse(* CompleteMatrix,Data1,maxele,inputFile);
		else 	            errore(ERROR_DATA_FORMAT, laserRegioniConfig.inputDataFileName, FName, TRUE);
		break;
	case TIPO_LF_FIRSTLAST:    //LETTURA DATI XF YF ZF IF XL YL ZL IL               (laser test)    colonne 8
		if(colonne == 8)    Leggi_FirstLastPulse(* CompleteMatrix,Data1,maxele,inputFile);  //LETTURA DAT X Y Z I X Y Z I 
		else 	            errore(ERROR_DATA_FORMAT, laserRegioniConfig.inputDataFileName, FName, TRUE);
		break;
	case TIPO_LF_T_FIRSTLAST:    //LETTURA DATI TEMPO XF YF ZF IF XL YL ZL IL   (stromboli 2009)    colonne 9
		if(colonne == 9)    Leggi_T_FirstLastPulse(* CompleteMatrix,Data1,maxele,inputFile);  //LETTURA DAT X Y Z I X Y Z I 
		else 	            errore(ERROR_DATA_FORMAT, laserRegioniConfig.inputDataFileName, FName, TRUE);
		break;
	case TIPO_LF_LASTFIRST_INSIEME_CODICI:    //TEMPO CODICE X Y Z I   colonne 6
		if(colonne == 6)    Leggi_Pulse_xyzi_c( * CompleteMatrix,Data1,maxele,inputFile);   //LETTURA DATI TEMPO CODICE X Y Z I
		else 	            errore(ERROR_DATA_FORMAT, laserRegioniConfig.inputDataFileName, FName, TRUE);
		break;
	case TIPO_UAV:    //TEMPO X Y Z Eco NumECo I scan  colonne 8
		if(colonne == 8)    Leggi_Pulse_uav( * CompleteMatrix,Data1,maxele,inputFile);   //LETTURA DATI TEMPO CODICE X Y Z I
		else 	            errore(ERROR_DATA_FORMAT, laserRegioniConfig.inputDataFileName, FName, TRUE);
		break;

	default:					QUA DEVO RIMETTERE LA FUNZIONE!!!!!!!!!! 
		printf("\n Formato non riconosciuto\n"); 
		errore(ERROR_DATA_FORMAT, laserRegioniConfig.inputDataFileName, FName, TRUE);
		//break;
		}*/
	fclose(inputFile);

	printf("\n\t\tPunti raw selezionati : %ld",Data1->numPoints);

	if(Data1->numPoints == 0) {
		errore(NO_SELECTED_DATA_ERROR, " Punti Selezionati=0", FName, TRUE);
		
	}

	//buildMatriceSparsa(Data1, *CompleteMatrix, Data1->widthGrid, Data1->heightGrid);
	
	//free(out_file);

	//riempie matrice sparsa
	//Accresci(	Data1, Data1->heightGrid, Data1->widthGrid, Data1->pelsX);

	//freeMatrix(Data1->heightGrid,MatrixInit);

	Data1->Xg = (2 * Data1->LoLeftX + Data1->widthGrid * Data1->pelsX) / 2;
	Data1->Yg = (2 * Data1->LoLeftY + Data1->heightGrid * Data1->pelsY) / 2;
  
	//if(laserRegioniConfig.tipoOutputASCII == USCITA_ASCII_EN) ;
	//	esporta(Data1);  //$ economia di variabili (dim)?
}

