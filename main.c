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
  printf("\n\tTransicion de %s a %s mediante simbolo %c\n", t.q1.nombre, t.q2.nombre, t.simbolo);
}

void printAutomata(Automata *a){
  int i;

  printf("\nAutomata con estos estados: ");
  for (i = 0; i < a->nestados; i++){
    printEstado(a->estados[i]);
  }

  printf("\nAutomata con estas transiciones: ");
  for (i = 0; i < a->ntransiciones; i++){
    printTransicion(a->transiciones[i]);
  }

  printf("\nAutomata con alfabeto: ");
  for (i = 0; i < strlen(a->alfabeto); i++){
    printf("%c ", a->alfabeto[i]);
  }

  printf("\n\n");
}

void asignaEstado(Automata *a, char *nombre, Tipo tipo){
  Estado e;

  strcpy(e.nombre, nombre);
  e.tipo = tipo;

  a->estados[contEstados] = e;
  if (e.tipo == INICIAL || e.tipo == INICIALFINAL){
    a->estadoActual = e;
  }


  contEstados++;
}

void asignaAlfabeto(Automata *a, char *alfabeto){
  strcpy(a->alfabeto, alfabeto);
}

void asignaTransicion(Automata *a, char *q1, char simbolo, char *q2){
  Transicion t;
  Estado e1;
  Estado e2;
  int j;

  for (j = 0; j < a->nestados; j++){
    if (strcmp(a->estados[j].nombre, q1) == 0){
      e1 = a->estados[j];
    }
  }

  for (j = 0; j < a->nestados; j++){
    if (strcmp(a->estados[j].nombre, q2) == 0){
      e2 = a->estados[j];
    }
  }

  t.q1 = e1;
  t.q2 = e2;
  t.simbolo = simbolo;

  a->transiciones[contTrans] = t;
  contTrans++;
}

void liberaAutomata(Automata *a){
  free(a->estados);
  free(a->transiciones);
  free(a->alfabeto);
  free(a);
}

Automata * crearAutomata(int nestados, int ntransiciones, int nsimbolos){
  Automata *a = (Automata *)malloc(sizeof (Automata));

  a->nestados = nestados;
  a->estados = (Estado *)malloc(nestados * sizeof(Estado));

  a->ntransiciones = ntransiciones;
  a->transiciones = (Transicion *)malloc(ntransiciones * sizeof(Transicion));

  a->alfabeto = (char *)malloc(nsimbolos * sizeof(char));

  contTrans = 0;
  contEstados = 0;

  return a;
}

int transitar (Automata *a, char simbolo){
  int i;
  int transita = 0;

  for (i = 0; i < a->ntransiciones; i++){
    Transicion *t = &(a->transiciones[i]);

    if (strcmp(t->q1.nombre, a->estadoActual.nombre) == 0 && t->simbolo == simbolo){
      printf("\n%s --%c--> %s", t->q1.nombre, simbolo, t->q2.nombre);
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
    if (a->estadoActual.tipo == FINAL || a->estadoActual.tipo == INICIALFINAL){
      return 1;
    }
  }

  return 0;
}

int main(int argc, char *argv[]) {
   Estado *estados;
   Transicion *transiciones;

   int nestados, ntransiciones, nsimbolos;

   Automata *a;

   char input[10];
   int i;

   nestados = 3;
   ntransiciones = 3;
   nsimbolos = 3;

   a = crearAutomata(nestados, ntransiciones, nsimbolos);

   asignaAlfabeto(a, "abc");

   asignaEstado(a, "q0", INICIALFINAL);
   asignaEstado(a, "q1", NORMAL);
   asignaEstado(a, "q2", NORMAL);

   asignaTransicion(a, "q0", 'a', "q1");
   asignaTransicion(a, "q1", 'b', "q2");
   asignaTransicion(a, "q2", 'c', "q0");

   printAutomata(a);

   strcpy(input, "abc");

   if (parsea(a, input) == 1){
     printf("\nAcepta cadena %s\n", input);
   } else {
     printf("\nNo acepta cadena %s\n", input);
   }

   liberaAutomata(a);


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

  return 0;
}
