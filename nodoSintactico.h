#ifndef _NODOSINTACTICO
#define _NODOSINTACTICO

#include <string>
#include <sstream>
#include "tablaSimbolos.cpp"
using namespace std;

int contador=0;

string ambito;
TablaSimbolos tabla;
bool error = false;

class nodoSintactico
{
public:
    char tipo;
    char tipoDato;
    int token;
    int fila;
    int regla;
    int linea;
    string valor;
    list<nodoSintactico*> hijos;

    nodoSintactico(char tipo,int token,int fila, string valor,int regla,int linea=0);
    ~nodoSintactico();
    nodoSintactico(int fila,int token,string valor);
    string generaValor();
    friend ostream& operator<<(ostream& os, const nodoSintactico& nodo);
    char validaTipos();
    stringstream& generaCodigo(stringstream& codigo);
};


nodoSintactico::nodoSintactico(int fila,int token,string valor){
    this->tipo='N';
    this->token=token;
    this->fila=fila;
    this->valor=valor;
}

ostream& operator<<(ostream& os,  nodoSintactico& nodo){
    for(int i=0;i<contador;i++){
        os << "|-";
    }
    os << nodo.valor << endl;
    contador++;
    list<nodoSintactico*>::iterator it;
    for(it=nodo.hijos.begin();it!=nodo.hijos.end();it++){
        os << *(*it);
    }
    contador--;
    return os;
}

nodoSintactico::nodoSintactico(char tipo, int token,int fila, string valor,int regla,int linea){
    this->tipo=tipo;
    this->token=token;
    this->fila=fila;
    this->valor=valor;
    this->regla=regla;
    this->linea=linea;
}

string nodoSintactico::generaValor(){
    if(tipo == 'E') return this->valor;
    else if(tipo == 'N'){
        string valor = "";
        for(list<nodoSintactico*>::iterator it = hijos.begin(); it != hijos.end(); it++){
            valor += (*it)->generaValor();
        }
        return valor;
    }
    return "";
}

nodoSintactico::~nodoSintactico()
{

}


