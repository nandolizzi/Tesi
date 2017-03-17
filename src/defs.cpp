#include <iostream>
#include <string>
#include <Core>
#include <vector>


#include "defs.h"
#include "const.h"
#include"tools.h"

using namespace Eigen;
using namespace std;

#define tempMin 1000000000
#define tempMax -1000

void setItem(Item &n_it, float n, float e, float q, int identity, const std::pair<int, int>& c)
{
	n_it.nord = n;
	n_it.est = e;
	n_it.quota = q;
	n_it.id = identity;
	n_it.coordinate = c;
};

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
	data1->pelsX /*= data1->pelsY */= laserRegioniConfig.gridUnit;  // Usa due diverse variabili per x e y ma se sono le stesse potrei unificarle

	data1->LoLeftX      = laserRegioniConfig.loLeftX;
	data1->LoLeftY      = laserRegioniConfig.loLeftY;
	data1->UpRightX     = data1->LoLeftX + (double)(data1->pelsX * data1->widthGrid);
	data1->UpRightY     = data1->LoLeftY + (double)(data1->pelsX * data1->heightGrid);

	return SUCCESS;
	
}

void printData(DataSet *data1)
{
	std::cout <<"Per ora niente"<< std::endl;
	std::cout << "cont= " << data1->cont << " dz= "<< data1->dz << std::endl;
	std::cout << "widthGrid= " << data1->widthGrid << " heightGrid= " << data1->heightGrid << std::endl;
	std::cout << "numPoints= " << data1->numPoints << std::endl;
	std::cout << "Xg= " << data1->Xg << " Yg= " << data1->Yg << std::endl;
	std::cout << "xminInput= "<< data1->xminInput << " xmaxInput= " << data1->xmaxInput << " yminInput= " << data1->yminInput << " ymaxInput= " << data1->ymaxInput << std::endl;
	std::cout << "zmin= " << data1->zmin << " zmax= " << data1->zmax /*<< " Imax= " << data1->Imax << " Imin= " << data1->Imin */<< std::endl;
	std::cout << "pelsX= " << data1->pelsX/* << " pelsY= " << data1->pelsY*/ << std::endl;
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



void  leggiDatiInput(const char *filename, DataSet *data1, list<Item>&points)
{
	extern Configurator laserRegioniConfig;
	char nomeFileInput[255]="\0";
	const char * FName = "leggiDatiInput";
	/* Commento le due inizializzazioni delle matrici perché le faccio in maniera diversa */
	//unsigned short   **MatrixInit;	//Matrice altezze temporanea e finale
	//struct elemento **CompleteMatrixInit = NULL;	//matrice di struct elemento temporanea
	char * paramError = NULL;

	short int			tipo;
	/* La prof li usava per il file del debug, per ora li commento. Se non necessito del debug li spengerò. */
	//char				*out_file = NULL, *tmp_out_file =NULL;
	//long int			i_dz = 0;	// Indice per Data1->dz
	long				celleVuote = 0;

	int  maxele;					//numero totale di righe nel file input
	long tot_grid_points;			//punti grd
	long punti_selezionati;
	long int i_dz = 0;	// Indice per Data1->dz
    int colonne;
	errno_t err;
	FILE  *inputFile= new FILE;
	
	/* Effettuo un controllo per verificare i dati relativi al numero di righe e di colonne*/
	if ((paramError = validateCFGDataRAW()) != NULL)
		errore(PARAM_VALIDATION_ERROR, " NULLO o mancante ", paramError, TRUE);
	
	/* Non so bene perché ma copia il nome del file dati da param[] che è stata inizializzata attraverso
		il file di configurazione. */
	strcpy_s(nomeFileInput, 255,laserRegioniConfig.inputDataFileName);

	/* Qua devo allocare due matrici, la MatrixInit e la CompleteMatrix... lui le chiama in una singola funzione perché in realtà
		quella è una funzione che controlla l'allocazione di tali matrici(-> errore), quindi all'interno di quella richiama 
		la funzione per allocarle entrambe.
			
			In realtà sembra che non mi serva la matrice CompleteMatrix... */

	/*MatrixXi MatrixInit;
	MatrixInit.resize( data1->heightGrid, data1->widthGrid);*/

	//std::vector <elemento> CompleteMatrixInit(Data1->heightGrid * Data1->widthGrid);
	vector <DataSet> dataset_vector(data1->heightGrid * data1->widthGrid);
	/*CompleteMatrixInit.resize(Data1->heightGrid * Data1->widthGrid);*/

  tipo = 0;
  cout << laserRegioniConfig.inputDataFileName<< endl;
  char * nomeDaTastiera= (char*) filename;
  cout << nomeDaTastiera<< endl;
  
  //err = fopen_s(&inputFile, "test5_3.txt", "r");
  err = fopen_s(&inputFile, nomeDaTastiera, "r");
	if (err != 0)
			errore(FILE_OPENREAD_ERROR, laserRegioniConfig.inputDataFileName, FName, TRUE);
	 
	rewind(inputFile);

	printf("\nInizio conteggio punti...");
	maxele = fileRows(inputFile);           //maxele : tutti i punti presenti nel file raw

	tot_grid_points= (long int)((data1->widthGrid)*(data1->heightGrid));

	//ALLOCO SEMPRE IL VETTORE dz E POI RIMANE A ZERO NEL CASO DI UN SINGOLO IMPULSO
	
	for(int i= 0; i < dataset_vector.size(); i++)
		dataset_vector[i].dz;



	printf("\n\t\tPunti in input: %ld \n",maxele);
	printf("\t\tPunti Griglia: %ld \n",tot_grid_points);
	printf("\nInizio lettura dati RAW...%s\n", laserRegioniConfig.inputDataFileName);

	fseek(inputFile,0,SEEK_SET);
	//lettura fileASCII
   
	colonne = selezionaCaso(inputFile);
	if (colonne != 3)
	{
		cout<< "Error! The data file format is inappropriate"<< endl;
		return;
	}

	Leggi_SinglePulse_xyz(points, data1, maxele, inputFile);
	fclose(inputFile);

	printf("\n\t\tPunti raw selezionati : %ld\n",data1->numPoints);

	cout<< "Width (min - max): " << data1->xminInput << "-" << data1->xmaxInput << endl;
	cout<< "Height (min - max): " << data1->yminInput << "-" << data1->ymaxInput << endl;
	cout<< "Matrice: " <<data1->widthGrid<< "x" << data1->heightGrid<< "="<< data1->widthGrid*data1->heightGrid<< endl;
	cout << "Grigliatura: " << data1->pelsX << endl;

	if(data1->numPoints == 0) {
		errore(NO_SELECTED_DATA_ERROR, " Punti Selezionati=0", FName, TRUE);
		
	}

	//buildMatriceSparsa(data1, points, data1->widthGrid, data1->heightGrid);
	
	//free(out_file);

	//riempie matrice sparsa
	//Accresci(	Data1, Data1->heightGrid, Data1->widthGrid, Data1->pelsX);

	//freeMatrix(Data1->heightGrid,MatrixInit);
	data1->Xg = (2 * data1->LoLeftX + data1->widthGrid * data1->pelsX) / 2;
	data1->Yg = (2 * data1->LoLeftY + data1->heightGrid * data1->pelsX) / 2;
  
	//if(laserRegioniConfig.tipoOutputASCII == USCITA_ASCII_EN) ;
	//	esporta(Data1);  //$ economia di variabili (dim)?

}

int  Leggi_SinglePulse_xyz(list<Item>&points, DataSet *data, int tot_ele, FILE *inputFile)
{
	extern Configurator laserRegioniConfig;
	int			punti_selezionati= 0, x= 0, y=0 ;
	double			t1, t2, t3;
	double			tempXminTot= tempMin,tempXmaxTot= tempMax, tempYminTot= tempMin, tempYmaxTot= tempMax, tempZmin= tempMin, tempZmax= tempMax;
	double 			tempX, tempY, tempZ;
	long int		j;
    int puntiButtati = 0;
	int check;
	char punto[1000];
	int colonne = 0;
    long int punti = 0;

	tempXminTot = 1000000000;
	tempYminTot = 1000000000;
	tempXmaxTot = -1000;
	tempYmaxTot =-1000;
	tempZmin = 1000000000;
	tempZmax = -1000;
   
    fgets(punto,1000,inputFile);  //butto la prima riga
	

	/* tot_ele contava il numero di righe del file di dati => lo moltiplico per il numero di colonne del file*/

	for ( j = 0; j < tot_ele * 3; j = j + 3 )
		{
			colonne = VerificaPunto(punto,inputFile);
			if(colonne == 3){
				punti++;
				sscanf_s(punto,"%lf %lf %lf",&t1, &t2, &t3);
				tempX =  t1 ;    //  i_array[j]=coordinata Est=x
				tempY =  t2 ;   //  i_array[j+1]=coordinata Nord=y
				tempZ =  t3 ;	//  i_array[j+2]=coordinata z

				if (laserRegioniConfig.showAdditionalInfos)
				{
					tempXminTot=  (tempX > tempXminTot ? tempXminTot : tempX);
					tempXmaxTot = (tempX < tempXmaxTot ? tempXmaxTot : tempX);
					tempYminTot = (tempY > tempYminTot ? tempYminTot : tempY);
					tempYmaxTot = (tempY < tempYmaxTot ? tempYmaxTot : tempY);	
				}

				tempZmin = (tempZ > tempZmin ? tempZmin : tempZ);
				tempZmax = (tempZ < tempZmax ? tempZmax : tempZ);

				if ( tempX >= data->LoLeftX  && tempX < data->UpRightX && tempY >= data->LoLeftY && tempY < data->UpRightY )
				{
					Item new_item;
					//si scaricano tutti i punti all'elemento di griglia minore
					x =(long)( ( tempX - data->LoLeftX ) / data->pelsX);
					y = (long)( ( tempY - data->LoLeftY ) / data->pelsX);
					
					/* Estrapolo i valori di riga e colonna della futura matrice grigliata */
					int col= data->heightGrid - (int)y - 1;
					int row= (int) x;
					
					/* Salvo i valori appena letti in una struct Item e li metto all'interno della lista.
						Faccio corrispondere id a punti selezionati, tale variabile aumenta di iterazione in iterazione. */
					setItem(new_item, tempX, tempY, tempZ, punti_selezionati,std::make_pair(row,col));
					points.push_back(new_item);
					punti_selezionati++;
				}
		    }
			else
				puntiButtati++;
		}

		printf("\n\t\tPunti raw totali : %ld",punti);
		printf("\n\t\tPunti buttati : %ld",puntiButtati);
		writeList(points, "prova_XY.txt");
   
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
int VerificaPunto(char *str,FILE *InFile)
{
	char PrecCar='*';
	unsigned int numero_sottostr=0,i=0;

	fgets(str,1000,InFile);//Prendo una stringa intera

	for ( i = 0; i < strlen(str) ; i++)
	{
		if( str[i] == ',') str[i] = ' ';
		if( (str[i] == ' ' && PrecCar != ' ' && PrecCar != ',' && PrecCar != '*' && PrecCar != 9) || 
			(str[i] == ',' && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*' && PrecCar != 9) ||
			(str[i] == 9  && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*'  && PrecCar != ',' && PrecCar != 9) || 
			(str[i] == 10 && PrecCar != ' ' && PrecCar != ' ' && PrecCar != '*'  && PrecCar != ',' && PrecCar != 9))//separatori spazio o virgola
			numero_sottostr++;//Calcolo le sottostringhe
		PrecCar = str[i];
	}


	return numero_sottostr++;
};

/*void buildMatriceSparsa(DataSet *data1,List& points, int rows, int col)
{
	int emptyCells= 0,m;
	double				v[SHRT_MAX];
	long				ip[SHRT_MAX];
	float				delta;

	List singleCell;
	cout << "QUI" << endl;

	ElementNode *temp = points.getFirstNode();

	for ( ; temp != NULL; temp = temp -> next_element )
	{
		for ( int i = 0; i < rows; i++ )   //scorre le righe
		{ 
			m= i *rows;
			for (int j = 0; j < col; j++ )  //scorro le colonne	
			{
				{
					emptyCells++;
					if (!(singleCell.writeList("Sublist.txt")))
						return;
					//data1->z[m+j] = QUOTA_BUCHI;
					
				}
				else
				{
					cout << "QUI else" << endl;
				}
				/*if ( !mtemp[i][j].est )   //controllo se la cella ij contiene valori
				{
					celleVuote++;
					num = 0;
					Data->z[m+j] = QUOTA_BUCHI;
				}
				else
				{
					if ( !mtemp[i][j].next)
					{           
						// unico punto
						num = 1;
						if( mtemp[i][j].tipo == 'L')   // accetto solo Last
							Data->z[m+j]  = (float)mtemp[i][j].valore; // /(float)100; 
	//						matSparsa[i][j] = (short) mtemp[i][j].valore; 
						    
					}
					else	
					{						
						p = &mtemp[i][j]; 
						num = 1;
						v[0] =  mtemp[i][j].valore;
						k = 0;

						while ( (*p).next )
						{ 
							if ( p->tipo == 'L' && p->valore != QUOTA_BUCHI)
							{
								v[k] =  p->valore;
								k++;
							}
							p = p->next;						  
						}

						num = k;
						if ( num )   // else erano solo First num = 0
						{
						  
							ordina( v, ip, num, num, 1, 0 );  //ordinamento decrescente
	//						OrdinaVet ( v, ip, num, num, 1, 0 );  //ordinamento decrescente

							delta = (float)(v[ip[num-1]]-v[ip[0]]);
	//APRILE05:OUTLIER  se delta > di sono outlier?
							if ( fabs(delta) > laserRegioniConfig.dislivelloMatriceSparsa)
							{
								Data->z[m+j] = (float)v[ip[num-1]]; // /(float)100; // Punto più alto ( ricerca edifici ) 
	//							matSparsa[i][j]=(short)(v[ip[num-1]]); // Punto più alto ( ricerca edifici )  //MAGGIO05
	//							matSparsa[i][j]=(short)(v[ip[0]]);
							}
							else
							{
								if ( num%2 )
									Data->z[m+j] = (float)v[ip[num/2]]; // /(float)100;
	//								matSparsa[i][j] = (short) (v[ip[num/2]]);
								else
								{
									// Data->z[m+j] = (float)v[ip[num/2]]; // /(float)100;
	//								matSparsa[i][j] = (short) v[ip[num/2]];
									Data->z[m+j] = (float) ((v[ip[num/2]]+v[ip[num/2-1]])/2);
								}
							}
						}  // if num
					}      // else su non unico punto
				}          // else su cella non vuota
				MaxD = num > MaxD ? num : MaxD;
				if(num > 255) num = 255;
	//			*(densita+i*Walt+j) = (unsigned char)num;
				*(densita+m+j) = (unsigned char)num;
			}             //for j
		}                 //for i
	}
		if (!(singleCell.writeList("Sublist.txt")))
			return;
		cout << "empty cells:"<< emptyCells << endl;
		return;
};*/