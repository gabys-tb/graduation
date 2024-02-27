#ifndef SISTEMA_H
#define SISTEMA_H
#include "CelulaUsuario.h"

class Sistema {
    private:
        CelulaUsuario *primeiro;
        CelulaUsuario *ultimo;
        int tamanho = 0;
    public:
        Sistema();
        ~Sistema();
        void limpar();
        CelulaUsuario* pesquisar_id(int id);
        void imprimir_erro(int id);
        void acessar_inbox(int id);
        void adicionar_usuario(int id);
        void remover_usuario(int id);
        void entregar_mensagem(CelulaUsuario* celula, Email email);
};

#endif