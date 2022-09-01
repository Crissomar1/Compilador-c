#ifndef _PILA
#define _PILA

#include <list>
#include <iostream>
#include <string>

using namespace std;

template<class T>
class Pila{

   private:      
      list <T> lista;      
      
   public:      
      void push( T x);
      T top();
      T pop();
      void muestra();
};


#endif
