#ifndef DIC_HASH_H
#define DIC_HASH_H
#include "Estruturas.h"
#include "Memlog.h"

struct Info{
    std::string verbete;
    int pos;
};

class DicionarioHash {
    private:
        int m; 
        int f_hash(std::string p);
        Verbete * tabela;
        int * vazio;
        void particao(int esq, int dir, int *i, int *j, Info *A);
        void ordena(int esq, int dir, Info *A);
        void quick_sort(Info *A, int n);
        int pesquisa(std::string chave);
    public:
        DicionarioHash(int n);
        ~DicionarioHash();
        void insere(Entrada p);
        void remove_verbetes();
        void escreve(std::ofstream *file);
};

#endif