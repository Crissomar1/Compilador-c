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

     cout << "Pila: ";   
     
     for (it= lista.rbegin(); it != lista.rend(); it++){
         cout << (*it) << " ";         
     } 
  
     cout << endl;
  }
