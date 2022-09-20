#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>

#include "lexico.cpp"
#include "pila.cpp"
#include "nodoSintactico.h"

using namespace std;


int main(int argc, char *argv[]){

    int tablaLR[5][4]={
        2, 0, 0,1,
        0, 0, -1,0,
        0, 3, -3,0,
        2,0,0,4,
        0,0,-2,0
    };
    int idReglas[2]={2,2};
    int lonReglas[2]={3,1};


    Pila<nodoSintactico*> pila;
    int fila, columna, accion;
    bool aceptacion;
    nodoSintactico *nodo= new nodoSintactico('E',2,0,"$",NULL,NULL,NULL);

    pila.push(/*TipoSimbolo::PESOS*/nodo);//2 en el ejemplo y ejercicios actual


    Lexico lexico; 
    lexico.entrada("a+b+c+d+e+f");
    while (true)
    {
        lexico.sigSimbolo();

        fila=pila.top()->transicion;
        switch(lexico.tipo){    //Un pequeño traductor de analizador lexico para que funcione con nuestra tabla de transiciones
            case TipoSimbolo::IDENTIFICADOR:
                columna=0;
                break;
            case TipoSimbolo::OPADIC:
                columna=1;
                break;
            case TipoSimbolo::PESOS:
                columna=2;
                break;
        }
        accion=tablaLR[fila][columna];

        pila.muestra();
        cout << "entrada: " << lexico.simbolo << endl;
        cout << "accion: " << accion << endl;
        if (accion>0){
            nodoSintactico *estado= new nodoSintactico('E',lexico.tipo,accion,lexico.simbolo,NULL,NULL,NULL);
            pila.push(estado);
        }
        if (accion<=-2){
            int rule=abs(accion)-2;//se resta 1 por el offset a la representacion de reglas en negativo y se resta otro por dispocision de arreglos de reglas
            int red=lonReglas[rule];
            int ter=idReglas[rule];
            int i=0;
            //crear un nodo para la regla
            nodoSintactico ;
            
            while(i<red){
                pila.pop();
                i++;
            }
            
            fila=pila.top();
            switch(lexico.tipo){    //Un pequeño traductor de analizador lexico para que funcione con nuestra tabla de transiciones
            case TipoSimbolo::IDENTIFICADOR:
                columna=0;
                break;
            case TipoSimbolo::OPADIC:
                columna=1;
                break;
            case TipoSimbolo::PESOS:
                columna=2;
                break;
             }
            accion=tablaLR[fila][3];

            pila.push(ter);
            pila.push(accion);
            pila.muestra();
            cout << "entrada: " << lexico.simbolo << endl;
            cout << "accion: " << accion << endl;
        }
        if (accion==-1) cout << "aceptación" << endl;
        cin.get();
    }
    

    cin.get();
  
    return 0;
}
