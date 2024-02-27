#include "Pilha.h"

//tira todos elementos da pilha
void Pilha::limpa(){
    while(!vazia())
        desempilha();   
}

//destrutor da classe
Pilha::~Pilha(){
    limpa();
}

//coloca elemento no topo da pilha
void Pilha::empilha(Index index){
    Celula *nova;
    nova = new Celula();
    nova->index = index;
    nova->prox = topo;
    topo = nova;
    tamanho++;
}

//tira elemento do topo da pilha
Index Pilha::desempilha(){
    Index aux; Celula *p;
    
    if(tamanho == 0) {throw "A pilha está vazia!";}
    
    aux = topo->index;
    p = topo;
    topo = topo->prox;
    delete p;
    tamanho--;
    
    return aux;
}
