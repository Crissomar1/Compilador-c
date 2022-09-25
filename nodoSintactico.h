#ifndef _NODOSINTACTICO
#define _NODOSINTACTICO

#include <string>
using namespace std;

class nodoSintactico
{
public:
    char tipo;
    int token;
    int transicion;
    string valor;
    list<nodoSintactico*> hijos;

    nodoSintactico(char tipo,int token,int fila, string valor);
    ~nodoSintactico();
    nodoSintactico(int transicion,int token,string valor);
    string generaValor();
    friend ostream& operator<<(ostream& os, const nodoSintactico& nodo);
};


nodoSintactico::nodoSintactico(int transicion,int token,string valor){
    this->tipo='N';
    this->token=token;
    this->transicion=transicion;
    this->valor=valor;
}

ostream& operator<<(ostream& os,  nodoSintactico& nodo){
    if (nodo.tipo=='E'){
        os << nodo.valor << nodo.token;
    }else{
        os <<nodo.valor<<"("<< nodo.generaValor()<<")"<< nodo.token;
    }
    return os;
}

nodoSintactico::nodoSintactico(char tipo, int token,int fila, string valor){
    this->tipo=tipo;
    this->token=token;
    this->transicion=fila;
    this->valor=valor;
}

string nodoSintactico::generaValor(){
    if(tipo == 'E') return this->valor;
    else if(tipo == 'N'){
        string valor = "";
        for(list<nodoSintactico*>::iterator it = hijos.begin(); it != hijos.end(); it++){
            valor += (*it)->generaValor();
        }
        return valor;
    }
    return "";
}

nodoSintactico::~nodoSintactico()
{

}



#endif