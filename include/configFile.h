#pragma once


class ConfigFile
{
public:
  
  ConfigFile();
  ~ConfigFile();

  void print() const;
  bool load( const char *filename );
  bool save( const char *filename );
  
  
private:

  struct StringNode
  {
    char *line;
    StringNode *next;
  };
  
  // Pointer to the first and last elementi in the list
  StringNode *sof_;
};