char nodoSintactico::validaTipos(){
    list<nodoSintactico*>::iterator it;
    int i,espacio=0;
    string simbolo;
    string tipoDef;
    stringstream ss;
    char tipoDato, tipoDato2;
    string ambitoAnt;
    if(tipo == 'N'){
        switch (regla+1)
        {
        case 1:
            ambito = "global";
            hijos.front()->validaTipos();
            break;
        case 2:
            break;
        case 3:
            hijos.front()->validaTipos();
            hijos.back()->validaTipos();
            break;
        case 4:
            hijos.front()->validaTipos();
            break;
        case 5:
            hijos.front()->validaTipos();
            break;
        case 6:
            for(it=hijos.begin(),i = 0;it!=hijos.end();it++,i++){
                switch (i)
                {
                case 0:
                    tipoDef = valor;
                    tipoDato=(*it)->valor[0];
                    break;
                case 1:
                    simbolo = (*it)->valor;
                    if(tabla.existe(simbolo,ambito)||tabla.existe(simbolo,ambito+"Param")){
                        cout<<"Ln "<<this->linea<<": ";
                        cout << "Error semantico: " << simbolo << " ya existe"<< endl;
                        error=true;
                    }else{
                        tabla.inserta(simbolo,tipoDef,tipoDato,ambito);
                    }
                    break;
                case 2:
                    (*it)->validaTipos();
                    break;
                case 3:
                    break;

                default:
                    cout << "Error en la regla 6" << endl;
                    break;   
                }
            }
            break;
        case 7:
            break;
        case 8:
            for(it=hijos.begin(),i = 0;it!=hijos.end();it++,i++){
                switch (i)
                {
                case 0:
                    break;
                case 1:
                    tipoDef = "DefVar";
                    tipoDato=tabla.getTipoAnt();
                    simbolo = (*it)->valor;
                    if(tabla.existe(simbolo,ambito)||tabla.existe(simbolo,ambito+"Param")){
                        cout<<"Ln "<<this->linea<<": ";
                        cout << "Error semantico: " << simbolo << " ya existe"<< endl;
                        error=true;
                    }else{
                        tabla.inserta(simbolo,tipoDef,tipoDato,ambito);
                    }
                    break;
                case 2:
                    (*it)->validaTipos();
                    break;

                default:
                    cout << "Error en la regla 8" << endl;
                    break;   
                }
            }
            
            break;
        case 9:
            for(it=hijos.begin(),i = 0;it!=hijos.end();it++,i++){
                switch (i)
                {
                case 0:
                    tipoDef = "DefFunc";
                    tipoDato=(*it)->valor[0];
                    break;
                case 1:
                    simbolo = (*it)->valor;
                    if(tabla.existe(simbolo,ambito)){
                        cout<<"Ln "<<(*it)->linea<<": ";
                        cout << "Error semantico: " << simbolo << " ya existe"<< endl;
                        error=true;
                    }else{
                        tabla.inserta(simbolo,tipoDef,tipoDato,ambito);
                    }
                    break;
                case 2:
                    break;
                case 3:
                    ambitoAnt = ambito;
                    ambito = simbolo;
                    (*it)->validaTipos();
                    break;
                case 4:
                    break;
                case 5:
                    (*it)->validaTipos();
                    ambito = ambitoAnt;
                    break;

                default:
                    cout << "Error en la regla 9" << endl;
                    break;   
                }
            }
            break;
        case 10:
            break;
        case 11:
            for(it=hijos.begin(),i = 0;it!=hijos.end();it++,i++){
                switch (i)
                {
                case 0:
                    tipoDef = "DefVar";
                    tipoDato=(*it)->valor[0];
                    break;
                case 1:
                    simbolo = (*it)->valor;
                    if(tabla.existe(simbolo,ambito+"Param")){
                        cout<<"Ln "<<this->linea<<": ";
                        cout << "Error semantico: " << simbolo << " ya existe"<< endl;
                        error=true;
                    }else{
                        tabla.inserta(simbolo,tipoDef,tipoDato,ambito+"Param");
                    }
                    break;
                case 2:
                    (*it)->validaTipos();
                    break;

                default:
                    cout << "Error en la regla 11" << endl;
                    break;   
                }
            }
            break;
        case 12:
            break;
        case 13:
            for(it=hijos.begin(),i = 0;it!=hijos.end();it++,i++){
                switch (i)
                {
                case 0:
                    break;
                case 1:
                    tipoDef = "DefVar";
                    tipoDato=(*it)->valor[0];
                    break;
                case 2:
                    simbolo = (*it)->valor;
                    if(tabla.existe(simbolo,ambito+"Param")){
                        cout<<"Ln "<<this->linea<<": ";
                        cout << "Error semantico: " << simbolo << " ya existe"<< endl;
                        error=true;
                    }else{
                        tabla.inserta(simbolo,tipoDef,tipoDato,ambito+"Param");
                    }
                    break;
                case 3:
                    (*it)->validaTipos();
                    break;

                default:
                    cout << "Error en la regla 13" << endl;
                    break;   
                }
            }
            break;
        case 14:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            break;
        case 15:
            break;
        case 16:
            it=hijos.begin();
            (*it)->validaTipos();
            it++;
            (*it)->validaTipos();
            break;
        case 17:
            (*hijos.begin())->validaTipos();
            break;
        case 18:
            (*hijos.begin())->validaTipos();
            break;
        case 19:
            break;
        case 20:
            (*hijos.begin())->validaTipos();
            (*hijos.end())->validaTipos();
            break;
        case 21:
            it=hijos.begin();
            simbolo = (*it)->valor;
            if(!(tabla.existe(simbolo,ambito)||tabla.existe(simbolo,ambito+"Param"))){
                cout<<"Ln "<<this->linea<<": ";
                cout << "Error semantico: " << simbolo << " no definido"<< endl;
                error=true;
            }else{
                tipoDato = tabla.getTipoDato(simbolo,ambito);
                it++;
                it++;
                (*it)->validaTipos();
                tipoDato2 = (*it)->tipoDato;
                if(tipoDato != tipoDato2){
                    cout<<"Ln "<<this->linea<<": ";
                    cout << "Error semantico: " << simbolo << " no es de tipo " << tipoDato2 << endl;
                    error=true;
                }
            }
            break;
        case 22:
            it=hijos.begin();
            it++;
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo booleano" << endl;
                error=true;
            }
            it++;
            it++;
            (*it)->validaTipos();
            it++;
            (*it)->validaTipos();
            break;
        case 23:
            it=hijos.begin();
            it++;
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo booleano" << endl;
                error=true;
            }
            it++;
            it++;
            (*it)->validaTipos();
            break;
        case 24:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != tabla.getTipoDato(ambito,"global")){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es del tipo de la funcion" << endl;
                error=true;
            }
            break;

        case 25:
            it=hijos.begin();
            (*it)->validaTipos();
            break;
        case 26:
            break;
        case 27:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            break;
        case 28:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            break;
        case 29:
            break;
        case 30:
            it=hijos.begin();
            (*it)->validaTipos();
            this->tipoDato = (*it)->tipoDato;
            break;
        case 31:
            break;
        case 32:
            it=hijos.begin();
            ambitoAnt=ambito;
            ss<<ambito;
            getline(ss,simbolo,',');
            getline(ss,ambito);
            (*it)->validaTipos();
            tipoDato = (*it)->tipoDato;
            tipoDato2 = tabla.getTipoDatoArg(espacio++,simbolo);
            if(tipoDato != tipoDato2){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo de Argumento" << endl;
                error=true;
            }
            it++;
            ambito=ambitoAnt;
            (*it)->validaTipos();
            espacio=0;
            break;
        case 33:
            break;
        case 34:
            it=hijos.begin();
            it++;
            ambitoAnt=ambito;
            ss<<ambito;
            getline(ss,simbolo,',');
            getline(ss,ambito);
            (*it)->validaTipos();
            if((*it)->tipoDato != tabla.getTipoDatoArg(espacio++,simbolo)){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo de Argumento" << endl;
                error=true;
            }
            it++;
            ambito=ambitoAnt;
            (*it)->validaTipos();
            break;
        case 35:
            it=hijos.begin();
            (*it)->validaTipos();
            this->tipoDato = (*it)->tipoDato;
            break;
        case 36:
            if(!(tabla.existe((*hijos.begin())->valor,ambito)||tabla.existe((*hijos.begin())->valor,ambito+"Param"))){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout<<"Error semantico: "<<(*hijos.begin())->valor<<" no definido"<<endl;
                error=true;
            }else{
                this->tipoDato = tabla.getTipoDato((*hijos.begin())->valor,ambito);
            }
            break;
        case 37:
            this->tipoDato = 'i';
            break;
        case 38:
            this->tipoDato = 'f';
            break;
        case 39:
            this->tipoDato = 's';
            break;
        case 40:
            it=hijos.begin();
            this->tipoDato = tabla.getTipoDato((*it)->valor,ambito);
            if(tabla.getTipo((*it)->valor,ambito) != "DefFunc"){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout<<"Error semantico: "<<(*it)->valor<<" no es Funcion"<<endl;
                error=true;
            }
            ambitoAnt=ambito;
            ambito=(*it)->valor+","+ambito;
            it++;
            it++;
            (*it)->validaTipos();
            ambito=ambitoAnt;
            break;
        case 41:
            it=hijos.begin();
            (*it)->validaTipos();
            break;
        case 42:
            it=hijos.begin();
            (*it)->validaTipos();
            break;
        case 43:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            this->tipoDato = (*it)->tipoDato;
            break;
        case 44:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            this->tipoDato = (*it)->tipoDato;
            break;
        case 45:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo bool" << endl;
                error=true;
            }
            this->tipoDato = (*it)->tipoDato;
            break;
        case 46:
            it=hijos.begin();
            (*it)->validaTipos();
            tipoDato = (*it)->tipoDato;
            it++;
            it++;
            (*it)->validaTipos();
            tipoDato2 = (*it)->tipoDato;
            if(tipoDato != tipoDato2){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo " << tipoDato << endl;
                error=true;
            }
            this->tipoDato = (*it)->tipoDato;
            break;
        case 47:
            it=hijos.begin();
            (*it)->validaTipos();
            tipoDato = (*it)->tipoDato;
            it++;
            it++;
            (*it)->validaTipos();
            tipoDato2 = (*it)->tipoDato;
            if(tipoDato != tipoDato2){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo " << tipoDato << endl;
                error=true;
            }
            this->tipoDato = (*it)->tipoDato;
            break;
        case 48:
            it=hijos.begin();
            (*it)->validaTipos();
            tipoDato = (*it)->tipoDato;
            it++;
            it++;
            (*it)->validaTipos();
            tipoDato2 = (*it)->tipoDato;
            if(tipoDato != tipoDato2){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo " << tipoDato << endl;
                error=true;
            }
            this->tipoDato = 'b';
            break;
        case 49:
            it=hijos.begin();
            (*it)->validaTipos();
            tipoDato = (*it)->tipoDato;
            it++;
            it++;
            (*it)->validaTipos();
            tipoDato2 = (*it)->tipoDato;
            if(tipoDato != tipoDato2){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo " << tipoDato << endl;
                error=true;
            }
            this->tipoDato = 'b';
            break;
        case 50:
            it=hijos.begin();
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo bool" << endl;
                error=true;
            }
            it++;
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo bool" << endl;
                error=true;
            }
            this->tipoDato = 'b';
            break;
        case 51:
            it=hijos.begin();
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo bool" << endl;
                error=true;
            }
            it++;
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo bool" << endl;
                error=true;
            }
            this->tipoDato = 'b';
            break;
        case 52:
            it=hijos.begin();
            (*it)->validaTipos();
            this->tipoDato = (*it)->tipoDato;
            break;
        default:
            i=0;
            break;
        }
    }
    return ' ';
}
    

