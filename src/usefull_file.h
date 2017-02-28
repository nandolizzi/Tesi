#pragma once

class UsefullFile
{
public:

  virtual ~UsefullFile(){};

  /* Print the file to stdout in a readable format */
  virtual void print() const = 0;
  /* Load to memory a file
   * Return true on success, false otherwise */
  virtual bool load( const char *filename ) = 0;
  /* Save to disk a file
   * Return true on success, false otherwise */
  virtual bool save( const char *filename ) = 0;
};
