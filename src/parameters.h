#pragma once
#include "config_file.h"
#include "usefull_file.h"
#include "error.h"
#include "const.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>


/*------------------------------------------------------------*\
	Definisce l'elemento generico del file di configurazione
\*------------------------------------------------------------*/
 struct ParamElem
{
	char 			*name;			// Prefisso identificativo	
	int				type;			// Tipo dato				
	int				lenght;			// Lunghezza (per char)		
	int				state;			// Stato					
	void			*value;			// Riferimento alla memoria	
	/* La versione della profssa aveva il tipo void che però era incompatibile
		il tipo richiesto dalla funzione per il controllo degli errori in errore.c */

	// Funzione per la validazione dei dati (OPZIONALE)
	int (*validate)(const void *, int paramState);	
};

/*--------------------------------------------------------------*\
	Definizione struttura dati di configurazione del programma
\*--------------------------------------------------------------*/
typedef struct Configurator 
{
	char		projectName[MAX_STR_LEN];			//Nome progetto e file di log
	char		inputDataFileName[MAX_STR_LEN];	//Nome file dati di input
//	char		inputEstraiUnicoCFGFileName[MAX_STR_LEN]; //Nome file CFG per i dati di input RAW
//	int			dimImmagine;		//Dimensione immagine 1=Tutta, 0=Window
	float		sogliaCluster;		//Soglia Cluster
	int			dimRegione;			//Dimensione minima regione
	int         dimFiltro;          //Dimensione filtro gradiente (Sobel)
	int			tipoOutputBMP;		//Tipo di output BMP (1=8bits, 0=16bits)
	int			tipoUscita;		    //Tipo di output LEVEL da 1 a 4
	                                //LEVEL_1 : fald, Alto
	                                //LEVEL_2 : Zspline, InputSPline, GreenSpline
	                                //LEVEL_3 : gradiente, pendenza, pianoLocale, densita
	                                //LEVEL_4 : tutti i valori dei punti raw (CLASSE)
	int			tipoOutputASCII;	//Tipo di output ASCII(0=NO 1=EN 2=RC)
	int			tipoRicerca;		//Tipo di ricerca (0=DTM 1=Edifici)
	int			tipoLastFirst;		//Tipo di dato in input (1= 1 solo raggio,2= LastFirst)
	int		    norma;				//Sigma X
	float		sqmZ;				//Sigma Y
//	float		sigmaZ;				//Sigma Z
	float		sogliaPianoMaxResiduo;	//Soglia per massimo residuo
	//TODO: da verificare questo parametro: solo lo 0 o diverso da 0 hanno senso
//	int			maxIterazioni;		//Massimo numero di iterazioni
	float		sogliaGradContornoColmi;	//Soglia gradiente contorno e colmi
	float		sogliaGradOrientazione;		//Soglia gradiente orientazione
	int			numPartizioni;		//Numero di partizioni
//	int			ordineLastFirst;	//Ordine Last Pulse-First Pulse (0=First 1=Last)
	float		deltaFirstLast;		//Delta H tra First e Last Pulse
	int			tipoSpline;			//Tipo Spline (0=Bilineari 1=Bicubiche)
	double		splineParamG;		//Parametro G per Spline(in_metri)
	double		splineParamW;		//Parametro W per Spline(in_metri)
	double      splinePassoEst;		//Parametro passo Est per Spline(in_metri)
	double      splinePassoNord;	//Parametro passo Nord per Spline(in_metri)
	double      splineLambda;		//Parametro passo lambda per Spline
	int			splineNumIterazioni;//Numero iterazioni Spline
//	int			echo;				//1= una risposta, 2=FirstLast
	int			upLeftR;			//Coordinate window
	int			upLeftC;			//Coordinate window
	int			lowRightR;			//Coordinate window
	int			lowRightC;			//Coordinate window
    float       soglia_tt;          //define per la classificazione
    float       soglia_tt2;          //define per la classificazione
    float       CriteriTerreno;          //define per la classificazione APRRILE05bis
    float       soglia_ss1;          //define per la classificazione
    float       soglia_ss2;          //define per la classificazione APRILE05bis
    float       soglia_ssec;          //define per la classificazione APRILE05bis
    float       PercentualeFalde;     //define per la % di falde presenti in un edificio
    float       soglia_ueb;          //define per la classificazione
    float       percFirstTT;          //define per la classificazione
    float       DislivelloTT;          //define per la classificazione
    float       ext_terreno;          //define per la classificazione
    float       soglia_ingombro;          //define per la classificazione
    float       soglia_industriale;          //define per la classificazione
    float       limite_punti;          //define per la classificazione
	char		paletteFileName[MAX_STR_LEN];	//Nome file palette (opzionale)
	int			dislivelloMatriceSparsa;	//Valore di soglia di dislivello per la costruzione 
											//della matrice sparsa
	int			isInputDataRAW;
	int			showAdditionalInfos;		//Per visualizzare informazioni supplementari sulla lettura dei dati
	float		loLeftX;				//coordinata X del pto in basso a sinistra della finestra da elaborare
	float		loLeftY;				//coordinata Y del pto in basso a sinistra della finestra da elaborare
	short int	gridWidth;				//dimensione in pixel della griglia da elaborare
	short int	gridHeight;				//dimensione in pixel della griglia da elaborare
	float			gridUnit;				//dimensione della cella della griglia
//	int			jwgContornoToposys;		//Flag per stabilire se eseguire le routine jwg
//	int			jwgNumClasse;			//Numero classe da elaborare
    int         uscitaRisultatiClassificazione;              //risultato classificazione su 1 file con codice
	                                    //o con file separati
	char		ransacConfigFile[MAX_STR_LEN]; //Nome file di configurazione Ransac
	int			stimaFaldaRansac;		//Se true esegue il ransac su tutta la classe di punti in CalcolaFalda
    double      CodiceLast;             //ordine First/Last

	double RansacThreshold;                //soglia per la definizione della fascia di consenso attorno al piano individuato
    double RansacProb;                     //probabilita' di trovare un piano privo di errori
    double RansacGrosErr;                //probabilita' di avere errori grossolani negli insiemi di punti (standard 0.5)
    int RansacStop;                  //numero di punti minimo per cui fermare l'elaborazione del RANSAC
    int RansacMinNumPointsInPlane;         //numero minimo di punti in un piano


}Configurator;

