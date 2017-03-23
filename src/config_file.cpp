#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

#include "get_line.h"
#include "const.h"
#include "config_file.h"
#include "parameters.h"
#include "error.h"
#include "defs.h"

using namespace std;

/*-------------------------------*\
	Definizioni costanti = e #
\*-------------------------------*/
#define comment '#'
#define equal '='


/*-----------------------------------------*\
	Lista Parametri da leggere
\*-----------------------------------------*/

Configurator		laserRegioniConfig;

ParamElem params[] = {
	{"NomeProgetto", TIPO_STR, MAX_STR_LEN, PARAM_ASSENTE, laserRegioniConfig.projectName},
	{"NomeFileInDati", TIPO_STR, MAX_STR_LEN, PARAM_ASSENTE, laserRegioniConfig.inputDataFileName},
	{"SogliaCluster", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.sogliaCluster,validateSogliaCluster},
	{"DimMinRegione", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.dimRegione,validateDimMinRegione},
	{"DimFiltro", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.dimFiltro, validateDimFiltro},
	{"TipoOutputBMP", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.tipoOutputBMP, validateTipoOutputBMP},
	{"TipoUscita", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.tipoUscita, validateTipoOutput},
	{"TipoOutputASCII", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.tipoOutputASCII, validateTipoOutputASCII},
	{"norma", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.norma,validateNormalizzazione},
	{"sqmZ", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.sqmZ,validate_sqmZ},
	{"SogliaPianoMaxResiduo", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.sogliaPianoMaxResiduo,validateSogliaPianoMaxResiduo},
	{"SogliaGradContornoColmi", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.sogliaGradContornoColmi,validateSogliaGradContornoColmi},
	{"SogliaGradOrientazione", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.sogliaGradOrientazione,validateSogliaGradOrientazione},
	{"NumPartizioni", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.numPartizioni, validateNumPartizioni},
	{"TipoRicerca", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.tipoRicerca, validateTipoRicerca},
	{"TipoDatoLF", TIPO_INT, 0 , PARAM_ASSENTE, &laserRegioniConfig.tipoLastFirst, validateTipoDatoLF},
	{"TipoSpline", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.tipoSpline, validateTipoSpline},
	{"SplineG", TIPO_DOUBLE, 0, PARAM_ASSENTE, &laserRegioniConfig.splineParamG,validateSplineG},
	{"SplineW", TIPO_DOUBLE, 0, PARAM_ASSENTE, &laserRegioniConfig.splineParamW,validateSplineW},
	{"SplinePassoEst", TIPO_DOUBLE, 0, PARAM_ASSENTE, &laserRegioniConfig.splinePassoEst,validateSplinePassoEst},
	{"SplinePassoNord", TIPO_DOUBLE, 0, PARAM_ASSENTE, &laserRegioniConfig.splinePassoNord,validateSplinePassoNord},
	{"SplineLambda", TIPO_DOUBLE, 0, PARAM_ASSENTE, &laserRegioniConfig.splineLambda,validateSplineLambda},
	{"SplineNumIterazioni", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.splineNumIterazioni,validateSplineNumIterazioni},
	{"DeltaFirstLast", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.deltaFirstLast,validateDeltaFirstLast},
	{"UPLeftR", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.upLeftR},
	{"UPLeftC", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.upLeftC},
	{"LOWRightR", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.lowRightR},
	{"LOWRightC", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.lowRightC},
	{"Palette", TIPO_STR, MAX_STR_LEN, PARAM_ASSENTE, &laserRegioniConfig.paletteFileName, validatePaletteFile},
	{"defineCRITERITERRENO", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.CriteriTerreno,validateCriteriTerreno},
	{"defineSOGLIA_SS1", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.soglia_ss1,validateSogliaSS1},
	{"defineSOGLIA_SS2", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.soglia_ss2,validateSogliaSS2},
	{"defineSOGLIA_SSEC", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.soglia_ssec,validateSogliaSSEC},
	{"defineEXT_TERRENO", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.ext_terreno,validateExtTerreno},
	{"definePERC_FIRST_TERRENO", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.percFirstTT,validatePercFirstTerreno},
	{"defineDISLIVELLO_TERRENO", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.DislivelloTT,validateDislivelloTerreno},
	{"defineSOGLIA_INGOMBRO", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.soglia_ingombro,validateSogliaINGOMBRO},
	{"defineSOGLIA_INDUSTRIALE", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.soglia_industriale,validateSogliaINDUSTRIALE},
	{"defineLIMITE_PUNTI", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.limite_punti,validateSogliaLIMITE_PUNTI},
	{"defineSOGLIA_TT2", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.soglia_tt2,validateSogliaTT2},
	{"defineSOGLIA_UEB", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.soglia_ueb,validateSogliaUEB},
	{"defineSOGLIA_TT", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.soglia_tt,validateSogliaTT},
	{"definePERCENTUALEFALDE", TIPO_FLOAT, 0, PARAM_ASSENTE, &laserRegioniConfig.PercentualeFalde,validatePercentualeFalde},
	{"dislivelloMatriceSparsa", TIPO_INT, 0 , PARAM_ASSENTE, &laserRegioniConfig.dislivelloMatriceSparsa, validateDislivelloMatriceSparsa},
	{"LoLeftX", TIPO_FLOAT, 0 , PARAM_ASSENTE, &laserRegioniConfig.loLeftX, validateLoLeftX},
	{"LoLeftY", TIPO_FLOAT, 0 , PARAM_ASSENTE, &laserRegioniConfig.loLeftY, validateLoLeftY},
	{"GridWidth", TIPO_SHORT, 0 , PARAM_ASSENTE, &laserRegioniConfig.gridWidth, validateGridWidth},
	{"GridHeight", TIPO_SHORT, 0 , PARAM_ASSENTE, &laserRegioniConfig.gridHeight, validateGridHeight},
	{"GridUnit", TIPO_FLOAT, 0 , PARAM_ASSENTE, &laserRegioniConfig.gridUnit, validateGridUnit},
	{"showAdditionalRAWInfos", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.showAdditionalInfos, validateShowAdditionalInfos},
	{"ransacConfigFile", TIPO_STR, MAX_STR_LEN, PARAM_ASSENTE, &laserRegioniConfig.ransacConfigFile, validateRansacConfigFile},
	{"stimaFaldaRansac", TIPO_INT, 0, PARAM_ASSENTE, &laserRegioniConfig.stimaFaldaRansac, validateStimaFaldaRansac},
	{"uscitaRisultatiClassificazione", TIPO_INT, 0 , PARAM_ASSENTE, &laserRegioniConfig.uscitaRisultatiClassificazione, validateuscitaRisultatiClassificazione},
	{"CodiceLast", TIPO_DOUBLE, 0, PARAM_ASSENTE, &laserRegioniConfig.CodiceLast,validateCodiceLast},
	{"RansacThreshold", TIPO_DOUBLE, 0, PARAM_ASSENTE, &laserRegioniConfig.RansacThreshold,validateRansacThreshold},
	{"RansacProb", TIPO_DOUBLE, 0, PARAM_ASSENTE, &laserRegioniConfig.RansacProb,validateRansacProb},
	{"RansacGrosErr", TIPO_DOUBLE, 0, PARAM_ASSENTE, &laserRegioniConfig.RansacGrosErr,validateRansacGrosErr},
	{"RansacStop", TIPO_INT, 0 , PARAM_ASSENTE, &laserRegioniConfig.RansacStop, validateRansacStop},
	{"RansacMinNumPointsInPlane", TIPO_INT, 0 , PARAM_ASSENTE, &laserRegioniConfig.RansacMinNumPointsInPlane, validateRansacMinNumPointsInPlane},
	};

