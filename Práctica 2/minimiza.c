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

void estadosAccesibles(AFND* afnd){
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
