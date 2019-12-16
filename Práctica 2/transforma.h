/**
 * Autores: Sofia Sanchez y Jesus Daniel Franco
 * Fichero: transforma.h
 *
 * Contiene las funciones
 *
 */

#ifndef TRANSFORMA_H
#define TRANSFORMA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "intermedia.h"


/**
 * AFNDTransforma
 *
 * Transforma un AFND en un AFD equivalente
 *
 * Argumentos de entrada:
 *  - afnd: Automata no determinista que vamos a transformar
 *
 * Salida:
 *   Automata determinista creado
 *   NULL en caso de error
 */

AFND* AFNDTransforma(AFND* afnd);

/**
 * crear_automata
 *
 * Nos permite formar el automata derminista llamando a las funciones de la API
 * que insertan los simbolos, estados y transiciones
 *
 * Argumentos de entrada:
 *  - afnd: AFND anterior donde tenemos los simbolos
 *  - creados: lista con todos los nuevos estados del AFD
 *  - contador: contiene el numero de estados del nuevo AFD
 *  - num_simbolos: contiene el numero de simbolos del AFD
 *
 * Salida:
 *  Automata determinista ya creado
 *
 */
AFND *crear_automata(AFND *afnd, Intermedia **creados, int contador, int num_simbolos);

/**
 * Liberar memoria
 *
 * Nos permite liberar la memoria reservada para la lista creados de estructuras
 * intermedias eliminando la memoria reservada para las trasiciones y
 * para las estructuras intermedias
 *
 * Argumentos de entrada:
 *  - creados: lista de estructuras intermedias
 *  - creado: estructura intermedia que tenemos que eliminar
 *  - contador: contador para saber cuantos tenemos que liberar
 */
void liberar_memoria(Intermedia **creados, int contador);

#endif
