#pragma once

/*---------------------------------------------*\
	FIle const.h della prof.ssa
\*---------------------------------------------*/

#define NUM_CLASSI_INIZ 10000  //rapportare alla dimensione immagine
#define NUM_CLASSI_INC 1000

#define	PIGRECO        3.14159265358979323846
#define	NONE 0
#define	FALSE 0                //$ 204
#define	TRUE 1                 //$ 204
#define NOT_FOUND	-1
#define USCITA_8BITS	1
#define USCITA_16BITS	0

#define DIM_IMM_TUTTA	1
#define DIM_IMM_WINDOW 0
	
#define USCITA_ASCII_NO	0
#define USCITA_ASCII_EN 1
#define USCITA_ASCII_RC 2

#define TIPORICERCA_DTM		0
#define TIPORICERCA_EDIFICI	1
#define TIPORICERCA_MEDIANO		2

#define TIPO_LF_1SOLO		1
#define TIPO_LF_LASTFIRST	2
#define TIPO_LF_1SOLO_INTENSITA 3
#define TIPO_LF_LASTFIRST_INSIEME 4
#define TIPO_LF_LASTFIRST_INSIEME_NOTEMPO 5
#define TIPO_LF_FIRSTLAST	6
#define TIPO_LF_T_FIRSTLAST	7
#define TIPO_LF_LASTFIRST_INSIEME_CODICI 8
#define TIPO_UAV 9

#define ORDINE_LF_FIRSTPULSE	0
#define ORDINE_LF_LASTPULSE		1

#define TIPO_SPLINE_BILIN		0
#define TIPO_SPLINE_BICUB		1

#define	 SUCCESS	0	
#define  ERROR	(!SUCCESS)

#define BLACK 0
#define WHITE 255

//JOHN 28/05/05
#define LOG_DIR					"Logs"
#define OUTPUTS_DIR				"Outputs"

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

 #define  N_BORDO  2        //N_Bordo * passo spline : dimensione del bordo dei dati di input per le spline (problema di bordo delle spline)

#define QUOTA_BUCHI -10000
#define QUOTA_MAX 20000

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

#define LEVEL_1     1     //da settare nel config su tipoOutput
#define LEVEL_2     2
#define LEVEL_3     3
#define LEVEL_4     4
//JOHN06
#define	NON_ASSEGNATO 0
#define	ASSEGNATO 200
// #define	ASSEGNATO_STRETTA 2
#define	ASSEGNATO_LOW_V   3
#define  PICCOLA   1 
#define  STRETTA   2
#define  ACQUA     3
#define  BORDO     4					 
#define  TT        5		//$ 1 classe
#define  TT_1      6		//$   terreno adiacente a TT con dislivello bordo < di 2 metri
#define  TT_2      7	    //$   
#define  CC        8       //$   cortili
#define  BUCA      9         //$   buca
#define  VERDE2    10      //gruppi di sporchini
#define  DACLASSIFICARE        11	    //$   da classificare
#define  TT_3       12	    //$   cortili comunicanti con terreno
#define  TT_4       13	    //$   terreno adiacente a buche
#define  TT_5       14	    //$   terreno adiacente a buche
#define  TT_FL      15     //punti classificati terreno che hanno F&L differenti
#define  TT_VERDE1  16     //First-Last
#define  APP6       17     
#define  VERDE3     18      //Regione declassificata da Edificio a Verde (no presenza di Piani Locali)
#define  CURV       20    //terreno (forse) non orizzontale, ma liscio
#define  DECLASS    21
#define  TT_20      22	    //$   terreno >100000mq
#define  STRETTA_FL 23     //punti classificati STRETTE che hanno F&L differenti
#define  ALTRO_FL   24     //punti classificati altro che hanno F&L differenti
#define  SSEC       80	    //$   edifici + bassi di 2 metri : capanni o altro - terreno?
#define  SST       120		//$   edifici + alti di 2 metri dal terreno  
#define  SS      255	    //$   edifici : regione + alte delle vicine
#define  SS_1    254	    //$  
#define  SS_2    253		//$   
#define  SS_3    252		//$   
#define  SS_4    251		//$    
#define  SS_5    250		//$   
#define  SS_6    249		//$   
#define  SS_7    248		//$    
#define  SS_8    247
#define  SS_9    245
#define  SS_20    246      //edificio industriale

