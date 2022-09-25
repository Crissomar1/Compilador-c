#ifndef _GRAMATICA
#define _GRAMATICA

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Gramatica
{
    public:
    int reglas;
    vector<int> idRegla;
    vector<int> lonRegla;
    vector<string> simRegla;
    int filas, columnas;
    vector<vector<int> > tablaLR;
    Gramatica();
    ~Gramatica();
};

Gramatica::Gramatica()
{
    //leer archivo
    ifstream archivo("GramaticaCompilador/compilador.lr", ios::in);
    if(archivo.fail()){
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }
    //leer reglas
    archivo >> reglas;
    idRegla.resize(reglas);
    lonRegla.resize(reglas);
    simRegla.resize(reglas);
    for(int i = 0; i < reglas; i++){
        archivo >> idRegla[i];
        archivo >> lonRegla[i];
        archivo >> simRegla[i];
    }
    //leer tabla
    archivo >> filas >> columnas;
    tablaLR.resize(filas);
    for(int i = 0; i < filas; i++){
        tablaLR[i].resize(columnas);
        for(int j = 0; j < columnas; j++){
            archivo >> tablaLR[i][j];
        }
    }
    archivo.close();
    
}

Gramatica::~Gramatica()
{
}


#endif