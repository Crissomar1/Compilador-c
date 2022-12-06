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

void sintactica();
void analisisSemantico();
string generaCodigo();

int main(int argc, char *argv[]){
    nodoSintactico *nodo= new nodoSintactico('E',TipoSimbolo::PESOS,0,"$",0,0);
    pila.push(/*TipoSimbolo::PESOS*/nodo);//2 en el ejemplo y ejercicios actual

    
    ifstream archivo("Prueba.txt");
    stringstream ss;
    ss << archivo.rdbuf();
    entrada = ss.str();
    cout << "Entrada: "<<endl << entrada << endl << endl;
    
    lexico.entrada(entrada);
    sintactica();
    analisisSemantico();
    if (error){
        cout << "No es posible generar codigo con error." << endl;
    }else{
        cout << "No hay errores Generando codigo:" << endl;
        cout << generaCodigo() << endl;
    }
  
    return 0;
}

void desplazar(){
    nodoSintactico *estado= new nodoSintactico('E',columna,siguienteFila,lexico.simbolo,0,lexico.linea);
    pila.push(estado);
}

void reducir(){
    int regla = abs(siguienteFila)-2;
    int n = gramatica.lonRegla[regla];
    nodoSintactico *nodo= new nodoSintactico('N',siguienteFila,gramatica.idRegla[regla],gramatica.simRegla[regla],regla,lexico.linea);
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

    nodoSintactico *nodo2= new nodoSintactico('E',lexico.tipo,siguienteFila,lexico.simbolo,0,lexico.linea);
    pila.push(nodo2);
}

void sintactica(){
    while (true)
    {
        lexico.sigSimbolo();
        if(lexico.tipo==TipoSimbolo::ERROR){
            cout << "Error lexico en la linea: " << lexico.linea << endl;
            return;
        }

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
            cout << "ln " << lexico.linea;
          cout << ": Error simbolo inesperado: " << lexico.simbolo << endl;
            cin.get();
            return;
        }

    }
    

    std::cin.get();
}

void analisisSemantico(){
    cout << "Analisis Semantico" << endl;
    pila.analiza();
}

string generaCodigo(){
    return pila.generaCodigo();
}