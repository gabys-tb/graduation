#include "MetodosOrdenacao.h"

//função partição auxiliar ao quicksort tradicional
void InfoOrdenacao::particao(int esq, int dir, int *i, int *j, Registro *A) {
    Registro x;
    *i = esq; *j = dir;
    x = A[(*i + *j)/2]; /* obtem o pivo x */
    LEMEMLOG((long int)(&A[(*i+*j)/2]), sizeof(Registro), 0);
    num_copias++;
    do {
        while (x.chave > A[*i].chave) {
            (*i)++; 
            num_comp++;
            LEMEMLOG((long int)(&A[*i]), sizeof(Registro), 0);
        } 
        num_comp++;
        LEMEMLOG((long int)(&A[*i]), sizeof(Registro), 0);

        while (x.chave < A[*j].chave) {
            (*j)--; 
            num_comp++;
            LEMEMLOG((long int)(&A[*j]), sizeof(Registro), 0);
        }
        num_comp++;
        LEMEMLOG((long int)(&A[*j]), sizeof(Registro), 0);

        if (*i <= *j) {
            troca(&A[*i], &A[*j]);
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

//função ordena
void InfoOrdenacao::ordena(int esq, int dir, Registro *A) { 
    int i, j;
    particao(esq, dir, &i, &j, A);
    if (esq < j) ordena(esq, j, A);
    if (i < dir) ordena(i, dir, A);
}

//quicksort tradicional
void InfoOrdenacao::quick_sort_recursivo(Registro *A, int n) {
    ordena(0, n-1, A);
}

//gera números aleatórios no intervalo [esq, dir];
int InfoOrdenacao::rand_pos(int esq, int dir){
    return esq + (rand() % (dir-esq+1));
}

//obtém a mediana de k posições aleatórias do vetor
Registro InfoOrdenacao::mediana(Registro *A, int esq, int dir, int k) {
    Registro aux; 
    int p;
    
    /*se vetor tiver tamanho menor q k, 
    pega a mediana da forma padrão*/
    if (dir-esq < k){
        LEMEMLOG((long int)(&A[(esq+dir)/2]), sizeof(Registro), 0);
        return A[(esq + dir) / 2];
    }

    Registro * lista = new Registro[k];
    for(int i=0; i<k; i++) {
        p = rand_pos(esq, dir); 
        lista[i]=A[p];
        LEMEMLOG((long int)(&A[p]), sizeof(Registro), 0);
        num_copias++;
    }

    //ordenando o vetor lista
    quick_sort_recursivo(lista, k);
    
    aux = lista[k/2];
    num_copias++;

    delete [] lista; 
    lista = NULL;

    return aux;
}

//partição auxiliar ao quicksort mediana
void InfoOrdenacao::particao_mediana(int esq, int dir, int *i, int *j, Registro *A, int k) {
    Registro x;
    *i = esq; *j = dir;
    x = mediana(A, esq, dir, k); /* obtem o pivo x */
    num_copias++;
    do {
        while (x.chave > A[*i].chave) {
            (*i)++; 
            num_comp++;
            LEMEMLOG((long int)(&A[*i]), sizeof(Registro), 0);
        } 
        num_comp++;
        LEMEMLOG((long int)(&A[*i]), sizeof(Registro), 0);

        while (x.chave < A[*j].chave) {
            (*j)--; 
            num_comp++;
            LEMEMLOG((long int)(&A[*j]), sizeof(Registro), 0);
        }
        num_comp++;
        LEMEMLOG((long int)(&A[*j]), sizeof(Registro), 0);
        if (*i <= *j) {
            troca(&A[*i], &A[*j]);
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

//função ordena auxiliar ao quicksort mediana
void InfoOrdenacao::ordena_mediana(int esq, int dir, Registro *A, int k) { 
    int i, j;
    particao_mediana(esq, dir, &i, &j, A, k);
    if (esq < j) ordena_mediana(esq, j, A, k);
    if (i < dir) ordena_mediana(i, dir, A, k);
}

//quicksort que escolhe mediana de k elementos como pivo
void InfoOrdenacao::quick_sort_mediana(Registro *A, int n, int k) {
    ordena_mediana(0, n-1, A, k);
}

//troca os valores das posições passadas
void InfoOrdenacao::troca(Registro * a, Registro * b) {
    Registro aux;
    aux = *a; 
    *a = *b;
    *b = aux;
    LEMEMLOG((long int)(&(*a)), sizeof(Registro), 0);
    LEMEMLOG((long int)(&(*b)), sizeof(Registro), 0);
    ESCREVEMEMLOG((long int)(&(*a)), sizeof(Registro), 0);
    ESCREVEMEMLOG((long int)(&(*b)), sizeof(Registro), 0);
    num_copias+=3;
}

//método de seleção
void InfoOrdenacao::selecao(Registro * A, int esq, int dir) {
    int i, j, min;

    for (i = esq; i <= dir; i++) {
        min = i;
        for (j = i + 1 ; j <= dir; j++) {
            if (A[j].chave < A[min].chave) {min = j;}
            num_comp++;
            LEMEMLOG((long int)(&(A[j])), sizeof(Registro), 0);
            LEMEMLOG((long int)(&(A[min])), sizeof(Registro), 0);
        }
        troca(&A[i], &A[min]);
    }
}

//função ordena 
void InfoOrdenacao::ordena_selecao(int esq, int dir, Registro *A, int m) { 
    int i, j;
    if((dir-esq) < m) {selecao(A, esq, dir);}
    else {
        particao(esq, dir, &i, &j, A);
        if (esq < j) ordena_selecao(esq, j, A, m);
        if (i < dir) ordena_selecao(i, dir, A, m);
    }
}

//quicksort com selecao para vetores com tamnho menor ou igual a m
void InfoOrdenacao::quick_sort_selecao(Registro *A, int n, int m) {
    ordena_selecao(0, n-1, A, m);
}

//processa primeiro a partição direita
void InfoOrdenacao::quick_sort_nao_recursivo(Registro *A, int n) {
    Pilha pilha;
    Index index; // campos esq e dir
    int esq, dir, i, j;

    esq = 0;
    dir = n-1;
    index.dir = dir;
    index.esq = esq;
    pilha.empilha(index);
    do {
        if (dir > esq) {
            particao(esq, dir, &i, &j, A);
            index.dir = j;
            index.esq = esq;
            pilha.empilha(index);
            esq = i;
        }
        else {
            index = pilha.desempilha();
            dir = index.dir;
            esq = index.esq;
        }
    } while (!pilha.vazia());
}

//processa primeiro a menor partiçao
void InfoOrdenacao::quick_sort_empilha_inteligente(Registro *A, int n) {
    Pilha pilha;
    Index item; 
    int esq, dir, i, j;

    esq = 0;
    dir = n-1;
    item.dir = dir;
    item.esq = esq;
    pilha.empilha(item);
    do {
        if (dir > esq) {
            particao (esq, dir, &i, &j, A);
            if (j-esq > dir-i) {
                item.dir = j;
                item.esq = esq;
                pilha.empilha(item);
                esq = i;
            }
            else {
                item.esq = i;
                item.dir = dir;
                pilha.empilha(item);
                dir = j;
            }
        }
        else {
            item = pilha.desempilha();
            dir = item.dir;
            esq = item.esq;
        }
    } while (!pilha.vazia());
}


//cria dois array menores auxiliares para ordena o vetor A 
void InfoOrdenacao::merge(Registro *A, int esq, int meio, int dir) {
  
    int n_esq = meio - esq + 1;
    int n_dir = dir - meio;

    Registro *vet_esq, *vet_dir;

    vet_esq = new Registro[n_esq];
    vet_dir = new Registro[n_dir];

    for (int i = 0; i < n_esq; i++) {vet_esq[i] = A[esq + i]; num_copias++;}
    for (int j = 0; j < n_dir; j++) {vet_dir[j] = A[meio + 1 + j]; num_copias++;}

    int i, j, k;
    i = 0;
    j = 0;
    k = esq;

    while (i < n_esq && j < n_dir) {
        if (vet_esq[i].chave <= vet_dir[j].chave) {
            A[k] = vet_esq[i];
            i++;
            num_copias++;
            num_comp++;
        } 
        else {
            A[k] = vet_dir[j];
            j++;
            num_copias++;
            num_comp++;
        }
        k++;
    }

    while (i < n_esq) {
        A[k] = vet_esq[i];
        i++;
        k++;
        num_copias++;
    }

    while (j < n_dir) {
        A[k] = vet_dir[j];
        j++;
        k++;
        num_copias++;
    }

    delete [] vet_esq;
    delete [] vet_dir;
}    

/*divide o array em dois arrays menores, 
ordena cada um e os junta */
void InfoOrdenacao::merge_sort(Registro *A, int esq, int dir) {
    if (esq < dir) {
        
        int meio = (esq+dir)/ 2;

        merge_sort(A, esq, meio);
        merge_sort(A, meio + 1, dir);
        merge(A, esq, meio, dir);
    }
}

//coloca na posição correta as folhas e nós 
void InfoOrdenacao::refaz(Registro *A, int esq, int dir){
    int i, j;
    Registro x;

    i = esq; /* nó pai */
    j = i * 2 + 1;
    
    x = A[i];
    num_copias++;
    while (j <= dir){  //dir é ultima posicao acessivel
        if (j < dir) {
            if (A[j].chave < A[j+1].chave) {num_comp++; j++;}
            num_comp++;
        }
        if (x.chave >= A[j].chave) {num_comp++; break;}
        num_comp++;

        A[i] = A[j];
        i = j;
        j = i * 2 + 1;
        num_copias++;

    }
    A[i] = x;
    num_copias++;
}

//constrói o heap
void InfoOrdenacao::constroi(Registro *A, int n) {
    int esq;
    esq = (n / 2);
    while (esq > 0) {
        esq--;
        refaz(A, esq, n-1);
    }
}

void InfoOrdenacao::heap_sort(Registro *A, int n) {
    int esq, dir;

    constroi(A, n); 
    esq = 0; dir = n-1;
    
    while (dir > 0) { /* ordena o vetor */
        troca(&A[0], &A[dir]);
        dir--;
        refaz(A, esq, dir);
    }
}
