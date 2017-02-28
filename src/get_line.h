#pragma once

#include <stdio.h>
#include <stdlib.h>

/* Read from an input file the next text line. 
 * Return the read string by means of a newly allocated char array, 
 * or NULL in case of error or if the end of the file has been reached. 
 * Whe you have finished to use the returned string, use free() to dealloc */
char *getLine(FILE *fin);