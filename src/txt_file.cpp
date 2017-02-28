#include "txt_file.h"
#include "get_line.h"

#include <stdio.h>

TxtFile::TxtFile()
{
  // Empty text file
  sof_ = NULL;
}

TxtFile::~TxtFile()
{
  for( StringNode *next = sof_; sof_ != NULL; sof_ = next )
  {
    next = sof_->next;
    free( sof_->line );
    delete sof_;
  }
}

void TxtFile::print() const
{
  for( StringNode *sn = sof_; sn != NULL; sn = sn->next )
    printf("%s\n", sn->line );
  printf("\n");
}

bool TxtFile::load( const char *filename )
{
  FILE *fd = fopen(filename, "r");
  
  // Can't open the file
  if( fd == NULL )
    return false;
  
  char *line;
  StringNode *sn = NULL;
  while( ( line = getLine(fd) ) != NULL )
  {
    if( sn == NULL )
    {
      // First line
      sof_ = new StringNode();
      sn = sof_;
    }
    else
    {
      sn->next = new StringNode();
      sn = sn->next;
    }
    
    sn->line = line;
    sn->next = NULL;
  }
  
  fclose(fd);    
  return true;
}

bool TxtFile::save( const char *filename )
{
  FILE *fd = fopen(filename, "w");

  // Can't open the file
  if( fd == NULL )
    return false;
  
  for( StringNode *sn = sof_; sn != NULL; sn = sn->next )
    fprintf(fd, "%s\n", sn->line );
  fprintf(fd, "\n");
  
  fclose(fd);
  return true;
}