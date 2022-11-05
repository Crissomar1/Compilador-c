#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include <sstream>

#include "lexico.cpp"
#include "pila.cpp"
#include "nodoSintactico.h"
#include "gramatica.h"

using namespace std;

Gramatica gramatica;

Pila pila;
int fila, columna, siguienteFila;
bool aceptacion;

bool lockSimbolo = false;
Lexico lexico; 
string entrada ;

void semantica();

int main(int argc, char *argv[]){
    nodoSintactico *nodo= new nodoSintactico('E',TipoSimbolo::PESOS,0,"$");

    pila.push(/*TipoSimbolo::PESOS*/nodo);//2 en el ejemplo y ejercicios actual

    
    ifstream archivo("Prueba.txt");
    stringstream ss;
    ss << archivo.rdbuf();
    entrada = ss.str();
    cout << "Entrada: "<<endl << entrada << endl << endl;
    
    lexico.entrada(entrada);
    semantica();
    pila.muestra();
  
    return 0;
}

void desplazar(){
    nodoSintactico *estado= new nodoSintactico('E',columna,siguienteFila,lexico.simbolo);
    pila.push(estado);
}

void reducir(){
    int regla = abs(siguienteFila)-2;
    int n = gramatica.lonRegla[regla];
    nodoSintactico *nodo= new nodoSintactico('N',siguienteFila,gramatica.idRegla[regla],gramatica.simRegla[regla]);
    for(int i=0;i<n;i++){
        nodo->hijos.push_front(pila.top());
        pila.pop();
    }

    columna=gramatica.idRegla[regla];
    fila = pila.top()->fila;

    pila.push(nodo);

    siguienteFila = gramatica.tablaLR[fila][columna];
    pila.top()->fila = siguienteFila;

    siguienteFila = gramatica.tablaLR[pila.top()->fila][lexico.tipo];
    if(siguienteFila<-1){
        reducir();
        return;
    }

    nodoSintactico *nodo2= new nodoSintactico('E',lexico.tipo,siguienteFila,lexico.simbolo);
    pila.push(nodo2);
}

void semantica(){
    while (true)
    {
        lexico.sigSimbolo();

        fila=pila.top()->fila;
        columna=lexico.tipo;
        
        siguienteFila=gramatica.tablaLR[fila][columna];

        if (siguienteFila>0){
            desplazar();
        }
        if (siguienteFila<=-2){
            reducir();
        }
        if (siguienteFila==-1){
            cout << "aceptación" << endl;
            break;
        }
        if (siguienteFila==0){
          cout << "error simbolo inesperado: " << lexico.simbolo << endl;
            cin.get();
            return;
        }

    }
    

    std::cin.get();
}