ConfigFile::ConfigFile()
{
	// Empty configuration file
	sof_ = NULL;
}

ConfigFile::~ConfigFile()
{
	for( StringNode *next = sof_; sof_ != NULL; sof_ = next )
	{
		next = sof_->next;
		free( sof_->line );
		delete sof_;
	}
}

/*Funzione per la stampa del file di tipo config */

void ConfigFile::print() const
{
	cout<<"I'm printing a Configuration file" << endl;
	for( StringNode *sn = sof_; sn != NULL; sn = sn->next )
		cout << sn -> line << "\n"<< endl;
	cout << endl;
}


/* Funzione booleana per controllare il caricamento del file
	e che impone anche i settaggi indicati nel file stesso*/

bool ConfigFile::load( const char *filename )
{
	FILE *fp  = fopen(filename, "r");
	if (fp == NULL)
	{
		/*Verifica apertura di un file non vuoto*/
		cout << "The configuration file was empty"<< endl;
		return false;
	}
	
	/* Il file non è risultato vuoto, si procede con la lettura delle
	  impostazioni desiderate*/

	char *line;
	StringNode *sn = NULL;
	int read_value= 0;


	cout << "I'm reading the configuration file" << endl;

	while(( line = getLine(fp) ) != NULL)
	{
		/* Creo la lista contenente tutte le righe */
		if( sn == NULL )
		{
			// Inizializzo il primo nodo della lista
			sof_ = new StringNode();
			sn = sof_;
		}
		else 
		{
			// inizializzo il nodo successivo a quello attuale e impongo l'attuale nodo come il successivo
			sn->next = new StringNode();
			sn = sn->next;
		}
		/* Copio il valore *char che sto leggendo nel line del nodo della lista
			ed impongo che il nodo successivo a quello attuale sia NULL */
		sn->line = line;
		sn->next = NULL;
	}
	cout << "I create a list" << endl;
	// Inizializzo a 0 la variabile pos che utilizzerò per cercare "="
	size_t pos= 0;
		/* Creata la lista passo ad analizzare il singolo nodo */
		for( sn = sof_; sn != NULL; sn = sn->next )
		{
			/* Verifico che il primo carattere della linea sia o meno "#" */
			if (sn -> line[0] == comment)
			{
				//cout << "This row was a comment:\n"<< sn -> line << endl;
			}
				// Scarto eventuali linee vuote
			else if( sn -> line == " ")
			{
				//cout << "This row was empty" << endl;
			}
			// Passo alla lettura di righe non nulle e non utilizzate per commenti
			else
			{
				/* Dichiaro una stringa che di appoggio per le righe che risultano 
					effettuare un settaggio; successivamente individuo l'indice corrispondente
					alla posizione di "=" */
				string valid_line( sn -> line);
				pos = valid_line.find(equal);
				// Se non vi è presente un'assegnazione (ovvero un "=") scarto la riga
				if(valid_line.find(equal) == string::npos)
				{
					//cout << "This row was without usefull information:\n" << sn -> line << endl; 
				}
				// Se vi è un'assegnazione verifico che essa sia valida e la elaboro
				else
				{
					/* Attraverso il seguente rapporto verifico quanti sono gli
						elementi da inizializzare */
					int numParams = sizeof(params) / sizeof(ParamElem);
					/* Creo una sottostringa, che va da zero a "=", per confrontare il nome 
						del parametro contenuto nel file con quelli presenti nella lista dei parametri "settabili".
						Converto la sottostringa in un *char per effettuare il confronto. */
					string name_compare = valid_line.substr(0,pos);
					const char *n_compare = name_compare.c_str();
					for (int i = 0; i < numParams; i++)
					{
						// Il parametro che si vuole settare non esiste

						if (strncmp(n_compare, params[i].name, strlen(params[i].name)) != 0)
						{
							continue;
						}
						
						/* Se il parametro esiste creo una variabile *char per selezionare il tipo
							corrispondente a quello richiesto dal parametro. */
						const char *input_type = selectFormat(params[i].type);
						if (input_type == NULL)
						{
							cout << " Parameter type it was not recognized inside the line:\n" << valid_line << endl;
							continue;
						}
						/* Se riconosco il tipo di input passo a verificare se esso è già settato o meno */
						if (params[i].state != PARAM_ASSENTE)
						{
							cout<< "The parameter it was already set; this line is ignorated:\n"<< valid_line<< endl;
							continue;
						}
						/* Se il parametro non è stato già settato verifico la presena di un
							eventuale spazio dopo l' "=". Creo dunque una sottosrtringa di un singolo carattere
							successivo a "=" e la confronto con  " ". */
						string space = valid_line.substr(pos+1, 1);
						string comp= " ";
						if(space == comp)
						{
							/* Creo una sottostringa per contenere il valore dell'impostazione che si vuole eseguire;
								se è presente uno spazio la sottostringa relativa al valore da settare partirà
								da 2 posizioni dopo l "=" . Successivamente converto la sottostringa in  un *char 
								per effettuare il confronto con l'attributo valore del parametro. */
							string value = valid_line.substr(pos + 2);
							const char *value_to_insert = value.c_str();
							/* Confronto il valore che voglio inserire con quello preimpostato. */
							read_value = sscanf_s(value_to_insert, input_type, params[i].value);
							if ((read_value != 0) && (read_value != EOF))
							{
								/* Se il parametro che voglio settare ed il parametro preimpostato hanno lo stesso valore
									e il valore che voglio inserire è diverso da EOF allora indico che il valore del parametro 
									è presente. */
								params[i].state = PARAM_PRESENTE;
								//La sscanf ha restituito qualcosa!
								if (params[i].validate != NULL)
								{
									if (params[i].validate(params[i].value,PARAM_PRESENTE) != 0)
									{
										errore(PARAM_VALIDATION_ERROR, (char*)params[i].value, params[i].name, false); 
										params[i].state = PARAM_ERROR;
									}
								}
							}
						}
						else 
						{
							/* Eseguo le stesse operazioni di prima, questa volta la 
								sottostringa partirà dal carattere successivo a "=". */
							string value = valid_line.substr(pos + 1);
							const char *value_to_insert = value.c_str();
							read_value = sscanf_s(value_to_insert, input_type, params[i].value);
							if ((read_value != 0) && (read_value != EOF))
							{
								params[i].state = PARAM_PRESENTE;
								//La sscanf ha restituito qualcosa!
								if (params[i].validate != NULL)
								{
									if (params[i].validate(params[i].value,PARAM_PRESENTE) != 0)
									{
										errore(PARAM_VALIDATION_ERROR, (char*)params[i].value, params[i].name, false); 
										params[i].state = PARAM_ERROR;
									}
								}
							}
						}
					}
				}
				}
			}
		cout<< "Configuration file read with success:\n"<< filename<< endl;
		fclose(fp);
 		return true;
	}



