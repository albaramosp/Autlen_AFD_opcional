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
  for (i = 0; i < 4; i++){
    printEstado(&(a->estados[i]));
  }

  printf("Automata con estas transiciones: ");
  for (i = 0; i < 7; i++){
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

Automata * crearAutomata( Estado *estados, char *simbolos,  Transicion *transiciones, Estado *estadoInicial){
  Automata *a = (Automata *)malloc(sizeof (Automata));

  a->estados = estados;
  a->estadoActual = estadoInicial;
  a->transiciones = transiciones;
  a->simbolos = simbolos;

  return a;
}

int transitar (Automata *a, char simbolo){
  int i;
  int transita = 0;

  for (i = 0; i < 8; i++){
    Transicion *t = &(a->transiciones[i]);

    if (t->q1 == a->estadoActual && t->simbolo == simbolo){
      if (t->q1->tipo != 2 && t->q2->tipo == 2){
        printf("\n              __");
        printf("\n  %s --%c-->  |%s|", t->q1->nombre, simbolo, t->q2->nombre);
        printf("\n             |__|");
      }else if (t->q1->tipo == 2 && t->q2->tipo == 2){
        printf("\n  __          __");
        printf("\n |%s| --%c--> |%s|", t->q1->nombre, simbolo, t->q2->nombre);
        printf("\n |__|        |__|");
      }else if (t->q1->tipo == 2 && t->q2->tipo != 2){
        printf("\n__          ");
        printf("\n |%s| --%c--> %s", t->q1->nombre, simbolo, t->q2->nombre);
        printf("\n  |__|          ");
      } else {
          printf("\n%s --%c--> %s", t->q1->nombre, simbolo, t->q2->nombre);
      }

      a->estadoActual = t->q2;
      transita = 1;
      break;
    }
  }

  return transita;
}

int parsea ( Automata *a, char *cadena){
  int i = 0;

  for (i = 0; i < strlen(cadena); i++){
    if (transitar(a, cadena[i]) == 0){
      printf("\nEl AFD se para");
      return 0;
    }
  }

  for (i = 0; i < 2; i++){
    if (a->estadoActual->tipo == 2){
      return 1;
    }
  }
  
  return 0;
}

int main( ) {
   Estado estados[N_ESTADOS];
   Transicion transiciones[N_TRANS];
   Automata *a;
   char input[10];

  asignaEstado(&estados[0], 0, "q0");
  asignaEstado(&estados[1], 2, "q1");
  asignaEstado(&estados[2], 2, "q2");
  asignaEstado(&estados[3], 1, "q3");

  asignaTransicion(&transiciones[0], &estados[0], &estados[3], 'a');
  asignaTransicion(&transiciones[1], &estados[3], &estados[3], 'a');
  asignaTransicion(&transiciones[2], &estados[3], &estados[3], 'b');
  asignaTransicion(&transiciones[3], &estados[0], &estados[1], 'b');
  asignaTransicion(&transiciones[4], &estados[2], &estados[1], 'b');
  asignaTransicion(&transiciones[5], &estados[1], &estados[2], 'a');
  asignaTransicion(&transiciones[6], &estados[1], &estados[1], 'b');
  asignaTransicion(&transiciones[7], &estados[2], &estados[2], 'a');

  a = crearAutomata(estados, "ab*", transiciones, &estados[0]); //reconoce ab*a

  printf("\nIntroducir cadena de entrada a analizar por el AFD: ");
  scanf("%s", input);

  if (parsea(a, input) == 1){
    printf("\nAcepta cadena %s\n", input);
  } else {
    printf("\nNo acepta cadena %s\n", input);
  }

  return 0;
}
