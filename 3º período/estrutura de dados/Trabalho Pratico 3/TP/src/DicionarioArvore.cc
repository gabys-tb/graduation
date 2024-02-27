#include "DicionarioArvore.h"

//percorre a árvore, desalocando a memória de cada nó
void DicionarioArvore::limpar(Node *node) {
    if (node == NULL) { return;}
 
    limpar(node->esq);
    limpar(node->dir);
	
    delete node;
}

//destrutor da classe
DicionarioArvore::~DicionarioArvore(){
	limpar(raiz);
}

//retorna o maior de dois inteiros
int DicionarioArvore::max(int a1, int a2) {
    if (a1 > a2) {return a1;}
    else {return a2;}
}

//retorna a altura do nó
int DicionarioArvore::altura(Node *&node) {
	LEMEMLOG((long int)(&(node)), sizeof(Node), 0);

	if (node == NULL) { return 0; }
	return node->altura;
}

//retorna diferença de altura entre nó direito e esquerdo
int DicionarioArvore::get_fb(Node *&node) {
	if (node == NULL) {return 0;}
	int fb = altura(node->dir) - altura(node->esq);

	return fb;
}

//rotaciona o nó para a direita
void DicionarioArvore::rotacao_direita(Node *&node) {
	Node *aux;

	//rotacionando
	aux = node->esq;
	node->esq = node->esq->dir;
	aux->dir = node;

	ESCREVEMEMLOG((long int)(&(node->esq)), sizeof(Node), 0);

	//atualizando alturas
	node->altura = max(altura(node->esq), altura(node->dir)) + 1;
	aux->altura = max(altura(aux->esq), altura(aux->dir)) + 1;

	//atualiza os pais
	aux->pai = node->pai;
	if(node->esq != NULL) {node->esq->pai = node;}
	node->pai = aux;
	
	ESCREVEMEMLOG((long int)(&(node->pai)), sizeof(Node), 0);

	//atualiza o avô
	node = aux;
}

//rotaciona o nó para a esquerda
void DicionarioArvore::rotacao_esquerda(Node *&node) {
	Node *aux;

	//rotacionando
	aux = node->dir;
	node->dir = node->dir->esq;
	aux->esq = node;

	ESCREVEMEMLOG((long int)(&(node->dir)), sizeof(Node), 0);

	//atualizando alturas
	node->altura = max(altura(node->esq), altura(node->dir)) + 1;
	aux->altura = max(altura(aux->esq), altura(aux->dir)) + 1;

	//atualiza os pais
	aux->pai = node->pai;
	if(node->dir != NULL) {node->dir->pai = node;}
	node->pai = aux;

	ESCREVEMEMLOG((long int)(&(node->pai)), sizeof(Node), 0);

	//atualiza o avô
	node = aux;
}

void DicionarioArvore::balanceia(Node *&node){
	//obtendo FB
	int fb_node = get_fb(node);
	
	//verifica desbalanceamento para esquerda
	if (fb_node < -1) { 
		int fb_esq = get_fb(node->esq);
		if (fb_esq < 0) { //caso esq esq
			rotacao_direita(node);
		} 
		else if (fb_esq > 0) { //caso esq dir
			rotacao_esquerda(node->esq);
			rotacao_direita(node);
		}
  	}
	//verifica desbalanceamento para direita
  	if (fb_node > 1) { 
		int fb_dir = get_fb(node->dir);
		if (fb_dir > 0) { //caso dir dir
			rotacao_esquerda(node);
		} 
		else if (fb_dir < 0) { //caso dir esq
			rotacao_direita(node->dir);
			rotacao_esquerda(node);
		}
	}
}

//chama insere_recursivo para a raiz
void DicionarioArvore::insere(Entrada p){
	insere_recursivo(raiz, p);
}

//percorre a árvore e insere o nó na posição correta de acordo com o verbete
void DicionarioArvore::insere_recursivo(Node *&node, Entrada p) { 
	//verifica se nó é folha
	if(node == NULL) {
		node = new Node;
		node->v.verbete = p.verbete;
		ESCREVEMEMLOG((long int)(&(node)), sizeof(Node), 0);
		if(!p.significado.empty()) {node->v.lista.inserir(p.significado);}
		return;
	}
	//percorre a árvore
	LEMEMLOG((long int)(&(node)), sizeof(Node), 0);
	if(p.verbete < node->v.verbete) {
		insere_recursivo(node->esq, p);
		node->esq->pai = node;
	}
	else if(p.verbete > node->v.verbete){
		LEMEMLOG((long int)(&(node)), sizeof(Node), 0);
		insere_recursivo(node->dir, p);
		node->dir->pai = node;
	}
	else if (p.significado != ""){ //se o verbete já está no dicionário, adiciona o novo significado a lista
		node->v.lista.inserir(p.significado);
		LEMEMLOG((long int)(&(node)), sizeof(Node), 0);
		LEMEMLOG((long int)(&(node)), sizeof(Node), 0);
		return;
	}
	//atualizando altura do pai
	node->altura = 1 + max(altura(node->esq), altura(node->dir));

	//balanceia a árvore
	balanceia(node);
}

