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
    nodoSintactico *hijoIzq;
    nodoSintactico *hijoOperacion;
    nodoSintactico *hijoDer;

    nodoSintactico(char tipo,int token,int fila, string valor, nodoSintactico *hijoIzq, nodoSintactico *hijoDer, nodoSintactico *hermanoDer);
    ~nodoSintactico();
    nodoSintactico(int transicion,int token,nodoSintactico *hijoIzq, nodoSintactico *hijoOperacion, nodoSintactico *hijoDer);
    string generaValor();
};


nodoSintactico::nodoSintactico(int transicion,int token, nodoSintactico *hijoIzq, nodoSintactico *hijoOperacion, nodoSintactico *hijoDer){
    this->tipo='N';
    this->token=token;
    this->transicion=transicion;
    this->valor="";
    this->hijoIzq=hijoIzq;
    this->hijoOperacion=hijoOperacion;
    this->hijoDer=hijoDer;
}

nodoSintactico::nodoSintactico(char tipo, int token,int fila, string valor, nodoSintactico *hijoIzq, nodoSintactico *hijoDer, nodoSintactico *hermanoDer)
{
    this->tipo = tipo;
    this->token = token;
    this->transicion = fila;
    this->valor = valor;
    this->hijoIzq = hijoIzq;
    this->hijoDer = hijoDer;
    this->hijoOperacion = hijoOperacion;
}

string nodoSintactico::generaValor(){
    if(tipo == 'E') return this->valor;
    else if(tipo == 'N'){
        string valorIzq = this->hijoIzq->generaValor();
        string valorDer = this->hijoDer->generaValor();
        string operacion = this->hijoOperacion->generaValor();
        return valorIzq + operacion + valorDer;
    }
}

nodoSintactico::~nodoSintactico()
{

}

class Estado:private nodoSintactico
{
private:
    int estado;
    string valor;
    Estado *hijoIzq;
    Estado *hijoDer;
    Estado *hermanoDer;
};

#endif