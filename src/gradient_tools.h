#pragma once

#include <iostream>
#include <string>

#include "const.h"
#include "config_file.h"
#include "output_tools.h"

struct PLine{
	int tipo;    //2 x linea, 3 x cerchio max = 5 
	int caso;    //1 x strade   2 x building
	int nome;    //polilinea di appartenenza
	int n_linee_assoc; //numero linee associate
	int nomeIMG[100];    //linee associata
	int stato;   //per le IMG 
	//0 default - non elaborata
	//1 se associata ad una linea di cartografia
	//2 se non associata
	float E[5], N[5];   //in posizione 0 il baricentro 1 e 2 i 2 estremi 
	//oppure fino a 5 punti se una curva
	float Teta;    //orientamento
	//se DXF arctan degli estremi
	//se img da Burns o da Mediana
	float length;
	float sigma0;
	int Punti;
	int semeR, semeC;
	float a, b, c;   //parametri della linea
	//	 struct nodo *relazioni; //$ 204//$ puntatore alla lista dei dati lungo il bordo
};

void build_kernel(float *Hr, float *Hc, int dim);
bool kernelf(float *Z, float *kern, float *filter_something, float dvd, int Width, int Height, int Lx, int Ly);
int Gradiente(float *grx, float *gry, unsigned char *gra, int width, int height, float passo, float LoLeftX, float LoLeftY);
int build_partitions(float *a, float *b);

bool Teta(float *grx, float *gry, unsigned char *map1, float *a, float sogliaGradiente, int Lx, int Ly, int width, int height, int partizioni, int MaxCol);
unsigned char Analisi_teta(double teta, float *a, int partizione, int MaxCol);
int conta(unsigned char *map1, int * cnt, int larg, int alt, int MaxCol);
int Fusione(int *cnt1, int *cnt2, unsigned char *map1, unsigned char *map2, unsigned char *map, int larg, int alt);