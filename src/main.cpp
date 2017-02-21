#include <stdio.h>
#include <iostream>
#include <Core>

#include "input_validate.h"

using namespace std;

int main(int argc, char const *argv[])
{
	// inizializzo un intero di appoggio per non utilizzare argc
	int n_par= argc;

	// Verifico che si sia inserito il giusto numero di parametri
	if(!input_number_parameter( n_par))
		return 1;

	// Creo una matrice che contenga le dimensioni dei parametri passati al programma
	int *dim_argv = (int*)malloc( (argc) * sizeof(int) );

	// Routine per calcolare le dimensioni delle stringhe dei paramentri
	for (int j= 0; j < n_par; j++)
	{
		for (int i = 0; i < argv[j][i] != '\0'; i++)
		{
			dim_argv[j]= i;
		}
	}

	// alloco la memoria per la copia del nome del file dei dati
	char *new_argv_1 = (char*)malloc( (dim_argv[1]) * sizeof(char));
	
	// ciclo di copia del parametro in un array di appoggio
	for (int i = 0; i <= dim_argv[1]; i++)
	{
		new_argv_1 [i] = argv[1][i];
	}
	// Chiudo l'array che altrimenti avrebbe qualcosa appeso ( ma se ho allocato un qualcosa con le giuste dimensioni perché accade??)
	new_argv_1 [dim_argv[1]+1]= '\0';

	// Verifico che l'estensione sia corretta
	if(!data_extension( new_argv_1))
		return 1;

	// Stessa cosa per il file di configurazione
	
	// alloco la memoria per la copia del nome del file dei dati
	char *new_argv_2 = (char*)malloc( (dim_argv[2]) * sizeof(char));
	
	// ciclo di copia del parametro in un array di appoggio
	for (int i = 0; i <= dim_argv[2]; i++)
	{
		new_argv_2 [i] = argv[2][i];
	}
	new_argv_2 [dim_argv[2]+1]= '\0';

	// Verifico che l'estensione sia corretta
	if(!conf_extension( new_argv_2))
		return 1;
	
	cout << "The three file you passed were all correct" << endl;

	return 1;
}
