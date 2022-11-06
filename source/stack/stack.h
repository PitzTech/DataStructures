#ifndef STACK_H
#define STACK_H

typedef struct stack_interface_struct StackInterface;
#include "stdlib.h"
#include "stdbool.h" // C99 DEPENDENT

typedef struct stack_struct {
  int* _data;
  size_t _mem_allocated;
  size_t _mem_used;
  unsigned int _size;
} stack;

struct stack_interface_struct {
  bool (*is_empty)(stack*);
  void (*push)(stack*, int*);
  void (*pop)(stack*);
  void (*wipe)(stack*);
  int (*top)(stack*);
  unsigned int (*size)(stack*);
  stack(*new)();
};

extern StackInterface Stack;

#endif /* STACK_H */
