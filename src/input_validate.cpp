#include "input_validate.h"
#include <iostream>
#include <string.h>

using namespace std;

bool input_number_parameter( int &num_par)
{
	/* Effettuo dei controlli sul numero dei parametri. Se è sbagliato restituisco false*/
	if (  num_par < 2 )
	{
		cout << "Error! You didn't insert the name of the data file." << endl;
		return false; 
	}

	if (  num_par < 3 )
	{
		cout << "Error! You didn't insert the name of the configuration file." << endl;
		return false; 
	}

	if ( num_par > 3 )
	{
		cout << "Error! You insert too much arguments. The program needs only the names of the data file and the name of the configuration file." << endl;
		return false;
	}
	/* Se il numero dei parametri è corretto restituisco true*/
	else
		return true;
}

bool data_extension(const char *filename)
{
	string name(filename);
	size_t pos = name.rfind('.');

  	/* Se non è stato inserito nessun '.' vuol dire che il file che si è cercato di caricare non possedeva estensione alcuna.*/
  	if (name.rfind('.') == string::npos)
  	{
  		cout << "Error! You insert a data file without extension." << endl;
  		return false;
  	}

  	/* Se si è trovato il '.' si verifica che l'estensione del file sia del tipo richiesto (.txt) */
  	string extension = name.substr(pos + 1);
  	string comp_ext = "txt";
  	
  	if ( extension == comp_ext )
  	{
  		/* L'estensione è corretta quindi restituisco true */
  	 	return true;
	}
	else
	{
		/* L'estensione non è corretta.*/
		cout << "Error! The file passed how data it's not a .txt file!" << endl;
		return false;
	}
}

bool conf_extension(const char *filename)
{
	string name(filename);
	size_t pos = name.rfind('.');

  	/* Se non è stato inserito nessun '.' vuol dire che il file che si è cercato di caricare non possedeva estensione alcuna.*/
  	if (name.rfind('.') == string::npos)
  	{
  		cout << "Error! You insert a configuration file without extension." << endl;
  		return false;
  	}

  	/* Se si è trovato il '.' si verifica che l'estensione del file sia del tipo richiesto (.conf) */
  	string extension = name.substr(pos + 1);
  	string comp_ext = "conf";
  	
  	if ( extension == comp_ext )
  	{
  		/* L'estensione è corretta quindi restituisco true */
  	 	return true;
	}
	else
	{
		/* L'estensione non è corretta.*/
		cout << "Error the file passed how configuration it's not a .conf file!" << endl;
		return false;
	}
}