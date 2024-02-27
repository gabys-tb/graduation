#ifndef CELULA_EMAIL_H
#define CEULULA_EMAIL_H
#include <stdio.h>
#include <iostream>
#include <string.h>

class Email {
    private: 
        std::string texto;
        int pri;    
    public:
        Email(){
            this->texto = "\0" ;
            pri = -1;
        };
        std::string get_texto(){return texto;}
        void set_texto(std::string texto){this->texto = texto;}
        int get_pri(){return pri;};
        void set_pri(int pri){this->pri = pri;}
};

class CelulaEmail {
    private:
        Email email;
        CelulaEmail *prox;
    public:
        CelulaEmail(){ 
            prox = NULL;
        }
    friend class Inbox;
};

#endif