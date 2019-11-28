/**
 * Autores: Sofia Sanchez y Jesus Daniel Franco
 * Fichero: prueba1.c
 *
 * Contiene las funciones
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "transforma.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;
	AFND * afd;

	p_afnd = AFNDNuevo("prueba1", 6, 2);

	AFNDInsertaSimbolo(p_afnd,"0");
	AFNDInsertaSimbolo(p_afnd,"1");

	AFNDInsertaEstado(p_afnd, "q0",INICIAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	AFNDInsertaEstado(p_afnd, "q3", FINAL);
	AFNDInsertaEstado(p_afnd, "q4", NORMAL);
	AFNDInsertaEstado(p_afnd, "q5", NORMAL);

	AFNDInsertaTransicion(p_afnd, "q0", "0", "q1");
	AFNDInsertaTransicion(p_afnd, "q0", "1", "q3");
	AFNDInsertaTransicion(p_afnd, "q1", "0", "q4");
	AFNDInsertaTransicion(p_afnd, "q2", "0", "q0");
	AFNDInsertaTransicion(p_afnd, "q2", "0", "q3");
	AFNDInsertaTransicion(p_afnd, "q2", "1", "q1");
	AFNDInsertaTransicion(p_afnd, "q3", "0", "q5");
	AFNDInsertaTransicion(p_afnd, "q5", "1", "q1");

	AFNDCierraLTransicion(p_afnd);

	/*afd  = AFNDTransforma(p_afnd);
	AFNDImprime(stdout,afd);
	AFNDADot(afd);*/
	AFNDADot(p_afnd);

	estadosAccesibles(p_afnd);

	AFNDElimina(p_afnd);

	return 0;
}
