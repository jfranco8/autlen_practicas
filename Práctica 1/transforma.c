#include "transforma.h"

typedef struct{
  char *nombre_estado;
  char *estados;
}nuevo_estado;

typedef struct{
  char *simbolo;
  nuevo_estado inicio;
  nuevo_estado fin;
}transicion;

typedef struct{
  nuevo_estado *estados;
  transicion *transiciones;
}intermedia;

int ordenAlfabetico(char *cadena1, char *cadena2){
  if(!cadena1 || !cadena2){
    return NULL;
  }

  int l;
  if(strlen(cadena1) < strlen(cadena2)){
    l = strlen(cadena1);
  } else {
    l = strlen(cadena2);
  }

  int i, compara = 1;
  for(i=0; i<l, i++){
    if(cadena1[i] < cadena2[i]){
      compara = 0;
      break;
    }
  }

  return compara;
}

AFND* AFNDTransforma(AFND* afnd){

}
