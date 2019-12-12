 #include "minimiza.h"

 /*afnd *AFNDMinimiza(AFND* afnd){
   Luego
 }


devuelve 0 si no está*/
int notInCreados(int *creados, int pos, int num_estados){
  int i;

  for(i=0; i<num_estados; i++){
    if(pos == creados[i]){
      return 1;
    }
  }

  return 0;
}

void estadosAccesibles(AFND *afnd){
   int pos_inicial, pos_llega;
   int *creados, *accesibles;
   int i_num_creados = 0;
   int num_estados, num_simbolos;
   int i_simbolo, i_estado, i;
   int num_creados;

   pos_inicial = AFNDIndiceEstadoInicial(afnd);
   num_estados = AFNDNumEstados(afnd);
   num_simbolos = AFNDNumSimbolos(afnd);

   creados = (int *)malloc(sizeof(int) + 4);
   creados[0] = pos_inicial;
   i_num_creados  = 0;
   num_creados = 1;

   while(creados[i_num_creados] != -1 || i_num_creados == 0){
     for(i_simbolo = 0; i_simbolo < num_simbolos; i_simbolo ++){
       for(i_estado = 0; i_estado < num_estados; i_estado ++){
         if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, creados[i_num_creados], i_simbolo, i_estado) == 1){
           if(notInCreados(creados, i_estado, i_num_creados) == 0){
             printf("Hay transición de %d a %d\n", creados[i_num_creados], i_estado);
             creados = (int *)realloc(creados, sizeof(creados)+sizeof(int) + 4*num_creados);
             creados[num_creados] = i_estado;
             num_creados ++;
             creados[num_creados] = -1;
           }
         }
       }
     }
     i_num_creados ++;
   }


   printf("Creados: \n");

   for(i=0; i<num_creados; i++){
     printf("%d\n", creados[i]);
   }

   free(creados);

}


int isDistinguible(int **matriz, int estado1, int estado2){
  if(estado1 == estado2){
    return 1;
  }

  if(matriz[estado1][estado2] == 1){
    return 0;
  }
  return 1;
}


int isDistinguibleRecursiva(AFND* afnd, int **matriz, int pos1, int pos2, int num_estados, int num_simbolos){
  int i_simbolo;
  int nuevo_pos1, nuevo_pos2;
  int i;
  /*int clase[num_estados];*/
  int contador1 = 0; /* para saber si es distinguible o no */
  int contador2 = 0; /* para saber si es distinguible o no */
  int contador = 0, new_pos1, new_pos2;

  /*for(i=0; i < num_estados; i++){
    clase[i] = 0;
  }*/

  /*miramos si estan marcados*/
  if (isDistinguible(matriz, pos1, pos2) == 0){
    return 1;
  }

  /* */
  if (pos1 == pos2) {
    return 0;
  }

  /* para cada simbolo */
  for (i_simbolo = 0; i_simbolo < num_simbolos; i_simbolo++){
    new_pos1 = -1;
    new_pos2 = -1;
    /* para cada estado */
    for(i=0; i < num_estados; i++){
      if(i!=pos1 && i!=pos2){
        if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, pos1, i_simbolo, i) == 1){
          new_pos1 = i;
        /*  printf("hay transicion de %d a %d por el sim %d\n", pos1, i, i_simbolo);
          contador1 += isDistinguibleRecursiva(afnd, matriz, pos1,i,num_estados,num_simbolos);
          printf("\t dice que %d y %d es distinguible si 1: RES = %d\n", pos1, i, contador1);*/
        }
        if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, pos2, i_simbolo, i) == 1){
          new_pos2 = i;
        /*  printf("hay transicion de %d a %d por el sim %d\n", pos2, i, i_simbolo);
          contador2 += isDistinguibleRecursiva(afnd, matriz, pos2,i,num_estados,num_simbolos);
          printf("\t dice que %d y %d es distinguible si 1: RES = %d\n", pos2, i, contador2);*/
        }
      }
    }
    if(new_pos1!=-1 && new_pos2!=-1){
      contador += isDistinguibleRecursiva(afnd, matriz, new_pos1, new_pos2,num_estados,num_simbolos);
    }
  }

  /* cuando el contador es mayor que 0 es porque hemos encontrado cosas distingubles */
  /*if (contador1 != 0 && contador2 != 0) {*/
  if (contador != 0) {
    return 1;
  }

  return 0;
}

