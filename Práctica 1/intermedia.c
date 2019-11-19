#include "intermedia.h"

struct _Transicion{
  char simbolo[MAX_NOMBRE]; /*es el simbolo con el que puedo ir al estado final*/
  char estado_final[MAX_NOMBRE];
  int *t_codificacion; /*esto es una lista [1,1,0,0,0,0,1,0]*/
};


/* Intermedia es la estructura que nos define los estados
del autómata finito determinista */
struct _Intermedia{
  char nombre_estado[MAX_NOMBRE];
  int *i_codificacion; /*esto es una lista [1,1,0,0,0,0,1,0]*/
  int tipo; /*tipo que va a ser: final, inicial, etc*/
  Transicion *transiciones[MAX_TRANSICIONES]; /*no se es necesario hacerlo dinamico, con lo cual lo hemos hecho estatico*/
};



/*
* CREAR_TRANSICION
*
* Desde un estado inicial define una transicion a otro estado por medio
* de un símbolo determinado
*
* Salida:
*   transicion creada si se crea de manera satisfactoria
*   NULL en caso de error
*/

Transicion *crear_transicion(int num_estados, char* simbolo, char* final, int *estado_final) {
  Transicion *transicion = NULL;
  int i;

  transicion = (Transicion *)malloc(sizeof(Transicion));
  if (transicion == NULL){
    printf("Error al reservar memoria para la nueva transicion\n");
    return NULL;
  }

  strcpy(transicion->simbolo, simbolo);
  strcpy(transicion->estado_final,final);

  /* Codificación del estado al que se transita*/
  transicion->t_codificacion = (int*)malloc(sizeof(int)*num_estados);
  if (transicion->t_codificacion == NULL){
    printf("Error al reservar memoria para codificacion del estado destino\n");
    return NULL;
  }

  /*Guardamos el estado al que se puede transitar con el símbolo dado*/
  for (i = 0; i < num_estados; i++) {
    transicion->t_codificacion[i] = estado_final[i];
  }

  return transicion;
}


/*
* ELIMINAR_TRANSICION
*
* Libera toda la memoria de la transicion pasada como argumento
*
* Salida:
*   void
*/

void eliminar_transicion(Transicion *transicion) {
  free(transicion->t_codificacion);
  free(transicion);
}


/*
* CREAR_INTERMEDIA
*
* Creación de un estado del autómata finito determinista
*
* Salida:
*   estado del AFD creado si se crea de manera satisfactoria
*   NULL en caso de error
*/

Intermedia *crear_intermedia(char* nombre, int num_estados, int tipo, int *estado) {
  Intermedia *intermedia = NULL;
  int i;

  intermedia = (Intermedia *)malloc(sizeof(Intermedia));
  if (!intermedia) {
    printf("Error al reservar memoria para el estado el AFD\n");
    return NULL;
  }

  intermedia->tipo = tipo;
  strcpy(intermedia->nombre_estado, nombre);
  intermedia->i_codificacion = (int*)malloc(sizeof(int)*num_estados);

  /* Guardamos en codificacion la propia del estado (o estado) inicial
   Es decir, si el AFND tiene como estados iniciales q0 y q2, nuestro
   estado inicial en el AFD será q0q2 = [1, 0, 1, 0, 0...]*/
  for (i = 0; i< num_estados; i++) {
    intermedia->i_codificacion[i] = estado[i];
  }

  return intermedia;
}


/*
* ELIMINAR_INTERMEDIA
*
* Libera toda la memoria del estado del AFD pasado como argumento
*
* Salida:
*   void
*/

void eliminar_intermedia(Intermedia *intermedia) {
  free(intermedia->i_codificacion);
  free(intermedia);
}


/*
* COMPARAR_CODIFICACION
*
* Compara que si dos codificaciones representan al mismo estado o no
*
* Salida:
*   1 si los estados son iguales
*   0 si los estados son diferentes
*   -1 en caso de error
*/

