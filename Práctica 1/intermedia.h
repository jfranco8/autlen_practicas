#ifndef INTERMEDIA_H
#define INTERMEDIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"

#define MAX_NOMBRE 500
#define MAX_TRANSICIONES 500


typedef struct  _intermedia intermedia;
typedef struct _nuevo_estado nuevo_estado;
typedef struct _transicion transicion;


AFND* AFNDTransforma(AFND* afnd);

#endif
