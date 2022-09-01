#include "pila.h"
#include "lexico.h"
#include <sstream>


template<class T>
  void Pila<T>::push( T x){
       lista.push_front(x);
  }

template<class T>
 T  Pila<T>::pop(){

     int x= *lista.begin();
     lista.erase ( lista.begin() );
     
     return x;
  }

 template<class T>
  T Pila<T>::top(){
     return *lista.begin();     
  }

  template<class T>
  void Pila<T>::muestra(){

     list<int>::reverse_iterator it;

     cout << "Pila: ";   
     
     for (it= lista.rbegin(); it != lista.rend(); it++){
         cout << (*it) << " ";         
     } 
  
     cout << endl;
  }
