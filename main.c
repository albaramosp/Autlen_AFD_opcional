#include "main.h"

void printEstado( Estado *q){
  if (q->tipo == 0){
    printf("\n\tEstado %s de tipo inicial\n", q->nombre);
  } else if (q->tipo == 1){
    printf("\n\tEstado %s de tipo final\n", q->nombre);
  } else {
    printf("\n\tEstado %s de tipo normal\n", q->nombre);
  }
}

void printTransicion( Transicion *t){
  printf("\n\tTransicion de %s a %s mediante simbolo %c\n", t->q1->nombre, t  ->q2->nombre, t->simbolo);
}

void printAutomata(Automata *a){
  int i;

  printf("Automata con estos estados: ");
  for (i = 0; i < a->nestados; i++){
    printEstado(&(a->estados[i]));
  }

  printf("Automata con estas transiciones: ");
  for (i = 0; i < a->ntransiciones; i++){
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

Automata * crearAutomata( Estado *estados, int nestados, char *simbolos,  Transicion *transiciones, int ntransiciones, Estado *estadoInicial){
  Automata *a = (Automata *)malloc(sizeof (Automata));

  a->estados = estados;
  a->nestados = nestados;
  a->estadoActual = estadoInicial;
  a->transiciones = transiciones;
  a->ntransiciones = ntransiciones;
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

int main(int argc, char *argv[]) {
   Estado *estados;
   Transicion transiciones[N_TRANS];
   Automata *a;
   char input[10];
   int nestados;
   char *alfabeto = (char *)malloc(20 * sizeof(char));
   int i;

   if (argc != 2){
     return -1;
   }

   nestados = atoi(argv[1]);
   estados = (Estado *)malloc(nestados * sizeof(Estado));

   printf("\nIntroduce el alfabeto como una sola cadena: ");
   scanf("%s", alfabeto);

   for (i = 0; i < nestados; i++){
     int tipo;
     char *nombre;
     printf("\nIntroduce el estado %d (nombre tipo -0 para inicial, 1 para final, 2 para normal-): ", i+1);
     scanf("%s %d", nombre, &tipo);
     asignaEstado(&estados[i], tipo, nombre);
   }

   /*
  AFD * a = creaAFD (4, //Num estados
                     2  //Num simbolos
                    )
   asignaEstado(a, "q0", INICIAL);
   asignaEstado(a, "q1", INICIAL);

   AFD * a2 = creaAFD (6, //Num estados
                      5  //Num simbolos
                     )
    asignaEstado(a, "q0", INICIAL);
    asignaEstado(a, "q1", INICIAL);
    asignaTrans(a, "q0", "a", "q1")
    asignaTrans(a, "q0", "a", "q1")

    AFD * a3 = creaAFD ({
                          {"q0", INICIAL},
                          {"q1", NORMAL}
                        }, //Num estados
                       {"ab"}  //Num simbolos
                      )

                      */

   for (i = 0; i < ntransiciones; i++){
     Estado *q1;
     Estado *q2;
     char simbolo;
     printf("\nIntroduce la transicion %d (Qini Qfin): ", i+1);
     scanf("%s %d", nombre, &tipo);
     asignaEstado(&estados[i], tipo, nombre);
   }

/*
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
  */

  a = crearAutomata(estados, nestados, alfabeto, transiciones, 0, &estados[0]); //reconoce ab*a
  printAutomata(a);

/*
  printf("\nIntroducir cadena de entrada a analizar por el AFD: ");
  scanf("%s", input);

  if (parsea(a, input) == 1){
    printf("\nAcepta cadena %s\n", input);
  } else {
    printf("\nNo acepta cadena %s\n", input);
  }
  */

  return 0;
}
