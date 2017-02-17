#pragma once

/* Classe necessaria alla configurazione del file */

 class Param_elem
   {
   
   public:
   
   /* Costruttore, costruttore di copia e distruttore */
   
   Param_elem(){};
   Param_elem(char *descr, int type, int length, int state, void *name);
   Param_elem(const Param_elem &other);
   ~Param_elem(){};

   // Stampa a video della cella
   void printCell() const;

   // Metodi per la restituzione dei parametri privati
   inline int getType() const { return _type ; };
   inline int getLength() const { return _length; };
   inline int getState() const { return _state; };

   // Metodo per la modifica dei valori della cella
   void setCell(char *descr, int type, int length, int state, void *value);

   private:

   int _type, _length, _state;
   char *_descr;
   void *_value;
   };
