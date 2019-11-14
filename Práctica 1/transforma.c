#include "transforma.h"

typedef struct{
  char simbolo[MAX_NOMBRE]; //es el simbolo con el que puedo ir al estado final
  char estado_final[MAX_NOMBRE];
  int *t_codificacion; //esto es una lista [1,1,0,0,0,0,1,0]
}Transicion;

typedef struct{
  char nombre_estado[MAX_NOMBRE];
  int *i_codificacion; //esto es una lista [1,1,0,0,0,0,1,0]
  int tipo; //tipo que va a ser: final, inicial, etc
  Transicion transiciones[MAX_TRANSICIONES]; //no se es necesario hacerlo dinamico, con lo cual lo hemos hecho estatico
}Intermedia;


/*
*
*
*
*/
Transicion *crear_transicion(num_estados) {
  Transicion *transicion = NULL;
  int i;

  transicion->t_codificacion = (int*)malloc(sizeof(int)*num_estados);
  for (i = 0; i < num_estados; i++) {
    transicion->t_codificacion[i] = 0;
  }

  //ya esta todo inicializado
  return transicion;
}

/*
*
*
*
*/
Intermedia *crear_intermedia(nombre, num_estados, tipo) {
  Intermedia *intermedia = NULL;
  int i;

  intermedia->tipo = tipo;
  intermedia->i_codificacion = (int*)malloc(sizeof(int)*num_estados);

  //hay que inicializarla toda a 0
  for (i = 0; i< num_estados; i++) {
    intermedia->i_codificacion[i] = 0;
  }

  //transiciones es un estatico con lo cual demomento no tenemos que inicializarlo
  //ya esta todo inicializado
  return intermedia;
}


AFND* AFNDTransforma(AFND* afnd){

  Intermedia *intermedia = NULL;
  int num_estados, num_simbolos;

  //obtenemos datos del automata original
  num_estados = AFNDNumEstados(afnd);
  num_simbolos = AFNDNumSimbolos(afnd);

  /*
  Yo se que toda la informacion necesaria la tengo en AFND.
  Aqui ya tengo las transiciones y los num_simbolos





}
