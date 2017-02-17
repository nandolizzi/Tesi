#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

#include "configFile.h"
using namespace std;



ConfigFile::ConfigFile()
{
  // Empty text file
  sof_ = NULL;
}

ConfigFile::~ConfigFile()
{
  for( StringNode *next = sof_; sof_ != NULL; sof_ = next )
  {
    next = sof_->next;
    free( sof_->line );
    delete sof_;
  }
}

void ConfigFile::print() const
{
	for( StringNode *sn = sof_; sn != NULL; sn = sn->next )
		printf("%s\n", sn->line );
		printf("\n");
}

bool ConfigFile::load( const char *filename )
{
	ifstream myfile (filename);
	string line;

	// Apro il file in lettura, se sono in grado di leggerlo
	if (myfile)
    {
		// finchè ci sono righe da leggere 
		while (getline( myfile, line ))
      {
		  // se il primo carattere è diverso da #, ovvero il simbolo identificato come commento
		  if (line[0] != '#')
        {
			// verifico che vi sia il simbolo = all'interno della riga
			size_t pos= line.find('=');
			
			// se non è presente il simbolo = la riga è "errata", ovvero non vi è un valore da caricare
			if  ( line.find('=') == string::npos)
			{
				cout << "Nella seguente riga non è stato inserito nessun valore:\n"<< line << "\n" << endl;
			}
			// altrimenti verifico se è presente uno spazio tra la variabile ed il valore da inizializzare
			
			else
			{
				// cerco eventuali spazi nella riga
				size_t pos_1= line.find('\0');
				
				/* se l'eventuale spazio è di indice maggiore rispetto al simbolo = 
					vuol dire che sono interessato alla sottostringa che va da 0 all'indice dell'= stesso*/
				if (pos < pos_1)
				{
					// ricavo la sottostringa nella quale ricercare l'elemento della struct
					string verify = line.substr(0,pos);

					/* richiamo una funzione per la verifica della presenza di quell'elemento nella struct
						all'interno della funzione riscrivo anche il nuovo valore da configurare*/
					
					/* check (verify); */
				}
				else if (pos > pos_1)
				{
					string verify = line.substr(0,pos);
				}

			}
		}
    myfile.close();
    }
  else cout << "fooey\n";

  return false;
 }
