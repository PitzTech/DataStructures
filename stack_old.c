#include "stdbool.h" // C99 DEPENDENT
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef enum {
  T_BOOL,
  T_CHAR,
  T_SIGNED_CHAR,
  T_UNSIGNED_CHAR,
  T_SHORT,
  T_SIGNED_SHORT,
  T_SIGNED_SHORT_INT,
  T_UNSIGNED_SHORT,
  T_UNSIGNED_SHORT_INT,
  T_INT,
  T_SIGNED_INT,
  T_UNSIGNED_INT,
  T_LONG,
  T_SIGNED_LONG,
  T_SIGNED_LONG_INT,
  T_UNSIGNED_LONG,
  T_UNSIGNED_LONG_INT,
  T_LONG_LONG,
  T_LONG_LONG_INT,
  T_SIGNED_LONG_LONG,
  T_SIGNED_LONG_LONG_INT,
  T_UNSIGNED_LONG_LONG,
  T_UNSIGNED_LONG_LONG_INT,
  T_FLOAT,
  T_DOUBLE,
  T_LONG_DOUBLE,
  T_OTHER,
} T_TYPENAME;

size_t TYPE_SIZE[] = {
  sizeof(bool), // T_BOOL,
  sizeof(char), // T_CHAR,
  sizeof(signed char), // T_SIGNED_CHAR,
  sizeof(unsigned char), // T_UNSIGNED_CHAR,
  sizeof(short), // T_SHORT,
  sizeof(signed short), // T_SIGNED_SHORT,
  sizeof(signed short int), // T_SIGNED_SHORT_INT,
  sizeof(unsigned short), // T_UNSIGNED_SHORT,
  sizeof(unsigned short int), // T_UNSIGNED_SHORT_INT,
  sizeof(int), // T_INT,
  sizeof(signed int), // T_SIGNED_INT,
  sizeof(unsigned int), // T_UNSIGNED_INT,
  sizeof(long), // T_LONG,
  sizeof(signed long), // T_SIGNED_LONG,
  sizeof(signed long int), // T_SIGNED_LONG_INT,
  sizeof(unsigned long), // T_UNSIGNED_LONG,
  sizeof(unsigned long int), // T_UNSIGNED_LONG_INT,
  sizeof(long long), // T_LONG_LONG,
  sizeof(long long int), // T_LONG_LONG_INT,
  sizeof(signed long long), // T_SIGNED_LONG_LONG,
  sizeof(signed long long int), // T_SIGNED_LONG_LONG_INT,
  sizeof(unsigned long long), // T_UNSIGNED_LONG_LONG,
  sizeof(unsigned long long int), //  T_UNSIGNED_LONG_LONG_INT,
  sizeof(float), // T_FLOAT,
  sizeof(double), // T_DOUBLE,
  sizeof(long double), // T_LONG_DOUBLE,
  0, // T_OTHER,
};

// #define GENERATE_STACK_TYPE()

typedef struct stack_struct stack;

struct stack_struct {
  // union {
  //   int * intData;
  //   char * charData;
  //   float * floatData;
  //   double * doableData;
  // } _data;
  void * _data; // arr
  // void (*push)(stack *, void *);
  // void (*pop)(stack *);
  // bool (*is_empty)(stack *);
  // void * (*last)(stack *);
  int (*size)(stack *);
  size_t _size;
  int _used;
  T_TYPENAME _data_type;
};

void stack_push(stack *self, void *value ) {
  const size_t value_size = sizeof(value);
  printf("SIZE VALUE %zu \n ", sizeof(value));
  printf("SIZE POINTER %zu \n\n ", sizeof(&value));
  const size_t data_element_size = TYPE_SIZE[self->_data_type];

  if (self->_data == NULL) {
    printf("INITIALIZING \n\n");
    self->_data = malloc(data_element_size * 10);
    self->_size = value_size * 10;
  }

  if (self->_used > 0 && data_element_size != value_size) {
    printf("self->_data[0] %d\n", ((int *)self->_data)[0]);
    printf("sizeof(self->_data[0]) %zu\n", data_element_size);
    printf("value %lf\n", (int)value);
    printf("sizeof(value) %zu\n", sizeof(value));
    printf("INVALID ELEMENT TYPE\n");
    // INVALID ELEMENT TYPE
    return;
  }

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
void stack_pop(stack *self) {}
bool stack_is_empty(stack *self) { return true; }
void * last(stack *self) {
  if (self->_data == NULL) {
    printf("NULL \n");
    return;
  }

  printf("\n\nPRINTING %d position\n", self->_used - 1);
  printf("Pointer address %p\n", &self->_data[self->_used - 1]);
  printf("Pointer VALUE %d\n\n",((int *)self->_data)[self->_used - 1]);

  return self->_data[self->_used - 1];
}

// #define 

stack Stack(T_TYPENAME data_type) {
  stack new_stack = {
      // .push = push,
      // .pop = pop,
      // .is_empty = is_empty,
      // .last = last,
      ._used = 0,
      ._size = 0,
      ._data = NULL,
      ._data_type = data_type
  };

  return new_stack;
}

int main() {
  stack my_stack = Stack(T_FLOAT);

  float teste = 0.2;
  printf("SIZE OF TEST %zu\n\n", sizeof(teste));
  

  // my_stack.push(&my_stack, &teste);
  // my_stack.last(&my_stack);
  // my_stack.push(&my_stack, &teste);
  // my_stack.last(&my_stack);

  stack_push(&my_stack, &teste);
  stack_last(&my_stack);
  stack_push(&my_stack, &teste);
  stack_last(&my_stack);


  printf("%lf\n", my_stack.last(&my_stack));
  
  

  printf("%d\n", my_stack._used);
  printf("%zu\n", my_stack._size);

  return 0;
}
//gcc stack.c -o out && ./out 


// C11 DEPENDENT - and  "stdbool.h"
#define GET_TYPENAME(x) _Generic((x), \
  _Bool: T_BOOL, \
  char: T_CHAR, \
  signed char: T_SIGNED_CHAR, \
  unsigned char: T_UNSIGNED_CHAR, \
  short: T_SHORT, \
  signed short: T_SIGNED_SHORT, \
  signed short int: T_SIGNED_SHORT_INT, \
  unsigned short: T_UNSIGNED_SHORT, \
  unsigned short int: T_UNSIGNED_SHORT_INT, \
  int: T_INT, \
  signed int: T_SIGNED_INT, \
  unsigned int: T_UNSIGNED_INT, \
  long: T_LONG, \
  signed long: T_SIGNED_LONG, \
  signed long int: T_SIGNED_LONG_INT, \
  unsigned long: T_UNSIGNED_LONG, \
  unsigned long int: T_UNSIGNED_LONG_INT, \
  long long: T_LONG_LONG, \
  long long int: T_LONG_LONG_INT, \
  signed long long: T_SIGNED_LONG_LONG, \
  signed long long int: T_SIGNED_LONG_LONG_INT, \
  unsigned long long: T_UNSIGNED_LONG_LONG, \
  unsigned long long int: T_UNSIGNED_LONG_LONG_INT, \
  float: T_FLOAT, \
  double: T_DOUBLE, \
  long double: T_LONG_DOUBLE, \
  default: T_OTHER)
