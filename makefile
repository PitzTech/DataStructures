PROJ_NAME=stack_estrutura

C_SOURCE=$(wildcard ./source/*/*.c)

H_SOURCE=$(wildcard ./source/*/*.h)

OBJ=$(subst .c,.o,$(subst source,objects,$(C_SOURCE)))

CC=gcc

CC_FLAGS=-c   \
	-W          \
	-Wall       \
  -std=c99    \
	#-ansi      \
	-pedantic   \
  -lm

RM = rm -rf

all: objFolder $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	@ echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@
	@ echo 'Finished building binary: $@'
	@ echo ' '

./objects/%.o: ./source/*/%.c ./source/*/%.h
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

./objects/main.o: ./source/main.c $(H_SOURCE)
	@ echo 'Building target using GCC compiler: $<'
	$(CC) $< $(CC_FLAGS) -o $@
	@ echo ' '

objFolder:
	@ mkdir -p objects

clean:
	@ $(RM) ./objects/*.o $(PROJ_NAME) *~
	@ rmdir objects

.PHONY: all clean
