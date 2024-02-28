#include "DicionarioHash.h"

//construtor da classe
DicionarioHash::DicionarioHash(int n){
    m = 3*n;
    vazio = new int[m];

    for (int i=0; i<m; i++){
        vazio[i] = 1;
    }

    tabela = new Verbete[m];
}

//destrutor da classe
DicionarioHash::~DicionarioHash(){
    delete [] vazio;
    delete [] tabela;
}

//retorna um posição da tabela de acordo com a entrada
int DicionarioHash::f_hash(std::string p){
    int soma = 0;
    for (int i=0; i<(int)p.length(); i++) {
        soma +=  p[i];
    }

    return soma % m;
}

//insere verbete na tabela
void DicionarioHash::insere(Entrada p){
    //obtem posicao 
    int pos = f_hash(p.verbete);
    int i = 0;

    LEMEMLOG((long int)(&(tabela[pos])), sizeof(Verbete), 0);
    //se posicao estiver ocupada, percorre a tabela seuqnecialmente até achar uma posição vazia
    while ( (i < m) && p.verbete != tabela[(pos+i)%m].verbete) {
        LEMEMLOG((long int)(&(tabela[(pos+i)%m])), sizeof(Verbete), 0);
        if (vazio[(pos+i)%m]) {
            break;
        }
        i++;
    }

    erroAssert((i != m), "tabela está cheia!");
    
    //insere vervete na posição
    tabela[(pos+i)%m].verbete = p.verbete;
    if (p.significado != "") { tabela[(pos+i)%m].lista.inserir(p.significado); }
    vazio[(pos+i)%m] = 0;
    ESCREVEMEMLOG((long int)(&(tabela[(pos+i)%m])), sizeof(Verbete), 0);
}

//coloca com status vazio verbetes que possuem significado
void DicionarioHash::remove_verbetes() {
    for(int i=0; i<m; i++) {
        LEMEMLOG((long int)(&(tabela[i])), sizeof(Verbete), 0);
        if(tabela[i].lista.get_tamanho() != 0){
            ESCREVEMEMLOG((long int)(&(vazio[i])), sizeof(Verbete), 0);
            vazio[i] = 1;
        }
    }
}

//ordena e escreve dicionario no aquivo file
void DicionarioHash::escreve(std::ofstream *file){
    Info * vetor_aux;

    //tabela auxiliar 
    vetor_aux = new Info[m/3];
    int j = 0;

    /* guarda o tamanho de posições 
    ocupadas no vetor */
    int count = 0;

    //percorre tabela hash 
    for (int i=0; i<(m/3); i++){
        while(vazio[j]){
            LEMEMLOG((long int)(&(vazio[j])), sizeof(Verbete), 0);
            j++;
        } 

        if(j >= m){break;}


        vetor_aux[i].verbete = tabela[j].verbete;
        vetor_aux[i].pos = j;

        LEMEMLOG((long int)(&(tabela[vetor_aux[i].pos])), sizeof(Verbete), 0);

        j++;
        count++;
    }

    quick_sort(vetor_aux, count);
    
    //escreve dicionario no arquivo de saida
    for(int i=0; i<count; i++){
        *file << vetor_aux[i].verbete << "\n";
        tabela[vetor_aux[i].pos].lista.escreve(file);
        LEMEMLOG((long int)(&(tabela[vetor_aux[i].pos])), sizeof(Verbete), 0);
    }

    delete [] vetor_aux;
}


//função partição auxiliar ao quicksort 
void DicionarioHash::particao(int esq, int dir, int *i, int *j, Info *A) {
    std::string x;
    *i = esq; *j = dir;
    x = A[(*i + *j)/2].verbete; //obtem pivo
    
    do{ //percorre o vetor e compara elementos com pivo
        while (x > A[*i].verbete) {(*i)++;} 
        while (x < A[*j].verbete) {(*j)--;}

        if (*i <= *j) {
            Info aux;
            aux = A[*i];
            A[*i] = A[*j];
            A[*j] = aux;
            (*i)++; (*j)--;
           
        }
    } while (*i <= *j);

}

//função ordena
void DicionarioHash::ordena(int esq, int dir, Info *A) { 
    int i, j;
    particao(esq, dir, &i, &j, A);
    if (esq < j) ordena(esq, j, A);
    if (i < dir) ordena(i, dir, A);
}

//quicksort tradicional
void DicionarioHash::quick_sort(Info *A, int n) {
    ordena(0, n-1, A);
}
