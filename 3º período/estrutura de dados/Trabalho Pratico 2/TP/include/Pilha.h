#ifndef PILHA_H
#define PILHA_H
#include "Celula.h"

class Pilha{
    private:
        Celula* topo;
    public:
        Pilha(){tamanho = 0; topo = NULL;}
        ~Pilha();
        bool vazia() {return tamanho == 0;};
        void empilha(Index index);
        Index desempilha();
        void limpa();
    protected:
        int tamanho;
};

#endif 