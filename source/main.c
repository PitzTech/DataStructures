#include "stdio.h"
#include "stdlib.h"

#include "stack.h"

int main() {
  printf("RODOU\n");

  stack(t) teste = Stack(int).new();
  Stack(int).push(&teste, 1);
  printf("TOP: %d\n", Stack(int).top(&teste));
  Stack(int).push(&teste, 3);
  printf("TOP: %d\n", Stack(int).top(&teste));
  Stack(int).pop(&teste);
  printf("TOP: %d\n", Stack(int).top(&teste));


  return EXIT_SUCCESS;
}
