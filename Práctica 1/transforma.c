#include "transforma.h"

typedef struct{
  char simbolo[MAX_NOMBRE]; /*es el simbolo con el que puedo ir al estado final*/
  char estado_final[MAX_NOMBRE];
  int *t_codificacion; /*esto es una lista [1,1,0,0,0,0,1,0]*/
}Transicion;


/* Intermedia es la estructura que nos define los estados
del autómata finito determinista */
typedef struct{
  char nombre_estado[MAX_NOMBRE];
  int *i_codificacion; /*esto es una lista [1,1,0,0,0,0,1,0]*/
  int tipo; /*tipo que va a ser: final, inicial, etc*/
  Transicion *transiciones[MAX_TRANSICIONES]; /*no se es necesario hacerlo dinamico, con lo cual lo hemos hecho estatico*/
}Intermedia;


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

/*
* AFNDTransforma
*
* Transforma un AFND en un AFD equivalente
*
* Salida:
*   AFND creado equivalente
*   NULL en caso de error
*/

AFND* AFNDTransforma(AFND* afnd){

  /*Intermedia *inicial; creo que aqui vamos a guardar todos los estados que vayan saliendiendo en el afnd*/
  Intermedia **creados = NULL;
  int num_estados, num_simbolos, check, tipo_estado_nuevo, flag_hay_transiciones = 0, aux;
  int pos_inicial, cont_transiciones, k, flag_estado_final = 0;
  char nombre_inicial[MAX_NOMBRE], simbolo[MAX_NOMBRE];
  char nombre_nuevo_estado[MAX_NOMBRE];
  char str[MAX_NOMBRE]; /*este sirve para pasar el nombre de cada subestado a cadena de caracteres y luego concatenar para poder hacer q0q1 */
  AFND *determinista;
  size_t tam_creados;

  /*i_simbolo me sirve para saber porque simbolo voy
  i me sirve para contar por el estado que voy en la lista creados
  i_subestado me sirve para saber el indice del subestado por el que voy. Si tengo q0q2 primero tendre i_subestado = 0 y luego i_subestado = 2
  i_cada_estado_AFND me sirve para comprobar los estados destino en las transiciones
  i_trans me dice por donde me he quedado en las transiciones de un nuevo estado
  contador es para saber donde tengo que añadir luego a la lista de creados
  contador_expandidos es para saber donde tengo que añadir luego en la lista de expandidos*/
  int i,i_simbolo,i_subestado, contador = 0, i_cada_estado_AFND;
  int num_estados_creados = 1;
  int *nuevo_estado;
  int *codificacion_inicial;

  /* obtenemos datos del automata original*/
  num_estados = AFNDNumEstados(afnd);
  num_simbolos = AFNDNumSimbolos(afnd);

  nuevo_estado = (int*)malloc(sizeof(int)*num_estados);
  codificacion_inicial = (int*)malloc(sizeof(int)*num_estados);

  
  /* obtenemos el estado inicial.
  Lo que recibimos es la posicion del estado inicial*/
  pos_inicial = AFNDIndiceEstadoInicial(afnd);

  /* tenemos que crear la estructura intermedia para el estado incial
  obtenemos el nombre del estado incial*/
  strcpy(nombre_inicial, AFNDNombreEstadoEn(afnd, pos_inicial));

  
  for (k=0; k<num_estados; k++){
    nuevo_estado[k] = 0;
  }

  /* como soy el inicial y se que posicion tengo tendre que decirle a la i_codificacion que soy el [1,0,0,0,0] */
  
  for (i=0; i<num_estados; i++){
    if(i == pos_inicial){
      codificacion_inicial[i] = 1;
    }
    else{
      codificacion_inicial[i] = 0;
    }
  }

  /* COMPROBANDO LAS LAMBDAS DEL ESTADO INICIAL */
  for (i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND++) {
    if (AFNDCierreLTransicionIJ(afnd, pos_inicial, i_cada_estado_AFND) == 1 && pos_inicial != i_cada_estado_AFND) {
      printf(" ===== HAY TRANSICION LAMDA DE %d A %d ==========\n", pos_inicial, i_cada_estado_AFND);
      /* Si se puede ir con transiciones lambda lo indicamos en la codificacion y en el nombre*/
      strcat(nombre_inicial, "q");
      sprintf(str, "%d", i_cada_estado_AFND);
      strcat(nombre_inicial,str);
      codificacion_inicial[i_cada_estado_AFND] = 1;
    }
  }
 

  creados = (Intermedia **)malloc(sizeof(Intermedia *)+8);
  creados[0] = crear_intermedia(nombre_inicial, num_estados, INICIAL, codificacion_inicial);
  creados[1] = NULL;
  i = contador;
  contador ++;

  
  while(creados[i] != NULL || i == 0){

    printf("////////////////////////////////Iteracion %d\n", i);
    printf("////////////////////////////////Iteracion %d\n", i);
    printf("////////////////////////////////Iteracion %d\n", i);

    cont_transiciones = 0;
    
    printf("++++++Imprimiendo creados[i]\n" );
    if (i == 3){
      if (!creados[i+1]) {
        printf("NO HAY 3 kikikikikiikikikikikikikikikik\n" );
      }

      else {
        printf("SI HAY tikitikitikitikitkikikikikikiiki\n");
      }
    }
    imprimir_intermedia(creados[i], num_estados);


    /*ahora queremos para cada simbolo --> tenemos el numero de simbolos*/
    for (i_simbolo = 0; i_simbolo < num_simbolos; i_simbolo++){

      /* lo que tengo que hacer es coger el simbolo del alfabeto*/
      strcpy(simbolo, AFNDSimboloEn(afnd, i_simbolo)); /*ya tenemos el primer simbolo*/
      printf("$$$$$$$ PARA EL SIMBOLO %s $$$$$$\n", simbolo);

      /*para cada sub estado del estado actual: Con subestado nos queremos referir a que si el estado actual es q0q1 tenemos el estado incial*/
      flag_hay_transiciones = 0;

      for (k=0; k<num_estados; k++){
        nuevo_estado[k] = 0;
      }

      for(i_subestado = 0; i_subestado < num_estados; i_subestado++) {
        /* comprobamos que subestado estamos trabajando mirando en la cadena [0,0,0,0,0,0] que posiciones estan a 1, si esta a 1 --> tenemos un subestado*/
        if (creados[i]->i_codificacion[i_subestado] == 1) {
          printf("TTTTTTTTTTTTTT PARA CADA SUB ESTADO TTTTTTTTTTTTT  %d\n", i_subestado);
          /* si estamos en un subestado tenemos que mirar a donde podemos ir*/
          if (flag_hay_transiciones != 1) {
            strcpy(nombre_nuevo_estado, "");
          }

          printf(" --> antes de empezar a mirar si hay transiciones o no: %s\n", nombre_nuevo_estado);
          for (i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND ++) {
            if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i_subestado, i_simbolo, i_cada_estado_AFND) == 1) {
              flag_hay_transiciones = 1;
              printf("Hay transiciones <<<<<<<<<<<<<<<\n");

              if(nuevo_estado[i_cada_estado_AFND] == 0){
                strcpy(str, "");
                strcat(nombre_nuevo_estado, "q");
                sprintf(str, "%d", i_cada_estado_AFND);
                strcat(nombre_nuevo_estado, str);
                printf("nomre_nuevo_estado: %s ççççççççççççççççççççç+++++++++++++\n", nombre_nuevo_estado);
                nuevo_estado[i_cada_estado_AFND] = 1;
              }

              if(AFNDTipoEstadoEn(afnd, i_cada_estado_AFND) == FINAL || AFNDTipoEstadoEn(afnd, i_cada_estado_AFND) == INICIAL_Y_FINAL){
                flag_estado_final = 2;
                printf("---> TENEMOS UN ESTADO FINAL %s <<<<----", nombre_nuevo_estado);
              }
            }
          }
          }
        }

        for (i_subestado = 0; i_subestado < num_estados; i_subestado++) {
          if(nuevo_estado[i_subestado] == 1) { /* para los estados a los que podemos ir, miramos las lambdas */
            for (i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND++) {
              if (AFNDCierreLTransicionIJ(afnd, i_subestado, i_cada_estado_AFND) == 1 && i_subestado != i_cada_estado_AFND) {
                printf(" ==== ESTAMOS MIRANDO PARA OTROS ESTADOS QUE NO SON EL INICIAL SI HAY TRANSICIONES LAMBDA === \n");
                if (nuevo_estado[i_cada_estado_AFND] == 0) {
                strcat(nombre_nuevo_estado, "q");
                sprintf(str, "%d", i_cada_estado_AFND);
                strcat(nombre_nuevo_estado, str);
                nuevo_estado[i_cada_estado_AFND] = 1;
                imprimir_codificiacion(nuevo_estado, num_estados);

              }


              if(AFNDTipoEstadoEn(afnd, i_cada_estado_AFND) == FINAL || AFNDTipoEstadoEn(afnd, i_cada_estado_AFND) == INICIAL_Y_FINAL){
                flag_estado_final = 2;
                printf("---> TENEMOS UN ESTADO FINAL lambas %s <<<<----", nombre_nuevo_estado);
              }
            }
          }
        }
      }

          if(flag_hay_transiciones == 1){
            /* TRANSICION */
            /* creados[i]->transiciones[cont_transiciones] = (Transicion *)malloc(sizeof(Transicion)); */
            creados[i]->transiciones[cont_transiciones] = crear_transicion(num_estados, simbolo, nombre_nuevo_estado, nuevo_estado);
            printf("^^^^^^Imprimiendo transicion que añadimos a creados[i]\n" );
            imprimir_transicion(creados[i]->transiciones[cont_transiciones], num_estados);
            cont_transiciones++;
            creados[i]->transiciones[cont_transiciones] = NULL;
            /* EN TEORIA YA TENEMOS EL NUEVO ESTADO CREADO, ES DECIR, TENEMOS UNA NUEVA ESTRUCTURA INTERMEDIA QUE TENEMOS QUE AÑADIR A CREADOS NO ?
            PRIMERO TENEMOS QUE COMPROBAR SI YA ESTA EN CREADOS O NO. SI NO ESTA LO METEMOS --> podemos directamente ni crearlo */
            printf("La codificacion que he probado es:\n" );
            
            for (aux = 0; aux <num_estados;aux++){
              printf("%d-",nuevo_estado[aux] );
            }

            printf("\n ANTES DE IS ESTADO IN !!!!!!!!!!! %d", num_estados_creados-1);
            check = is_estado_in(nuevo_estado, creados, num_estados, num_estados_creados-1);
            printf("CHECK = %d\n", check);
            if (check == 0) { /* igual todo lo que hacemos aqui podemos juntarlo en una funcion para que sea mas corta */
              printf("Dentro del check. No esta en creados\n" );
              if (flag_estado_final == 2){
                tipo_estado_nuevo = FINAL;
              } else {
                tipo_estado_nuevo = NORMAL;
              }
              flag_estado_final = 0;
              tam_creados = sizeof(creados);

              printf(",,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,Cuantos tengo añadidos en creados j = %d\n", num_estados_creados);

              creados = (Intermedia **)realloc(creados, tam_creados+sizeof(Intermedia *)+8*num_estados_creados);
              creados[num_estados_creados] = crear_intermedia(nombre_nuevo_estado, num_estados, tipo_estado_nuevo, nuevo_estado);
              num_estados_creados++;
              creados[num_estados_creados] = NULL;
              printf("Voy a imprimir el ultimo que meto en creados\n");
              imprimir_intermedia(creados[num_estados_creados-1], num_estados);
            }
          }
    }
    i++;
  }


  printf(" ----->>>>>>>> EL ALGORITMO HA TERMINADO <<<<<<<<<<<-------- VALOR DE LA i = %d\n", i);
  /* Creamos el autómata determinista para poder dibujarlo */
  
  free(creados[i]);
  free(nuevo_estado);
  free(codificacion_inicial);
  contador = i;

  printf("contador: %d\n", contador);
  determinista = AFNDNuevo("afd", contador, num_simbolos);

  /* Insertamos los símbolos en el nuevo autómata */
  for (i=0; i<num_simbolos; i++){
    AFNDInsertaSimbolo(determinista, AFNDSimboloEn(afnd, i));
  }

  /* Insetamos los estados */
  for (i=0; i<contador; i++){
    AFNDInsertaEstado(determinista, creados[i]->nombre_estado, creados[i]->tipo);
  }

  /* Insertamos las transiciones*/
  /* AFNDInsertaTransicion(p_afnd, "q0", "+", "q1"); */
  for (i=0; i<contador; i++){
    k = 0;
    while(creados[i]->transiciones[k] != NULL){
      AFNDInsertaTransicion(determinista,
                            creados[i]->nombre_estado,
                            creados[i]->transiciones[k]->simbolo,
                            creados[i]->transiciones[k]->estado_final);

      k++;
    }
  }

  for ( i = 0; i < contador; i++) {
    k = 0;
    while(creados[i]->transiciones[k] != NULL){
      eliminar_transicion(creados[i]->transiciones[k]);
      k++;
    }

    eliminar_intermedia(creados[i]);
  }

  free(creados);
  return determinista;

}
