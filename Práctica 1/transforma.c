/**
 * Autores: Sofia Sanchez y Jesus Daniel Franco
 * Fichero: intermedia.h
 *
 * Contiene las funciones
 *
 */

#include "transforma.h"

/**
 * Get_tipo_estado
 *
 * Argumentos de entrada:
 *  - afnd:
 *  - posicion:
 *  - tipo_antes:
 *
 * Salida:
 *
 *
 */
int get_tipo_estado(AFND *afnd, int posicion, int tipo_antes){
  if(tipo_antes==INICIAL) {
    if(AFNDTipoEstadoEn(afnd, posicion) == INICIAL){
      return INICIAL;
    }
    if(AFNDTipoEstadoEn(afnd, posicion) == FINAL){
      return INICIAL_Y_FINAL;
    }
    if(AFNDTipoEstadoEn(afnd, posicion) == INICIAL_Y_FINAL){
      return INICIAL_Y_FINAL;
    }
    if(AFNDTipoEstadoEn(afnd, posicion) == NORMAL){
      return INICIAL;
    }
  }
  if(tipo_antes==FINAL) {
    if(AFNDTipoEstadoEn(afnd, posicion) == INICIAL){
      return INICIAL_Y_FINAL;
    }
    if(AFNDTipoEstadoEn(afnd, posicion) == FINAL){
      return FINAL;
    }
    if(AFNDTipoEstadoEn(afnd, posicion) == INICIAL_Y_FINAL){
      return INICIAL_Y_FINAL;
    }
    if(AFNDTipoEstadoEn(afnd, posicion) == NORMAL){
      return FINAL;
    }
  }
  if(tipo_antes==INICIAL_Y_FINAL) {
    return INICIAL_Y_FINAL;
  }
  /*Si la posicion anterior era normal, se queda con la que viene*/
  return AFNDTipoEstadoEn(afnd, posicion);
}

void inicializar_codificacion(int *cod, int num_estados) {
  int i;
  for (i = 0; i <num_estados; i++){
    cod[i] = 0;
  }
}

void inicializar_codificacion_inicial(int *cod, int num_estados, int pos_inicial){
  int i;

  for (i = 0; i < num_estados; i++){
    if(i == pos_inicial){
      cod[i] = 1;
    }
    else{
      cod[i] = 0;
    }
  }
}

AFND *crear_automata_determinista(AFND *afnd, Intermedia **creados, int contador, int num_simbolos) {
  AFND *determinista = NULL;
  int i, k;
  determinista = AFNDNuevo("afd", contador, num_simbolos);

  /* Insertamos los símbolos en el nuevo autómata */
  for (i = 0; i < num_simbolos; i++){
    AFNDInsertaSimbolo(determinista, AFNDSimboloEn(afnd, i));
  }

  /* Insetamos los estados */
  for (i = 0; i < contador; i++){
    AFNDInsertaEstado(determinista, get_intermedia_nombre(creados[i]), get_intermedia_tipo(creados[i]));
  }

  /* Insertamos las transiciones*/
  for (i = 0; i < contador; i++){
    k = 0;
    while(get_intermedia_transicion(creados[i], k) != NULL){
      AFNDInsertaTransicion(determinista,
                            get_intermedia_nombre(creados[i]),
                            get_transicion_simbolo(get_intermedia_transicion(creados[i],k)),
                            get_transicion_estadofinal(get_intermedia_transicion(creados[i],k)));

      k++;
    }
  }

  return determinista;
}

