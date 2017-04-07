#include "output_tools.h"
#include <iostream>
#include <string>

extern Configurator laserRegioniConfig;

std::string makeExtension(const char *filename, const char *newExtension)
{
	//std::string output_name("..\\Outputs\\");
	std::string name(filename);
	std::string extension(newExtension);
	size_t pos = name.std::string::rfind('.');
	
	/*Nel caso particolare del file palette non vi è un'estensione, per cui si aggiunge
		comunque la nuova estensione. */
	if ((name != "palette" || name != "Palette"))
	{
		std::string project_name = name.std::string::substr(0, pos);
		std::string output_name = project_name;
		output_name += extension;
		return output_name;
	}
	/* Se non è stato inserito nessun '.' vuol dire che il file che si è cercato di caricare non possedeva estensione alcuna.*/
	else if (name.std::string::rfind('.') == std::string::npos)
	{
		std::cout << "Error! You insert a file without extension." << std::endl;
		return NULL;
	}
	else
	{
		/*Se si è trovato il punto si ricava la sottostringa contentente il nome del progetto e vi si aggiunge l'estensione desiderata. */
		std::string project_name = name.std::string::substr(0, pos);
		std::string output_name = project_name;
		output_name += extension;
		std::cout << "Nome rimpiazzato: " << output_name << std::endl;
		//delete project_name_char;
		return output_name;
	}
};

/*---------------------------------------------------------------------------*\
Nome Routine:
HeaderWrPalette

Scrive l'header di un file BMP relativo ad una immagine RAW data utilizzando
la palette in input

Parametri:
<OUTPUT> FILE * bmp	-	File bmp da scrivere
<INPUT> long int Width	-	Larghezza immagine
<INPUT> long int Height	-	Altezza immagine
<INPUT> char * nomeFilePalette	-	Nome del file palette da caricare
(Se nullo utilizza la palette di default
a toni di grigio
\*---------------------------------------------------------------------------*/
void   HeaderWrPalette(FILE *bmp, long int Width, long int Height, char * nomeFilePalette)
{
	FILE * palette = NULL;
	const char * FName = "HeaderWrPalette";
	int pudding, i;
	unsigned char b, m, a, d;
	long int SizeFile, OffBits, Size, Compression, SizeImage, XPels, YPels, ClrUsed, ClrImportant;
	short int Reserved, Planes, BitCount;


	/* Costruzione dell'header */

	/* pudding = resto di 4 delle colonne; */

	pudding = Width % 4;
	if (pudding != 0) pudding = 4 - pudding;

	fseek(bmp, 0, SEEK_SET);
	b = 'B';
	m = 'M';
	fwrite(&b, sizeof(unsigned char), 1, bmp);
	fwrite(&m, sizeof(unsigned char), 1, bmp);

	SizeFile = Height*Width + pudding + 1078;

	fwrite(&SizeFile, sizeof(long), 1, bmp);
	Reserved = 0;
	fwrite(&Reserved, sizeof(short), 1, bmp);
	fwrite(&Reserved, sizeof(short), 1, bmp);
	OffBits = 1078;
	fwrite(&OffBits, sizeof(long), 1, bmp);
	Size = 40;
	fwrite(&Size, sizeof(long), 1, bmp);
	fwrite(&Width, sizeof(long), 1, bmp);
	fwrite(&Height, sizeof(long), 1, bmp);
	Planes = 1;
	fwrite(&Planes, sizeof(short), 1, bmp);
	BitCount = 8;
	fwrite(&BitCount, sizeof(short), 1, bmp);
	Compression = 0;
	fwrite(&Compression, sizeof(long), 1, bmp);
	SizeImage = (Width + pudding)*Height;
	fwrite(&SizeImage, sizeof(long), 1, bmp);
	XPels = 0;
	fwrite(&XPels, sizeof(long), 1, bmp);
	YPels = 0;
	fwrite(&YPels, sizeof(long), 1, bmp);
	ClrUsed = 0;
	fwrite(&ClrUsed, sizeof(long), 1, bmp);
	ClrImportant = 0;
	fwrite(&ClrImportant, sizeof(long), 1, bmp);
	/*palette*/
	//   	if ((nomeFilePalette == NULL) || ((palette = fopen(nomeFilePalette, "rb")) == NULL))
	if ((nomeFilePalette == NULL) || (fopen_s(&palette, nomeFilePalette, "rb")) != NULL)
	{
#ifdef DEBUG
		//		laserlog(mainLog, FName, "File palette '%s' non trovato. Utilizzo palette di default a toni di grigio.\n", nomeFilePalette);
#endif
		//Palette di default: toni di grigio
		d = 0;
		for (i = 0; i<256; i++)
		{
			a = i;
			fwrite(&a, sizeof(unsigned char), 1, bmp);
			fwrite(&a, sizeof(unsigned char), 1, bmp);
			fwrite(&a, sizeof(unsigned char), 1, bmp);
			fwrite(&d, sizeof(unsigned char), 1, bmp);
		}
	}
	else
	{
		//palette da file
		writePalette(bmp, palette);
		fclose(palette);
	}

}

/***************************************************************************

InvertiRaw2Bmp_h
Legge l'immagine dalla bitmap del file RAW e scrive il file BMP
facendo anche l'inversione. Versione che riceve l'header.

ver. 3.0 $ 04/03/99 $

***************************************************************************/

