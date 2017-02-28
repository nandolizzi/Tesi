#include "get_line.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_MAXLINE 256

static int endOfLine(FILE *fin, int c)
{
  int eol = (c=='\r' || c=='\n');
  if (c == '\r')
  {
    c = getc(fin);
    if (c != '\n' && c != EOF)
      ungetc(c, fin);
  }
  return eol;
}


char *getLine(FILE *fin)
{
	int i, c;
	char *newl;
	int maxline = INIT_MAXLINE;
	char *line = (char *) malloc(maxline);

	/* Si effettua un controllo per verificare che il file non sia vuoto*/
	if (line == NULL)
	{
		return NULL;
	}
	for (i = 0; (c=getc(fin))!=EOF && !endOfLine(fin,c); i++)
	{
		if (i >= maxline -1)
		{
			maxline *= 2;
			newl = (char *) realloc (line, maxline);
			/*Si effettua un controllo in seguito alla allocazione
			  della memoria*/
			if (newl == NULL)
			{
				free(line);
				return NULL;
			}
			line = newl;
		}
		/* Si assegna di volta in volta a c il valore corrispondente a line [i],
		   uscita dal loop avrò in c solo l'ultimo valore letto da line */
		line[i] = c;
	}
	
	line[i]= '\0';

	/*Se il carattere di terminazione del file si presenta in corrispondenza di i= 0 		  allora la chiamata della funzione non ritorna nulla */
	if (c == EOF && i == 0)
	{
		free(line);
		return NULL;
	}
	else
		return line;
}
