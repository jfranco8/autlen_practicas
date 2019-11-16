#include "transforma.h"

typedef struct{
  char simbolo[MAX_NOMBRE]; //es el simbolo con el que puedo ir al estado final
  char estado_final[MAX_NOMBRE];
  int *t_codificacion; //esto es una lista [1,1,0,0,0,0,1,0]
}Transicion;

typedef struct{
  char nombre_estado[MAX_NOMBRE];
  int *i_codificacion; //esto es una lista [1,1,0,0,0,0,1,0]
  int tipo; //tipo que va a ser: final, inicial, etc
  Transicion transiciones[MAX_TRANSICIONES]; //no se es necesario hacerlo dinamico, con lo cual lo hemos hecho estatico
}Intermedia;


/*
* Funcion que crea una transicion
*
*
*/
Transicion *crear_transicion(int num_estados, char* simbolo, char* final) {
  Transicion *transicion = NULL;
  int i;

  strcpy(transicion->simbolo, simbolo);
  strpcy(transicion->estado_final,final);

  //ESTO NO SE MUY BIEN SI ES ASI PORQUE IGUAL LO QUE TENGO QUE HACER ES PASARLE LA LISTA ENETERA NO ???? 
  // ********* DUDA ************** PERO SI YA LA TENGO EN INTERMEDIA PARA QUE LA QUIERO AQUI ???? --> no me acuerdo para que era 
  transicion->t_codificacion = (int*)malloc(sizeof(int)*num_estados);
  for (i = 0; i < num_estados; i++) {
    transicion->t_codificacion[i] = 0;
  }

  //ya esta todo inicializado
  return transicion;
}

/*
* Funcion que elimina una transicion
*
*/

void eliminar_transicion(Transicion *transicion) {

  free(transicion->t_codificacion);
  free(transicion);

}


/*
* Funcion que crea una estructura intermedia
*
*
*/
Intermedia *crear_intermedia(char* nombre, int num_estados, int tipo) {
  Intermedia *intermedia = NULL;
  int i;

  intermedia = (Intermedia *)malloc(sizeof(Intermedia));
  if (!intermedia) {
    print("Error al reservar memoria en intermedia\n");
    return NULL;
  }

  intermedia->tipo = tipo;

  intermedia->i_codificacion = (int*)malloc(sizeof(int)*num_estados);

  //hay que inicializarla toda a 0
  for (i = 0; i< num_estados; i++) {
    intermedia->i_codificacion[i] = 0;
  }

  //transiciones es un estatico con lo cual demomento no tenemos que inicializarlo
  //ya esta todo inicializado
  return intermedia;
}

/*
* Funcion que elimina una estructura intermedia
*
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
    
    
    */


   /* En creados añadimos el estado inicial
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

    */


   /* !!!!!! DUDAS !!!!!!!
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

// Funcion que me comprueba si algo esta en creados o no
// HAY QUE TERMINARLA. NO LA HE HECHO PORQUE NO SABIA TODAVIA SI ERA NECESARIA
// Devuelve 1 si ya esta en creados. 0 Si no lo esta
int comprobar_creados(int *codificacion, Intermedia *creados) {
  int i;

  for (i = 0; i < /*no se con que comparar*/; i++) {
    creados[i] // esto es lo que tenemos. Ahora queremos ver si su codificacion es igual
  }
}

