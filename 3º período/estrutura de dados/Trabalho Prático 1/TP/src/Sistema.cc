#include "Sistema.h"

Sistema::Sistema(){
    primeiro = new (CelulaUsuario);
    ultimo = primeiro;
}

void Sistema::limpar() {
    CelulaUsuario *p;
    p = primeiro->prox;
    while (p!=NULL) {
        primeiro->prox = p->prox;
        delete p;
        p = primeiro->prox;
    }
    ultimo = primeiro;
    tamanho = 0;
}

Sistema::~Sistema(){
    limpar();
    delete primeiro;
}

CelulaUsuario* Sistema::pesquisar_id(int id){
    CelulaUsuario *p;
    
    p = primeiro->prox;
    while (p!=NULL){
        if (p->usuario.get_id() == id) {
            return p;
        } 
        p = p->prox;
    }
    return p;
}

void Sistema::imprimir_erro(int id){
    std::cout << "ERRO: CONTA " << id << " NAO EXISTE" << std::endl;
}

void Sistema::adicionar_usuario(int id){
    if (pesquisar_id(id)!=NULL){
        std::cout << "ERRO: CONTA " << id << " JA EXISTENTE" << std::endl;
        return;
    }
    
    CelulaUsuario *p;
    p = new (CelulaUsuario);

    if (tamanho == 0){
        primeiro->prox = p;
        p->usuario.set_id(id);
        ultimo = p;
    }
    else {
        ultimo->prox = p;
        p->usuario.set_id(id);
        ultimo = p;
    }

    tamanho++;
    std::cout << "OK: CONTA " << id << " CADASTRADA" << std::endl;
}

void Sistema::remover_usuario(int id) {
    CelulaUsuario *aux1, *aux2;

    aux1 = primeiro;
    aux2 = primeiro->prox;
    while(aux2 != NULL){
        if (aux2->usuario.get_id() == id){
            aux1->prox = aux2->prox;
            delete aux2;
            tamanho--;
            std::cout << "OK: CONTA " << id << " REMOVIDA" << std::endl;
            if (aux1->prox == NULL){
                ultimo = aux1;
            }
            return;
        }
        aux1 = aux2;
        aux2 = aux2->prox;
    }

    imprimir_erro(id);
}

void Sistema::acessar_inbox(int id){
    CelulaUsuario* celula;
    
    celula = pesquisar_id(id);
    if (celula == NULL) {
        imprimir_erro(id);
        return;
    }
    
    Inbox* i; Email email;
    i = celula->usuario.get_inbox();
    if (i->get_tamanho() == 0) {
        std::cout << "CONSULTA " << id << ":" << " CAIXA DE ENTRADA VAZIA" << std::endl;
    }
    else {
        email = i->remover_comeco();
        std::cout << "CONSULTA " << id << ": " << email.get_texto() << std::endl;
    }
}

void Sistema::entregar_mensagem(CelulaUsuario *celula, Email email){
    Inbox* i;
    i = celula->usuario.get_inbox();
    i->inserir_prioridade(email);
    std::cout << "OK: MENSAGEM PARA " << celula->usuario.get_id() << " ENTREGUE" << std::endl;
}