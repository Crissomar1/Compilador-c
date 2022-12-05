#include "lexico.h"

  Lexico::Lexico(string fuente){
     this->linea=1;
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
          
          case TipoSimbolo::C_PARENTECIS:
          case TipoSimbolo::A_PARENTECIS:
               cad= "Parentecis";
               break;
          case TipoSimbolo::A_LLAVE:
          case TipoSimbolo::C_LLAVE:
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
          case TipoSimbolo::TIPO:
               cad= "Tipo";
               break;
          case TipoSimbolo::EQUAL:
               cad= "Igual";
               break;
         }
         
         return cad;
  }
  
  void Lexico::entrada(string fuente){
     linea=1;
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
               if(esEspacio(c)) estado=0;
               if(c=='\n') linea++;
               else
               if(esLetra(c)) sigEstado(9);
               else
          
             if ( c == '"') sigEstado(11);
             else
             if ( c == '+' || c=='-') aceptacion(TipoSimbolo::OPADIC);
             else
             if ( c == '*' || c=='/') aceptacion(TipoSimbolo::OPMULT);
             else
             if ( c == '=') sigEstado(4);
             else
              if ( c == '$' ) aceptacion(TipoSimbolo::PESOS);
               else
               if(esDigito(c)) sigEstado(1);
               else
               if(c == '.') aceptacion(TipoSimbolo::ERROR);
               else
               if(c == '<'|| c=='>') sigEstado(5);
               else
               if(c == '!') sigEstado(6);
               else
               if(c == '&') sigEstado(7);
               else
               if(c == '|') sigEstado(8);
               else
               if(c == '(') aceptacion(TipoSimbolo::A_PARENTECIS);
               else
               if(c == ')') aceptacion(TipoSimbolo::C_PARENTECIS);
               else
               if(c == '{') aceptacion(TipoSimbolo::A_LLAVE);
               else
               if(c == '}') aceptacion(TipoSimbolo::C_LLAVE);
               else
               if(c == ';') aceptacion(TipoSimbolo::PUNTCOMM);
               else
               if(c == ',') aceptacion(TipoSimbolo::COMM);

             break;
          case 1:
               if(esDigito(c)) sigEstado(1);
               else
               if(c=='.') sigEstado(2);
               else{
               retroceso();
               tipo=TipoSimbolo::ENTERO;
               }
               break;

          case 2:
               if(esDigito(c)) sigEstado(3);
               else{
                    retroceso();
                    tipo=TipoSimbolo::ERROR;
                    continua=false;
               }
               break;
               
          case 3:
               if(esDigito(c)) sigEstado(3);
               else{
               retroceso();
               tipo=TipoSimbolo::REAL;
               }
               
               break;  
          case 4:
               if(c=='=') aceptacion(TipoSimbolo::EQUAL);
               else{
               retroceso();
               tipo=TipoSimbolo::ASIGN;
               continua=false;}
               break; 
          case 5:
               if(c=='=') aceptacion(TipoSimbolo::OPRELA);
               else{
               retroceso();
               tipo=TipoSimbolo::OPRELA;
               continua=false;}
               break;
          case 6:
               if(c=='=') aceptacion(TipoSimbolo::EQUAL);
               else{
               retroceso();
               tipo=TipoSimbolo::NOT;
               continua=false;}
               break; 
          case 7:
               if(c=='&') aceptacion(TipoSimbolo::AND);
               else{
               retroceso();
               tipo=TipoSimbolo::ERROR;
               continua=false;}
               break;
          case 8:
               if(c=='|') aceptacion(TipoSimbolo::OR);
               else{
               retroceso();
               estado=-1;
               continua=false;}
               break;
          case 9:
               if(esLetra(c)) sigEstado(9);
               else{
                    int res = esReservada(simbolo);
                    if(res!=-1){
                         retroceso();
                         switch (res)
                         {
                         case 0:
                              tipo=TipoSimbolo::IF;
                              break;
                         case 1:
                              tipo=TipoSimbolo::WHILE;
                              break;
                         case 2:
                              tipo=TipoSimbolo::RET;
                              break;
                         case 3:
                              tipo=TipoSimbolo::ELSE;
                              break;
                         case 4:
                         case 5:
                         case 6:
                              tipo=TipoSimbolo::TIPO;
                              break;
                         
                         default:
                              break;
                         }
                    } 
               
               else
               if(esDigito(c)) sigEstado(10);
               else{
               retroceso();
               tipo=TipoSimbolo::IDENTIFICADOR;
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
               break;
          case 11:
               if(c=='"') aceptacion(TipoSimbolo::CADENA);
               else sigEstado(11);
               break;
      }  
           
   }    
    //Fin del Automata
   
    		
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
  
  void Lexico::aceptacion(int tipo){
       this->tipo=tipo;
       simbolo+= c;
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

   int Lexico::esReservada  (string sim){
     string reservadas[]{
          "if",
          "while",
          "return",
          "else",
          "int",
          "float",
          "void"
     };
     for (size_t i = 0; i < 6; i++)
     {
          if (sim==reservadas[i]) return i;
     }
     return -1;
     
   }

            
   void Lexico::retroceso(){
      if ( c != '$') ind--;
      
        continua= false;
    }