#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>

#include "lexico.cpp"
#include "pila.cpp"

using namespace std;


int main(int argc, char *argv[]){

    int tablaLR[5][4]={
        2, 0, 0,1,
        0, 0, -1,0,
        0, 3, -2,0,
        2,0,0,4,
        0,0,1,0
    };
    int idReglas[2]={2,2};
    int lonReglas[2]={3,0};


    Pila<int> pila;
    int fila, columna, accion;
    bool aceptacion;

    pila.push(TipoSimbolo::PESOS);
    pila.push(0);

    Lexico lexico; 
    lexico.entrada("a+b+c+d+e+f");
    while (true)
    {
        lexico.sigSimbolo();

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
        accion=tablaLR[fila][columna];

        pila.muestra();
        cout << "entrada: " << lexico.simbolo << endl;
        cout << "accion: " << accion << endl;
        if (accion>0){
            pila.push(lexico.tipo);
            pila.push(accion);
        }
        if (accion<=-2){
            int rule=abs(accion);
            int red=lonReglas[rule];
            int ter=idReglas[rule];
            int i=0;

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
            accion=tablaLR[fila][columna];
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