void liberar_memoria(Intermedia **creados, Intermedia *creado, int contador){
  int i, k;

  free(creado);
  for (i = 0; i < contador; i++) {
    k = 0;
    while(get_intermedia_transicion(creados[i], k)  != NULL){
      eliminar_transicion(get_intermedia_transicion(creados[i],k));
      k++;
    }

    eliminar_intermedia(creados[i]);
  }

  free(creados);
}
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
AFND* AFNDTransforma(AFND* afnd){

  /*Intermedia *inicial; creo que aqui vamos a guardar todos los estados que vayan saliendiendo en el afnd*/
  Intermedia **creados = NULL;
  AFND *determinista;
  size_t tam_creados;

  int num_estados, num_simbolos, check, tipo_estado_nuevo = NORMAL;
  int pos_inicial; 
  int flag_estado_final = 0, flag_hay_transiciones = 0;

  /*
  Explicacion de las cadenas de caracteres utilizadas

  nombre_inicial sirve para guardar el nombre del estado inicial
  simbolo sirve para guardar la cadena de caracteres para el simbolo de una transicion
  nombre_nuevo_estado lo utlilizamos para guardar el nombre del nuevo estado que se ha generado con las transiciones
  str lo utlizamos como cadena auxiliar para añadir el numero al lado de una q en un nuevo estado
  */
  char nombre_inicial[MAX_NOMBRE], simbolo[MAX_NOMBRE], nombre_nuevo_estado[MAX_NOMBRE], str[MAX_NOMBRE];

  /*
  Explicacion de los contadores

  i_simbolo: me sirve para saber porque simbolo voy
  i: me sirve para contar por el estado que voy en la lista creados
  i_subestado: me sirve para saber el indice del subestado por el que voy. Si tengo q0q2 primero tendre i_subestado = 0 y luego i_subestado = 2
  i_cada_estado_AFND: me sirve para comprobar los estados destino en las transiciones
  i_trans: me dice por donde me he quedado en las transiciones de un nuevo estado
  contador: es para saber donde tengo que añadir luego a la lista de creados
  cont_transiciones: nos permite llevar la cuenta de las transiciones que metemos en un estado nuevo
  */
  int i,i_simbolo,i_subestado, contador = 0, i_cada_estado_AFND, cont_transiciones;
  int num_estados_creados = 1;
  int *nuevo_estado;
  int *codificacion_inicial, k;

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


  inicializar_codificacion(nuevo_estado, num_estados);

  /* como soy el inicial y se que posicion tengo tendre que decirle a la i_codificacion que soy el [1,0,0,0,0] */
  inicializar_codificacion_inicial(codificacion_inicial, num_estados, pos_inicial);

  /* COMPROBANDO LAS LAMBDAS DEL ESTADO INICIAL */
  for (i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND++) {
    if (AFNDCierreLTransicionIJ(afnd, pos_inicial, i_cada_estado_AFND) == 1 && pos_inicial != i_cada_estado_AFND) {
      
      /* Si se puede ir con transiciones lambda lo indicamos en la codificacion y en el nombre*/
      strcat(nombre_inicial, "q");
      sprintf(str, "%d", i_cada_estado_AFND);
      strcat(nombre_inicial,str);
      codificacion_inicial[i_cada_estado_AFND] = 1;

      flag_estado_final = get_tipo_estado(afnd, i_cada_estado_AFND, tipo_estado_nuevo);
      tipo_estado_nuevo = flag_estado_final;
    } 
    else {
      if(pos_inicial == i_cada_estado_AFND){
        tipo_estado_nuevo = INICIAL;
      }
    }
  }

  creados = (Intermedia **)malloc(sizeof(Intermedia *)+8);
  creados[0] = crear_intermedia(nombre_inicial, num_estados, tipo_estado_nuevo, codificacion_inicial);
  tipo_estado_nuevo = NORMAL;
  creados[1] = NULL;
  i = contador;
  contador ++;


  while(creados[i] != NULL || i == 0){

    cont_transiciones = 0;

    /*ahora queremos para cada simbolo --> tenemos el numero de simbolos*/
    for (i_simbolo = 0; i_simbolo < num_simbolos; i_simbolo++){
      /* lo que tengo que hacer es coger el simbolo del alfabeto*/
      strcpy(simbolo, AFNDSimboloEn(afnd, i_simbolo)); /*ya tenemos el  simbolo*/
      /*para cada sub estado del estado actual: Con subestado nos queremos referir a que si el estado actual es q0q1 tenemos el estado incial*/
      flag_hay_transiciones = 0;

      inicializar_codificacion(nuevo_estado, num_estados);

      for(i_subestado = 0; i_subestado < num_estados; i_subestado++) {
        /* comprobamos que subestado estamos trabajando mirando en la cadena [0,0,0,0,0,0] que posiciones estan a 1, si esta a 1 --> tenemos un subestado*/
        if (get_intermedia_codificacion(creados[i])[i_subestado] == 1) {

          /* si estamos en un subestado tenemos que mirar a donde podemos ir*/
          if (flag_hay_transiciones != 1) {
            strcpy(nombre_nuevo_estado, "");
          }

          for (i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND ++) {
            if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i_subestado, i_simbolo, i_cada_estado_AFND) == 1) {
              flag_hay_transiciones = 1;

              if(nuevo_estado[i_cada_estado_AFND] == 0){
                nuevo_estado[i_cada_estado_AFND] = 1;
              }

              flag_estado_final = get_tipo_estado(afnd, i_cada_estado_AFND, tipo_estado_nuevo);
              tipo_estado_nuevo = flag_estado_final;
              if(tipo_estado_nuevo == INICIAL_Y_FINAL){
                tipo_estado_nuevo = FINAL;
              } 
              else {
                if(tipo_estado_nuevo == INICIAL){
                  tipo_estado_nuevo = NORMAL;
                }
              }
            }
          }
        }
      }

      for (i_subestado = 0; i_subestado < num_estados; i_subestado++) {
        if(nuevo_estado[i_subestado] == 1) { /* para los estados a los que podemos ir, miramos las lambdas */
          for (i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND++) {
            if (AFNDCierreLTransicionIJ(afnd, i_subestado, i_cada_estado_AFND) == 1 && i_subestado != i_cada_estado_AFND) {          
              if (nuevo_estado[i_cada_estado_AFND] == 0) {
                nuevo_estado[i_cada_estado_AFND] = 1;
              }

              flag_estado_final = get_tipo_estado(afnd, i_cada_estado_AFND, tipo_estado_nuevo);
              tipo_estado_nuevo = flag_estado_final;

              if(tipo_estado_nuevo == INICIAL_Y_FINAL){
                tipo_estado_nuevo = FINAL;
              } 

              else {
                if(tipo_estado_nuevo == INICIAL){
                  tipo_estado_nuevo = NORMAL;
                }
              }
            }
          }
        }
      }

      if(flag_hay_transiciones == 1){
        strcpy(nombre_nuevo_estado, "");
        for(k = 0; k < num_estados; k++){
          if(nuevo_estado[k] == 1){
            strcat(nombre_nuevo_estado, "q");
            sprintf(str, "%d", k);
            strcat(nombre_nuevo_estado, str);
          }
        }
        /* TRANSICION */
        set_intermedia_transicion(creados[i], cont_transiciones, crear_transicion(num_estados, simbolo, nombre_nuevo_estado, nuevo_estado));
        cont_transiciones++;

            
        set_intermedia_transicion(creados[i], cont_transiciones, NULL);

        /* EN TEORIA YA TENEMOS EL NUEVO ESTADO CREADO, ES DECIR, TENEMOS UNA NUEVA ESTRUCTURA INTERMEDIA QUE TENEMOS QUE AÑADIR A CREADOS NO ?
        PRIMERO TENEMOS QUE COMPROBAR SI YA ESTA EN CREADOS O NO. SI NO ESTA LO METEMOS --> podemos directamente ni crearlo */
            
            
        check = is_estado_in(nuevo_estado, creados, num_estados, num_estados_creados-1);
        if (check == 0) { /* igual todo lo que hacemos aqui podemos juntarlo en una funcion para que sea mas corta */
          /* No esta en la lista de creados, entonces tenemos que añadirlo */
          tam_creados = sizeof(creados);

          creados = (Intermedia **)realloc(creados, tam_creados+sizeof(Intermedia *)+(8*num_estados_creados));
          creados[num_estados_creados] = crear_intermedia(nombre_nuevo_estado, num_estados, tipo_estado_nuevo, nuevo_estado);
          tipo_estado_nuevo = NORMAL;
          num_estados_creados++;
          creados[num_estados_creados] = NULL;
              
        }
      } 
      else {
        set_intermedia_transicion(creados[i], cont_transiciones, NULL);
      }
    }
    i++;
  }


  
  /* Creamos el autómata determinista para poder dibujarlo */

  
  creados[i]=NULL;
  free(nuevo_estado);
  free(codificacion_inicial);
  contador = i;

  determinista = crear_automata_determinista(afnd, creados, contador, num_simbolos);
  
  liberar_memoria(creados, creados[i], contador);
  
  return determinista;

}
