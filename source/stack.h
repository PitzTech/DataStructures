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
} stack__##T;                         \
                                      \
typedef struct  {                     \
  bool (*is_empty__##T)(stack__##T*);           \
  void (*push__##T)(stack__##T*, T*);           \
  void (*pop__##T)(stack__##T*);                \
  void (*wipe__##T)(stack__##T*);               \
  T (*top__##T)(stack__##T*);                   \
  unsigned int (*size__##T)(stack__##T*);       \
  stack__##T(*new__##T)();                      \
} StackInterface__##T;                \
                                                                                                                    \
static void resize__##T(stack__##T* self, size_t new_size) {                                                                  \
  T* tmp = (T*)realloc(self->_data, new_size);                                                                  \
                                                                                                                    \
  if (tmp == NULL) {                                                                                                \
    THROW_ERROR(ANSI_COLOR_RED "Erro ao realocar memória para stack__##T", ENOMEM);                                      \
  }                                                                                                                 \
                                                                                                                    \
  self->_mem_allocated = new_size;                                                                                  \
  self->_data = tmp;                                                                                                \
}                                                                                                                   \
                                                                                                                    \
static void initialize__##T(stack__##T* self) {                                                                               \
  if (self->_data != NULL) {                                                                                        \
    return;                                                                                                         \
  }                                                                                                                 \
                                                                                                                    \
  size_t reserved_space = sizeof(T) * 10;                                                                         \
  self->_data = (T*)malloc(reserved_space);                                                                       \
                                                                                                                    \
  if (self->_data == NULL) {                                                                                        \
    THROW_ERROR(ANSI_COLOR_RED "Erro ao alocar memória para stack__##T", ENOMEM);                                        \
  }                                                                                                                 \
                                                                                                                    \
  self->_mem_allocated = reserved_space;                                                                            \
}                                                                                                                   \
                                                                                                                    \
static bool is_initialized__##T(stack__##T* self) {                                                                           \
  bool isInitialized = !(self->_mem_allocated <= 0 || self->_data == NULL);                                         \
  return isInitialized;                                                                                             \
}                                                                                                                   \
                                                                                                                    \
static bool is_empty__##T(stack__##T* self) {                                                                                 \
  bool is_stack_empty = self->_size == 0;                                                                           \
  return is_stack_empty;                                                                                            \
}                                                                                                                   \
                                                                                                                    \
static void push__##T(stack__##T* self, T* element) {                                                                       \
  if (!is_initialized(self)) {                                                                                      \
    initialize__##T(self);                                                                                               \
  }                                                                                                                 \
                                                                                                                    \
  if (self->_mem_allocated <= self->_mem_used + sizeof(T)) {                                                      \
    resize__##T(self, sizeof(T) * SURPLUS_SLOTS + self->_mem_allocated);                                               \
  }                                                                                                                 \
                                                                                                                    \
  T* copy_addr = (T*)memcpy(&self->_data[self->_size], &element, sizeof(T));                                  \
  if (copy_addr == NULL) {                                                                                          \
    THROW_ERROR(ANSI_COLOR_RED "push__##T() - Erro ao atribuir valor para stack__##T" ANSI_COLOR_RESET, ENOMEM);              \
  }                                                                                                                 \
                                                                                                                    \
  self->_size++;                                                                                                    \
  self->_mem_used += sizeof(T);                                                                                   \
}                                                                                                                   \
                                                                                                                    \
static void pop__##T(stack__##T* self) {                                                                                      \
  if (!is_initialized(self)) {                                                                                      \
    return;                                                                                                         \
  }                                                                                                                 \
                                                                                                                    \
  unsigned int available_slots = (self->_mem_allocated + sizeof(T) - self->_mem_used) / sizeof(T);              \
  if (available_slots > SURPLUS_SLOTS) {                                                                            \
    resize__##T(self, self->_mem_allocated - sizeof(T));                                                               \
  }                                                                                                                 \
                                                                                                                    \
  self->_size -= 1;                                                                                                 \
  self->_mem_used -= sizeof(T);                                                                                   \
}                                                                                                                   \
                                                                                                                    \
static void wipe__##T(stack__##T* self) {                                                                                     \
  free(self->_data);                                                                                                \
  self->_data = NULL;                                                                                               \
  self->_mem_allocated = 0;                                                                                         \
  self->_mem_used = 0;                                                                                              \
  self->_size = 0;                                                                                                  \
}                                                                                                                   \
                                                                                                                    \
static T top__##T(stack__##T* self) {                                                                                       \
  if (!is_initialized(self)) {                                                                                      \
    THROW_ERROR(ANSI_COLOR_RED "top__##T() - Erro ao resgatar topo da stack__##T" ANSI_COLOR_RESET, EFAULT);                  \
  }                                                                                                                 \
  T* element = self->_data[self->_size - 1];                                                                      \
                                                                                                                    \
  return element;                                                                                                   \
}                                                                                                                   \
                                                                                                                    \
static unsigned int size__##T(stack__##T* self) {                                                                             \
  unsigned int elementSize = self->_size;                                                                           \
  return elementSize;                                                                                               \
}                                                                                                                   \
                                                                                                                    \
static stack__##T new(){                                                                                                 \
  stack__##T new_stack = {                                                                                               \
    ._data = NULL,                                                                                                  \
    ._mem_allocated = 0,                                                                                            \
    ._mem_used = 0,                                                                                                 \
    ._size = 0                                                                                                      \
  };                                                                                                                \
                                                                                                                    \
  initialize__##T(&new_stack);                                                                                           \
                                                                                                                    \
  return new_stack;                                                                                                 \
}                                                                                                                   \
                                                                                                                    \
StackInterface Stack__##T = {                                                                                            \
  .new = new__##T,                                                                                                       \
  .push = push__##T,                                                                                                     \
  .top = top__##T,                                                                                                       \
  .size = size__##T,                                                                                                     \
  .wipe = wipe__##T,                                                                                                     \
  .is_empty = is_empty__##T,                                                                                             \
  .pop = pop__##T                                                                                                        \
};

#define stack(T) stack__##T

#define Stack(T) Stack__##T

#endif /* STACK_H */
