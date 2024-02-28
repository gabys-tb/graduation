#ifndef ORDENACAO_H
#define ORDENACAO_H
#include <stdlib.h>  
#include "Registro.h" 
#include "Pilha.h" 
#include "Memlog.h"

class InfoOrdenacao {
    private:
        int num_comp = 0; 
        int num_copias = 0;
        
        void particao(int esq, int dir, int *i, int *j, Registro *A);
        void ordena(int esq, int dir, Registro *A);

        int rand_pos(int esq, int dir);
        Registro mediana(Registro *A, int esq, int dir, int k);
        void particao_mediana(int esq, int dir, int *i, int *j, Registro *A, int k);
        void ordena_mediana(int esq, int dir, Registro *A, int k);

        void troca(Registro *A, Registro *b);
        void selecao(Registro *A, int esq, int dir);
        void ordena_selecao(int esq, int dir, Registro *A, int m);
    
        void merge(Registro *A, int esq, int meio, int dir);
        
        void refaz(Registro *A, int esq, int dir);
        void constroi(Registro *A, int n);
        
    public:
        void quick_sort_recursivo(Registro *A, int n);
        void quick_sort_mediana(Registro *A, int n, int k);
        void quick_sort_selecao(Registro *A, int n, int m);
        void quick_sort_nao_recursivo(Registro *A, int n);
        void quick_sort_empilha_inteligente(Registro *A, int n);

        void merge_sort(Registro *A, int esq, int dir);
        void heap_sort(Registro *A, int n);

        int get_comp(){return num_comp;}
        int get_copias(){return num_copias;}
        void reset(){num_comp = 0; num_copias = 0;}
};


#endif