void tachaTablaRecursiva(AFND* afnd, int **matriz_distiguibles, int num_estados, int num_simbolos){
  int flag = 0;
  int i, j;
  for (i=0; i < num_estados; i++){
    for(j=0; j < num_estados; j++){
      if(i != j){
        printf("mira isdistinguible (%d, %d)\n", i, j);
        if (isDistinguibleRecursiva(afnd, matriz_distiguibles, i, j, num_estados, num_simbolos) == 1){
          if(matriz_distiguibles[i][j] != 1) {
            printf("tacha el par %d, %d\n", i, j);
            flag=1;
          }
          matriz_distiguibles[i][j] = 1;
          matriz_distiguibles[j][i] = 1;
        }
      }
    }
  }

  for (i=0; i < num_estados; i++){
    for(j=0; j < num_estados; j++){
      printf("%d-", matriz_distiguibles[i][j]);
    }
    printf("\n");
  }

  if(flag==1) tachaTablaRecursiva(afnd, matriz_distiguibles, num_estados, num_simbolos);
}

void estadosDistinguibles(AFND *afnd){
  int num_estados, num_simbolos;
  int **matriz_distiguibles;
  int i, j;
  int estado_final;

  num_estados = AFNDNumEstados(afnd);
  num_simbolos = AFNDNumSimbolos(afnd);

  matriz_distiguibles = (int **)malloc(sizeof(int *)*num_estados);
  for (i=0; i < num_estados; i++){
    matriz_distiguibles[i] = (int *)malloc(sizeof(int)*num_estados);
    for (j=0; j < num_estados; j++){
      matriz_distiguibles[i][j] = 0;
    }
  }
  printf("ha reservado memoria para la matriz jeje\n");

  /* Hayamos los primeros distinguibles, los que sean finales */
  for (i=0; i < num_estados; i++){
    if(AFNDTipoEstadoEn(afnd, i) == FINAL || AFNDTipoEstadoEn(afnd, i) == INICIAL_Y_FINAL){
      for (j=0; j < num_estados; j++){
        if(AFNDTipoEstadoEn(afnd, j) != FINAL && AFNDTipoEstadoEn(afnd, j) != INICIAL_Y_FINAL){
          matriz_distiguibles[i][j] = 1;
          matriz_distiguibles[j][i] = 1;
        }
      }
    }
  }

  for (i=0; i < num_estados; i++){
    for(j=0; j < num_estados; j++){
      printf("%d-", matriz_distiguibles[i][j]);
    }
    printf("\n");
  }


  /* para cada p-q*/
  /*for (i=0; i < num_estados; i++){
    for(j=0; j < num_estados; j++){
      if(i != j){
        printf("mira isdistinguible (%d, %d)\n", i, j);
        if (isDistinguibleRecursiva(afnd, matriz_distiguibles, i, j, num_estados, num_simbolos) == 1){
          if(matriz_distiguibles[i][j] != 1) flag=1;
          matriz_distiguibles[i][j] = 1;
          matriz_distiguibles[j][i] = 1;
        }
      }
    }
  }*/

  tachaTablaRecursiva(afnd, matriz_distiguibles, num_estados, num_simbolos);


  /* imprimimos la matriz */
  /*for (i=0; i < num_estados; i++){
    for(j=0; j < num_estados; j++){
      printf("%d-", matriz_distiguibles[i][j]);
    }
    printf("\n");
  }*/
}
