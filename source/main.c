#include "stdio.h"
#include "stdlib.h"

#include "stack.h"

int main() {
  printf("RODOU\n");

  stack teste = Stack.new();
  Stack.push(&teste, 1);
  printf("TOP: %d\n",Stack.top(&teste));
  Stack.push(&teste,3);
  printf("TOP: %d\n",Stack.top(&teste));
  Stack.pop(&teste);
  printf("TOP: %d\n",Stack.top(&teste));
  

  return EXIT_SUCCESS;
}
