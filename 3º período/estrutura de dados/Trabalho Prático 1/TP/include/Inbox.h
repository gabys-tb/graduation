#ifndef INBOX_H
#define INBOX_H
#include "CelulaEmail.h"

class Inbox {
    private:
        CelulaEmail *primeiro;
        CelulaEmail *ultimo;
        int tamanho;
  
    public:
        Inbox();
        ~Inbox();
        int get_tamanho() {return tamanho;};
        void inserir_comeco(Email email);
        void inserir_final(Email email);
        void inserir_prioridade(Email email);
        Email remover_comeco();
        void limpar();
    
};
  
#endif