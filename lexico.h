#ifndef _LEXICO
#define _LEXICO

#include <iostream>
#include <string>
using namespace std;

class TipoSimbolo{
public:
 static const int ERROR= -1;       
 static const int IDENTIFICADOR= 0;
 static const int OPADIC= 1;
 static const int OPMULT= 2;
 static const int PESOS= 3;       
 static const int ENTERO= 4;
 static const int REAL= 5;
 static const int ASIGN= 6;
 static const int OPRELA= 7;
 static const int AND= 8;
 static const int OR= 9;
 static const int NOT= 10;
 static const int PARENTECIS= 11;
 static const int LLAVE= 12;
 static const int PUNTCOMM= 13;
 static const int IF= 14;
 static const int WHILE= 15;
 static const int RET= 16;
 static const int ELSE= 17;
 static const int INT= 18;
 static const int FLOAT= 19;
};


class Lexico{
      private:
       string fuente;
              
       int ind;       
       bool continua;
       char c;
       int estado;

       char sigCaracter();       
       void sigEstado(int estado);
       void aceptacion(int estado);
       bool esLetra(char c);
       bool esDigito(char c);
       bool esEspacio(char c);
       
       bool esReservada(string sim);
       void retroceso();
              
      public:
       string simbolo;
       int tipo;
             
       Lexico(string fuente);             
       Lexico();
       
       void entrada(string fuente);              
       string tipoAcad(int tipo);

       int sigSimbolo();
       bool terminado();
       
};


#endif