int comparar_codificacion(int *codificacion1, int *codificacion2, int num_estados){
  int i;
  
  if(!codificacion1 || !codificacion2){
    return -1;
  }

  
  printf("codificacion 1:\n" );
  for (i = 0; i < num_estados; i++) {
    printf("%d-\n", codificacion1[i] );
  }

  printf("codificacion 2:\n" );
  for (i = 0; i < num_estados; i++) {
    printf("%d-\n", codificacion2[i] );
  }

  for (i=0; i<num_estados; i++){
    if(codificacion1[i] != codificacion2[i]){
      return 0;
    }
  }

  /* si recorremos toda la lista y no hay diferencias, son */
  return 1;
}


/*
* IS_ESTADO_IN
*
* Determina si un estado ya está en la lista de estados creados o no
*
* Salida:
*   1 si ya está en creado
*   0 si no lo está
*   -1 en caso de error
*/

int is_estado_in(int *codificacion, Intermedia **creados, int num_estados, int num_creados) {
  int i;

  if(!codificacion  || !creados){
    return -1;
  }

  num_creados = num_creados + 1;


  printf("!!!!!!!! DENTRO IS ESTADO IN !!!! \n num_creados: %d\n",num_creados );
  for (i = 0; i < num_creados; i++) {
    /* Vemos si la codificacion dada coincide con alguna de las que ya tenemos
     en creados. Si coincide, devolvemos un 1 */
    if (comparar_codificacion(codificacion, creados[i]->i_codificacion, num_estados) == 1){
      return 1;
    }
  }

  /* si la codificacion no coincide con ningun estados de lso ya creados,
   devolvemos un 0 */
  return 0;
}

/*
*
*
*
*/
void imprimir_intermedia(Intermedia *intermedia, int num_estados) {
  int i;

  printf("**********IMPRIMIENDO ESTRUCTURA INTERMEDIA********\n" );
  printf("nombre_estado: %s\n", intermedia->nombre_estado);
  
  for (i = 0; i < num_estados; i++) {
    printf("%d-", intermedia->i_codificacion[i]);
  }

  printf("\n" );

  printf("tipo: %d\n", intermedia->tipo);
}


/*
*
*
*
*/

void imprimir_transicion(Transicion *transicion, int num_estados) {
  int i;

  printf("**********IMPRIMIENDO TRANSICION********\n" );
  printf ("simbolo: %s\n", transicion->simbolo);
  printf("estado destino: %s\n", transicion->estado_final);
  
  for (i = 0; i < num_estados; i++) {
    printf("%d-", transicion->t_codificacion[i]);
  }

  printf("\n" );
}


/*
*
*
*
*/
void imprimir_codificiacion(int *cod, int num_estados) {
  int i;

  printf("????? imprimiendo codificacion ?????\n");

  for(i = 0; i < num_estados; i++) {
    printf ("%d-", cod[i]);
  }

  printf("\n");
}

/************************************/
/***** GETTERS Y SETTERS ************/
/************************************/

int *get_intermedia_codificacion(Intermedia *intermedia) {
    return intermedia->i_codificacion;
}

void set_intermedia_transicion(Intermedia *intermedia, int posicion, Transicion *transicion) {
    intermedia->transiciones[posicion] = transicion;
}

Transicion *get_intermedia_transicion(Intermedia *intermedia, int posicion) {
    return intermedia->transiciones[posicion];
}

char *get_intermedia_nombre(Intermedia *intermedia) {
    return intermedia->nombre_estado;
}


void set_intermedia_nombre(Intermedia *intermedia, char *nombre) {
    strcpy(intermedia->nombre_estado, nombre);
}

int get_intermedia_tipo(Intermedia *intermedia) {
    return intermedia->tipo;
}

void set_intermedia_tipo(Intermedia *intermedia, int tipo) {
    intermedia->tipo = tipo;
}

char *get_transicion_simbolo(Transicion *transicion) {
    return transicion->simbolo;
}

char *get_transicion_estadofinal(Transicion *transicion) {
    return transicion->estado_final;
}