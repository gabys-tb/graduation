#ifndef ARVORE_H
#define ARVORE_H
#include "Estruturas.h"
#include "ListaSignificado.h"
#include "Memlog.h"

class Node {
	private:
		Verbete v;
		int altura = 1;
		Node *esq = NULL;
		Node *dir = NULL;
		Node *pai = NULL;

		void escreve(std::ofstream *file) {
			*file << v.verbete << "\n";
			v.lista.escreve(file);
		}
			
	friend class DicionarioArvore;
};

class DicionarioArvore {
	public:
		Node *raiz = NULL;
		~DicionarioArvore();
		void limpar(Node *node);
		int max(int a1, int a2);
		int altura(Node *&node);
		int get_fb(Node *&node);
		void balanceia(Node *&node);
		void rotacao_direita(Node* &node);
		void rotacao_esquerda(Node* &node);
		void insere(Entrada p);
		void insere_recursivo(Node* &node, Entrada p);
		//int sem_significado(Node * node, std::string v);
		void escreve(std::ofstream *file);
		void escreve_in_ordem(std::ofstream *file, Node *&node);
		std::string remove_nodes(Node *&node);
		void antecessor(Node *&q, Node* r);
		void atualiza();
};


#endif