void InvertiRaw2Bmp_h(HEADER *h, FILE *bmp)
{
	int i, j, pudding;
	unsigned char d;

	d = 0;

	fseek(bmp, h->bfOffBits, SEEK_SET);

	pudding = h->biWidth % 4;
	if (pudding != 0) pudding = 4 - pudding;

	for (i = 0; i<h->biHeight; i++){
		fwrite(h->bitmap + (h->biHeight - i - 1)*(h->biWidth), sizeof(unsigned char), (int)h->biWidth, bmp);

		for (j = 0; j<pudding; j++) fwrite(&d, sizeof(unsigned char), 1, bmp);
	}

}

/****************************************************************************

InvertiRaw2Bmp
Legge l'immagine dalla bitmap del file RAW e scrive il file BMP
(opzione senza header) con inversione

ver. 3.0 $ 04/03/99 $

***************************************************************************/void InvertiRaw2Bmp(unsigned char *bitmap, long int Height, long int Width,
	long int offset, FILE *bmp)
{
	int i, j, pudding;
	unsigned char d;

	pudding = Width % 4; if (pudding != 0) pudding = 4 - pudding;
	d = 0;

	//   fseek(bmp,offset,SEEK_SET);

	for (i = 0; i<Height; i++){
		fwrite(bitmap + (Height - i - 1)*Width, sizeof(unsigned char), (int)Width, bmp);

		for (j = 0; j<pudding; j++) fwrite(&d, sizeof(unsigned char), 1, bmp);
	}

}

/*-------------------------------------------------------------------------*\

Nome Routine:
writePalette

Scrive la palette contenuta nel file .act di input sul file di output di tipo
bmp.
Il file di output dev'essere già aperto E POSIZIONATO sul punto di scrittura
della palette.

E' importante notare che la palette in input è costituita da terne di bytes
che indicano i colori mentre la palette scritta nel file bmp dev'essere
formata da quaterne di bytes in cui l'ultimo byte è inutilizzato.
La routine si aspetta in input quindi una palette con TERNE di valori!!!

Parametri:
<OUTPUT> FILE * out_file	-	File bmp di output
<INPUT> FILE * palette		-	Puntatore al file palette
\*-------------------------------------------------------------------------*/
void writePalette(FILE * out_file, FILE * palette)
{
	const char * FName = "writePalette";
	unsigned char	buffer[4];
	size_t			readed = 0, written = 0;
	int counter = 0;
	for (counter = 0; counter < 256; counter++)
	{
		buffer[0] = '\0';
		readed = written = 0;
		readed = fread(buffer, sizeof(unsigned char), 3, palette);
		if ((readed != 3) && (!feof(palette)))
			errore(ROUTINE_FILEWR_GENERIC_ERROR, "palette", FName, TRUE);
		buffer[3] = 0;
		//vuole l'ordine di BGR
		written = fwrite(&buffer[2], sizeof(unsigned char), 1, out_file);
		written = fwrite(&buffer[1], sizeof(unsigned char), 1, out_file);
		written = fwrite(&buffer[0], sizeof(unsigned char), 1, out_file);
		written = fwrite(&buffer[3], sizeof(unsigned char), 1, out_file);
	}

}

void writeBpw(char *filename, DataSet *data1)
{
	FILE *out;
	const char *		FName = "scrivi_bpw";

	strcpy_s(&filename[strlen(filename) - 5], strlen(filename) - 5 + strlen("_Alto.bpw"), "_Alto.bpw");
 
	if (fopen_s(&out, filename, "w") != NULL)
		errore(FILE_OPENREAD_ERROR, laserRegioniConfig.projectName, FName, FALSE);
	fprintf(out, "    %4.2f\n    0.0\n    0.0\n   -%4.2f\n    %9.2lf\n   %10.2lf\n", data1->pelsX, data1->pelsX, data1->LoLeftX, data1->LoLeftY + data1->heightGrid*data1->pelsX);

	fclose(out);
};

/*----------------------------------------------------------------------------------------*\
Nome Routine:
export
Salva una porzione di dati in formato ASCII ENz

\*-----------------------------------------------------------------------------------------*/
void export(DataSet *data1)
{
	//int i, j, Wlarg, Walt;
	FILE *exp;
	//char *nomeFileOut = NULL;
	std::string file_out_name;
	int nopunti, k, col, rows;
	float x, y;
	errno_t err;

	//JOHN_COOR
	//Wlarg = (Data->LoRightC - Data->UpLeftC)/Data->pelsX;
	//Walt = (Data->LoRightR - Data->UpLeftR)/Data->pelsY;
	col = data1->widthGrid;
	rows = data1->heightGrid;

	nopunti = data1->heightGrid * data1->widthGrid;

	file_out_name = makeExtension(laserRegioniConfig.projectName, ".xyz");
	const char *file_out_name_char = file_out_name.c_str();
	err = fopen_s(&exp, file_out_name_char, "w");
	if (err != 0)
		errore(FILE_OPENWRITE_ERROR, (char*)file_out_name_char , "Export", TRUE);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < col; ++j )
		{

			x = data1->LoLeftX + j*data1->pelsX;
			/* Versione originale è pelsY ma nella mia uso solo una variabile.
				Anche in quella originale, in realtà, venivano assegnati con gli stessi valori. */
			y = (data1->LoLeftY + data1->heightGrid* data1->pelsX) - i*data1->pelsX;
			k = i* col + j;
			if (data1-> z[k] != QUOTA_BUCHI)
				fprintf(exp, " %9.2f,%10.2f,%9.2f\n", x, y, data1->z[k]);
		}
	}

	fclose(exp);
}