//escreve dicionario no arq de saída
void DicionarioArvore::escreve(std::ofstream *file){
	escreve_in_ordem(file, raiz);
}

//escreve no arquivo fazendo um caminhamento "em ordem"
void DicionarioArvore::escreve_in_ordem(std::ofstream *file, Node *&node){
	if (node != NULL) {
		escreve_in_ordem(file, node->esq);

		node->escreve(file);
		LEMEMLOG((long int)(&(node)), sizeof(Node), 0);
		
		escreve_in_ordem(file, node->dir);
	}
}

//obtem o antecessor de q, e deleta q
void DicionarioArvore::antecessor(Node *&q, Node* r) {
	//faz chamadas recursivas até encontrar o antecessor
	if(r->dir != NULL) {
		antecessor(q, r->dir);
		return;
	}

	Node * aux;
	//pai do antecessor
	aux = r->pai;

	//se o pai n for o nó a ser deletado, atualiza o nó direito
	if(aux != q) {aux->dir = r->esq;}
	if (r->esq != NULL){r->esq->pai = aux;}

	//percorre a árvore do antecessor até q
	while(aux != q){
		
		//atualizando altura do pai
		aux->altura = 1 + max(altura(aux->esq), altura(aux->dir));

		//balanceia a árvore
		balanceia(aux);

		//atualiza o avô
		if (aux->pai == q) {q->esq = aux;}
		else {aux->pai->dir = aux;}
		aux = aux->pai;
	}

	//atualiza atributos do antecessor
	r->dir = q->dir;

	/*se o antecessor é o filho da esquerda do nó a ser deletado
	entao ele aponta pra */
	if (r->v.verbete != q->esq->v.verbete) {
		r->esq = q->esq;
		//faz filhos do nó deletado apontarem pro novo pai
		q->esq->pai = r;
		q->dir->pai = r;
	}
	else {   /*se o antecessor for o nó a esquerda de q */
		if(r->esq != NULL ) {r->esq->pai = r;}
		q->dir->pai = r;
	}

	//atualiza pai do antecessor
	r->pai = q->pai;
	

	Node *f;
	f = q;
	q = r;
	ESCREVEMEMLOG((long int)(&(q)), sizeof(Node), 0);

	//deleta a memória alocada em q
	delete(f);
}

//deleta nós com significado
std::string DicionarioArvore::remove_nodes(Node *&node) {
	Node * aux;
	std::string v = "0";
	if (node == NULL) {
		return v;
	}

	LEMEMLOG((long int)(&(node)), sizeof(Node), 0);
	if (node->v.lista.get_tamanho() == 0){ //faz um caminhamento em ordem pela árvore
		v = remove_nodes(node->esq);
		if(v == "0") {v = remove_nodes(node->dir);} 
	}
	else {
		if (node->dir == NULL) { //nó tem um ou nenhum filho
			aux = node;
			//guarda o verbete do nó a ser deletado
			v = node->v.verbete;
			//atualiza atributos
			if (node->esq != NULL) {node->esq->pai = node->pai;}
			node = node->esq;
			ESCREVEMEMLOG((long int)(&(node)), sizeof(Node), 0);
		
			delete aux;
		}
		else if(node->esq == NULL) { //nó tem um filho
			aux = node;
			//guarda o verbete do nó a ser deletado
			v = node->v.verbete;

			//atualiza atributos
			node->dir->pai = node->pai;
			node = node->dir;
			ESCREVEMEMLOG((long int)(&(node)), sizeof(Node), 0);

			delete aux;
		}
		else { //nó tem os dois filhos
			v = node->v.verbete;
			antecessor(node, node->esq);
		}	
	}

	if(node != NULL) { //atualizando altura do pai
		node->altura = 1 + max(altura(node->esq), altura(node->dir));
		//balanceia a árvore
		balanceia(node);
	}
	
	return v;
}

//deleta todos verbetes com significado da árvore
void DicionarioArvore::atualiza(){
	std::string c;
	do{
		c = remove_nodes(raiz);
	} while (c != "0");
}