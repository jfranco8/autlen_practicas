#ifndef TRANSFORMA_H
#define TRANSFORMA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"

typedef struct  _intermedia intermedia;
typedef struct _nuevo_estado nuevo_estado;
typedef struct _transicion transicion;


AFND* AFNDTransforma(AFND* afnd);

#endif