/*-------------------------------------------*\
	Definizione variabile globale per
	la configurazione del programma
\*-------------------------------------------*/
//extern Configurator		laserRegioniConfig;
//int					numParams;

/*-------------------------------------------*\
	Prototipi di funzioni
\*-------------------------------------------*/

char * selectFormat(int tipo);

int validateSogliaCluster(const void * value, int paramState);  
int validateDimMinRegione(const void * value, int paramState);  
int readConfFile(const char *confFileName,int stopWhenError);
int validateTipoOutputBMP(const void * value,int paramState);
int validateTipoOutput(const void * value,int paramState);
int validateTipoOutputASCII(const void * value,int paramState);
int validateNumPartizioni(const void * value,int paramState);
int validateTipoRicerca(const void * value,int paramState);
int validateOrdineLF(const void * value,int paramState);
int validateTipoSpline(const void * value,int paramState);
//int validateEcho(const void * value,int paramState);
int validateTipoDatoLF(const void * value,int paramState);
int validateDimFiltro(const void * value,int paramState);
int validateNomeFileCFGDatiRAW(const void * value, int paramState);
int validateSogliaPianoMaxResiduo(const void * value, int paramState);  
int validateSogliaTT(const void * value, int paramState);
int validateSogliaTT2(const void * value, int paramState);
int validateSogliaSS1(const void * value, int paramState);
int validateSogliaSSEC(const void * value, int paramState);
int validateCriteriTerreno(const void * value, int paramState);
int validateSogliaSS2(const void * value, int paramState);  //APRILE05bis
int validateSogliaUEB(const void * value, int paramState);
int validateSogliaINGOMBRO(const void * value, int paramState);
int validatePercFirstTerreno(const void * value, int paramState);
int validateDislivelloTerreno(const void * value, int paramState);
int validateExtTerreno(const void * value, int paramState);
int validateSogliaINDUSTRIALE(const void * value, int paramState);
int validatePercentualeFalde(const void * value, int paramState);
int validateSogliaLIMITE_PUNTI(const void * value, int paramState);
int validatePaletteFile(const void * value, int paramState);
int validateDislivelloMatriceSparsa(const void * value, int paramState);
int validateLoLeftX(const void * value, int paramState);
int validateLoLeftY(const void * value, int paramState);
int validateGridWidth(const void * value, int paramState);
int validateGridHeight(const void * value, int paramState);
int validateGridUnit(const void * value, int paramState);
int validateIsInputDataRAW(const void * value, int paramState);
int validateShowAdditionalInfos(const void * value, int paramState);
int validateJWGContornoTOPOSYS(const void * value, int paramState);
int validateJWGNumClasse(const void * value, int paramState);
int validateJWGOutputOriginali(const void * value, int paramState);
int validateRansacConfigFile(const void * value, int paramState);
int validateStimaFaldaRansac(const void * value, int paramState);
//int printAllParameters();
int validateuscitaRisultatiClassificazione(const void * value, int paramState);
int validateCodiceLast(const void * value, int paramState);
int validateSogliaGradContornoColmi(const void * value, int paramState);
int validateSogliaGradOrientazione(const void * value, int paramState);
int validateDeltaFirstLast(const void * value, int paramState);
int validateSplineG(const void * value, int paramState);
int validateSplineW(const void * value, int paramState);
int validateSplinePassoEst(const void * value, int paramState);
int validateSplinePassoNord(const void * value, int paramState);
int validateSplineLambda(const void * value, int paramState);
int validateSplineNumIterazioni(const void * value, int paramState);
int validateRansacThreshold(const void * value, int paramState);
int validateRansacProb(const void * value, int paramState);
int validateRansacGrosErr(const void * value, int paramState);
int validateRansacStop(const void * value, int paramState);
int validateRansacMinNumPointsInPlane(const void * value, int paramState);
int validate_sqmZ (const void * value, int paramState);
int validateNormalizzazione (const void * value, int paramState);