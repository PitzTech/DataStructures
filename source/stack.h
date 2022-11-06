#include "stdbool.h" // C99 DEPENDENT
#include "stdlib.h"
#include "string.h"
#include "errno.h"

#ifndef STACK_H
#define STACK_H

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define THROW_ERROR(message, code) \
   errno = (code);                 \
   perror(message);                \
   exit(code);

#define SURPLUS_SLOTS 10

#define GENERATE_STACK_TYPE(T)  \
                                  \
typedef struct {                      \
  T* _data;                           \
  size_t _mem_allocated;              \
  size_t _mem_used;                   \
  unsigned int _size;                 \
} stack_##T;                         \
                                      \
typedef struct  {                     \
  bool (*is_empty)(stack_##T*);           \
  void (*push)(stack_##T*, T*);           \
  void (*pop)(stack_##T*);                \
  void (*wipe)(stack_##T*);               \
  T (*top)(stack_##T*);                   \
  unsigned int (*size)(stack_##T*);       \
  stack_##T (*new)();                      \
} StackInterface_##T;                \
                                                                                                                    \
void resize_##T(stack_##T* self, size_t new_size) {                                                                  \
  T* tmp = (T*)realloc(self->_data, new_size);                                                                  \
                                                                                                                    \
  if (tmp == NULL) {                                                                                                \
    THROW_ERROR(ANSI_COLOR_RED "Erro ao realocar memória para stack_##T", ENOMEM);                                      \
  }                                                                                                                 \
                                                                                                                    \
  self->_mem_allocated = new_size;                                                                                  \
  self->_data = tmp;                                                                                                \
}                                                                                                                   \
                                                                                                                    \
void initialize_##T(stack_##T* self) {                                                                               \
  if (self->_data != NULL) {                                                                                        \
    return;                                                                                                         \
  }                                                                                                                 \
                                                                                                                    \
  size_t reserved_space = sizeof(T) * 10;                                                                         \
  self->_data = (T*)malloc(reserved_space);                                                                       \
                                                                                                                    \
  if (self->_data == NULL) {                                                                                        \
    THROW_ERROR(ANSI_COLOR_RED "Erro ao alocar memória para stack_##T", ENOMEM);                                        \
  }                                                                                                                 \
                                                                                                                    \
  self->_mem_allocated = reserved_space;                                                                            \
}                                                                                                                   \
                                                                                                                    \
bool is_initialized_##T(stack_##T* self) {                                                                           \
  bool isInitialized = !(self->_mem_allocated <= 0 || self->_data == NULL);                                         \
  return isInitialized;                                                                                             \
}                                                                                                                   \
                                                                                                                    \
bool is_empty_##T(stack_##T* self) {                                                                                 \
  bool is_stack_empty = self->_size == 0;                                                                           \
  return is_stack_empty;                                                                                            \
}                                                                                                                   \
                                                                                                                    \
void push_##T(stack_##T* self, T* element) {                                                                       \
  if (!is_initialized_##T(self)) {                                                                                      \
    initialize_##T(self);                                                                                               \
  }                                                                                                                 \
                                                                                                                    \
  if (self->_mem_allocated <= self->_mem_used + sizeof(T)) {                                                      \
    resize_##T(self, sizeof(T) * SURPLUS_SLOTS + self->_mem_allocated);                                               \
  }                                                                                                                 \
                                                                                                                    \
  T* copy_addr = (T*)memcpy(&self->_data[self->_size], &element, sizeof(T));                                  \
  if (copy_addr == NULL) {                                                                                          \
    THROW_ERROR(ANSI_COLOR_RED "push_##T() - Erro ao atribuir valor para stack_##T" ANSI_COLOR_RESET, ENOMEM);              \
  }                                                                                                                 \
                                                                                                                    \
  self->_size++;                                                                                                    \
  self->_mem_used += sizeof(T);                                                                                   \
}                                                                                                                   \
                                                                                                                    \
void pop_##T(stack_##T* self) {                                                                                      \
  if (!is_initialized_##T(self)) {                                                                                      \
    return;                                                                                                         \
  }                                                                                                                 \
                                                                                                                    \
  unsigned int available_slots = (self->_mem_allocated + sizeof(T) - self->_mem_used) / sizeof(T);              \
  if (available_slots > SURPLUS_SLOTS) {                                                                            \
    resize_##T(self, self->_mem_allocated - sizeof(T));                                                               \
  }                                                                                                                 \
                                                                                                                    \
  self->_size -= 1;                                                                                                 \
  self->_mem_used -= sizeof(T);                                                                                   \
}                                                                                                                   \
                                                                                                                    \
void wipe_##T(stack_##T* self) {                                                                                     \
  free(self->_data);                                                                                                \
  self->_data = NULL;                                                                                               \
  self->_mem_allocated = 0;                                                                                         \
  self->_mem_used = 0;                                                                                              \
  self->_size = 0;                                                                                                  \
}                                                                                                                   \
                                                                                                                    \
T top_##T(stack_##T* self) {                                                                                       \
  if (!is_initialized_##T(self)) {                                                                                      \
    THROW_ERROR(ANSI_COLOR_RED "top_##T() - Erro ao resgatar topo da stack_##T" ANSI_COLOR_RESET, EFAULT);                  \
  }                                                                                                                 \
  T* element = self->_data[self->_size - 1];                                                                      \
                                                                                                                    \
  return element;                                                                                                   \
}                                                                                                                   \
                                                                                                                    \
unsigned int size_##T(stack_##T* self) {                                                                             \
  unsigned int elementSize = self->_size;                                                                           \
  return elementSize;                                                                                               \
}                                                                                                                   \
                                                                                                                    \
stack_##T new_##T(){                                                                                                 \
  stack_##T new_stack = {                                                                                               \
    ._data = NULL,                                                                                                  \
    ._mem_allocated = 0,                                                                                            \
    ._mem_used = 0,                                                                                                 \
    ._size = 0                                                                                                      \
  };                                                                                                                \
                                                                                                                    \
  initialize_##T(&new_stack);                                                                                           \
                                                                                                                    \
  return new_stack;                                                                                                 \
}                                                                                                                   \
                                                                                                                    \
StackInterface_##T Stack_##T = {                                                                                            \
  .new = new_##T,                                                                                                       \
  .push = push_##T,                                                                                                     \
  .top = top_##T,                                                                                                       \
  .size = size_##T,                                                                                                     \
  .wipe = wipe_##T,                                                                                                     \
  .is_empty = is_empty_##T,                                                                                             \
  .pop = pop_##T                                                                                                        \
}; 

#define Stack(T) Stack_##T

#define stack(T) stack_##T


#endif /* STACK_H */
