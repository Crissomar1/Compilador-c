#ifndef _NODOSINTACTICO
#define _NODOSINTACTICO

#include <string>
using namespace std;

int contador=0;

class nodoSintactico
{
public:
    char tipo;
    int token;
    int fila;
    string valor;
    list<nodoSintactico*> hijos;

    nodoSintactico(char tipo,int token,int fila, string valor);
    ~nodoSintactico();
    nodoSintactico(int fila,int token,string valor);
    string generaValor();
    friend ostream& operator<<(ostream& os, const nodoSintactico& nodo);
};


nodoSintactico::nodoSintactico(int fila,int token,string valor){
    this->tipo='N';
    this->token=token;
    this->fila=fila;
    this->valor=valor;
}

ostream& operator<<(ostream& os,  nodoSintactico& nodo){
    for(int i=0;i<contador;i++){
        os << "|-";
    }
    os << nodo.valor << endl;
    contador++;
    list<nodoSintactico*>::iterator it;
    for(it=nodo.hijos.begin();it!=nodo.hijos.end();it++){
        os << *(*it);
    }
    contador--;
    return os;
}

nodoSintactico::nodoSintactico(char tipo, int token,int fila, string valor){
    this->tipo=tipo;
    this->token=token;
    this->fila=fila;
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