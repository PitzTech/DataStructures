#include "stdbool.h" // C99 - Verify if default codeblock compiler is based on C99
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef union {
  int intValue;
  char* charValue;
  float floatValue;
  double doableValue;
} StackPushParameterType;

typedef struct stackStruct stack;

struct stackStruct {
  // union {
  //   int * intData;
  //   char * charData;
  //   float * floatData;
  //   double * doableData;
  // } _data;
  void* _data; // arr
  void (*push)(stack*, void*);
  void (*pop)(stack*);
  bool (*isEmpty)(stack*);
  void (*last)(stack*);
  int (*size)(stack*);
  size_t _size;
  int _used;
};

void push(stack* self, void* value) {
  size_t valueSize = sizeof(value);
  size_t dataElementSize;

  if (self->_data == NULL) {
    printf("INITIALIZING \n\n");
    self->_data = malloc(valueSize * 10);
    self->_size = valueSize * 10;
  }

  dataElementSize = sizeof(self->_data[0]);

  if (self->_used > 0 && dataElementSize != valueSize) {
    printf("self->_data[0] %d\n", ((int*)self->_data)[0]);
    printf("sizeof(self->_data[0]) %zu\n", dataElementSize);
    printf("value %d\n", (int)value);
    printf("sizeof(value) %zu\n", sizeof(value));
    printf("INVALID ELEMENT TYPE\n");
    // INVALID ELEMENT TYPE
    return;
  }

  if (self->_size == self->_used) {
    printf("ENTROU\n");
    self->_size += valueSize * 10;
    self->_data = realloc(self->_data, self->_size);
  }

  printf("Pointer address %p\n", &self->_data[self->_used]);
  printf("Pointer VALUE %d\n", ((int*)self->_data)[self->_used]);

  memcpy(&self->_data[self->_used], &value, sizeof(value));

  printf("Pointer address %p\n", &self->_data[self->_used]);
  printf("Pointer VALUE %d\n", ((int*)self->_data)[self->_used]);
  self->_used++;
}
void pop(stack* self) {}
bool isEmpty(stack* self) { return true; }
void last(stack* self) {
  if (self->_data == NULL) {
    printf("NULL \n");
    return;
  }

  printf("\n\nPRINTING %d position\n", self->_used - 1);
  printf("Pointer address %p\n", &self->_data[self->_used - 1]);
  printf("Pointer VALUE %d\n\n", ((int*)self->_data)[self->_used - 1]);
}

stack Stack() {
  stack newStack = {
      .push = push,
      .pop = pop,
      .isEmpty = isEmpty,
      .last = last,
      ._used = 0,
      ._size = 0,
      ._data = NULL
  };

  return newStack;
}

int main() {
  stack myStack = Stack();

  myStack.push(&myStack, 2);
  myStack.last(&myStack);
  myStack.push(&myStack, 4);
  myStack.last(&myStack);
  myStack.push(&myStack, 6);
  myStack.last(&myStack);

  printf("%d\n", myStack._used);
  printf("%zu\n", myStack._size);

  return 0;
}
