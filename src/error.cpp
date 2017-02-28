/*----------------------------------------------------------------------------------------*\
	Nome File:
	Errore.c

	Descrizione:
	Routines per la gestione degli errori

------------------------------------------------------------------------------------------
	HISTORY
------------------------------------------------------------------------------------------
	Novembre 2004	-	Versione finale Carla Nardinocchi

	29/11/04	-	JZ	-	Codificati gli errori con defines. Modificato il nome da 'errore'
							a "Errore"
							Aggiunto include const.h
	28/05/05	-	JZ	-	Aggiunto errore DIR_CREATION_ERROR
	11/06/06	-	JZ	-	Aggiunto errore NO_SELECTED_DATA_ERROR
	14/06/06	-	JZ	-	Aggiunto errore NOT_IMPLEMENTED_FUNCTION_ERROR
	22/06/06	-	JZ	-	Aggiunto errore MISSING_NC_ERROR


\*-----------------------------------------------------------------------------------------*/

#include "error.h"


/*------------------------------------------------------------------------------------*\
	Nome routine:
	Errore

	Stampa un messaggio di errore codificato ed eventualmente termina l'esecuzione
	dell'applicazione con lo stesso codice di errore.

	Parametri:
	<INPUT> int id			-	ID errore
	<INPUT> char *nome		-	Messaggio specifico da aggiungere al testo predefinito
	<INPUT> char *routine	-	Nome routine in cui viene sollevato l'errore
	<INPUT> int rt			-	Se True termina l'applicazione

	Valore di ritorno:
\*------------------------------------------------------------------------------------*/

// la professoressa avea messo un char
int errore(int id,char* nome,const char *routine,int rt)
{

 switch(id){
  case MEMORY_ALLOCATION_ERROR: 
	  printf("\n %s:Errore di allocazione di memoria per %s",routine,nome);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
          exit(MEMORY_ALLOCATION_ERROR);
#endif
	  }
	  else
		  return 0;
	  break;
  case FILE_OPENREAD_ERROR: 
	  printf("\n %s:Impossibile aprire il file %s in lettura",routine,nome);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		  exit(FILE_OPENREAD_ERROR);
#endif
	  }
	  break;
  case FILE_READ_ERROR: 
	  printf("\n %s:Errore lettura file %s",routine,nome);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		  exit(FILE_READ_ERROR);
#endif
	  }
	  break;
  case FILE_OPENWRITE_ERROR: 
	  printf("\n %s:Impossibile aprire il file %s in scrittura",routine,nome);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		  exit(FILE_OPENWRITE_ERROR);
#endif
	  }
	  break;
  case ROUTINE_GENERIC_ERROR: 
	  printf("\n %s:Problema generico sulla variabile o metodo %s\n",routine,nome);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		  exit(ROUTINE_GENERIC_ERROR);
#endif
	  }
	  break;
  case ROUTINE_FILEWR_GENERIC_ERROR: 
	  printf("\n %s:%s",routine,nome);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		  exit(ROUTINE_FILEWR_GENERIC_ERROR);
#endif
	  }
      break;
  case TYPE_UNKNOWN_ERROR: 
	  printf("\n %s:Tipo di dato non riconosciuto:%s",routine,nome);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		  exit(TYPE_UNKNOWN_ERROR);
#endif
	  }
      break;
  case PARAM_VALIDATION_ERROR: 
	  printf("\n Verifica del parametro '%s' non riuscita o parametro assente.\n", routine );
	  printf(" Valore Parametro: '%s'\n", nome);
	  if (rt == TRUE) 
	  {
		  printf("\n Programma terminato con errore\n");
#ifdef DEBUG
		  abort();
#else
		  exit(PARAM_VALIDATION_ERROR);
#endif
	  }
		break;
  case STRING_MANIPULATION_ERROR:
	  printf("\n %s:Impossibile copiare o modificare la stringa '%s': stringa non valida.\n", routine, nome);
	  if (rt == TRUE)
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		  exit(STRING_MANIPULATION_ERROR);
#endif
	  }
	  break;
	  //JOHN 28/05/05
	  case DIR_CREATION_ERROR: 
	  printf("\n %s:Impossibile creare la directory %s",routine,nome);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		  exit(DIR_CREATION_ERROR);
#endif
	  }
	  break;
	  //JOHN 11/06/06	
	  case NO_SELECTED_DATA_ERROR:
	  printf("\n %s:Nessun dato selezionato %s",routine,nome);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		 //exit(NO_SELECTED_DATA_ERROR);
			exit(0);
#endif
	  }
	  break;

	  //JOHN 14/06/06	
	  case NOT_IMPLEMENTED_FUNCTION_ERROR:
	  printf("\n %s:Funzionalità non ancora implementata per il parametro %s",routine,nome);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		  exit(NOT_IMPLEMENTED_FUNCTION_ERROR);
#endif
	  }
	  break;

	  //JOHN 22/06/06	
	  case MISSING_NC_REGIONS:
	  printf("\n %s:Regioni non classificate mancanti",routine);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		  exit(MISSING_NC_REGIONS);
#endif
	  }
	  break;
	  	  case ERROR_DATA_FORMAT:
	  printf("\n Formato dati del file %s non noto", nome);
	  if(rt == TRUE) 
	  {
		  printf("\n Terminazione non corretta della routine %s\n",routine);
#ifdef DEBUG
		  abort();
#else
		  exit(ERROR_DATA_FORMAT);
#endif
	  }
	  break;

 }
 return 1;
}
