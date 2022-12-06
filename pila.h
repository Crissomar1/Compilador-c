#ifndef _PILA
#define _PILA

#include <list>
#include <iostream>
#include <string>
#include "nodoSintactico.h"

using namespace std;

class Pila{

   private:      
      list <nodoSintactico*> lista;      
      
   public:      
      void push( nodoSintactico* x);
      nodoSintactico* top();
      nodoSintactico* pop();
      void muestra();
      void analiza();
      string generaCodigo();
};


#endif