AFND* AFNDTransforma(AFND* afnd){

  // TENGO UN LIO CON LOS PUNTEROS DE LAS COSAS ESTAS
  // le he puesto MAX NOMBRE PARA QUE NO ME DIERA ERROR PORQUE SI NO AL HACER creados[contador] = inicial; ME DA ERROR AL ASIGNAR VARIABLES
  Intermedia *creados[MAX_NOMBRE] = NULL, *inicial, *estado_actual; //creo que aqui vamos a guardar todos los estados que vayan saliendiendo en el afnd
  int num_estados, num_simbolos;
  Intermedia *expandidos = NULL; //la creo aunque demomento no etiendo para que la quiero
  int pos_inicial;
  char* nombre_inicial, *simbolo;

  //i_simbolo me sirve para saber porque simbolo voy 
  //i me sirve para contar por el estado que voy en la lista creados
  //i_cada_estado_AFND me sirve para comprobar los estados destino en las transiciones
  int i,i_simbolo,i_subestado, contador = 0, i_cada_estado_AFND; 
  //obtenemos datos del automata original
  num_estados = AFNDNumEstados(afnd);
  num_simbolos = AFNDNumSimbolos(afnd);

  //obtenemos el estado inicial. 
  //Lo que recibimos es la posicion del estado inicial
  pos_inicial = AFNDIndiceEstadoInicial(afnd);

  //tenemos que crear la estructura intermedia para el estado incial
  //obtenemos el nombre del estado incial
  nombre_inicial = AFNDNombreEstadoEn(afnd, pos_inicial);

  //como soy el inicial y se que posicion tengo tendre que decirle a la i_codificacion que soy el [1,0,0,0,0]
  inicial = crear_intermedia(nombre_inicial, num_estados, pos_inicial); //a esta funcion se le pasa el tipo pero no se si es necesario --> LE HE PASADO POS_INICIAL PARA QUE NP ME SALGA ERROR TODO EL RATO PERO HAY QUE CAMBIARLO
  //lo hago aqui cuando ya he creado la estructura intermedia
  inicial->i_codificacion[pos_inicial] = 1;
  
  creados[contador] = inicial;
  contador ++;

  //para cada estado que tenemos en creados: ---> !! he comparado i < num_estados porque es lo unico que me cuadra pero igual lo que tneemos
  // que hacer es para cada estado del afnd ??? no se nuestro algoritmo no es asi pero ESTO HAY QUE OENSARLO
  for (i = contador-1; i < num_estados; i++){
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
          //                                                                   - tenemos el indice de los destinos --> destino
          //ahora tengo que mirar para cada estado del AFND si hay transicion --> la funcion me devuelve 1 si la hay 
          for (i_cada_estado_AFND = 0; i_cada_estado_AFND < num_estados; i_cada_estado_AFND ++) {
            if (AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i_subestado, i_simbolo, i_cada_estado_AFND) == 1) {
              //es decir, si existe transicion --> tenemos que ponerlo de alguna manera

              // ESTO QUE PONGO AQUI DEBAJO HAY QUE HACERLO YA?
              //esta lista podria ser la codificacion del nuevo estado?
              //tenemos que concatenar el nombre?
              //Hay otra manera mas sencilla de hacerlo?
              int* nuevo_estado;
              char nombre_nuevo_estado[MAX_NOMBRE];
              char str[MAX_NOMBRE]; //este sirve para pasar el nombre de cada subestado a cadena de caracteres y luego concatenar para poder hacer q0q1
              strcat(nombre_nuevo_estado, "q");
              sprintf(str, "%d", i_cada_estado_AFND);
              strcat(nombre_nuevo_estado, str);
              nuevo_estado[i_cada_estado_AFND] = 1; // lo marcamos así?

              //EN TEORIA YA TENEMOS EL NUEVO ESTADO CREADO, ES DECIR, TENEMOS UNA NUEVA ESTRUCTURA INTERMEDIA QUE TENEMOS QUE AÑADIR A CREADOS NO ?
              //PRIMERO TENEMOS QUE COMPROBAR SI YA ESTA EN CREADOS O NO. SI NO ESTA LO METEMOS --> podemos directamente ni crearlo
              int check = comprobar_creados(nuevo_estado, creados);
              if (check == 0) {
                //es decir si no esta creado --> lo creamos y lo añadimos
                Transicion *trans_nuevo_estado = crear_transicion(num_estados, simbolo, nombre_nuevo_estado);
                Intermedia *inter_nuevo_estado = crear_intermedia(nombre_nuevo_estado, num_estados, i); //le he pasado i por pasarle algo porque no se si es necesario el tipo
                

                creados[contador] =  //recordamos que en contador es el contador de por donde vamos en la lista de creados
              }
            }
          }
        }
      }
    }
  }
}