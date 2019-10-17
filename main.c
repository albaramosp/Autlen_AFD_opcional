#include "main.h"

int contEstados = 0;
int contTrans = 0;

void printEstado(Estado q){
  if (q.tipo == INICIAL){
    printf("\n\tEstado %s de tipo inicial\n", q.nombre);
  } else if (q.tipo == FINAL){
    printf("\n\tEstado %s de tipo final\n", q.nombre);
  } else if (q.tipo == INICIALFINAL){
    printf("\n\tEstado %s de tipo inicial y final\n", q.nombre);
  } else {
    printf("\n\tEstado %s de tipo normal\n", q.nombre);
  }
}

void printTransicion( Transicion t){
  printf("\n\tTransicion de %s a %s mediante simbolo %c\n", t.q1->nombre, t.q2->nombre, t.simbolo);
}

void printAutomata(Automata *a){
  int i;

  printf("Automata con estos estados: ");
  for (i = 0; i < a->nestados; i++){
    printEstado(a->estados[i]);
  }

  printf("Automata con estas transiciones: ");
  for (i = 0; i < a->ntransiciones; i++){
    printTransicion(a->transiciones[i]);
  }
}
/*
void asignaEstado1(Estado *q, int tipo, char *nombre){
  q->tipo = tipo;
  strcpy( q->nombre, nombre);
}
*/

void asignaEstado2(Automata *a, char *nombre, Tipo tipo){
  Estado *e = (Estado *)malloc(sizeof(Estado));
  strcpy(e->nombre, nombre);
  e->tipo = tipo;

  a->estados[contEstados] = *e;
  if (e->tipo == INICIAL || e->tipo == INICIALFINAL){
    a->estadoActual = e;
  }


  contEstados++;
}
/*
void asignaTransicion1(Transicion *t, Estado *q1, Estado *q2, char simbolo){
  t->q1 = q1;
  t->q2 = q2;
  t->simbolo = simbolo;
}
*/

void asignaAlfabeto(Automata *a, char *alfabeto){
  strcpy(a->simbolos, alfabeto);
}

void asignaTransicion2(Automata *a, char *q1, char simbolo, char *q2){
  Transicion t;
  Estado *e1;
  Estado *e2;
  int j;

  for (j = 0; j < a->nestados; j++){
    if (strcmp(a->estados[j].nombre, q1) == 0){
      e1 = &(a->estados[j]);
    }
  }

  for (j = 0; j < a->nestados; j++){
    if (strcmp(a->estados[j].nombre, q2) == 0){
      e2 = &(a->estados[j]);
    }
  }

  t.q1 = e1;
  t.q2 = e2;
  t.simbolo = simbolo;

  a->transiciones[contTrans] = t;
  contTrans++;
}

/*
Automata * crearAutomata1( Estado *estados, int nestados, char *simbolos,  Transicion *transiciones, int ntransiciones, Estado *estadoInicial){
  Automata *a = (Automata *)malloc(sizeof (Automata));

  a->estados = estados;
  a->nestados = nestados;
  a->estadoActual = estadoInicial;
  a->transiciones = transiciones;
  a->ntransiciones = ntransiciones;
  a->simbolos = simbolos;

  return a;
}
*/

void liberaAutomata2(Automata *a){
  free(a->estados);
  free(a->transiciones);
  free(a);
}

Automata * crearAutomata2(int nestados, int ntransiciones){
  Automata *a = (Automata *)malloc(sizeof (Automata));

  a->nestados = nestados;
  a->estados = (Estado *)malloc(nestados * sizeof(Estado));
  a->ntransiciones = ntransiciones;
  a->transiciones = (Transicion *)malloc(ntransiciones * sizeof(Transicion));

  contTrans = 0;
  contEstados = 0;

  return a;
}

int transitar (Automata *a, char simbolo){
  int i;
  int transita = 0;

  for (i = 0; i < a->ntransiciones; i++){
    Transicion *t = &(a->transiciones[i]);

    if (strcmp(t->q1->nombre, a->estadoActual->nombre) == 0 && t->simbolo == simbolo){
      if (t->q1->tipo != FINAL && t->q2->tipo == FINAL){
        printf("\n              __");
        printf("\n  %s --%c-->  |%s|", t->q1->nombre, simbolo, t->q2->nombre);
        printf("\n             |__|");
      }else if (t->q1->tipo == FINAL && t->q2->tipo == FINAL){
        printf("\n  __          __");
        printf("\n |%s| --%c--> |%s|", t->q1->nombre, simbolo, t->q2->nombre);
        printf("\n |__|        |__|");
      }else if (t->q1->tipo == FINAL && t->q2->tipo != FINAL){
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

/*
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
*/

int parsea ( Automata *a, char *cadena){
  int i = 0;

  for (i = 0; i < strlen(cadena); i++){
    if (transitar(a, cadena[i]) == 0){
      printf("\nEl AFD se para");
      return 0;
    }
  }

  for (i = 0; i < 2; i++){
    if (a->estadoActual->tipo == FINAL || a->estadoActual->tipo == INICIALFINAL){
      return 1;
    }
  }

  return 0;
}

int main(int argc, char *argv[]) {
   Estado *estados;
   Transicion *transiciones;
   Automata *a;
   char input[10];
   int nestados;
   int ntransiciones;
   char *alfabeto = (char *)malloc(20 * sizeof(char));
   int i;

   nestados = 3;
   estados = (Estado *)malloc(nestados * sizeof(Estado));

   ntransiciones = 3;
   estados = (Estado *)malloc(nestados * sizeof(Estado));

   strcpy(alfabeto, "abc");

   a = crearAutomata2(nestados, ntransiciones);

   asignaEstado2(a, "q0", INICIALFINAL);
   asignaEstado2(a, "q1", NORMAL);
   asignaEstado2(a, "q2", NORMAL);

   asignaTransicion2(a, "q0", 'a', "q1");
   asignaTransicion2(a, "q1", 'b', "q2");
   asignaTransicion2(a, "q2", 'c', "q0");

   //printAutomata(a);

   strcpy(input, "abc");

   if (parsea(a, input) == 1){
     printf("\nAcepta cadena %s\n", input);
   } else {
     printf("\nNo acepta cadena %s\n", input);
   }

   liberaAutomata2(a);

/*
   asignaEstado(&estados[0], INICIALFINAL, "q0");
   asignaEstado(&estados[1], NORMAL, "q1");
   asignaEstado(&estados[2], NORMAL, "q2");


   asignaTransicion(&transiciones[0], &estados[0], &estados[3], 'a');
   asignaTransicion(&transiciones[1], &estados[3], &estados[3], 'a');
   asignaTransicion(&transiciones[2], &estados[3], &estados[3], 'b');
   asignaTransicion(&transiciones[3], &estados[0], &estados[1], 'b');
   asignaTransicion(&transiciones[4], &estados[2], &estados[1], 'b');
   asignaTransicion(&transiciones[5], &estados[1], &estados[2], 'a');
   asignaTransicion(&transiciones[6], &estados[1], &estados[1], 'b');
   asignaTransicion(&transiciones[7], &estados[2], &estados[2], 'a');
*/
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


/*

  */

  //a = crearAutomata(estados, nestados, alfabeto, transiciones, 0, &estados[0]); //reconoce ab*a


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
