#ifndef LISTA_H
#define LISTA_H
#include <string>
#include <iostream>
#include <fstream>
#include <string.h>

class CelulaSignificado{
    private:
        std::string significado;
        CelulaSignificado *prox = NULL;
    friend class ListaSignificado;
};

class ListaSignificado {
    private:
        CelulaSignificado *primeiro = NULL;
        CelulaSignificado *ultimo = NULL;
        int tamanho = 0;
  
    public:
        ListaSignificado();
        ~ListaSignificado();
        void inserir_comeco(std::string significado);
        void inserir(std::string significado);
        void limpar();
        void escreve(std::ofstream *file);
        int get_tamanho();
};
  
#endif