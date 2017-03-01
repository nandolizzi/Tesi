#include "parameters.h"
#include "config_file.h"
#include "usefull_file.h"
#include "error.h"
#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>
#include <string.h>

/*#define	 SUCCESS	0	
#define  ERROR	(!SUCCESS)*/

/*-------------------------------------------------------------*\
	Nome routine:
	selectFormat

	Da un tipo di dato, ritorna il suo formato di input/output
	da utilizzarsi con le funzioni di I/O

	Parametri:
	<INPUT> int tipo	-	Tipo di dato 

	Valore di ritorno:
	Stringa da utilizzarsi con le funzioni di I/O per formattare
	la scrittura oppure NULL se il tipo non è riconosciuto
\*-------------------------------------------------------------*/
char * selectFormat(int tipo)
{
	char *ret;

	switch(tipo)
	{
		case TIPO_CHAR	 : ret = "%c";	break;
		case TIPO_STR	 : ret = "%s";	break;
		case TIPO_SHORT	 : ret = "%hd";	break;
		case TIPO_USHORT : ret = "%hu";	break;
		case TIPO_INT	 : ret = "%d";	break;
		case TIPO_UINT	 : ret = "%u";	break;
		case TIPO_LONG	 : ret = "%ld";	break;
		case TIPO_ULONG	 : ret = "%uld";break;
		case TIPO_LLONG	 : ret = "%dl";	break;
		case TIPO_ULLONG : ret = "%ul";	break;
		case TIPO_FLOAT	 : ret = "%f";	break;
		case TIPO_DOUBLE : ret = "%lf";	break;
		case TIPO_LDOUBLE: ret = "%le";	break;
		default: ret = NULL;	break;

	}

	return(ret);
}


/*-------------------------------------------------------------------*\
	Nome routine:
	funzione di validazione dei dati

	Parametri:
	<INPUT> const void * value	-	Puntatore al valore del parametro
	<INPUT> int paramState		-	Stato del parametro: può essere ASSENTE
									o ERRORE

	NB: nel caso di parametro assente il valore *(typecast *)value è 
	comunque 0 quindi non è possibile distinguere questo valore iniziale 
	da un possibile	valore impostato a 0. Per questo è importante 
	testare il valore di paramState per verificare se il parametro è 
	stato inizializzato o meno.
\*-------------------------------------------------------------------*/
int validateSogliaCluster(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = (float) SOGLIA_CLUSTER;
	}

	return SUCCESS;
}

int validateDimMinRegione(const void * value, int paramState)
{
	int fVal = *(int *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(int *)value = DIM_MIN_REGIONE;
	}

	return SUCCESS;
}


int validateNumPartizioni (const void * value, int paramState)
{
	int intVal = *(int *) value;

	if ((intVal != 8) && (intVal != 12))
	{
		printf("Tipo di output BMP '%d' non riconosciuto.\n Impostato a 8 \n", intVal);
		*(int *)value = 8;
    }
	else if ((paramState == PARAM_ASSENTE) )
	    *(int *)value = NUM_PARTIZIONI;

	return SUCCESS;
}

int validateTipoOutputBMP(const void * value, int paramState)
{
	int intVal = *(int *)value;

	if ((intVal != 0) && (intVal != 1))
	{
		printf("Tipo di output BMP '%d' non riconosciuto.\n Impostato a 1 \n", intVal);
		*(int *)value = 1;       
	}
	else if ((paramState == PARAM_ASSENTE) )
	    *(int *)value = OUTPUT_BMP;

	return SUCCESS;
}

int validateTipoOutput(const void * value, int paramState)
{
	int intVal = *(int *)value;

	if ((intVal < 0) && (intVal >5))
	{
		printf("Tipo di output '%d' non riconosciuto.\n Impostato a 0 \n", intVal);
		*(int *)value = 0;       
	}
	else if ((paramState == PARAM_ASSENTE) )
	    *(int *)value = OUTPUT;


	return SUCCESS;
}
int validateDimFiltro(const void * value, int paramState)
{
	int intVal = *(int *)value;

	if ((intVal !=3) && (intVal !=5) && (intVal !=7) && (intVal !=9))
	{
		printf("Tipo di output DimFiltro '%d' non riconosciuto.\nImpostato a 3\n", intVal);
		*(int *)value = 3;       
	}
	else if ((paramState == PARAM_ASSENTE) )
	    *(int *)value = DIM_FILTRO;

	return SUCCESS;
}


int validateTipoSpline(const void * value, int paramState)
{
	int intVal = *(int *)value;


	if ((intVal != 0) && (intVal != 1))
	{
		printf("Tipo Spline '%d' non riconosciuto.\nImpostato bilineari (0)\n", intVal);
	    *(int *)value = 0;
	}
    else if ((paramState == PARAM_ASSENTE) )
	    *(int *)value = TIPO_SPLINE;


	return SUCCESS;
}


