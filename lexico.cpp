#include "lexico.h"

  Lexico::Lexico(string fuente){
    ind= 0;                  
    this->fuente= fuente;
  }      

  Lexico::Lexico(){
    ind= 0;                  
  }      
  
  string Lexico::tipoAcad(int tipo){
         string cad= "";
         
         switch (tipo){
           case TipoSimbolo::IDENTIFICADOR:
                cad= "Identificador";
                break;
                
           case TipoSimbolo::OPADIC:
                cad= "Op. Adicion";
                break;

           case TipoSimbolo::OPMULT:
                cad= "Op. Multiplicacion";
                break;            

           case TipoSimbolo::PESOS:
                cad= "Fin de la Entrada";
                break;            

           case TipoSimbolo::ENTERO:
                cad= "Entero";
                break;
          case TipoSimbolo::ERROR:
                cad= "ERROR";
                break;
          case TipoSimbolo::REAL:
               cad= "Real";
               break;
          case TipoSimbolo::ASIGN:
               cad= "Asingnacion";
               break;
          case TipoSimbolo::OPRELA:
               cad= "Op relativa";
               break;
          case TipoSimbolo::AND:
               cad= "op And";
               break;
          case TipoSimbolo::OR:
               cad= "Op or";
               break;
          case TipoSimbolo::NOT:
               cad= "Op not";
               break;
          case TipoSimbolo::PARENTECIS:
               cad= "Parentecis";
               break;
          case TipoSimbolo::LLAVE:
               cad= "Llave";
               break;
          case TipoSimbolo::PUNTCOMM:
               cad= "Punto y coma";
               break;
          case TipoSimbolo::IF:
               cad= "If";
               break;
          case TipoSimbolo::WHILE:
               cad= "While";
               break;
          case TipoSimbolo::RET:
               cad= "Return";
               break;
          case TipoSimbolo::ELSE:
               cad= "Else";
               break;
          case TipoSimbolo::INT:
               cad= "Def entero";
               break;
          case TipoSimbolo::FLOAT:
               cad= "Def real";
               break;
         }
         
         return cad;
  }
  
  void Lexico::entrada(string fuente){
       ind= 0;                  
      this->fuente= fuente;
  }

int Lexico::sigSimbolo(){
    
    estado=0;
    continua= true;
    simbolo= "";
    
    //Inicio del Automata
    while (continua){
      c= sigCaracter();
      
      switch (estado){
        case 0:
               if(esLetra(c)) sigEstado(9);
               else
             if ( c == '+' || c=='-') aceptacion(2);
             else
             if ( c == '*' || c=='/') aceptacion(0);
             else
             if ( c == '=') sigEstado(4);
             else
              if ( c == '$' ) aceptacion(3);
               else
               if(esDigito(c)) sigEstado(1);
               else
               if(c == '.') aceptacion(-2);
               else
               if(c == '<'|| c=='>') sigEstado(5);
               else
               if(c == '!') sigEstado(6);
               else
               if(c == '&') sigEstado(7);
               else
               if(c == '|') sigEstado(8);
               else
               if(c == '('||c == ')') aceptacion(10);
               else
               if(c == '{'||c == '}') aceptacion(11);
               else
               if(c == ';') aceptacion(12);

             break;
          case 1:
               if(esDigito(c)) sigEstado(1);
               else
               if(c=='.') sigEstado(2);
               else{
               retroceso();
               estado=1;
               continua=false;}
               break;

          case 2:
               if(esDigito(c)) sigEstado(3);
               else{
                    retroceso();
                    estado=-1;
                    continua=false;
               }
               break;
               
          case 3:
               if(esDigito(c)) sigEstado(3);
               else{
               retroceso();
               estado=5;
               continua=false;}
               
               break;  
          case 4:
               if(c=='=') aceptacion(4);
               else{
               retroceso();
               estado=6;
               continua=false;}
               break; 
          case 5:
               if(c=='=') aceptacion(4);
               else{
               retroceso();
               estado=4;
               continua=false;}
               break;
          case 6:
               if(c=='=') aceptacion(4);
               else{
               retroceso();
               estado=7;
               continua=false;}
               break; 
          case 7:
               if(c=='&') aceptacion(8);
               else{
               retroceso();
               estado=-1;
               continua=false;}
               break;
          case 8:
               if(c=='|') aceptacion(9);
               else{
               retroceso();
               estado=-1;
               continua=false;}
               break;
          case 9:
               if(esLetra(c)) sigEstado(9);
               else{
                    string res = esReservada(simbolo);
                    if(res!=""){
                    retroceso();
                    estado=20;
                    continua=false;
                    } 
               
               else
               if(esDigito(c)) sigEstado(10);
               else{
               retroceso();
               estado=14;
               continua=false;}}
               break;    
          case 10:
               if(esLetra(c)) sigEstado(9);
               else 
               if(esDigito(c)) sigEstado(10);
               else{
               retroceso();
               estado=14;
               continua=false;}
      }  
           
   }    
    //Fin del Automata
    
      switch (estado){
          case 0:
              tipo= TipoSimbolo::OPMULT;
              break; 
         case 2:
              tipo= TipoSimbolo::OPADIC;
              break; 
          case 1:
              tipo= TipoSimbolo::ENTERO;
              break; 
          case 5:
               tipo= TipoSimbolo::REAL;
               break;
          case 3:
               tipo= TipoSimbolo::PESOS;
               break;
          case 4:
               tipo= TipoSimbolo::OPRELA;
               break;
          case 6:
               tipo= TipoSimbolo::ASIGN;
               break;
          case 7:
               tipo= TipoSimbolo::NOT;
               break;
          case 8:
               tipo= TipoSimbolo::AND;
               break;
          case 9:
               tipo= TipoSimbolo::OR;
               break;
          case 10:
               tipo= TipoSimbolo::PARENTECIS;
               break;
          case 11:
               tipo= TipoSimbolo::LLAVE;
               break;
          case 13:
               tipo= TipoSimbolo::PUNTCOMM;
               break;
          case 14:
               tipo= TipoSimbolo::IDENTIFICADOR;
               break;
          
          default:                 
              tipo= TipoSimbolo::ERROR;
              break;
      }
    		
	return tipo;
}

 char Lexico::sigCaracter(){
      if (terminado()) return '$';
      
      return fuente[ind++];
 }

  void Lexico::sigEstado(int estado){
       this->estado= estado;
       simbolo+= c;
  }
  
  void Lexico::aceptacion(int estado){
       sigEstado(estado);
       continua= false;
  }

  bool Lexico::terminado(){//fin de cadena
         return ind >= fuente.length();
  }

   bool Lexico::esLetra(char c){
        return isalpha(c) || c=='_';
   }
   
   
   bool Lexico::esDigito(char c){
        return isdigit(c);
   }
   
   bool Lexico::esEspacio(char c){
        return c== ' ' || c== '\t';        
   }

   string Lexico::esReservada  (string sim){
     string reservadas[]{
          "if",
          "while",
          "return",
          "else",
          "int",
          "float"
     };
     for (size_t i = 0; i < 6; i++)
     {
          if (sim==reservadas[i]) return reservadas[i];
     }
     return "";
     
   }

            
   void Lexico::retroceso(){
      if ( c != '$') ind--;
      
        continua= false;
    }