#define  N_BORDO  2        //N_Bordo * passo spline : dimensione del bordo dei dati di input per le spline (problema di bordo delle spline)

#define QUOTA_BUCHI -10000

#define	FALDA_NON_TROVATA 99
#define FALDA_NON_TROVATA2 98
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

/******************************************\
	
	Inizializzo i magic number relativi
	ai possibili file di uscita.

\******************************************/
#define IMMREGIONI_EXT_BMP		"_Regioni.bmp"
#define IMMREGIONI_EXT_IMG		"_Regioni.img"
#define IMMREGIONI_EXT_ACT		"_Regioni.act"
#define DENSITAPNT_EXT			"_densita.bmp"
#define SEGMINFALDE_EXT			"_fald1.bmp"
#define INTENSITA_EXT			"_intensita.bmp"
#define INTENSITAISTO_EXT		"_intensita.txt"
#define SEGMINLINE_EXT			"_Line.bmp"
#define SEGMINLINE_EXT_CAD		"_Line.dxf"
#define SEGMINGRAD_EXT			"_Grad.bmp"
#define PENDENZA_EXT			"_Pend.bmp"
#define PIANOLOC_EXT			"_PianLocale.bmp"
#define SEGMINFALDE_ACT			"_fald1.act"
#define PENDENZA_ACT			"_Pendenza.act"
#define DENSITAPNT_ACT			"_Densita.act"
#define ESTRAIPUNTICONTORNO_EXT	"_cnt.xyz"
#define CONTORNO16_EXT			"_cnt.raw"
#define IMMAGINEFALDE2_EXT		"_fald2.bmp"
#define INTENSITA_ACT			"_Intensita.act"
#define IMMAGINEFALDE_ACT		"_fald2.act"
#define IMMAGINEFALDE3_EXT		"_fald3.bmp"
#define IMMAGINETERRENO2_EXT	"_Alto.bmp"
#define IMMAGINETERRENO2_ACT	"_Alto.act"
#define SALVAVTP_BT_EXT			"_BT.bt"
#define SALVAVTP_VTST_EXT		"_VTST.vtst"
#define ACCRESCI_8IMG_EXT		"_caf8.img"
#define SALVARAWRGB_EXT			"_RGB.img"
#define SALVAVRML_EXT			"_VRML.wrl"
#define SALVAVRML1_EXT			"_VRML1.wrl"

//APRILE05bis
#define ESPTERRENOPENDENZA_EXT      "_TerrenoPendenza.txt"
#define ESPSCARTATOPENDENZA_EXT      "_ScartatiPendenza.txt"
#define ESPOUTLIERPENDENZA_EXT      "_OutlierPendenza.txt"
#define ESPGREENPENDENZA_EXT      "_GreenPendenza.txt"
#define ESPGRIDCLASS_EXT        "_l3d.txt"
#define ESPRAWTERRENO_EXT       "_AccettatiSpline.txt"  //non si usa
#define ESPRAWGREEN_EXT         "_ScartatiSpline.txt"   //non si usa
#define ESPINPUTSPLINE_EXT      "_InputSpline.txt"
#define ESPSPLINEVERDE_EXT      "_ZSplineVerde.txt"
#define ESPSPLINEAPPR_EXT      "_ZSplineTerreno.bmp"
#define ESPRAWVERDE_EXT         "_GreenDaGrd.txt"       //non si usa
#define ESPSPLINE_EXT           "_Zspline.txt"
#define ESPOUTLIER_EXT          "_Outlier.txt"          //non si usa
#define ESPBUILDING_EXT         "_Building.txt"
#define ESPTERRENOSPLINE_EXT      "_Terreno.txt"
#define ESPCOR_DATA             "_Norma.txt"
#define ESPGREENSPLINE_EXT        "_Green.txt"
#define ESPTUTTO_EXT1            "_Classi.txt"
#define ESPTUTTO_EXT            "_CLASSI.txt"
#define ESPFILTER_EXT           "_FILT.txt"


#define SQR(X)	((X)*(X))
#define MOLTSQM   2