/* Funzione booleana per il controllo del salvataggio del file*/

bool ConfigFile::save( const char *filename )
{
  FILE *fd = fopen(filename, "w");

  // Can't open the file
  if( fd == NULL )
    return false;
  
  for( StringNode *sn = sof_; sn != NULL; sn = sn->next )
    fprintf(fd, "%s\n", sn->line );
  fprintf(fd, "\n");
  
  fclose(fd);
  return true;
}

/*
int ConfigFile::printAllParameters()
{
	int i;
	char * format;
	int numParams = sizeof(params) / sizeof(ParamElem);
	for(i=0; i<numParams; i++)
	{
		printf("%s=", params[i].name);
		format = selectFormat(params[i].type);
		switch (params[i].type)
		{
			case TIPO_INT:
				printf(format , *(int *)(params[i].value));
				break;
			case TIPO_FLOAT:
				printf(format , *(float *)(params[i].value));
				break;
			case TIPO_DOUBLE:
				printf(format , *(double *)(params[i].value));
				break;
			case TIPO_LONG:
				printf(format , *(long *)(params[i].value));
				break;
			case TIPO_SHORT:
				printf(format , *(short int *)(params[i].value));
				break;
			default:
				printf(format , params[i].value);
		}
		
		printf("\n");
	}
	return SUCCESS;
}*/