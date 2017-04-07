#include "gradient_tools.h"
#include "output_tools.h"

extern Configurator laserRegioniConfig;

void build_kernel(float *Hr, float *Hc, int dim)
{

	switch (dim)
	{
	case 2:

		//righe
		Hr[0] = -1.0; Hr[1] = -1.0;
		Hr[2] = 1.0;    Hr[3] = 1.0;

		//colonne
		Hc[0] = -1.0;    Hc[1] = 1.0;
		Hc[2] = -1.0;    Hc[3] = 1.0;

		break;

	case 3:

		//righe
		Hr[0] = -1.0; Hr[1] = -2.0; Hr[2] = -1.0;
		Hr[3] = 0;    Hr[4] = 0;    Hr[5] = 0;
		Hr[6] = 1.0;  Hr[7] = 2.0;  Hr[8] = 1.0;

		//colonne
		Hc[0] = -1.0;    Hc[1] = 0;    Hc[2] = 1.0;
		Hc[3] = -2.0;    Hc[4] = 0;    Hc[5] = 2.0;
		Hc[6] = -1.0;    Hc[7] = 0;    Hc[8] = 1.0;

		break;

	case 5:

		//righe
		Hr[0] = -2.0;  Hr[1] = -3.0; Hr[2] = -4.0; Hr[3] = -3.0; Hr[4] = -2.0;
		Hr[5] = -1.0;  Hr[6] = -2.0; Hr[7] = -3.0; Hr[8] = -2.0; Hr[9] = -1.0;
		Hr[10] = 0;    Hr[11] = 0;    Hr[12] = 0;    Hr[13] = 0;    Hr[14] = 0;
		Hr[15] = 1.0;  Hr[16] = 2.0;  Hr[17] = 3.0;  Hr[18] = 2.0;  Hr[19] = 1.0;
		Hr[20] = 2.0;  Hr[21] = 3.0;  Hr[22] = 4.0;  Hr[23] = 3.0;  Hr[24] = 2.0;

		//colonne
		Hc[0] = -2.0; Hc[1] = -1.0; Hc[2] = 0; Hc[3] = 1.0;    Hc[4] = 2.0;
		Hc[5] = -3.0; Hc[6] = -2.0; Hc[7] = 0; Hc[8] = 2.0;    Hc[9] = 3.0;
		Hc[10] = -4.0; Hc[11] = -3.0; Hc[12] = 0; Hc[13] = 3.0;    Hc[14] = 4.0;
		Hc[15] = -3.0; Hc[16] = -2.0; Hc[17] = 0; Hc[18] = 2.0;    Hc[19] = 3.0;
		Hc[20] = -2.0; Hc[21] = -1.0; Hc[22] = 0; Hc[23] = 1.0;    Hc[24] = 2.0;


		break;

	case 7:
		//righe
		Hr[0] = -3.0; Hr[1] = -4.0; Hr[2] = -5.0; Hr[3] = -6.0; Hr[4] = -5.0; Hr[5] = -4.0;  Hr[6] = -3.0;
		Hr[7] = -2.0; Hr[8] = -3.0; Hr[9] = -4.0; Hr[10] = -5.0; Hr[11] = -4.0; Hr[12] = -3.0;  Hr[13] = -2.0;
		Hr[14] = -1.0; Hr[15] = -2.0; Hr[16] = -3.0; Hr[17] = -4.0; Hr[18] = -3.0; Hr[19] = -2.0;  Hr[20] = -1.0;
		Hr[21] = 0;    Hr[22] = 0;    Hr[23] = 0;    Hr[24] = 0;    Hr[25] = 0;    Hr[26] = 0;     Hr[27] = 0;
		Hr[28] = 1.0;  Hr[29] = 2.0;  Hr[30] = 3.0;  Hr[31] = 4.0;  Hr[32] = 3.0;  Hr[33] = 2.0;   Hr[34] = 1.0;
		Hr[35] = 2.0;  Hr[36] = 3.0;  Hr[37] = 4.0;  Hr[38] = 5.0;  Hr[39] = 4.0;  Hr[40] = 3.0;   Hr[41] = 2.0;
		Hr[42] = 3.0;  Hr[43] = 4.0;  Hr[44] = 5.0;  Hr[45] = 6.0;  Hr[46] = 5.0;  Hr[47] = 4.0;   Hr[48] = 3.0;

		//colonne
		Hc[0] = -3.0; Hc[1] = -2.0; Hc[2] = -1.0; Hc[3] = 0;    Hc[4] = 1.0;  Hc[5] = 2.0;     Hc[6] = 3.0;
		Hc[7] = -4.0; Hc[8] = -3.0; Hc[9] = -2.0; Hc[10] = 0;    Hc[11] = 2.0;  Hc[12] = 3.0;     Hc[13] = 4.0;
		Hc[14] = -5.0; Hc[15] = -4.0; Hc[16] = -3.0; Hc[17] = 0;    Hc[18] = 3.0;  Hc[19] = 4.0;     Hc[20] = 5.0;
		Hc[21] = -6.0; Hc[22] = -5.0; Hc[23] = -4.0; Hc[24] = 0;    Hc[25] = 4.0;  Hc[26] = 5.0;     Hc[27] = 6.0;
		Hc[28] = -5.0; Hc[29] = -4.0; Hc[30] = -3.0; Hc[31] = 0;    Hc[32] = 3.0;  Hc[33] = 4.0;     Hc[34] = 5.0;
		Hc[35] = -4.0; Hc[36] = -3.0; Hc[37] = -2.0; Hc[38] = 0;    Hc[39] = 2.0;  Hc[40] = 3.0;     Hc[41] = 4.0;
		Hc[42] = -3.0; Hc[43] = -2.0; Hc[44] = -1.0; Hc[45] = 0;    Hc[46] = 1.0;  Hc[47] = 2.0;     Hc[48] = 3.0;

		break;

	case 9:
		//righe
		Hr[0] = -4.0; Hr[1] = -5.0; Hr[2] = -6.0; Hr[3] = -7.0; Hr[4] = -8.0; Hr[5] = -7.0;  Hr[6] = -6.0; Hr[7] = -5.0;  Hr[8] = -4.0;
		Hr[9] = -3.0; Hr[10] = -4.0; Hr[11] = -5.0; Hr[12] = -6.0; Hr[13] = -7.0; Hr[14] = -6.0;  Hr[15] = -5.0; Hr[16] = -4.0;  Hr[17] = -3.0;
		Hr[18] = -2.0; Hr[19] = -3.0; Hr[20] = -4.0; Hr[21] = -5.0; Hr[22] = -6.0; Hr[23] = -5.0;  Hr[24] = -4.0; Hr[25] = -3.0;  Hr[26] = -2.0;
		Hr[27] = -1.0; Hr[28] = -2.0; Hr[29] = -3.0; Hr[30] = -4.0; Hr[31] = -5.0; Hr[32] = -4.0;  Hr[33] = -3.0; Hr[34] = -2.0;  Hr[35] = -1.0;
		Hr[36] = 0;    Hr[37] = 0;    Hr[38] = 0;    Hr[39] = 0;    Hr[40] = 0;    Hr[41] = 0;     Hr[42] = 0;    Hr[43] = 0;     Hr[44] = 0;
		Hr[45] = 1.0;  Hr[46] = 2.0;  Hr[47] = 3.0;  Hr[48] = 4.0;  Hr[49] = 5.0;  Hr[50] = 4.0;   Hr[51] = 3.0;  Hr[52] = 2.0;   Hr[53] = 1.0;
		Hr[54] = 2.0;  Hr[55] = 3.0;  Hr[56] = 4.0;  Hr[57] = 5.0;  Hr[58] = 6.0;  Hr[59] = 5.0;   Hr[60] = 4.0;  Hr[61] = 3.0;   Hr[62] = 2.0;
		Hr[63] = 3.0;  Hr[64] = 4.0;  Hr[65] = 5.0;  Hr[66] = 6.0;  Hr[67] = 7.0;  Hr[68] = 6.0;   Hr[69] = 5.0;  Hr[70] = 4.0;   Hr[71] = 3.0;
		Hr[72] = 4.0;  Hr[73] = 5.0;  Hr[74] = 6.0;  Hr[75] = 7.0;  Hr[76] = 8.0;  Hr[77] = 7.0;   Hr[78] = 6.0;  Hr[79] = 5.0;   Hr[80] = 4.0;

		//colonne
		Hr[0] = -4.0; Hr[1] = -3.0; Hr[2] = -2.0; Hr[3] = -1.0; Hr[4] = 0;  Hr[5] = 1.0;  Hr[6] = 2.0;   Hr[7] = 3.0;   Hr[8] = 4.0;
		Hr[9] = -5.0; Hr[10] = -4.0; Hr[11] = -3.0; Hr[12] = -2.0; Hr[13] = 0;  Hr[14] = 2.0;  Hr[15] = 3.0;   Hr[16] = 4.0;   Hr[17] = 5.0;
		Hr[18] = -6.0; Hr[19] = -5.0; Hr[20] = -4.0; Hr[21] = -3.0; Hr[22] = 0;  Hr[23] = 3.0;  Hr[24] = 4.0;   Hr[25] = 5.0;   Hr[26] = 6.0;
		Hr[27] = -7.0; Hr[28] = -6.0; Hr[29] = -5.0; Hr[30] = -4.0; Hr[31] = 0;  Hr[32] = 4.0;  Hr[33] = 5.0;   Hr[34] = 6.0;   Hr[35] = 7.0;
		Hr[36] = -8.0; Hr[37] = -7.0; Hr[38] = -6.0; Hr[39] = -5.0; Hr[40] = 0;  Hr[41] = 5.0;  Hr[42] = 6.0;   Hr[43] = 7.0;   Hr[44] = 8.0;
		Hr[45] = -7.0; Hr[46] = -6.0; Hr[47] = -5.0; Hr[48] = -4.0; Hr[49] = 0;  Hr[50] = 4.0;  Hr[51] = 5.0;   Hr[52] = 6.0;   Hr[53] = 7.0;
		Hr[54] = -6.0; Hr[55] = -5.0; Hr[56] = -4.0; Hr[57] = -3.0; Hr[58] = 0;  Hr[59] = 3.0;  Hr[60] = 4.0;   Hr[61] = 5.0;   Hr[62] = 6.0;
		Hr[63] = -5.0; Hr[64] = -4.0; Hr[65] = -3.0; Hr[66] = -2.0; Hr[67] = 0;  Hr[68] = 2.0;  Hr[69] = 3.0;   Hr[70] = 4.0;   Hr[71] = 5.0;
		Hr[72] = -4.0; Hr[73] = -3.0; Hr[74] = -2.0; Hr[75] = -1.0; Hr[76] = 0;  Hr[77] = 1.0;  Hr[78] = 2.0;   Hr[79] = 3.0;   Hr[80] = 4.0;

		break;
	}
};

