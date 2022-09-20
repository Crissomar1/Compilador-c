#ifndef _NODOSINTACTICO
#define _NODOSINTACTICO

#include <string>
using namespace std;

class nodoSintactico
{
private:
    int tipo;
    string valor;
    nodoSintactico *hijoIzq;
    nodoSintactico *hijoDer;
    nodoSintactico *hermanoDer;
public:
    nodoSintactico(int tipo, string valor, nodoSintactico *hijoIzq, nodoSintactico *hijoDer, nodoSintactico *hermanoDer);
    ~nodoSintactico();
};

nodoSintactico::nodoSintactico(int tipo, string valor, nodoSintactico *hijoIzq, nodoSintactico *hijoDer, nodoSintactico *hermanoDer)
{
    this->tipo = tipo;
    this->valor = valor;
    this->hijoIzq = hijoIzq;
    this->hijoDer = hijoDer;
    this->hermanoDer = hermanoDer;
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
}

#endif