#include "graph.hpp"
#include <iostream>
#include <queue>

using namespace std;

// converte valor x em par
int Grafo::par(int x) {
    return x * 6 + 2;
}

// converte valor x em ímpar
int Grafo::impar(int x) {
    return x * 6 + 1;
}

// adiciona vértices ao grafo
void Grafo::add_vertice(int v1, int v2, int w) {
    //adicionando vertices ao grafo
    grafo[par(v1)].push_back(VerticeAdjacente(impar(v2), w));
    grafo[impar(v2)].push_back(VerticeAdjacente(par(v1), w));
    grafo[impar(v1)].push_back(VerticeAdjacente(par(v2), w));
    grafo[par(v2)].push_back(VerticeAdjacente(impar(v1), w));
}

// retorna o peso da aresta entre vértice u e v
int Grafo::peso_aresta(int u, int v){
    int n = grafo[u].size();
    for (int i=0; i<n; i++){
        if (grafo[u][i].vertice == v){
            return grafo[u][i].peso_aresta;
        }
    }
    return 0;
}

// algorimo de djikstra
void Grafo::djikstra() {
    if (n == 0){
        printf("Grafo vazio \n");
        return;
    }

    // vetor de distancias inicializado com infinito
    vector<int> d(n, INF);

    // vetor de vertices visitados
    vector<int> v(n, 0);

    // declarando fila de prioridades
    priority_queue<Vertice, std::vector<Vertice>, ComparadorDistancia> fila;

    // adicionando vertice de origem a fila
    Vertice a;
    d[par(1)] = 0;
    a.vertice = par(1);
    a.distancia = d[par(1)];
    fila.push(a);

    // enquanto fila não está vazia, percorre o grafo e atualiza o vetor de distancias
    while(fila.empty() == false){
        // vertice u sai da fila
        Vertice u = fila.top();
        fila.pop();
        int n_vizinhos = grafo[u.vertice].size();

        Vertice b;
        // percorre os vizinhos de u
        for(int i=0; i<n_vizinhos; i++) {
            // vizinho de u
            int w = (grafo[u.vertice][i]).vertice;
            int d_nova = u.distancia + peso_aresta(u.vertice, w);
            // verifica se é possível melhorar a distancia
            if(d[w] > d_nova){
                // atualiza distancia
                d[w]= d_nova;
                //add vertice a fila de prioridade
                b.vertice = w;
                b.distancia = d_nova;
                fila.push(b);
            }
        }

    }

    
    if(d[par(N)] == INF){d[par(N)] = -1;}
    printf("%d\n", d[par(N)]); 

}

