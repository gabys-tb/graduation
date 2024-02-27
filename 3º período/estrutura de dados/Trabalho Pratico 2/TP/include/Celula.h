#ifndef CELULA_H
#define CELULA_H
#include <stdio.h>

struct Index {
    int esq, dir;
};

class Celula {
    private:
        Index index;
        Celula *prox;
    public:
        Celula(){
            prox = NULL;
        }
    friend class Pilha;
};

#endif