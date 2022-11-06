#include "stdbool.h" // C99 DEPENDENT
#include "stdlib.h"
#include "string.h"
#include "errno.h"

#include "stack.h"

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

static void resize(stack* self, size_t new_size) {
  int* tmp = (int*)realloc(self->_data, new_size);

  if (tmp == NULL) {
    THROW_ERROR(ANSI_COLOR_RED "Erro ao realocar memória para stack", ENOMEM);
  }

  self->_mem_allocated = new_size;
  self->_data = tmp;
}

static void initialize(stack* self) {
  if (self->_data != NULL) {
    return;
  }

  size_t reserved_space = sizeof(int) * 10;
  self->_data = (int*)malloc(reserved_space);

  if (self->_data == NULL) {
    THROW_ERROR(ANSI_COLOR_RED "Erro ao alocar memória para stack", ENOMEM);
  }

  self->_mem_allocated = reserved_space;
}

static bool is_initialized(stack* self) {
  bool isInitialized = !(self->_mem_allocated <= 0 || self->_data == NULL);
  return isInitialized;
}

static bool is_empty(stack* self) {
  bool is_stack_empty = self->_size == 0;
  return is_stack_empty;
}

static void push(stack* self, int* element) {
  if (!is_initialized(self)) {
    initialize(self);
  }

  if (self->_mem_allocated <= self->_mem_used + sizeof(int)) {
    resize(self, sizeof(int) * SURPLUS_SLOTS + self->_mem_allocated);
  }

  int* copy_addr = (int*)memcpy(&self->_data[self->_size], &element, sizeof(int));
  if (copy_addr == NULL) {
    THROW_ERROR(ANSI_COLOR_RED "push() - Erro ao atribuir valor para stack" ANSI_COLOR_RESET, ENOMEM);
  }

  self->_size++;
  self->_mem_used += sizeof(int);
}

static void pop(stack* self) {
  if (!is_initialized(self)) {
    return;
  }

  unsigned int available_slots = (self->_mem_allocated + sizeof(int) - self->_mem_used) / sizeof(int);
  if (available_slots > SURPLUS_SLOTS) {
    resize(self, self->_mem_allocated - sizeof(int));
  }

  self->_size -= 1;
  self->_mem_used -= sizeof(int);
}

static void wipe(stack* self) {
  free(self->_data);
  self->_data = NULL;
  self->_mem_allocated = 0;
  self->_mem_used = 0;
  self->_size = 0;
}

static int top(stack* self) {
  if (!is_initialized(self)) {
    THROW_ERROR(ANSI_COLOR_RED "top() - Erro ao resgatar topo da stack" ANSI_COLOR_RESET, EFAULT);
  }
  int* element = self->_data[self->_size - 1];

  return element;
}

static unsigned int size(stack* self) {
  unsigned int elementSize = self->_size;
  return elementSize;
}

static stack new(){
  stack new_stack = {
    ._data = NULL,
    ._mem_allocated = 0,
    ._mem_used = 0,
    ._size = 0
  };

  initialize(&new_stack);

  return new_stack;
}


StackInterface Stack = {
  .new = new,
  .push = push,
  .top = top,
  .size = size,
  .wipe = wipe,
  .is_empty = is_empty,
  .pop = pop
};
