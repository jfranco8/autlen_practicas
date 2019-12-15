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

/* Devuelve 0 si no es accesible */
int isInAccesibles(int *accesibles, int pos){
  if(accesibles[pos] == 0){
    return 0;
  }
  return 1;
}

/*void estadosAccesibles(AFND *afnd){
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

}*/

int* estadosAccesibles(AFND *afnd){
   int pos_inicial, pos_llega;
   int *creados, *accesibles;
   int i_num_creados = 0;
   int num_estados, num_simbolos;
   int i_simbolo, i_estado, i;
   int num_creados;

   if(!afnd)
    return NULL;

   pos_inicial = AFNDIndiceEstadoInicial(afnd);
   num_estados = AFNDNumEstados(afnd);
   num_simbolos = AFNDNumSimbolos(afnd);

   creados = (int *)malloc(sizeof(int) + 4);
   creados[0] = pos_inicial;
   i_num_creados  = 0;
   num_creados = 1;

   accesibles = (int *)malloc(sizeof(int) * num_estados);
   for(i=0; i<num_estados; i++){
     accesibles[i] = 0;
   }

   while(creados[i_num_creados] != -1 || i_num_creados == 0){
     for(i_simbolo = 0; i_simbolo < num_simbolos; i_simbolo ++){
       for(i_estado = 0; i_estado < num_estados; i_estado ++){
         if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, creados[i_num_creados], i_simbolo, i_estado) == 1){
           if(notInCreados(creados, i_estado, i_num_creados) == 0){
             printf("Hay transición de %d a %d\n", creados[i_num_creados], i_estado);
             accesibles[i_estado] = 1;
             creados = (int *)realloc(creados, sizeof(creados)+sizeof(int) + 4*num_creados);
             creados[num_creados] = i_estado;
             num_creados ++;
             creados[num_creados] = -1;
           }
         }
         if(AFNDTipoEstadoEn(afnd, i_estado) == INICIAL || AFNDTipoEstadoEn(afnd, i_estado) == INICIAL_Y_FINAL)
          accesibles[i_estado] = 1;
       }
     }
     i_num_creados ++;
   }


   printf("Accesibles: \n");

   for(i=0; i<num_estados; i++){
     printf("%d\n", accesibles[i]);
   }

   free(creados);

   return accesibles;

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