/*-------------------------------------------------------------------*\
Nome routine:
kernelf

Filtro su dati float

Parametri:
<INPUT> float * Z	-	Valori su cui calcolare il kernelf.
<OUTPUT> float * kern	-	Risultato.
<INPUT> float * a	-	Matrice dei pesi per il calcolo.
<INPUT> int Lx, Ly - Interi rappresentanti le dimensioni del filtro.

\*-------------------------------------------------------------------*/
bool kernelf(float *Z, float *kern, float *filter_something, float dvd,	int Width, int Height, int Lx, int Ly)
{
	int i, j, k, l;
	float greyvalue;
	/* Shifto a destra la dimensione del filtro (la divido per 2). copio nella matrice dfel kernel i valori di data-> z
		da 0 alla dimensione del kernel shiftata a dx di una posizione, quindi applico il filtraggio dalla suddetta posizione
		fino alla fine delle righe e delle colonne meno le dimensioni del filtro shiftate e infine ricomincio a copiare
		i valori di data-> z. */
	int	dLy = Ly >> 1;
	std::cout << "Ly: " << Ly << " dLy: " << dLy<< std::endl;
	int dLx = Lx >> 1;
	std::cout << "Lx: " << Lx << " dLx: " << dLx << std::endl;

	/* Interi di appoggio per la scansione del vettore. */
	int temp1 = Height - dLy;
	int temp2 = Width - dLx;

	//Metto nella matrice risultanti i valori di Z tali e quali
	for (int j = 0; j<dLy; j++)
		for (int i = 0; i < Width; i++)
		{
			*(kern + j*Width + i) = Z[j*Width + i];
		}

	for (j = dLy; j<temp1; j++)
	{
		for (i = 0; i<dLx; i++)
			*(kern + Width*j + i) = Z[j*Width + i];

		/* Applico il filtraggio (tramite l'intero greyvalue?)*/
		for (i = dLx; i<temp2; i++)
		{
			greyvalue = 0;
			for (k = 0; k<Ly; k++)
				for (l = 0; l<Lx; l++)
					greyvalue = greyvalue + Z[(j - dLy + k)*Width + (i - dLx + l)] * (*(filter_something + k*Lx + l));


			*(kern + i + j*Width) = greyvalue / dvd;
		}
		for (i = temp2; i<Width; i++)
			*(kern + j*Width + i) = Z[j*Width + i];
	}

	for (j = temp1; j<Height; j++)
		for (i = 0; i<Width; i++)
			*(kern + j*Width + i) = Z[j*Width + i];

	return true;
};

