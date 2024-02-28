# Alvo inicial é link
.DEFAULT_GOAL := link

# Diretórios
MAIN_SRCDIR = ./src
SECONDARY_SRCDIR = $(MAIN_SRCDIR)/classes
TERCIARY_SRCDIR = $(MAIN_SRCDIR)/misc
OBJDIR = ./build
INCDIR = ./include
THIRD_PARTY_INCDIR = ./thirdParty

# Diretórios dos Testes
TESTS_DIR = ./tests
TESTS_SRCDIR = $(TESTS_DIR)/src
TESTS_OBJDIR = $(TESTS_DIR)/build

# Compilador
CC = g++

# Nome do programa
EXEC = spotlite

# Nome do programa dos Testes
EXEC_TEST = spotliteTests

# Preparo dos nomes de arquivos, transforma .cpp em .o
SRC = $(wildcard $(TERCIARY_SRCDIR)/*.cpp $(SECONDARY_SRCDIR)/*.cpp $(MAIN_SRCDIR)/*.cpp)
OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.cpp=.o)))

# Preparo dos nomes de arquivos, transforma .cpp em .o (Arquivos de Teste)
SRC_TESTS = $(wildcard $(SECONDARY_SRCDIR)/*.cpp $(TESTS_SRCDIR)/*.cpp)
OBJ_TESTS = $(addprefix $(TESTS_OBJDIR)/,$(notdir $(SRC_TESTS:.cpp=.o)))

# Flags
CFLAGS = -I $(THIRD_PARTY_INCDIR) -I $(INCDIR) -Wall -Wextra -pedantic -std=c++11
DBGFLAGS = -g -fno-inline
COVRFLAGS = -coverage

# Ignora estes comandos caso existam na máquina
.PHONY : compile link run clean valgrind coverage compiletests tests runtests 

# Compila as sources em arquivos de build .o 
# Se DEBUG=YES, compila com flags de debug
compile: $(OBJ)

ifeq ($(DEBUG),YES)
CFLAGS := $(CFLAGS) $(DBGFLAGS)
endif

$(OBJDIR)/%.o: $(TERCIARY_SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SECONDARY_SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/%.o: $(MAIN_SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# Linka os arquivos de build em um executável
link: compile
	$(CC) -o $(EXEC) $(OBJDIR)/*.o

# Roda o programa
run:
	./$(EXEC)

# Compila as sources em arquivos de build .o (Arquivos de Teste)
compiletests: $(OBJ_TESTS)

# Coverage das classes principais
$(TESTS_OBJDIR)/%.o: $(SECONDARY_SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(COVRFLAGS) $< -o $@	 

$(TESTS_OBJDIR)/%.o: $(TESTS_SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# Linka os arquivos de build em um executável (Arquivos de Teste)
tests: compiletests
	$(CC) -o $(TESTS_DIR)/$(EXEC_TEST) $(TESTS_OBJDIR)/*.o $(COVRFLAGS)

# Roda o programa no diretório de Testes
runtests:
	rm -f $(TESTS_DIR)/data/*.csv
	(cd $(TESTS_DIR) && ./$(EXEC_TEST))

# Exclui o executável e os arquivos de build
clean:
	rm -f $(EXEC)
	rm -f $(TESTS_DIR)/$(EXEC_TEST)
	rm -f $(OBJDIR)/*.o
	rm -f $(TESTS_OBJDIR)/*.o
	rm -f $(TESTS_OBJDIR)/*.gcno
	rm -f $(TESTS_OBJDIR)/*.gcov
	rm -f $(TESTS_OBJDIR)/*.gcda
	rm -f $(TESTS_DIR)/data/*.csv

# Roda valgrind a fim de testar memory leaks
valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./$(EXEC)

# Roda gcovr a fim de testar o coverage do código
coverage: runtests
	gcovr --print-summary $(TESTS_OBJDIR) -r $(SECONDARY_SRCDIR)