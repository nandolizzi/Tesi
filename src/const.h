#pragma once

/*---------------------------------------------*\
	Varie defines di costanti e valori di
	default per i parametri
\*---------------------------------------------*/
#define SOGLIA_CLUSTER  0.3     //m
#define DIM_MIN_REGIONE  3      //punti
#define NUM_PARTIZIONI   8
#define OUTPUT_BMP       0      //elaborazione completa: uscita 16 bit
#define OUTPUT           4      //nessuna uscita extra (1, 2, 3, 4)
#define DIM_FILTRO       3
#define OUTPUT_ASCII     0      //export
#define USCITA_OUTPUT    0      //uscitaRisultatiClassificazione : su files separati (default)
#define TIPO_RICERCA     0      //DTM
#define SOGLIA_TT   0.5 
#define SOGLIA_TT2  1.5          //m
#define SOGLIA_SS1  3            //m 
#define SOGLIA_SSEC 3          //m
#define SOGLIA_INGOMBRO  100000  //mq
#define PERC_FIRST_TERRENO  0.3  //
#define DISLIVELLO_TERRENO  300  //m
#define EXT_TERRENO  300000  //mq
#define LIMITE_PUNTI  3
#define SOGLIA_UEB    1          //m
#define SOGLIA_INDUSTRIALE  3    //m 
#define DISLIVELLO_MAT_SPARSA    3 //cm 250  differenza fra punti raw nella stessa cella: se > di prende il punto + basso
#define PERCENTUALEFALDE       0.3
#define SOGLIA_GRAD_CONTORNO    7
#define SOGLIA_GRAD_ORIENTAMENTO  2
#define SOGLIA_PIANO_MAX_RESIDUO  0.2
#define SQM_Z                 0.25
#define PERCPENDENZA          0.3
#define CODICE_LAST              1
#define DELTA_FIRSTLAST          0.2
// APRILE05bis   
#define CRITERITERRENO          5

// APRILE05bis   
#define SOGLIA_SS2              10

#define TIPO_SPLINE      0      //bilineari
#define SPLINE_G         0.3
#define SPLINE_W         0.6
#define SPLINE_PASSONORD  7
#define SPLINE_PASSOEST   7
#define SPLINE_ITERAZIONI  3
#define SPLINE_LAMBDA     0.1

#define RANSAC_THRESHOLD   0.30
#define RANSAC_PROB        0.99
#define RANSAC_GROSERR     0.90
#define RANSAC_STOP        10
#define RANSAC_MINNUMPOINTSINPLANE   10


#define	FALSE 0
#define TRUE 1
#define	NONE 0

#define	 SUCCESS	0	
#define  ERROR	(!SUCCESS)

/*---------------------------*\
	Definizioni dei Tipi
\*---------------------------*/

#define TIPO_CHAR	 1
#define TIPO_STR	 2
#define TIPO_SHORT	 3
#define TIPO_USHORT	 4
#define TIPO_INT	 5
#define TIPO_UINT	 6
#define TIPO_LONG	 7
#define TIPO_ULONG	 8
#define TIPO_LLONG	 9
#define TIPO_ULLONG	10
#define TIPO_FLOAT	11
#define TIPO_DOUBLE	12
#define TIPO_LDOUBLE 13

#define PARAM_ASSENTE		0
#define PARAM_PRESENTE		1
#define PARAM_ERROR			-1
#define MAX_STR_LEN			255



/*----------------------------*\
	Defines costanti error
\*----------------------------*/
#define MEMORY_ALLOCATION_ERROR			1
#define FILE_OPENREAD_ERROR				2
#define FILE_OPENWRITE_ERROR			3
#define ROUTINE_GENERIC_ERROR			4
#define ROUTINE_FILEWR_GENERIC_ERROR	5 
#define TYPE_UNKNOWN_ERROR				6 
#define PARAM_VALIDATION_ERROR			7
#define STRING_MANIPULATION_ERROR		8
#define FILE_READ_ERROR					9
#define DIR_CREATION_ERROR				10
#define NO_SELECTED_DATA_ERROR			11
#define NOT_IMPLEMENTED_FUNCTION_ERROR	12
#define MISSING_NC_REGIONS				13
#define ERROR_DATA_FORMAT               14

/*---------------------------------------------------*\
	Definizioni dei Tipi (che erano in Leggilaser)
\*---------------------------------------------------*/

#define TYPE_IMG	1
#define TYPE_ASC	2
#define TYPE_XYZ	3
#define TYPE_DTM	4
#define TYPE_CFG	5
#define TYPE_ELSE	6