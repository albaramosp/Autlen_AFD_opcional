#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum tipo {INICIAL, NORMAL, FINAL, INICIALFINAL} Tipo;

typedef struct {
  char  nombre[50];
  Tipo   tipo;
} Estado;

typedef struct  {
  Estado  q1;
  Estado  q2;
  char     simbolo;
} Transicion;

typedef struct {
  Estado     *estados;
  Estado     estadoActual;
  char       *alfabeto;
  Transicion *transiciones;
  int nestados;
  int ntransiciones;
} Automata;

int transitar (Automata *a, char simbolo);
int parsea ( Automata *a, char *cadena);
int parseoCorrecto ( Automata *a, char **cadena);
int parseoMal ( Automata *a, char **cadena);

void printEstado( Estado q);
void printTransicion( Transicion t);
void printAutomata(Automata *a);

void asignaEstado(Automata *a, char *nombre, Tipo tipo);
void asignaTransicion(Automata *a, char *q1, char simbolo, char *q2);

Automata * crearAutomata(int nestados, int ntransiciones, int nsimbolos);
