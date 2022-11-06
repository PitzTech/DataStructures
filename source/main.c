#include "stdio.h"
#include "stdlib.h"

#include "stack.h"

int main() {
  printf("RODOU TUDO\n");

  GENERATE_STACK_TYPE(char);
  GENERATE_STACK_TYPE(int);

  stack(char) teste = Stack(char).new();
  Stack(char).push(&teste, 'c');
  printf("TOP: %c\n", Stack(char).top(&teste));
  Stack(char).push(&teste, 'd');
  printf("TOP: %c\n", Stack(char).top(&teste));
  Stack(char).pop(&teste);
  printf("TOP: %c\n", Stack(char).top(&teste));

  stack(int) testeInt = Stack(int).new();
  Stack(int).push(&teste, 465);
  printf("TOP: %d\n", Stack(int).top(&teste));
  Stack(int).push(&teste, 123);
  printf("TOP: %d\n", Stack(int).top(&teste));
  Stack(int).pop(&teste);
  printf("TOP: %d\n", Stack(int).top(&teste));

  return EXIT_SUCCESS;
}