/*------------------------------------------------------------------------------------*\
Nome routine:
Gradiente

Di servizio per il calcolo del gradiente

Parametri:

\*------------------------------------------------------------------------------------*/
int Gradiente(float *grx, float *gry, unsigned char *gra, int width, int height, float passo, float LoLeftX, float LoLeftY)
{
	double Gx, Gy;		//,teta;
	double intensity;	//$C  corretto
	int i, j;
	long int m;
	FILE *poi;
	double pendenza, soglia, delta = 0.5;
	int punti;
	const char * FName = "Gradiente";
	const char * file_palette_name_char = NULL;
	float min, max;
	unsigned char *pen = new unsigned char[width*height];

	double VAR_Z;
	double maxG = -10000;
	double minG = 10000;
	int count = 0;

	VAR_Z = laserRegioniConfig.sqmZ*laserRegioniConfig.sqmZ;

	min = 0.1;
	max = 100.0;
	punti = width*height;
	
	//if ((pen = (unsigned char *)calloc(punti, sizeof(unsigned char))) == NULL) exit(0);

	for (i = 0; i<height; ++i)
	{
		m = i*width;
		for (j = 0; j<width; ++j)
		{
			//std::cout << "QUA!!! i: " << i << " j: "<< j << std::endl;
			Gx = (*(grx + j + m)) / 4;
			Gy = (*(gry + j + m)) / 4;
			intensity = fabs(Gx) + fabs(Gy);
			
			maxG = intensity > maxG ? intensity : maxG;
			minG = intensity < minG ? intensity : minG;
			if (intensity > 255) count++;

			*(gra + m + j) = intensity > 255 ? 255 : (unsigned char)intensity;
			pendenza = intensity / (double)(2 * passo);  //ATTENZIONE: messo a 2 (era 8)...già divisi i gradienti per 4 (riga 207)
			soglia = (float)(pendenza*passo + MOLTSQM*sqrt((double)(PERCPENDENZA*pendenza*PERCPENDENZA*pendenza) + VAR_Z));
			if (soglia < max)
				*(pen + m + j) = (int)((soglia - min) / delta);
			else  *(pen + m + j) = 255;
		}
	}

	if (laserRegioniConfig.tipoUscita >= LEVEL_3)
	{

		std::string file_out_name = makeExtension(laserRegioniConfig.projectName, PENDENZA_EXT);
		const char *file_out_name_char = file_out_name.c_str();

		if (fopen_s(&poi, file_out_name_char, "wb") != NULL)
			errore(FILE_OPENWRITE_ERROR, (char*)file_out_name_char, FName, TRUE);

		if (laserRegioniConfig.paletteFileName != NULL)
		{
			std::string file_palette_name = makeExtension(laserRegioniConfig.paletteFileName, PENDENZA_ACT);
			file_palette_name_char = file_palette_name.c_str();
		}


		HeaderWrPalette(poi, width, height, (char*)file_palette_name_char);
		InvertiRaw2Bmp(pen, height, width, 1078, poi);
		fclose(poi);
	}
	delete pen;

	return 1;
};

