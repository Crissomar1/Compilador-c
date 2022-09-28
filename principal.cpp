#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>

#include "lexico.cpp"
#include "pila.cpp"
#include "nodoSintactico.h"
#include "gramatica.h"

using namespace std;


int main(int argc, char *argv[]){
    Gramatica gramatica;

    Pila pila;
    int fila, columna, accion;
    bool aceptacion;
    nodoSintactico *nodo= new nodoSintactico('E',TipoSimbolo::PESOS,0,"$");

    pila.push(/*TipoSimbolo::PESOS*/nodo);//2 en el ejemplo y ejercicios actual


    Lexico lexico; 
    string entrada = "int a; a=1; float real = 23.98;";
    cout << "Entrada: " << entrada << endl;
    
    lexico.entrada(entrada);
    while (true)
    {
        lexico.sigSimbolo();

        fila=pila.top()->transicion;
        columna=lexico.tipo;
        accion=gramatica.tablaLR[fila][columna];

        pila.muestra();
        cout << "entrada: " << lexico.simbolo << endl;
        cout << "accion: " << accion << endl;
        if (accion>0){
            nodoSintactico *estado= new nodoSintactico('E',columna,accion,lexico.simbolo);
            pila.push(estado);
        }
        if (accion<=-2){
            int rule=abs(accion)-2;//se resta 1 por el offset a la representacion de reglas en negativo y se resta otro por dispocision de arreglos de reglas
            int red=gramatica.lonRegla[rule];
            int ter=gramatica.idRegla[rule];
            int i=0;
            //crear un nodo para la regla
            nodoSintactico *nodo= new nodoSintactico('N',accion,ter,gramatica.simRegla[rule]);
            cout<<red<<endl;
            while(i<red){
                nodo->hijos.push_front(pila.top());
                pila.pop();
                i++;
            }
            
            fila=pila.top()->transicion;
            accion=gramatica.tablaLR[fila][ter];
            nodo->transicion=accion;
            pila.push(nodo);
            pila.muestra();
            cout << "entrada: " << lexico.simbolo << endl;
            cout << "accion: " << accion << endl;
        }
        if (accion==-1){
            cout << "aceptación" << endl;
            break;
        }
        cin.get();
    }
    

    cin.get();
  
    return 0;
}
