#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N_ESTADOS 4
#define N_TRANS 8

typedef enum tipo {INICIAL, NORMAL, FINAL, INICIALFINAL} Tipo;

typedef struct {
  char  nombre[50];
  Tipo   tipo;
} Estado;

typedef struct  {
  Estado  *q1;
  Estado  *q2;
  char     simbolo;
} Transicion;

typedef struct {
  Estado     *estados;
  int nestados;
  Estado     *estadoActual;
  char       *simbolos;
  Transicion *transiciones;
  int ntransiciones;
} Automata;

/*
typedef struct {
  Estado     *estados;
  int nestados;
  Estado     **estadoActual;
  char       *simbolos;
  Transicion **transiciones;
  int ntransiciones;
} Automata;
*/

int transitar (Automata *a, char simbolo);
int parsea ( Automata *a, char *cadena);
int parseoCorrecto ( Automata *a, char **cadena);
int parseoMal ( Automata *a, char **cadena);

void printEstado( Estado q);
void printTransicion( Transicion t);
void printAutomata(Automata *a);

void asignaEstado(Estado *q, int tipo, char *nombre);
void asignaTransicion(Transicion *t, Estado *q1, Estado *q2, char simbolo);

Automata * crearAutomata( Estado *estados, int nestados, char *simbolos,  Transicion *transiciones, int ntransiciones, Estado *estadoInicial);
