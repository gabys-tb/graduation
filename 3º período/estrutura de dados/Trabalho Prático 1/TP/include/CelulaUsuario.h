#ifndef CELULA_USUARIO_H
#define CELULA_USUARIO_H
#include "Inbox.h"

class Usuario {
    private:
        int id;
        Inbox *inbox;
    public:
        Usuario(){
            this->id = -1;
            inbox = new (Inbox);
        };
        ~Usuario(){
            delete inbox;
        };
        int get_id(){return id;}
        Inbox* get_inbox(){return inbox;}
        void set_id(int id){this->id = id;}
};


class CelulaUsuario {
    private:
        Usuario usuario;
        CelulaUsuario *prox;
    public:
        CelulaUsuario(){prox = NULL;}
    friend class Sistema;        
};

#endif