#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char ** argv){
  char ***tabla = NULL;
  char **aux = NULL;
  char chr, aux_char[1];
  int i, j, k;
  int count_lines = 0;
  int num_simbolos;
  int max_linea;
  int num_estados;
  int ini, fin;
  char* alfabeto = NULL;
  int estado_actual, estado_final;

  if(argc!=2){
    return -1;
  }

  char *entrada = NULL;
  //printf("%ld", strlen(argv[1]));
  entrada = (char *)malloc(strlen(argv[1])*sizeof(char));
  strcpy(entrada, argv[1]);

  FILE *automata = fopen("automata_descr.txt", "r");
  if(automata == NULL){
    printf("Autómata NO descrito\n");
    return -1;
  }

  //Cargar la tabla del Autómata
  chr = getc(automata);
    while (chr != EOF)
    {
        //Count whenever new line is encountered
        if (chr == '\n')
        {
            count_lines = count_lines + 1;
        }
        //take next character from file.
        chr = getc(automata);
    }
  fclose(automata);
  automata = fopen("automata_descr.txt", "r");

  fgets(aux_char, 10, (FILE *)automata);
  num_simbolos = atoi(aux_char);
  max_linea=num_simbolos+2;
  printf("num_simbolos %d\n", num_simbolos);

  fgets(aux_char, 10, (FILE *)automata);
  num_estados = atoi(aux_char);
  printf("num_estados %d\n", num_estados);

  fgets(aux_char, 10, (FILE *)automata);
  ini = atoi(aux_char);
  printf("ini %d\n", ini);

  fgets(aux_char, 10, (FILE *)automata);
  fin = atoi(aux_char);
  printf("fin %d\n", fin);

  char *buffer = NULL;
  buffer = (char *)calloc(sizeof(char),max_linea);
  if(buffer == NULL){
    printf("Error al reservar memoria a buffer");
    return -1;
  }

  alfabeto = (char *)calloc(sizeof(char),num_simbolos);
  if(alfabeto == NULL){
    printf("Error al reservar memoria al alfabeto");
    return -1;
  }

  fgets(buffer, max_linea, (FILE *)automata);
  strcpy(alfabeto, buffer);

  printf("alfabeto: %s\n", alfabeto);

  tabla = (char***)malloc(sizeof(char**)*num_estados);
  for(i=0; i<num_estados; i++){
    tabla[i] = (char**)malloc(sizeof(char*)*num_estados);
    for(j=0; j<num_simbolos; j++){
      tabla[i][j] = (char*)malloc(sizeof(char)*num_simbolos);
    }
  }

  i=0;
  while(fgets(buffer, max_linea, (FILE *)automata)){
    printf("buffer lee %s\n", buffer);
    estado_actual = atoi(&buffer[0]);
    printf("estado actual %d\n", estado_actual);
    estado_final = atoi(&buffer[1]);
    printf("estado final %d\n", estado_final);
    i=2;
    j=0;
    while(buffer[i]){
      tabla[estado_actual][estado_final][j]=buffer[i];
      printf("%c\n", buffer[i]);
      i++;
      j++;
    }
  }

  //Comprobamos que la entrada esté determinada por  el autómata
  int estado = ini, *nuevo_estado = NULL;
  int l;
  nuevo_estado = (int*)malloc(sizeof(int)*num_estados);
  nuevo_estado[0]=estado;
  for(i=0; i<strlen(argv[1]);i++){
    printf("Leo %c \n", entrada[i]);
    for(l=0; l<num_estados;l++){}
      for(j=0; j<num_estados;j++){
        for(k=0; k<num_simbolos;k++){
          estado = nuevo_estado[l];
          if(tabla[estado][j][k]==entrada[i]){
            nuevo_estado[l]=j;
          }
        }
      }
      if(entrada[i+1] == '\0'){
        if(nuevo_estado[l]==fin){
          printf("Palabra aceptada\n");
          return 0;
        }
      }
    }


/*
  int estado = 0, nuevo_estado = 0;
  for(i=0; i<strlen(argv[1]); i++){
    printf("Leo %c \n", entrada[i]);
    for(j=0; j<num_estados; j++){
      for(k=0; k<)
      if(tabla[estado][j]==entrada[i]){
        nuevo_estado = j;
        break;
      }
    }
    estado = nuevo_estado;
    if(entrada[i+1] == '\0'){
      break;
    }
  }

  if(estado == 2){
    printf("Palabra aceptada\n");
    return 0;
  */
  printf("Palabra NO aceptada\n");
  return -1;
}