int validateTipoOutputASCII(const void * value, int paramState)
{
	int intVal = *(int *)value;

	if ((intVal != 0) && (intVal != 1))
	{
		printf("Tipo di output ASCII '%d' non riconosciuto.\nImpostato a 0 (export)\n", intVal);
		*(int *)value = 0;       
	}
    else if ((paramState == PARAM_ASSENTE) )
	    *(int *)value = OUTPUT_ASCII;

	return SUCCESS;
}

int validateTipoRicerca(const void * value, int paramState)
{
	int intVal = *(int *)value;

	if ((intVal != 0) && (intVal != 1) && (intVal != 2))
	{
		printf("Tipo di ricerca '%d' non riconosciuto.\nImpostato 1 (DTM)\n", intVal);
	    *(int *)value = 1;
	}
    else if ((paramState == PARAM_ASSENTE) )
	    *(int *)value = TIPO_RICERCA;

	return SUCCESS;
}

int validateOrdineLF(const void * value, int paramState)
{
	int intVal = *(int *)value;

	if ((paramState == PARAM_ASSENTE) || ((intVal != 0) && (intVal != 1)))
	{
		printf("Ordine Last-First Pulse '%d' non riconosciuto.\nVerificare la configurazione\n", intVal);
		return ERROR;
	}

	return SUCCESS;
}

int validateTipoDatoLF(const void * value, int paramState)
{
	int intVal = *(int *)value;

	//Questo parametro nel caso di dati RAW ASC viene letto direttamente dal file.
	//Negli altri casi viene utilizzato invece il valore qui impostato o quello letto
	//da configurazione
//	 *(int *)value = 1;
	return SUCCESS;
}

int validateNomeFileCFGDatiRAW(const void * value, int paramState)
{
	char * strVal = (char *) value;

	strcpy_s(strVal,2, "\0");

	//Impostare questo parametro non ha importanza perché comunque verrà 
	//letto da file di configurazione per i dati raw
	return SUCCESS;
}


int validatePercentualeFalde(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = (float)PERCENTUALEFALDE;
	}

	return SUCCESS;
}

int validateSogliaGradContornoColmi(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = SOGLIA_GRAD_CONTORNO;
	}

	return SUCCESS;
}
int validateSogliaGradOrientazione(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = SOGLIA_GRAD_ORIENTAMENTO;
	}

	return SUCCESS;
}

int validateDeltaFirstLast(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = (float)DELTA_FIRSTLAST;
	}

	return SUCCESS;
}

int validateSogliaPianoMaxResiduo(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = (float)SOGLIA_PIANO_MAX_RESIDUO;
	}

	return SUCCESS;
}

int validateSogliaTT(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = SOGLIA_TT;
	}

	return SUCCESS;
}


int validateSogliaTT2(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = SOGLIA_TT2;
	}

	return SUCCESS;
}
int validateSogliaSS1(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = SOGLIA_SS1;
	}

	return SUCCESS;
}

int validateSogliaSSEC(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = SOGLIA_SSEC;
	}

	return SUCCESS;
}

int validateCriteriTerreno(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = CRITERITERRENO;
	}

	return SUCCESS;
}

//APRILE05bis
int validateSogliaSS2(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = SOGLIA_SS2;
	}

	return SUCCESS;
}
int validateExtTerreno(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = EXT_TERRENO;
	}

	return SUCCESS;
}
int validatePercFirstTerreno(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = PERC_FIRST_TERRENO;
	}

	return SUCCESS;
}
int validateDislivelloTerreno(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = DISLIVELLO_TERRENO;
	}

	return SUCCESS;
}

int validateSogliaINGOMBRO(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = SOGLIA_INGOMBRO;
	}

	return SUCCESS;
}
int validateSogliaUEB(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = SOGLIA_UEB;
	}

	return SUCCESS;
}
int validateSogliaINDUSTRIALE(const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = SOGLIA_INDUSTRIALE;
	}

	return SUCCESS;
}
int validateSogliaLIMITE_PUNTI (const void * value, int paramState)
{
	float fVal = *(float *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(float *)value = LIMITE_PUNTI ;
	}

	return SUCCESS;
}

int validatePaletteFile(const void * value, int paramState)
{
	char * strVal = (char *) value;

	if (paramState == PARAM_ASSENTE)
	{
		strcpy_s(strVal,200,"palette");
	}

	return SUCCESS;
}

int validateDislivelloMatriceSparsa(const void * value, int paramState)
{
	int intVal = *(int *)value;

	if (paramState == PARAM_ASSENTE)
	{
		*(int *) value = DISLIVELLO_MAT_SPARSA;
		return SUCCESS;
	}

	return SUCCESS;
}

int validateLoLeftX(const void * value, int paramState)
{
	long intVal = *(long *) value;

	if (paramState == PARAM_ASSENTE)
	{
		*(long *) value = NONE;
	}
	return SUCCESS;
}

int validateLoLeftY(const void * value, int paramState)
{
	long intVal = *(long *) value;

	if (paramState == PARAM_ASSENTE)
	{
		*(long *) value = NONE;
	}
	return SUCCESS;
}

int validateGridWidth(const void * value, int paramState)
{
	short int intVal = *(short int *) value;

	if (paramState == PARAM_ASSENTE)
	{
		*(short int *) value = NONE;
	}
	return SUCCESS;
}