int** estadosDistinguibles(AFND *afnd){
  int num_estados, num_simbolos;
  int **matriz_distinguibles;
  /* i_simbolo lo utilizamos para cada simbolo
     i_cada_estado lo utilizamos para ver el siguiente estado y ver si hay transicion
   */
  int i, j, flag = 0, i_simbolo, i_cada_estado;
  /* new_pos1 y new_pos2 los utilizamos para obtener las siguientes transiciones a (i,j)*/
  int estado_final, new_pos1 = 0, new_pos2 = 0;

  if(!afnd)
    return NULL;

  num_estados = AFNDNumEstados(afnd);
  num_simbolos = AFNDNumSimbolos(afnd);
  printf("\nNUMERO ESTADOS: %d\nNUMERO SIMBOLOS: %d\n", num_estados, num_simbolos);

  /* reservamos memoria para la matriz */
  matriz_distinguibles = (int **)malloc(sizeof(int *)*num_estados);
  for (i=0; i < num_estados; i++){
    matriz_distinguibles[i] = (int *)malloc(sizeof(int)*num_estados);
  }

  /* inicializamos la matriz todo a 0*/
  for (i=0;i<num_estados;i++){
    for(j=0;j<num_estados;j++) {
      matriz_distinguibles[i][j] = 0;
    }
  }

  for (i=0; i < num_estados; i++){
    for(j=0; j < num_estados; j++){
      printf("%d-", matriz_distinguibles[i][j]);
    }
    printf("\n");
  }

  printf("ha reservado memoria para la matriz jeje\n");

  /* Hayamos los primeros distinguibles, los que sean finales */
  for (i=0; i < num_estados; i++){
    if(AFNDTipoEstadoEn(afnd, i) == FINAL || AFNDTipoEstadoEn(afnd, i) == INICIAL_Y_FINAL){
      for (j=0; j < num_estados; j++){
        if(AFNDTipoEstadoEn(afnd, j) != FINAL && AFNDTipoEstadoEn(afnd, j) != INICIAL_Y_FINAL){
          matriz_distinguibles[i][j] = 1;
          matriz_distinguibles[j][i] = 1;
        }
      }
    }
  }

  for (i=0; i < num_estados; i++){
    for(j=0; j < num_estados; j++){
      printf("%d-", matriz_distinguibles[i][j]);
    }
    printf("\n");
  }

  /* La primera vez se tachan bien */
  /* luego hay que mirar por pares, si tenemos (q0,q1) y me da con el 0 (q3,q4) entonces si los tengo marcados como distintos, es que
  (q0,q1) tambien son distitnos asi que marcamos (q0,q1) como distintos. Utiliza un flag para si cambiamos algo de la tabla
  volver a hacerlo hasta que el flag se quede a 0 */


  /* mientras que hayamos hayamos cambiado el flag, haremos este proceso*/
  flag = 1; /*para que entre por primera vez en el bucle*/
  while(flag){
    flag = 0;
    for (i=0; i < num_estados; i++){
      for(j=0; j < num_estados; j++){
        if(i != j){
          printf("mira isdistinguible (%d, %d)\n", i, j);
          /* miramos que no este marcado en la matriz para poder mirar sus transiciones */
          if (matriz_distinguibles[i][j] == 0) {
            printf("mira isdistinguible (%d, %d) --> NO ESTA MARCADO\n", i, j);
            /* si no esta marcado, lo estudiamos */
            /* vamos a mirar a donde podemos ir con las transiciones */
            for (i_simbolo = 0; i_simbolo < num_simbolos; i_simbolo++){
              /* para cada estado */
              for(i_cada_estado=0; i_cada_estado < num_estados; i_cada_estado++){

                if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, i_simbolo, i_cada_estado) == 1){
                  new_pos1 = i_cada_estado;
                  printf("(new_pos1, i_cada_estado) hay transicion entre %d y %d con el simbolo %d\n", i, i_cada_estado,i_simbolo);
                }
                if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, j, i_simbolo, i_cada_estado) == 1){
                  printf("(new_pos2, i_cada_estado) hay transicion entre %d y %d\n", j, i_cada_estado);
                  new_pos2 = i_cada_estado;
                }
              }
              /* lo miramos en el caso de que sean diferentes */
              printf("FLAG = %d\n", flag);
              if (new_pos2 != new_pos1) {
                printf("(new_pos1,new_pos2) --> (%d,%d)\n", new_pos1, new_pos2);
                /* tenemos que mirar si esta transicion esta marcada*/
                if(matriz_distinguibles[new_pos1][new_pos2] == 1){
                  printf("voy a marcar %d,%d\n", i,j);
                  matriz_distinguibles[i][j] = 1;
                  matriz_distinguibles[j][i] = 1;
                  flag = 1;
                  break;
                }
              }
            }
          }
        }
      }
    }
  }

  /* imprimimos la matriz */
  for (i=0; i < num_estados; i++){
    for(j=0; j < num_estados; j++){
      printf("%d-", matriz_distinguibles[i][j]);
    }
    printf("\n");
  }

  return matriz_distinguibles;

}


