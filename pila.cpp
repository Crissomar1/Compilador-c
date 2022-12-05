#include "pila.h"
#include "lexico.h"
#include <sstream>


void Pila::push( nodoSintactico* x){
       lista.push_front(x);
}

nodoSintactico*  Pila::pop(){

   nodoSintactico* x= *lista.begin();
   lista.erase ( lista.begin() );
   
   return x;
}

nodoSintactico* Pila::top(){
     return *lista.begin();     
  }

void Pila::muestra(){

   list<nodoSintactico*>::reverse_iterator it;
   contador=0;
   cout << "Arbol: ";
   
   for (it= lista.rbegin(); it != lista.rend(); it++){
      cout << *(*it) << " ";         
   } 

   cout << endl;
}

void Pila::analiza(){
   list<nodoSintactico*>::iterator it;
   contador=0;
   cout << "Anailisis: ";
   
   for (it= lista.begin(); it != lista.end(); it++){
      (*it)->validaTipos();         
   } 

   cout << endl;
}