int validateGridHeight(const void * value, int paramState)
{
	short int intVal = *(short int *) value;

	if (paramState == PARAM_ASSENTE)
	{
		*(short int *) value = NONE;
	}
	return SUCCESS;
}

int validateGridUnit(const void * value, int paramState)
{
	int intVal = *(int *) value;

	if (paramState == PARAM_ASSENTE)
	{
		*(int *) value = NONE;
	}
	return SUCCESS;
}



int validateShowAdditionalInfos(const void * value, int paramState)
{
	int intVal = *(int *) value;

	if (paramState == PARAM_ASSENTE)
	{
		*(int *) value = FALSE;
		return SUCCESS;
	}
	return SUCCESS;
}

int validateJWGContornoTOPOSYS(const void * value, int paramState)
{
	int intVal = *(int *) value;

	if (paramState == PARAM_ASSENTE)
	{
		*(int *) value = FALSE;
	}
	return SUCCESS;
}

int validateJWGNumClasse(const void * value, int paramState)
{
	int intVal = *(int *) value;

	if (paramState == PARAM_ASSENTE)
	{
		//Processo tutte le classi
		*(int *) value = -1;
	}
	return SUCCESS;
}

int validateuscitaRisultatiClassificazione(const void * value, int paramState)
{
	int intVal = *(int *) value;

	if (paramState == PARAM_ASSENTE)
	{
       *(int *) value = USCITA_OUTPUT; //default su unico file
	}
	return SUCCESS;
}

int validateRansacConfigFile(const void * value, int paramState)
{
	char * strVal = (char *) value;

	if ((paramState == PARAM_ASSENTE) || (strlen(strVal)==0))
	{
		strcpy_s(strVal, strlen("confRansac.cfg")+1,"confRansac.cfg\0");
//		strcpy(strVal, "input\\confRansac.cfg\0");
		return SUCCESS;
	}

	return SUCCESS;
}

int validateStimaFaldaRansac(const void * value, int paramState)
{
	int intVal = *(int *)value;
	if (paramState == PARAM_ASSENTE)
	{
		* (int *)value = FALSE;
		return SUCCESS;
	}
	if (intVal > 1)
		* (int *)value = TRUE;
	return SUCCESS;
}

int validateCodiceLast(const void * value, int paramState)
{
	double fVal = *(double *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(double *)value = CODICE_LAST;
	}

	return SUCCESS;
}

int validateSplineG(const void * value, int paramState)
{
	double fVal = *(double *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(double *)value = SPLINE_G;
	}

	return SUCCESS;
}
int validateSplineW(const void * value, int paramState)
{
	double fVal = *(double *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(double *)value = SPLINE_W;
	}

	return SUCCESS;
}
int validateSplinePassoEst(const void * value, int paramState)
{
	double fVal = *(double *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(double *)value = SPLINE_PASSOEST;
	}

	return SUCCESS;
}
int validateSplinePassoNord(const void * value, int paramState)
{
	double fVal = *(double *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(double *)value = SPLINE_PASSONORD;
	}

	return SUCCESS;
}
int validateSplineLambda(const void * value, int paramState)
{
	double fVal = *(double *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(double *)value = SPLINE_LAMBDA;
	}

	return SUCCESS;
}
int validateSplineNumIterazioni(const void * value, int paramState)
{
	int fVal = *(int *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(int *)value = SPLINE_ITERAZIONI;
	}

	return SUCCESS;
}
int validateRansacThreshold(const void * value, int paramState)
{
	double fVal = *(double *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(double *)value = RANSAC_THRESHOLD;
	}

	return SUCCESS;
}
int validateRansacProb(const void * value, int paramState)
{
	double fVal = *(double *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(double *)value = RANSAC_PROB;
	}

	return SUCCESS;
}
int validateRansacGrosErr(const void * value, int paramState)
{
	double fVal = *(double *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(double *)value = RANSAC_GROSERR;
	}

	return SUCCESS;
}

int validateRansacStop(const void * value, int paramState)
{
	int fVal = *(int *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(int *)value = RANSAC_STOP;
	}

	return SUCCESS;
}
int validateRansacMinNumPointsInPlane(const void * value, int paramState)
{
	int fVal = *(int *)value;

	if ((paramState == PARAM_ASSENTE) )
	{
	    *(int *)value = RANSAC_MINNUMPOINTSINPLANE;
	}

	return SUCCESS;
}

int validateNormalizzazione (const void * value, int paramState)
{
	int intVal = *(int *) value;

	if ((intVal != 0) && (intVal != 1))
	{
		printf("Tipo di output BMP '%d' non riconosciuto.\n Impostato a 0 \n", intVal);
		*(int *)value = 8;
    }
	else if ((paramState == PARAM_ASSENTE) )
	    *(int *)value = 0;

	return SUCCESS;
}

int validate_sqmZ (const void * value, int paramState)
{
	float intVal = *(float *) value;

    if ((paramState == PARAM_ASSENTE) )
	    *(float *)value = SQM_Z;

	return SUCCESS;
}

