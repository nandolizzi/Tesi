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
	real_ E[5], N[5];   //in posizione 0 il baricentro 1 e 2 i 2 estremi 
	//oppure fino a 5 punti se una curva
	real_ Teta;    //orientamento
	//se DXF arctan degli estremi
	//se img da Burns o da Mediana
	real_ length;
	real_ sigma0;
	int Punti;
	int semeR, semeC;
	real_ a, b, c;   //parametri della linea
	//	 struct nodo *relazioni; //$ 204//$ puntatore alla lista dei dati lungo il bordo
};

void build_kernel(real_ *Hr, real_ *Hc, int dim);
bool kernelf(real_ *Z, real_ *kern, real_ *filter_something, real_ dvd, int Width, int Height, int Lx, int Ly);
int Gradiente(real_ *grx, real_ *gry, unsigned char *gra, int width, int height, real_ passo, real_ LoLeftX, real_ LoLeftY);
int build_partitions(real_ *a, real_ *b);

bool Teta(real_ *grx, real_ *gry, unsigned char *map1, real_ *a, real_ sogliaGradiente, int Lx, int Ly, int width, int height, int partizioni, int MaxCol);
unsigned char Analisi_teta(double teta, real_ *a, int partizione, int MaxCol);
int conta(unsigned char *map1, long int * cnt, int larg, int alt, int MaxCol, int caso);
int Fusione(long int *cnt1, long int *cnt2, unsigned char *map1, unsigned char *map2, unsigned char *map, int larg, int alt);