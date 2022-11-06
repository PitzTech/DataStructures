#include "stdio.h"
#include "stdlib.h"

#include "stack.h"

int main() {
  printf("RODOU\n");

  GENERATE_STACK_TYPE(char);

  stack(char) teste = Stack(char).new();
  Stack(char).push(&teste, 'c');
  printf("TOP: %c\n", Stack(char).top(&teste));
  Stack(char).push(&teste, 'd');
  printf("TOP: %c\n", Stack(char).top(&teste));
  Stack(char).pop(&teste);
  printf("TOP: %c\n", Stack(char).top(&teste));


  return EXIT_SUCCESS;
}