AFND* AFNDMinimiza(AFND *afnd){

  int *accesibles = NULL;
  int **matriz_distinguibles = NULL, i_cada_estado_AFND;
  int i, j, num_estados, num_estados_creados = 0, i_simbolo, num_simbolos, cont_transiciones;
  int *codificacion_clase_equivalencia;
  Intermedia **estados_nuevos = NULL;
  char nombre_nuevo_estado[MAX_NOMBRE], contador = 0;
  AFND *minimizado;
  char buffer[MAX_NOMBRE];
  int check;

  num_estados = AFNDNumEstados(afnd);
  num_simbolos = AFNDNumSimbolos(afnd);

  printf("********** ESTADOS_ACCESIBLES **********\n");
  accesibles = estadosAccesibles(afnd);
  printf("********** MATRIZ_DISTINGUIBLES **********\n");
  matriz_distinguibles = estadosDistinguibles(afnd);

  printf("********** ACCESBLES IMPRESO FUERA **********\n");
  printf("Accesibles: \n");
  for(i=0; i<num_estados; i++){
    printf("%d\n", accesibles[i]);
  }
  printf("********** MATRIZ IMPRESA FUERA **********\n");
  for (i=0; i < num_estados; i++){
    for(j=0; j < num_estados; j++){
      printf("%d-", matriz_distinguibles[i][j]);
    }
    printf("\n");
  }

  /* Obtenemos las clases de equivalencia de la matriz, y para cada una de ellas
  creamos una estructura intermedia, un nuevo estado equivalente */

  estados_nuevos = (Intermedia **)malloc(sizeof(Intermedia *)+8);
  codificacion_clase_equivalencia = (int *)malloc(sizeof(int)*num_estados);

  for (i=0; i < num_estados; i++){
    if(accesibles[i] != 0){
      cont_transiciones = 0;
      strcpy(nombre_nuevo_estado, "q");
      /* Creamos la el nodo equivalencia de i (si no lo tenemos creado aún) */
      for(j=0; j<num_estados; j++){
        codificacion_clase_equivalencia[j] = 0;
      }

      for(j=0; j < num_estados; j++){
        if(isInAccesibles(accesibles, j) == 1){
          codificacion_clase_equivalencia[j] = matriz_distinguibles[i][j];
          if(codificacion_clase_equivalencia[j] == 0){
            sprintf(buffer, "_%d", j);
            strcat(nombre_nuevo_estado, buffer);
          }
        } else {
          codificacion_clase_equivalencia[j] = 1; /* La clase la forman los que estén a 0 */
        }
      }

      printf("Clase de equivalencia de %d: ", i);
      for(j=0; j < num_estados; j++){
        printf("%d", codificacion_clase_equivalencia[j]);
      }
      printf("\n");

      /* Guardamos la codificación inversa */
      check = is_estado_in(codificacion_clase_equivalencia, estados_nuevos, num_estados, num_estados_creados-1);
      if(check == 0){
        contador++;
        estados_nuevos = (Intermedia **)realloc(estados_nuevos, sizeof(estados_nuevos)+sizeof(Intermedia *)+(8*num_estados_creados));
        estados_nuevos[num_estados_creados] = crear_intermedia(nombre_nuevo_estado, num_estados, AFNDTipoEstadoEn(afnd, i), codificacion_clase_equivalencia);
        num_estados_creados++;
        estados_nuevos[num_estados_creados] = NULL;

        for(i_simbolo = 0; i_simbolo<num_simbolos; i_simbolo++){
          for(j=0; j<num_estados; j++){
            codificacion_clase_equivalencia[j] = 0;
          }
          strcpy(nombre_nuevo_estado, "q");
          for(i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND++){
            if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, i_simbolo, i_cada_estado_AFND) == 1){
              for(j=0; j < num_estados; j++){
                if(isInAccesibles(accesibles, j) == 1){
                  codificacion_clase_equivalencia[j] = matriz_distinguibles[i_cada_estado_AFND][j];
                  if(codificacion_clase_equivalencia[j] == 0){
                    sprintf(buffer, "_%d", j);
                    strcat(nombre_nuevo_estado, buffer);
                  }
                } else {
                  codificacion_clase_equivalencia[j] = 1; /* La clase la forman los que estén a 0 */
                }
              }

              /* Reservamos memoria para la transicion y se la asignamos al nuevo estado */
              set_intermedia_transicion(estados_nuevos[num_estados_creados-1], cont_transiciones, crear_transicion(num_estados, AFNDSimboloEn(afnd, i_simbolo), nombre_nuevo_estado, codificacion_clase_equivalencia));
              cont_transiciones++;

              /* ponemos la siguente transicion  a null para poder romper los bucles while*/
              set_intermedia_transicion(estados_nuevos[num_estados_creados-1], cont_transiciones, NULL);

            }
          }
        }
      }
    }
  }

  estados_nuevos[contador] = NULL;
  minimizado = crear_automata_determinista(afnd, estados_nuevos, contador, num_simbolos);

  if(accesibles)
    free(accesibles);

  if(matriz_distinguibles){
    for (i=0; i < num_estados; i++){
      if(matriz_distinguibles[i]){
        free(matriz_distinguibles[i]);
      }
    }
    free(matriz_distinguibles);
  }

  return minimizado;

}
