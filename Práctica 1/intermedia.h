#ifndef INTERMEDIA_H
#define INTERMEDIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"

#define MAX_NOMBRE 500
#define MAX_TRANSICIONES 500

typedef struct _Transicion Transicion;
typedef struct _Intermedia Intermedia;


Transicion *crear_transicion(int num_estados, char* simbolo, char* final, int *estado_final);

void eliminar_transicion(Transicion *transicion);

Intermedia *crear_intermedia(char* nombre, int num_estados, int tipo, int *estado);

void eliminar_intermedia(Intermedia *intermedia);


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

int comparar_codificacion(int *codificacion1, int *codificacion2, int num_estados);


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

int is_estado_in(int *codificacion, Intermedia **creados, int num_estados, int num_creados);

/*
*
*
*
*/
void imprimir_intermedia(Intermedia *intermedia, int num_estados) ;


/*
*
*
*
*/

void imprimir_transicion(Transicion *transicion, int num_estados);


/*
*
*
*
*/
void imprimir_codificiacion(int *cod, int num_estados);

int *get_intermedia_codificacion(Intermedia *intermedia);

void set_intermedia_transicion(Intermedia *intermedia, int posicion, Transicion *transicion);

Transicion *get_intermedia_transicion(Intermedia *intermedia, int posicion);

char *get_intermedia_nombre(Intermedia *intermedia);

void set_intermedia_nombre(Intermedia *intermedia, char *nombre);

int get_intermedia_tipo(Intermedia *intermedia);

void set_intermedia_tipo(Intermedia *intermedia, int tipo);

char *get_transicion_simbolo(Transicion *transicion);

char *get_transicion_estadofinal(Transicion *transicion);

#endif
