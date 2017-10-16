# Makefile baseado no exemplo dado pelo Professor Silvio Costa Sampaio

# $@ nome do alvo (target)
# $^ lista com os nomes de todos os pre-requisitos sem duplicatas
# $< nome do primeiro pre-requisito

# Comandos do sistema operacional
RM = rm -rf

# Compilador
CC=g++

# Variaveis para os subdiretorios
LIB_DIR=./lib
INC_DIR=./include
SRC_DIR=./src
OBJ_DIR=./build
BIN_DIR=./bin
DOC_DIR=./doc
TEST_DIR=./test

# Opcoes de compilacao
CFLAGS = -Wall -pedantic -ansi -std=c++11 -I. -I$(INC_DIR)

.PHONY: all clean distclean doxy

all: dir Sorting_Algorithms

debug: CFLAGS += -g -O0 -pg
debug: dir Sorting_Algorithms

Sorting_Algorithms: $(OBJ_DIR)/analysis_manager.o $(OBJ_DIR)/fill_manager.o $(OBJ_DIR)/simple_sorts.o $(OBJ_DIR)/bubble_sort_variants.o $(OBJ_DIR)/efficient_sorts.o $(OBJ_DIR)/distribution_sort.o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^
	@echo ">>> [Executavel Sorter criado em $(BIN_DIR)]"

$(OBJ_DIR)/analysis_manager.o: $(SRC_DIR)/analysis_manager.cpp $(INC_DIR)/analysis_manager.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<

$(OBJ_DIR)/fill_manager.o: $(SRC_DIR)/fill_manager.cpp $(INC_DIR)/fill_manager.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<

$(OBJ_DIR)/simple_sorts.o: $(SRC_DIR)/simple_sorts.cpp $(INC_DIR)/simple_sorts.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<

$(OBJ_DIR)/bubble_sort_variants.o: $(SRC_DIR)/bubble_sort_variants.cpp $(INC_DIR)/bubble_sort_variants.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<
	
$(OBJ_DIR)/efficient_sorts.o: $(SRC_DIR)/efficient_sorts.cpp $(INC_DIR)/efficient_sorts.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<

$(OBJ_DIR)/distribution_sort.o: $(SRC_DIR)/distribution_sort.cpp $(INC_DIR)/distribution_sort.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<
	
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) -c $(CFLAGS) -I$(INC_DIR)/ -o $@ $<


# Alvo (target) para a geração automatica de documentacao usando o Doxygen.
# Sempre remove a documentacao anterior (caso exista) e gera uma nova.
doxy:
	$(RM) $(DOC_DIR)/*
	doxygen Doxyfile

# Alvo (target) para a criação dos diretórios dos binários e dos objetos
# Usado antes de iniciar a compilação
dir:
	mkdir -p bin build doc tempos

# Alvo (target) para analisar o código em busca de vazamento de memória
valgrind_simple:
	valgrind -v --leak-check=full --show-reachable=yes ./bin/Sorter

valgrind_full:
	valgrind -v --leak-check=full --show-reachable=yes --track-origins=yes ./bin/Sorter
	
# Alvo (target) usado para limpar os arquivos temporarios (objeto)
# gerados durante a compilacao, assim como os arquivos binarios/executaveis.

clean: dir
	$(RM) $(BIN_DIR)/*
	$(RM) $(OBJ_DIR)/*

# FIM do Makefile