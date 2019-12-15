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
#include "transforma.h"

int* estadosAccesibles(AFND* afnd);
int** estadosDistinguibles(AFND *afnd);
AFND* AFNDMinimiza(AFND *afnd);

#endif
