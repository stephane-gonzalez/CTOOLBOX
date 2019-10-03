DFLAGS=-Wall -ansi -pedantic -g3 -DCOUNT_ALLOC
RFLAGS=-O3 -Wall -ansi -pedantic
FLAGS=$(RFLAGS)

SRC= $(wildcard src/*/*.c)
OBJ= $(SRC:.c=.o)
OUT = lib/libtoolbox.a

SRCEXEC= $(wildcard src/*.c)
OBJEXEC= $(SRC:.c=.o)
EXEC=main.exe

INC=-I./include
LIBDIR=-L./lib
LIB=-ltoolbox
CC=gcc
MAKELIB=ar cr


all: $(EXEC) 

# Creation de la librairie
$(OUT): $(OBJ)
	echo -n "Make static library $(OUT) => "
	@$(MAKELIB) $(OUT) $(OBJ)
	echo OK
	
# Compilation de l'executable	
$(EXEC): $(OUT)
	echo -n "Compile $(EXEC) => "
	@$(CC) $(INC) $(SRCEXEC) -o $(EXEC) $(LIBDIR) $(LIB)  $(FLAGS)
	echo OK

# Compilation de tous les fichiers c de la librairie
%.o: %.c
	echo -n "Compile $< => "
	@$(CC) $(INC) -o $@ -c $< $(FLAGS)
	echo OK

# Lancement de l'executable
run:$(EXEC)
	echo -n "Run => "
	@./$(EXEC)
	echo OK

clean:
	echo -n "Clean => "
	@rm -rf **/*.o **/*/*.o 
	@rm -f *.jpg *.dot $(EXEC)
	echo OK

cleanall: clean
	echo -n "Clean ALL => "
	@rm -f $(OUT)
	@rm -rf doc
	echo OK
