# Nome do projeto
PROJ_NAME=sistema
 
# Arquivos .c
C_SOURCE=$(wildcard ./src/*.c)

# Arquivos Objetos
#OBJ=objects*.o
OBJ=$(subst .c,.o,$(subst src,objects,$(C_SOURCE)))

# Compilador e linker
CC=gcc
 
ifdef OS
	RM = del objects\\*.o Sistema.exe
	else
  	ifeq ($(shell uname), Linux)
      RM = rm -f ./objects/*.o $(PROJ_NAME) *~
   	endif
endif

# Flags para compilador
CC_FLAGS=-c -W -Wall -pedantic -g -I includes/
 
# Compilação e vinculação

all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ) 
	$(CC) $^ -o $@ 


./objects/%.o: ./src/%.c
	$(CC) $< $(CC_FLAGS) -o $@

./objects/main.o: ./src/main.c
	$(CC) ./src/main.c $(CC_FLAGS)  -o $@

clean:
	@ $(RM)