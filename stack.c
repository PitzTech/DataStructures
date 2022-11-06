#include "stdbool.h" // C99 DEPENDENT
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "errno.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define THROW_ERROR(message, code) \
  errno=(code); \
  perror(message); \
  exit(code); \

typedef struct stack_struct stack;

struct stack_struct {
  int * _data;
  size_t _size;
  int _used;
};

void initialize_int_stack(stack *self) {
  if (self->_data != NULL) {
    return;  
  }
  
  size_t reserved_space = sizeof(int) * 10;
  self->_data = (int *) malloc(reserved_space);

  if (self->_data == NULL) {
    THROW_ERROR(ANSI_COLOR_RED "Erro ao alocar memória para stack", ENOMEM);
  }
  
  self->_size = reserved_space;
}

void stack_int_push(stack *self, void *value) {
  if (self->_size == self->_used) {
    printf("ENTROU\n");
    self->_size += value_size * 10;
    self->_data = realloc(self->_data, self->_size);
  }

  printf("Pointer address %p\n", &self->_data[self->_used]);
  printf("Pointer VALUE %f\n",((float *)self->_data)[self->_used]);

  memcpy(&self->_data[self->_used], &value, data_element_size);

  printf("Pointer address %p\n", &self->_data[self->_used]);
  printf("Pointer VALUE %lf\n",((double *)self->_data)[self->_used]);
  self->_used++;
}

// void stack_pop(stack *self) {}
// bool stack_is_empty(stack *self) { return true; }
// void * last(stack *self) {
//   if (self->_data == NULL) {
//     printf("NULL \n");
//     return;
//   }

//   printf("\n\nPRINTING %d position\n", self->_used - 1);
//   printf("Pointer address %p\n", &self->_data[self->_used - 1]);
//   printf("Pointer VALUE %d\n\n",((int *)self->_data)[self->_used - 1]);

//   return self->_data[self->_used - 1];
// }


stack StackInt() {
  stack new_stack = {
      ._used = 0,
      ._size = 0,
      ._data = NULL,
  };

  initialize_int_stack(&new_stack);
  
  return new_stack;
}

int main() {
  stack my_stack = StackInt();

  printf("%zu \nn\n", my_stack._size);

  // float teste = 0.2;
  // printf("SIZE OF TEST %zu\n\n", sizeof(teste));

  // push(&my_stack, &teste);
  // last(&my_stack);
  // push(&my_stack, &teste);
  // last(&my_stack);

  return EXIT_SUCCESS;
}
//gcc stack.c -o out && ./out 
