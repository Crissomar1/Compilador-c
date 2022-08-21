#include <cstdlib>
#include <iostream>
#include <string>

#include "lexico.cpp"

using namespace std;

int main(int argc, char *argv[]){

    
    Lexico lexico; 
    lexico.entrada("/12*33+2><!!&&&|||a  migo23+if+_amigo=3-+.0=0-");
    
    cout << "Resultado del Analisis Lexico" << endl << endl;
    cout << "Simbolo\t\tTipo" << endl;
    
    while ( lexico.simbolo.compare("$") != 0 ){
          lexico.sigSimbolo();
          
          cout <<  lexico.simbolo << "\t\t" << lexico.tipoAcad(lexico.tipo) << endl;          
    }
        
    cin.get();
  
    return 0;
}