stringstream& nodoSintactico::generaCodigo(stringstream& codigo){
    list<nodoSintactico*>::iterator it;
    int i,espacio=0;
    string simbolo;
    string tipoDef;
    stringstream ss;
    char tipoDato, tipoDato2;
    string ambitoAnt;
    if(tipo == 'N'){
        switch (regla+1)
        {
        case 1:
            codigo << ".386" << endl;
            codigo << ".model flat, stdcall" << endl;
            codigo << "option casemap :none" << endl;
            codigo << "include C:\\masm32\\macros\\acros.asm" << endl;
            codigo << "include \\masm32\\include\\masm32.inc" << endl;
            codigo << "include \\masm32\\include\\kernel32.inc" << endl;
            codigo << "includelib \\masm32\\lib\\kernel32.lib" << endl;
            codigo << "includelib \\masm32\\lib\\masm32.lib" << endl;
            codigo << ".data" << endl;
            tabla.generaCodigo(codigo);
            codigo << ".code" << endl;
            codigo << "start:" << endl;
            ambito = "global";
            hijos.front()->generaCodigo(codigo);
            codigo << "exit" << endl;
            codigo << "end start" << endl;
            break;
        case 2:
            break;
        case 3:
            hijos.front()->generaCodigo(codigo);
            hijos.back()->generaCodigo(codigo);
            break;
        case 4:
            break;
        case 5:
            hijos.front()->generaCodigo(codigo);
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            
            break;
        case 9:
            for(it=hijos.begin(),i = 0;it!=hijos.end();it++,i++){
                switch (i)
                {
                case 0:
                    tipoDef = "DefFunc";
                    tipoDato=(*it)->valor[0];
                    break;
                case 1:
                    simbolo = (*it)->valor;
                    codigo << ";" <<simbolo << ":" << endl;
                    break;
                case 2:
                    break;
                case 3:
                    ambitoAnt = ambito;
                    ambito = simbolo;
                    (*it)->generaCodigo(codigo);
                    break;
                case 4:
                    break;
                case 5:
                    (*it)->generaCodigo(codigo);;
                    ambito = ambitoAnt;
                    codigo<<";_fin"<<simbolo<<":"<<endl;
                    break;

                default:
                    cout << "Error en la regla 9" << endl;
                    break;   
                }
            }
            break;
        case 10:
            break;
        case 11:
            for(it=hijos.begin(),i = 0;it!=hijos.end();it++,i++){
                switch (i)
                {
                case 0:
                    tipoDef = "DefVar";
                    tipoDato=(*it)->valor[0];
                    break;
                case 1:
                    simbolo = (*it)->valor;
                    if(tabla.existe(simbolo,ambito+"Param")){
                        cout<<"Ln "<<this->linea<<": ";
                        cout << "Error semantico: " << simbolo << " ya existe"<< endl;
                        error=true;
                    }else{
                        tabla.inserta(simbolo,tipoDef,tipoDato,ambito+"Param");
                    }
                    break;
                case 2:
                    (*it)->validaTipos();
                    break;

                default:
                    cout << "Error en la regla 11" << endl;
                    break;   
                }
            }
            break;
        case 12:
            break;
        case 13:
            for(it=hijos.begin(),i = 0;it!=hijos.end();it++,i++){
                switch (i)
                {
                case 0:
                    break;
                case 1:
                    tipoDef = "DefVar";
                    tipoDato=(*it)->valor[0];
                    break;
                case 2:
                    simbolo = (*it)->valor;
                    if(tabla.existe(simbolo,ambito+"Param")){
                        cout<<"Ln "<<this->linea<<": ";
                        cout << "Error semantico: " << simbolo << " ya existe"<< endl;
                        error=true;
                    }else{
                        tabla.inserta(simbolo,tipoDef,tipoDato,ambito+"Param");
                    }
                    break;
                case 3:
                    (*it)->validaTipos();
                    break;

                default:
                    cout << "Error en la regla 13" << endl;
                    break;   
                }
            }
            break;
        case 14:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            break;
        case 15:
            break;
        case 16:
            it=hijos.begin();
            (*it)->validaTipos();
            it++;
            (*it)->validaTipos();
            break;
        case 17:
            (*hijos.begin())->validaTipos();
            break;
        case 18:
            (*hijos.begin())->validaTipos();
            break;
        case 19:
            break;
        case 20:
            (*hijos.begin())->validaTipos();
            (*hijos.end())->validaTipos();
            break;
        case 21:
            it=hijos.begin();
            simbolo = (*it)->valor;
            if(!(tabla.existe(simbolo,ambito)||tabla.existe(simbolo,ambito+"Param"))){
                cout<<"Ln "<<this->linea<<": ";
                cout << "Error semantico: " << simbolo << " no definido"<< endl;
                error=true;
            }else{
                tipoDato = tabla.getTipoDato(simbolo,ambito);
                it++;
                it++;
                (*it)->validaTipos();
                tipoDato2 = (*it)->tipoDato;
                if(tipoDato != tipoDato2){
                    cout<<"Ln "<<this->linea<<": ";
                    cout << "Error semantico: " << simbolo << " no es de tipo " << tipoDato2 << endl;
                    error=true;
                }
            }
            break;
        case 22:
            it=hijos.begin();
            it++;
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo booleano" << endl;
                error=true;
            }
            it++;
            it++;
            (*it)->validaTipos();
            it++;
            (*it)->validaTipos();
            break;
        case 23:
            it=hijos.begin();
            it++;
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo booleano" << endl;
                error=true;
            }
            it++;
            it++;
            (*it)->validaTipos();
            break;
        case 24:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != tabla.getTipoDato(ambito,"global")){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es del tipo de la funcion" << endl;
                error=true;
            }
            break;

        case 25:
            it=hijos.begin();
            (*it)->validaTipos();
            break;
        case 26:
            break;
        case 27:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            break;
        case 28:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            break;
        case 29:
            break;
        case 30:
            it=hijos.begin();
            (*it)->validaTipos();
            this->tipoDato = (*it)->tipoDato;
            break;
        case 31:
            break;
        case 32:
            it=hijos.begin();
            ambitoAnt=ambito;
            ss<<ambito;
            getline(ss,simbolo,',');
            getline(ss,ambito);
            (*it)->validaTipos();
            tipoDato = (*it)->tipoDato;
            tipoDato2 = tabla.getTipoDatoArg(espacio++,simbolo);
            if(tipoDato != tipoDato2){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo de Argumento" << endl;
                error=true;
            }
            it++;
            ambito=ambitoAnt;
            (*it)->validaTipos();
            espacio=0;
            break;
        case 33:
            break;
        case 34:
            it=hijos.begin();
            it++;
            ambitoAnt=ambito;
            ss<<ambito;
            getline(ss,simbolo,',');
            getline(ss,ambito);
            (*it)->validaTipos();
            if((*it)->tipoDato != tabla.getTipoDatoArg(espacio++,simbolo)){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo de Argumento" << endl;
                error=true;
            }
            it++;
            ambito=ambitoAnt;
            (*it)->validaTipos();
            break;
        case 35:
            it=hijos.begin();
            (*it)->validaTipos();
            this->tipoDato = (*it)->tipoDato;
            break;
        case 36:
            if(!(tabla.existe((*hijos.begin())->valor,ambito)||tabla.existe((*hijos.begin())->valor,ambito+"Param"))){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout<<"Error semantico: "<<(*hijos.begin())->valor<<" no definido"<<endl;
                error=true;
            }else{
                this->tipoDato = tabla.getTipoDato((*hijos.begin())->valor,ambito);
            }
            break;
        case 37:
            this->tipoDato = 'i';
            break;
        case 38:
            this->tipoDato = 'f';
            break;
        case 39:
            this->tipoDato = 's';
            break;
        case 40:
            it=hijos.begin();
            this->tipoDato = tabla.getTipoDato((*it)->valor,ambito);
            if(tabla.getTipo((*it)->valor,ambito) != "DefFunc"){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout<<"Error semantico: "<<(*it)->valor<<" no es Funcion"<<endl;
                error=true;
            }
            ambitoAnt=ambito;
            ambito=(*it)->valor+","+ambito;
            it++;
            it++;
            (*it)->validaTipos();
            ambito=ambitoAnt;
            break;
        case 41:
            it=hijos.begin();
            (*it)->validaTipos();
            break;
        case 42:
            it=hijos.begin();
            (*it)->validaTipos();
            break;
        case 43:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            this->tipoDato = (*it)->tipoDato;
            break;
        case 44:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            this->tipoDato = (*it)->tipoDato;
            break;
        case 45:
            it=hijos.begin();
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo bool" << endl;
                error=true;
            }
            this->tipoDato = (*it)->tipoDato;
            break;
        case 46:
            it=hijos.begin();
            (*it)->validaTipos();
            tipoDato = (*it)->tipoDato;
            it++;
            it++;
            (*it)->validaTipos();
            tipoDato2 = (*it)->tipoDato;
            if(tipoDato != tipoDato2){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo " << tipoDato << endl;
                error=true;
            }
            this->tipoDato = (*it)->tipoDato;
            break;
        case 47:
            it=hijos.begin();
            (*it)->validaTipos();
            tipoDato = (*it)->tipoDato;
            it++;
            it++;
            (*it)->validaTipos();
            tipoDato2 = (*it)->tipoDato;
            if(tipoDato != tipoDato2){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo " << tipoDato << endl;
                error=true;
            }
            this->tipoDato = (*it)->tipoDato;
            break;
        case 48:
            it=hijos.begin();
            (*it)->validaTipos();
            tipoDato = (*it)->tipoDato;
            it++;
            it++;
            (*it)->validaTipos();
            tipoDato2 = (*it)->tipoDato;
            if(tipoDato != tipoDato2){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo " << tipoDato << endl;
                error=true;
            }
            this->tipoDato = 'b';
            break;
        case 49:
            it=hijos.begin();
            (*it)->validaTipos();
            tipoDato = (*it)->tipoDato;
            it++;
            it++;
            (*it)->validaTipos();
            tipoDato2 = (*it)->tipoDato;
            if(tipoDato != tipoDato2){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo " << tipoDato << endl;
                error=true;
            }
            this->tipoDato = 'b';
            break;
        case 50:
            it=hijos.begin();
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo bool" << endl;
                error=true;
            }
            it++;
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo bool" << endl;
                error=true;
            }
            this->tipoDato = 'b';
            break;
        case 51:
            it=hijos.begin();
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo bool" << endl;
                error=true;
            }
            it++;
            it++;
            (*it)->validaTipos();
            if((*it)->tipoDato != 'b'){
                cout<<"Ln "<<(*it)->linea<<": ";
                cout << "Error semantico: " << (*it)->valor << " no es de tipo bool" << endl;
                error=true;
            }
            this->tipoDato = 'b';
            break;
        case 52:
            it=hijos.begin();
            (*it)->validaTipos();
            this->tipoDato = (*it)->tipoDato;
            break;
        default:
            i=0;
            break;
        }
    }
}
    

#endif