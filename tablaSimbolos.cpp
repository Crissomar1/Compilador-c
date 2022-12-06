#ifndef _TABLASIMBOLOS
#define _TABLASIMBOLOS

#include <iostream>
#include <string>
#include <list>

using namespace std;

class ElementoTabla
{
public:
    string ambito;
    string simbolo;
    string tipo;
    char tipoDato;
    void muestra();
};

void ElementoTabla::muestra()
{
    cout << "Simbolo: " << tipo << tipoDato << simbolo << " en: " << ambito << endl;
}

class TablaSimbolos
{
public:
    list<ElementoTabla> tabla;
    void inserta(string simbolo, string tipo, char tipoDato, string ambito);
    void muestra();
    bool existe(string simbolo, string ambito);
    string getTipo(string simbolo, string ambito);
    char getTipoDato(string simbolo, string ambito);
    char getTipoAnt();
    char getTipoDatoArg(int espacio, string ambito);
    stringstream& generaCodigo(stringstream &ss);
};

void TablaSimbolos::inserta(string simbolo, string tipo, char tipoDato, string ambito)
{
    ElementoTabla elemento;
    elemento.simbolo = simbolo;
    elemento.tipo = tipo;
    elemento.tipoDato = tipoDato;
    elemento.ambito = ambito;
    tabla.push_back(elemento);
}

void TablaSimbolos::muestra()
{
    list<ElementoTabla>::iterator it;
    for (it = tabla.begin(); it != tabla.end(); it++)
    {
        (*it).muestra();
    }
}

bool TablaSimbolos::existe(string simbolo, string ambito)
{
    list<ElementoTabla>::iterator it;
    for (it = tabla.begin(); it != tabla.end(); it++)
    {
        if ((*it).simbolo == simbolo && (*it).ambito == ambito)
        {
            return true;
        }
    }
    return false;
}

string TablaSimbolos::getTipo(string simbolo, string ambito)
{
    list<ElementoTabla>::iterator it;
    for (it = tabla.begin(); it != tabla.end(); it++)
    {
        if ((*it).simbolo == simbolo && (*it).ambito == ambito)
        {
            return (*it).tipo;
        }
    }
    for (it = tabla.begin(); it != tabla.end(); it++)
    {
        if ((*it).simbolo == simbolo && (*it).ambito == "global")
        {
            return (*it).tipo;
        }
    }
    return "";
}

char TablaSimbolos::getTipoDato(string simbolo, string ambito)
{
    list<ElementoTabla>::iterator it;
    for (it = tabla.begin(); it != tabla.end(); it++)
    {
        if ((*it).simbolo == simbolo && (*it).ambito == ambito)
        {
            return (*it).tipoDato;
        }
    }
    for(it = tabla.begin(); it != tabla.end(); it++)
    {
        if((*it).simbolo == simbolo && (*it).ambito == ambito+"Param")
        {
            return (*it).tipoDato;
        }
    }
    for(it = tabla.begin(); it != tabla.end(); it++)
    {
        if((*it).simbolo == simbolo && (*it).ambito == "global")
        {
            return (*it).tipoDato;
        }
    }
    
    return ' ';
}

char TablaSimbolos::getTipoAnt()
{
    return tabla.end()->tipoDato;
}

char TablaSimbolos::getTipoDatoArg(int espacio, string ambito)
{
    ambito = ambito + "Param";
    int contador = 0;
    list<ElementoTabla>::iterator it;
    for (it = tabla.begin(); it != tabla.end(); it++)
    {
        if((*it).ambito == ambito)
        {
            if(contador == espacio)
            {
                return (*it).tipoDato;
            }
            contador++;
        }
    }
    return ' ';
}

stringstream& TablaSimbolos::generaCodigo(stringstream &ss){
    list<ElementoTabla>::iterator it;
    for(it = tabla.begin(); it != tabla.end(); it++)
    {
        if((*it).ambito == "global"||(*it).tipo!="DefFunc")
        {
            ss << (*it).tipoDato << (*it).simbolo << " dd 0" << endl;
        }
    }
    return ss;
}



#endif