int build_partitions(float *a, float *b)
{
	int partitions;
	int i;
	float shift;

	partitions = laserRegioniConfig.numPartizioni;

	if (partitions == 8)  //SI LAVORA CON 8 PARTIZIONI
	{
		//45 gradi
		a[0] = 0.0;
		for (i = 1; i<partitions; i++) a[i] = a[i - 1] + 45;
		//calcolo dello shift: (360 / 8) / 2 = 22,5°
		shift = (float)(360.0 / (float)partitions);
		//le partizioni di "b" saranno: 22,5-67,5 ; 67,5 - 112,5 ; ecc.
		for (i = 0; i<partitions; i++) b[i] = a[i] + (float)(shift / 2);
	}
	else if (partitions == 12)
	{
		//30 gradi
		a[0] = 0.0;
		for (i = 1; i<partitions; i++) a[i] = a[i - 1] + 30;
		shift = (float)(360.0 / (float)partitions);
		for (i = 0; i<partitions; i++) b[i] = a[i] + (float)(shift / 2);
	}
	return partitions;
};

/*------------------------------------------------------------------------------------*\
Nome routine:
Teta

Di servizio per il calcolo dell'orientamento

Parametri:
<INPUT> float * grx	-	Gradiente lungo l'asse x
<INPUT> float * gry	-	Gradiente lungo l'asse y
<OUTPUT> unsigned char * map1	-	Output elaborazione: mappa delle classi
<INPUT>	float * a	-	Partizionamenti in base all'orientamento gradiente
<INPUT> float sogliaGradiente	-	Soglia sull'intensità del gradiente
<INPUT> int Lx		-
<INPUT> int Ly		-
<INPUT> int width	-	Larghezza grigliato
<INPUT> int height	-	Altezza grigliato
<INPUT> int partizioni	-	Numero di partizioni dell'orientamento dei gradienti
<INPUT> int MaxCol	-	Colore massimo

\*------------------------------------------------------------------------------------*/
bool Teta(float *grx, float *gry, unsigned char *map1, float *a, float sogliaGradiente, int Lx, int Ly, int width, int height, int partizioni, int MaxCol)
{
	double Gx, Gy, teta;
	double intensity;    //$C  corretto
	unsigned char classe;
	int i, j;


	for (i = 0; i<Lx / 2; i++)
	{
		for (j = 0; j<width; j++)
		{
			*(map1 + i*width + j) = MaxCol;
		}
	}

	for (i = Lx / 2; i<height - Lx / 2; i++)
	{
		for (j = 0; j<Ly / 2; j++)
			*(map1 + i*width + j) = MaxCol;
		for (j = Ly / 2; j<width - Ly / 2; j++)
		{
			Gx = (*(grx + j + i*width));
			Gy = (*(gry + j + i*width));
			intensity = fabs(Gx) + fabs(Gy);

			if (intensity <= sogliaGradiente)
				teta = 1000.0;   //$C messo soglia come float : E' DATA COME FLOAT
			else
				teta = ((atan2(Gy, Gx))*180.0) / PIGRECO;
			if (teta < 0)
				teta = 360.0 + teta;

			//Assegniamo una classe in base all'analisi del teta
			classe = Analisi_teta(teta, a, partizioni, MaxCol);
			*(map1 + j + i*width) = classe;
		}

		for (j = width - Ly / 2; j<width; j++)
			*(map1 + i*width + j) = MaxCol;

	}

	for (i = height - Lx / 2; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			*(map1 + i*width + j) = MaxCol;
		}
	}
	return true;
}

