#pragma once

#include <list>
#include <utility>
#include <map>


#include "config_file.h"
#include "const.h"
#include "parameters.h"
#include "defs.h"
//#include "gradient_tools.h"

#ifndef DEF_HEADER
#define DEF_HEADER
typedef struct {
	long int	biHeight, biWidth, biSize,
		bfOffBits, bfSize, biCompression,
		biSizeImage, biXPels, biYPels,
		biClrUsed, biClrImportant;
	short int bfReserved1, bfReserved2, biPlanes, biBitCount;
	unsigned char palette[256], *bitmap;
} HEADER;
#endif


std::string makeExtension(const char *filename, const char *newExtension);
void   HeaderWrPalette(FILE *bmp, long int Width, long int Height, char * nomeFilePalette);
void InvertiRaw2Bmp_h(HEADER *h, FILE *bmp);
void InvertiRaw2Bmp(unsigned char *bitmap, long int Height, long int Width, long int offset, FILE *bmp);
void writePalette(FILE * out_file, FILE * palette);
void writeBpw(char *filename, DataSet *data1);
void export(DataSet *data1);

