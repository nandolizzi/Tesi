#include <stdio.h>
#include <iostream>
#include <fstream>
#include <Core>
#include <string.h>

#include "input_validate.h"

using namespace std;

int main(int argc, char const *argv[])
{
	int num_par= argc;
	/* Si verifica innanzitutto che il numero di paramentri immessi sia pari a 3.
		sono interessato al nome del programma argv[0], al nome del file dei dati argv[1]
		e al nome del file di configurazione argv[2]. */
	
	if(!input_number_parameter( num_par))
		return 1;

	/* Si esegue un controllo sulle estensioni dei file.
		Per prima cosa si verifica l'estenzione del file dei dati. */
	string data_name(argv[1]);
	if(! data_extension(data_name));
		return 1;

	/* Si esegue la verifica dell'estensione del file di configurazione */
	string conf_name(argv[2]);
	if(! conf_extension(conf_name));
		return 1;
	
	/* Se le estensioni sono corrette carico i due file */



	return 0;
}