/*------------------------------------------------------------------------------------*\
Nome routine:
AnalisiTeta

Di servizio per il calcolo dell'orientamento

Parametri:

\*------------------------------------------------------------------------------------*/
unsigned char Analisi_teta(double teta, float *a, int partizione, int MaxCol)
{
	int col, i, delta;

	delta = MaxCol / partizione;
	if (teta == 1000.0)
	{
		col = MaxCol;
		return (unsigned char)col;
	}

	for (i = partizione - 1; i>0; i--)
		if (teta >= a[i]) 
		{
			col = i*delta;
			return (unsigned char)col;
		}

	if (a[0] == 0) 
	{ 
		col = 0; 
		return (unsigned char)col; 
	}
	else          
	{
		if (teta >= a[0])
		{
			col = 0;
			return (unsigned char)col;
		}
		col = delta*(partizione - 1);
		return (unsigned char)col;
	}
};

/*------------------------------------------------------------------------------------*\
Nome routine:
conta

Di servizio per il calcolo dell'orientamento

Parametri:

\*------------------------------------------------------------------------------------*/
int conta(unsigned char *map1, int * cnt, int larg, int alt, int MaxCol)
{
	const char * FName = "conta";
	long int pos, posatt, posliv;
	int m, n, i, j, k, l;
	
	int *coda = new int[larg*alt];
	unsigned char *label = new unsigned char[larg*alt];

	for (i = 0; i<alt; i++)
	{
		for (j = 0; j<larg; j++)
		{
			pos = -1; posatt = 0; posliv = 0;
			if (*(map1 + i*larg + j) != MaxCol)
			{
				coda[posatt] = i*larg + j;
				*(label + i*larg + j) = 1;
				do
				{
					//std::cout << "1    ";
					pos++;
					m = coda[pos] / larg;
					n = coda[pos] - m*larg;
					
					for (k = (m>0) ? m - 1 : 0; k <= m + 1 && k<alt; k++)
					{
						for (l = (n>0) ? n - 1 : 0; l <= n + 1 && l<larg; l++)
						{
							if ((*(map1 + m*larg + n) == *(map1 + k*larg + l)) &&
								(*(label + k*larg + l) == 0))
							{
								posatt++;
								//std::cout << "posatt: " << posatt << " k: " << k << " l: " << l << " righe: " << alt << " col: " << larg << " alt: " << coda[posatt -1];
								coda[posatt] = k*larg + l;

								*(label + k*larg + l) = 1;
							}
						}
					}
					if (pos == posliv) posliv = posatt;

					//std::cout << "    3 " << "posatt: " << posatt << " pos: " << pos << " posliv: " << posliv << std::endl;

				} while ((posliv - pos) > 0);

				for (int d = 0; d<pos; d++)
					*(cnt + coda[d]) = pos;
			}
		}
	}

	delete coda;
	delete label;

	return 0;
};

