#include "transforma.h"

typedef struct{
  char simbolo[MAX_NOMBRE]; //es el simbolo con el que puedo ir al estado final
  char estado_final[MAX_NOMBRE];
  int *t_codificacion; //esto es una lista [1,1,0,0,0,0,1,0]
}Transicion;


// Intermedia es la estructura que nos define los estados
// del autómata finito determinista
typedef struct{
  char nombre_estado[MAX_NOMBRE];
  int *i_codificacion; //esto es una lista [1,1,0,0,0,0,1,0]
  int tipo; //tipo que va a ser: final, inicial, etc
  Transicion *transiciones[MAX_TRANSICIONES]; //no se es necesario hacerlo dinamico, con lo cual lo hemos hecho estatico
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

  strcpy(transicion->simbolo, simbolo);
  strcpy(transicion->estado_final,final);

  // Codificación del estado al que se transita
  transicion->t_codificacion = (int*)malloc(sizeof(int)*num_estados);
  if (transicion == NULL){
    printf("Error al reservar memoria para la nueva transicion\n");
    return NULL;
  }

  // Guardamos el estado al que se puede transitar con el símbolo dado
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

  intermedia->i_codificacion = (int*)malloc(sizeof(int)*num_estados);

  // Guardamos en codificacion la propia del estado (o estado) inicial
  // Es decir, si el AFND tiene como estados iniciales q0 y q2, nuestro
  // estado inicial en el AFD será q0q2 = [1, 0, 1, 0, 0...]
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


  /* ALGORITMO:
  Cogemos el primero que hay en la lista de los creados.
    Desde cada estado de los creados:
      Para cada simbolo:
        Para cada subestado:
          Para cada estado posible si puedo ir con ese estado
          Si puedo ir con lambda
            se hace set de la lista [1,0,0,1]
      Añadimos una nueva transicion
      Lo añadimos a la lista de estados creados
    Lo añadimos a la lista de estados expandidos





   En creados añadimos el estado inicial
   c = q0;
   para q0:
    Para cada simbolo: - 0:
                        Para cada sub estado: en este caso solo tenemos q0.
                        q0 -> q0 [1,0,0,0,0]
                        q0 -> q1 [0,1,0,0,0]
                        tenemos que crear un nuevo estado --> hacemos el or de estas dos: [1,1,0,0,0] tenemos q0q1
                        Añadimos la transicion a ese estado: origen q0 destino q0q1
                        Añadimos q0q1 a c

                       - 1:
                        Para cada sub estado: en este caso solo tenemos q0.
                        q0 -> q0

                        como ya tenemos un estado que se corresponde con q0 no creamos otro
                        No añadimos transicion porque no hemosc creado
                        No añadimos q0 a c (puesto que ya lo hemos visto)
    Añadimos a expandidos
  Para cada  q0q1 que es el siguiente que hay:
    Para cada simbolo: - 0:
                        Para cada sub estado:
                          * q0: q0,q1-> q0q1[1,1,0,0,0]
                          * q1: q1 -> x
                          obtenemos que desde este solo podemos ir a el mismo
                        - 1:
                        Para cada sub estado:
                          * q0: q0 -> q0
                          * q1: q1 -> q2
                          Tenemos que crear un uevo estado --Z hacemos el or de estas dos [1,0,1,0,0] tenemos q0q2
                          Añadimos la transicion a ese estado: origen, es el mismo, es decir la estructura con la que estamos trabanando
                          y el destino es q0q2 que lo acabamos de crear.
                          Añadimos q0a2 a c
    Añadimos a expandidos
    Para cada q0q2: (no hemos incluido q0q1 porque ya lo hemos explorado)
      Para cada simbolo: - 0:
                        Para cada sub estado:
                          * q0: q0,q1
                          * q2: x
                          Tenemos el estado q0q2 -> q0,q1 que no lo añadimos

                         - 1:
                         PAra cada sub estado:
                         * q0: x
                         * q2: x
                         Como no se puede ir a nada y q0q2 ya lo tenemos en creados el algoritmo termina y ya lo tenemos todo pensado
    Añadimos a lista de expandidos




    !!!!!! DUDAS !!!!!!!
   - para que queremos la lista expandidos ???
   - la lista de creados esta bien -> es un array de no sabemos cuanto tamaño que contiene estructuras intermedias que es donde tenemos todas esas estructuras intermedias
          - en la lista de creados tenemos todos los nuevos estados y estos nuevos estados tienen esta informacion:
                * son ellos mismos el estado origen
                * tienen un estado final
                * tienen con que simbolo van a ir
                (cosas a saber de la transicion)
                * tienen su nombre
                * tienen su codificacion para poder saber que estado es y si ya esta no lo creamos mas
                * tienen si son de tipo final o de que tipo --> demomento no entiendo muy bien para que necesitamos esto
                (cosas a saber del estado)

    - seria util crear una funcion que compare si las codificaciones son iguales? no lo se -> pensarlo, auqnue creo que si puesto
    que vamos a tener que ver si ya esta creado o no
    */


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

int comparar_codificacion(int *codificacion1, int *codificacion2){
  if(!codificacion1 || !codificacion2){
    return -1;
  }

  int len1, len2, i;

  // calculamos las longitudes de los dos arrays.
  len1 = sizeof(len1)/sizeof(int);
  len2 = sizeof(len2)/sizeof(int);

  // si las longitudes son distintas NO pueden ser los mismos estado, ya que
  // no forman parte del mismo AF
  if (len1 != len2){
    return -1;
  }

  for (i=0; i<len1; i++){
    if(codificacion1[i] != codificacion2[i]){
      return 0;
    }
  }

  // si recorremos toda la lista y no hay diferencias, son iguales
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

int is_estado_in(int *codificacion, Intermedia **creados) {
  int i, num_creados;

  if(!codificacion  || !creados){
    return -1;
  }

  num_creados = sizeof(creados)/sizeof(Intermedia);

  for (i = 0; i < num_creados; i++) {
    // Vemos si la codificacion dada coincide con alguna de las que ya tenemos
    // en creados. Si coincide, devolvemos un 1
    if (comparar_codificacion(codificacion, creados[i]->i_codificacion) == 1){
      return 1;
    }
  }

  // si la codificacion no coincide con ningun estados de lso ya creados,
  // devolvemos un 0
  return 0;
}


// void encuentra_lambdas(AFND *afnd, ){
//
// }


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

  // TENGO UN LIO CON LOS PUNTEROS DE LAS COSAS ESTAS
  // le he puesto MAX NOMBRE PARA QUE NO ME DIERA ERROR PORQUE SI NO AL HACER creados[contador] = inicial; ME DA ERROR AL ASIGNAR VARIABLES
  Intermedia *inicial, *estado_actual; //creo que aqui vamos a guardar todos los estados que vayan saliendiendo en el afnd
  Intermedia *creados[MAX_NOMBRE], *expandidos[MAX_NOMBRE];
  int num_estados, num_simbolos, check, tipo_estado_nuevo;
  int pos_inicial, cont_transiciones, k, flag_estado_final;
  char* nombre_inicial, *simbolo;
  Transicion *trans_nuevo_estado;
  Intermedia *inter_nuevo_estado;
  char nombre_nuevo_estado[MAX_NOMBRE];
  char str[MAX_NOMBRE]; //este sirve para pasar el nombre de cada subestado a cadena de caracteres y luego concatenar para poder hacer q0q1
  AFND *determinista;

  //i_simbolo me sirve para saber porque simbolo voy
  //i me sirve para contar por el estado que voy en la lista creados
  //i_subestado me sirve para saber el indice del subestado por el que voy. Si tengo q0q2 primero tendre i_subestado = 0 y luego i_subestado = 2
  //i_cada_estado_AFND me sirve para comprobar los estados destino en las transiciones
  //i_trans me dice por donde me he quedado en las transiciones de un nuevo estado
  //contador es para saber donde tengo que añadir luego a la lista de creados
  //contador_expandidos es para saber donde tengo que añadir luego en la lista de expandidos
  int i,i_simbolo,i_subestado, contador = 0, i_cada_estado_AFND, i_trans, contador_expandidos = 0;

  //obtenemos datos del automata original
  num_estados = AFNDNumEstados(afnd);
  num_simbolos = AFNDNumSimbolos(afnd);

  //obtenemos el estado inicial.
  //Lo que recibimos es la posicion del estado inicial
  pos_inicial = AFNDIndiceEstadoInicial(afnd);

  //tenemos que crear la estructura intermedia para el estado incial
  //obtenemos el nombre del estado incial
  nombre_inicial = AFNDNombreEstadoEn(afnd, pos_inicial);

  int nuevo_estado[num_estados];
  for (k=0; k<num_estados; k++){
    nuevo_estado[k] = 0;
  }

  //como soy el inicial y se que posicion tengo tendre que decirle a la i_codificacion que soy el [1,0,0,0,0]
  int codificacion_inicial[num_estados];
  for (i=0; i<num_estados; i++){
    if(i == pos_inicial){
      codificacion_inicial[i] = 1;
    }
    else{
      codificacion_inicial[i] = 0;
    }
  }

  // COMPROBAR LAMBDAS ANTES
  inicial = crear_intermedia(nombre_inicial, num_estados, INICIAL, codificacion_inicial); //a esta funcion se le pasa el tipo pero no se si es necesario --> LE HE PASADO POS_INICIAL PARA QUE NP ME SALGA ERROR TODO EL RATO PERO HAY QUE CAMBIARLO
  //lo hago aqui cuando ya he creado la estructura intermedia

  creados[contador] = inicial;
  contador ++;
  i = contador-1;

  //para cada estado que tenemos en creados: ---> !! he comparado i < num_estados porque es lo unico que me cuadra pero igual lo que tneemos
  // que hacer es para cada estado del afnd ??? no se nuestro algoritmo no es asi pero ESTO HAY QUE OENSARLO
  while(creados[i]){
    cont_transiciones = 0;
    estado_actual = creados[i];



    //ahora queremos para cada simbolo --> tenemos el numero de simbolos
    for (i_simbolo = 0; i_simbolo < num_simbolos; i_simbolo++){

      //digo yo que tendremos alguna funcion que me diga a que estados voy con ese simbolo desde el actual ??? --> creo que si que la hay
      // lo que tengo que hacer es coger el simbolo del alfabeto
      strcpy(simbolo, AFNDSimboloEn(afnd, i_simbolo)); //ya tenemos el primer simbolo

      //para cada sub estado del estado actual: Con subestado nos queremos referir a que si el estado actual es q0q1 tenemos el estado incial
      for(i_subestado = 0; i_subestado < num_estados; i++) {
        //comprobamos que subestado estamos trabajando mirando en la cadena [0,0,0,0,0,0] que posiciones estan a 1, si esta a 1 --> tenemos un subestado
        if (estado_actual->i_codificacion[i_subestado] == 1) {
          //si estamos en un subestado tenemos que mirar a donde podemos ir
          //sabemos que el estado actual YA ES EN SI EL INICIAL --> en i_subestado tengo la posicion que soy: es decir si soy q0q2 primero tendre i_subestado = 0 y luego i_subestado = 2
          //con lo cual aqui ya tenemos la informacion necesaria y suficiente: - tenemos el indice del simbolo: i_simbolo
          //                                                                   - tenemos el indice de cada subestado i_subestado --> origen
          //                                                                   - tenemos el indice de los destinos --> i_cada_estado_AFND --> destino
          //ahora tengo que mirar para cada estado del AFND si hay transicion --> la funcion me devuelve 1 si la hay
          for (i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND ++) {
            if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i_subestado, i_simbolo, i_cada_estado_AFND) == 1) {
              //es decir, si existe transicion --> tenemos que ponerlo de alguna manera

              // ESTO QUE PONGO AQUI DEBAJO HAY QUE HACERLO YA?
              //esta lista podria ser la codificacion del nuevo estado?
              //tenemos que concatenar el nombre?
              //Hay otra manera mas sencilla de hacerlo?
              strcpy(nombre_nuevo_estado, "");
              strcpy(str, "");
              strcat(nombre_nuevo_estado, "q");
              sprintf(str, "%d", i_cada_estado_AFND);
              strcat(nombre_nuevo_estado, str);
              nuevo_estado[i_cada_estado_AFND] = 1; // lo marcamos así?
              if(AFNDTipoEstadoEn(afnd, i_cada_estado_AFND) == FINAL || AFNDTipoEstadoEn(afnd, i_cada_estado_AFND) == INICIAL_Y_FINAL){
                flag_estado_final = 2;
              }
            }
          }

          //MIRAR TRANSICIONES LAMBDAS

          //EN TEORIA YA TENEMOS EL NUEVO ESTADO CREADO, ES DECIR, TENEMOS UNA NUEVA ESTRUCTURA INTERMEDIA QUE TENEMOS QUE AÑADIR A CREADOS NO ?
          //PRIMERO TENEMOS QUE COMPROBAR SI YA ESTA EN CREADOS O NO. SI NO ESTA LO METEMOS --> podemos directamente ni crearlo
          check = is_estado_in(nuevo_estado, creados);
          if (check == 0) { //igual todo lo que hacemos aqui podemos juntarlo en una funcion para que sea mas corta
            //es decir si no esta creado --> lo creamos y lo añadimos
            trans_nuevo_estado = crear_transicion(num_estados, simbolo, nombre_nuevo_estado, nuevo_estado);
            if (flag_estado_final == 2){
              tipo_estado_nuevo = FINAL;
            } else {
              tipo_estado_nuevo = NORMAL;
            }
            inter_nuevo_estado = crear_intermedia(nombre_nuevo_estado, num_estados, i, nuevo_estado); //le he pasado i por pasarle algo porque no se si es necesario el tipo

            creados[i]->transiciones[cont_transiciones] = trans_nuevo_estado;
            cont_transiciones++;
            creados[i+1] = inter_nuevo_estado; //recordamos que en contador es el contador de por donde vamos en la lista de creados

            eliminar_intermedia(inter_nuevo_estado);
            eliminar_transicion(trans_nuevo_estado);
          }
          // QUEDAN COMPROBAR LAS TRANSICIONES LAMBDA. DONDE SE HACE ? creo que aqui --> aqui no porque antes estamos creando el estado, con lo cual
          // definitivamente aqui no es




          //una vez que ya la hemos añadido a la lista de creados se supone que tenemos que añadir en el que estamos a expandidos --> no se muy bien para que queremos expandidos
          // expandidos[contador_expandidos] = estado_actual;
          // contador_expandidos++;
          //cuando ya la tenemos en expandidos pasa a comprobar el siguiente que hay en creados


        if (AFNDLTransicionIJ(afnd,i_subestado, i_cada_estado_AFND) == 1) {
          //es decir si existe una transicion lambda desde i_subestado a i_cada_estado_AFND
          //tenemos que añadir al nuevo nombre i_cada_estado_AFND y poner en nuevo_estado[i_cada_estado_AFND] a 1
          //despues de esto ya podemos comprobar si esta en creados y si no esta lo creamos
        }



        }
      }
    }
    i++;
    for (k=0; k<num_estados; k++){
      nuevo_estado[k] = 0;
    }
  } //fin del primer while grande

  //Creamos el autómata determinista para poder dibujarlo
  contador = i+1;
  determinista = AFNDNuevo("afd", contador, num_simbolos);

  // Insertamos los símbolos en el nuevo autómata
  for (i=0; i<num_simbolos; i++){
    AFNDInsertaSimbolo(determinista, AFNDSimboloEn(afnd, i));
  }

  //Insetamos los estados
  for (i=0; i<contador; i++){
    AFNDInsertaEstado(determinista, creados[i]->nombre_estado, creados[i]->tipo);
  }

  // Insertamos las transiciones
  // AFNDInsertaTransicion(p_afnd, "q0", "+", "q1");
  for (i=0; i<contador; i++){
    k = 0;
    while(creados[i]->transiciones[k]){
      AFNDInsertaTransicion(determinista,
                            creados[i]->nombre_estado,
                            creados[i]->transiciones[k]->simbolo,
                            creados[i]->transiciones[k]->estado_final);

      k++;
    }
  }

  return determinista;

}
