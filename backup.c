#include "main.h"

void printEstado( Estado *q){
  if (q->tipo == 0){
    printf("\n\tEstado %s de tipo inicial\n", q->nombre);
  } else if (q->tipo == 1){
    printf("\n\tEstado %s de tipo normal\n", q->nombre);
  } else {
    printf("\n\tEstado %s de tipo final\n", q->nombre);
  }
}

void printTransicion( Transicion *t){
  printf("\n\tTransicion de %s a %s mediante simbolo %c\n", t->q1->nombre, t  ->q2->nombre, t->simbolo);
}

void printAutomata(Automata *a){
  int i;

  printf("Automata con estos estados: ");
  for (i = 0; i < 3; i++){
    printEstado(&(a->estados[i]));
  }

  printf("Automata con estas transiciones: ");
  for (i = 0; i < 3; i++){
    printTransicion(&(a->transiciones[i]));
  }
}

void asignaEstado(Estado *q, int tipo, char *nombre){
  q->tipo = tipo;
  strcpy( q->nombre, nombre);
}

void asignaTransicion(Transicion *t, Estado *q1, Estado *q2, char simbolo){
  t->q1 = q1;
  t->q2 = q2;
  t->simbolo = simbolo;
}

Automata * crearAutomata( Estado *estados, char *simbolos,  Transicion *transiciones, Estado *estadoInicial, Estado *eFinal){
  Automata *a = (Automata *)malloc(sizeof (Automata));

  a->estados = estados;
  a->estadoActual = estadoInicial;
  a->estadoFinal = eFinal;
  a->transiciones = transiciones;
  a->simbolos = simbolos;

  return a;
}

int transitar (Automata *a, char simbolo){
  printf("\nEntrando a transitar");
  int i;
  int transita = 0;

  for (i = 0; i < 3; i++){
    Transicion *t = &(a->transiciones[i]);
    printf("\nAnalizando transicion de simbolo %c", t->simbolo);

    if (t->q1 == a->estadoActual && t->simbolo == simbolo){
      printf("\nTransita a %s con el simbolo %c", t->q2->nombre, simbolo);
      a->estadoActual = t->q2;
      transita = 1;
      break;
    }
  }

  printf("\n\tTransita vale: %d", transita);
  return transita;
}

//a, aa, aaa..., aba, abba, abbb...a si
//b, bb, bab no
int parsea ( Automata *a, char *cadena){
  int i = 0;
  int j = 0;

  for (i = 0; i < strlen(cadena); i++){
    if (transitar(a, cadena[i]) == 0){
      return 0;
    }
  }

  if (a->estadoActual == a->estadoFinal){
    return 1;
  }

  return 0;
}

int main( ) {
   Estado *q0, *q1, *qf;
   Estado estados[3];
   Transicion *t1, *t2, *t3;
   Transicion transiciones[3];
   Automata *a;

  t1 = (Transicion *)malloc (sizeof (Transicion));
  t2 = (Transicion *)malloc (sizeof (Transicion));
  t3 = (Transicion *)malloc (sizeof (Transicion));

  q0 = (Estado *)malloc (sizeof (Estado));
  q1 = (Estado *)malloc (sizeof (Estado));
  qf = (Estado *)malloc (sizeof (Estado));

  asignaEstado(q0, 0, "q0");
  asignaEstado(q1, 1, "q1");
  asignaEstado(qf, 2, "qf");

  estados[0] = *q0;
  estados[1] = *q1;
  estados[2] = *qf;

  asignaTransicion(t1, q0, q1, 'a');
  asignaTransicion(t2, q1, q1, 'b');
  asignaTransicion(t3, q1, qf, 'a');

  transiciones[0] = *t1;
  transiciones[1] = *t2;
  transiciones[2] = *t3;

  a = crearAutomata(estados, "ab*", transiciones, q0, qf); //reconoce ab*a

  printAutomata(a);

  char cadena[] = "bbbbba";

  if (parsea(a, cadena) == 1){
    printf("\nAcepta cadena %s\n", cadena);
  } else {
    printf("\nNo acepta cadena %s\n", cadena);
  }

  return 0;
}
