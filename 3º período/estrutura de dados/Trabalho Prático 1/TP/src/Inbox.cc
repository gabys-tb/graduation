#include "Inbox.h"

Inbox::Inbox() {
    tamanho = 0;
    primeiro = new (CelulaEmail);
    ultimo = primeiro;
}

void Inbox::limpar() {
    CelulaEmail *p;
    
    p = primeiro->prox;
    while (p!=NULL) {
        primeiro->prox = p->prox;
        delete p;
        p = primeiro->prox;
    }
    ultimo = primeiro;
    tamanho = 0;
}

Inbox::~Inbox() {
    limpar();
    delete primeiro;
}

void Inbox::inserir_comeco(Email email) {
    CelulaEmail* nova = new (CelulaEmail);
    nova->email = email;
    nova->prox = primeiro->prox;
    primeiro->prox = nova;
    tamanho++;
    if(nova->prox == NULL)
        ultimo = nova;
}

void Inbox::inserir_prioridade(Email email) {
    if (tamanho == 0){
        inserir_comeco(email);
        return;
    }
    
    CelulaEmail *aux1, *aux2; 

    aux1 = primeiro;
    aux2 = aux1->prox;
    while(aux2 != NULL) {
        if(aux2->email.get_pri()<email.get_pri()){
            break;
        }
    
        aux1 = aux2;
        aux2 = aux2->prox;
    } 

    CelulaEmail *nova = new (CelulaEmail);

    aux1->prox = nova;
    nova->email = email;
    nova->prox = aux2;
    tamanho++;

    if(nova->prox == NULL)
        ultimo = nova;
}

Email Inbox::remover_comeco() {
    CelulaEmail *p; Email aux_email;
    std::string aux_texto;

    p = primeiro->prox;
    aux_email = p->email;
    primeiro->prox = p->prox;
    delete p;
    tamanho--;

    return aux_email;
}
