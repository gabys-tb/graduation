#include "ListaSignificado.h"

//construtor da classe
ListaSignificado::ListaSignificado() {
    tamanho = 0;
    primeiro = new (CelulaSignificado);
    ultimo = primeiro;
}

//deleta todas celulas da lista
void ListaSignificado::limpar() {
    CelulaSignificado *p;
    
    p = primeiro->prox;
    while (p!=NULL) {
        primeiro->prox = p->prox;
        delete p;
        p = primeiro->prox;
    }
    ultimo = primeiro;
    tamanho = 0;
}

//destrutor da classe
ListaSignificado::~ListaSignificado() {
    limpar();
    delete primeiro;
}

//insere significado no começo da lista
void ListaSignificado::inserir_comeco(std::string significado) {
    CelulaSignificado* nova = new (CelulaSignificado);

    nova->significado = significado;
    primeiro->prox = nova;
    tamanho++;
    if(nova->prox == NULL)
        ultimo = nova;
}

//insere significado na lista
void ListaSignificado::inserir(std::string significado) {
    if (tamanho == 0){
        inserir_comeco(significado);
        return;
    }
    else {
        CelulaSignificado *nova = new (CelulaSignificado);
        nova->significado = significado;
        ultimo->prox = nova;
        ultimo = nova;
        tamanho++;
    }
}

//escreve conteúdo das celulas no arquivo de saída
void ListaSignificado::escreve(std::ofstream *file){
    CelulaSignificado* aux = primeiro->prox;

    for (int i=1; i<=tamanho; i++) {
        *file << i << ". " << aux->significado << "\n";
        aux = aux->prox;
    }

}

//retorna o tamanho da lista
int ListaSignificado::get_tamanho(){
    return tamanho;
}