/*------------------------------------------------------------------------------------*\
Nome routine:
Fusione

Fonde le due matrici in input cnt1, cnt2 che rappresentano il partizionamento della
regioni secondo l'orientamento del gradiente con valori delle partizioni differenti.
Il range di valori delle partizioni ha la stessa dimensione ma parte da valori shiftati
di una quantità pari alla metà della dimensione della partizione.
Matrice 1 Partizioni: 0-45, 45-90, 90-135, 135-180, ecc.
Matrice 2 Partizioni: 22,5-67,5 , 67,5 - 112,5 , 112,5 - 157,5 , ecc.

Parametri:
<INPUT> int * cnt1	-	Matrice partizioni 1
<INPUT> int * cnt2  -	Matrice partizioni 2 (shiftata rispetto a 1)
<INPUT> unsigned char * map1	-	Matrice delle classi ottenuta dopo l'analisi del teta
<INPUT> unsigned char * map2	-	Matrice delle classi ottenuta dopo l'analisi del teta
<OUTPUT> unsigned char * map	-	Matrice risultante delle classi

\*------------------------------------------------------------------------------------*/
int Fusione(int *cnt1, int *cnt2, unsigned char *map1, unsigned char *map2, unsigned char *map, int larg, int alt)
{
	int i, j, N1, N2;

	for (i = 0; i<alt; i++)
	{
		for (j = 0; j<larg; j++)
		{

			N1 = *(cnt1 + i*larg + j);
			N2 = *(cnt2 + i*larg + j);

			//Se la prima partizione > seconda partizione -> valore classe da map1
			//altrimenti da map2
			(*(map + i*larg + j) = (N1>N2) ? *(map1 + i*larg + j) : *(map2 + i*larg + j));

		}
	}
	return 0;
}