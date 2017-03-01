#pragma once
#include "usefull_file.h"

class ConfigFile : public UsefullFile
{
public:
	ConfigFile();
	virtual ~ConfigFile();
	
	virtual void print() const;
 	virtual bool load( const char *filename );
	virtual bool save( const char *filename );

	//int printAllParameters();


private:
	struct StringNode
  {
    char *line;
    StringNode *next;
  };
  
  // Pointer to the first and last elementi in the list
  StringNode *sof_;
};