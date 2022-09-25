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

    // int tablaLR[5][4]={
    //     2, 0, 0,1,
    //     0, 0, -1,0,
    //     0, 3, -3,0,
    //     2,0,0,4,
    //     0,0,-2,0
    // };
    // int idReglas[2]={2,2};
    // int lonReglas[2]={3,1};

    Gramatica gramatica;

    Pila pila;
    int fila, columna, accion;
    bool aceptacion;
    nodoSintactico *nodo= new nodoSintactico('E',TipoSimbolo::PESOS,0,"$");

    pila.push(/*TipoSimbolo::PESOS*/nodo);//2 en el ejemplo y ejercicios actual


    Lexico lexico; 
    string entrada = "int main(){int a; a=1;}";
    cout << "Entrada: " << entrada << endl;
    
    lexico.entrada(entrada);
    while (true)
    {
        lexico.sigSimbolo();

        fila=pila.top()->transicion;
        // switch(lexico.tipo){    //Un pequeño traductor de analizador lexico para que funcione con nuestra tabla de transiciones
        //     case TipoSimbolo::IDENTIFICADOR:
        //         columna=0;
        //         break;
        //     case TipoSimbolo::OPADIC:
        //         columna=1;
        //         break;
        //     case TipoSimbolo::PESOS:
        //         columna=2;
        //         break;
        // }
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
