#ifndef ALGORITMOS_H
#define ALGORITMOS_H
#include "stdio.h"
#include <vector>
#include <iostream>
#include <utility>
#include <queue>
#define INF 0x3f3f3f3f
using namespace std;

// comparador para heap minimo
struct ComparadorGrau {
    bool operator()(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
        return p1.first > p2.first;  // ordena de acordo com o grau
    }
};

// algoritmo guloso para pareamento máximo
void guloso(vector<pair<int, vector<int>>>* &grafo_original) {
    int V = (*grafo_original).size();
    
    // declarando fila de prioridades
    priority_queue<pair<int, int>, vector<std::pair<int, int>>, ComparadorGrau> heap_minimo;

    for(int i=1; i<V; i++) {
        heap_minimo.push(make_pair((*grafo_original)[i].first, i));
    }

    // vetor de vertices visitados
    vector<int> visitado(V, 0);

    int v; int min = INF; int u;
    // conta arestas
    int count = 0;
    while(!heap_minimo.empty()) {
        // pega vertice de menor grau
        v = heap_minimo.top().second;
        heap_minimo.pop();

        if(!visitado[v]){
            int w = -1;
            min = INF;
            // dentre os vertices vizinhos de v, será selecionada a aresta para o vizinho de v menor grau
            for(int i=1; i<int((*grafo_original)[v].second.size()); i++) {
                u = (*grafo_original)[v].second[i];

                // se ja visitou u, passa pro prox vizinho
                if(visitado[u]){continue;}

                // busca vizinho de menor grau  min
                if (min > (*grafo_original)[u].first){ 
                    min = (*grafo_original)[u].first;
                    w = u;
                }
            }
            
            // verifica se aresta válida foi selecionada
            if(w != -1){ 
                visitado[v] = 1; // marca vertices da aresta
                visitado[w] = 1;
                // incrementa contador de arestas
                count++;
            }

        }
    }

    printf("Guloso: %d\n", count);
}

// algoritmo de busca em largura
bool bfs(vector<vector<pair<int,int>>> &grafo_residual, vector<int> &mae) {
    int t = grafo_residual.size()-1;

    vector<int> visitado(t+1, 0);
    queue<int> fila;
    
    // adicionando fonte a fila
    fila.push(0);
    // a fonte não tem mãe
    mae[0] = -1;
    visitado[0] = 1;
    mae[t] = -2;

    int v; int d_v;
    // enquanto fila não estiver vazia, executa loop
    while(!fila.empty()) {
        v = fila.front();
        fila.pop();
        
        d_v = grafo_residual[v].size();
        int w; 
        // percorrendo os vizinhos de v
        for(int i=0; i<d_v; i++) {
            w = grafo_residual[v][i].first;
            // se vizinho não foi visitado ainda e pode passar fluxo, é adicionando a caminho aumentante
            if(!visitado[w] && grafo_residual[v][i].second > 0){
                 // se vértice vizinho é sumidouro, bfs acaba
                if (w == t) {
                    mae[w] = v;
                    break;            
                }
                fila.push(w);
                mae[w] = v;
                visitado[w] = 1;
            }
        }
    }
    
    return (mae[t] != -2);
}

// algoritmo de edmonds-karp
void edmonds_karp(vector<vector<pair<int,int>>> &grafo_residual) {
    int t = grafo_residual.size()-1;
    
    // guarda vertices do caminho aumentante
    vector<int> mae(grafo_residual.size());
    
    // fluxo máximo
    int capacidade_residual= 1;
    int fluxo_maximo = 0;
    // auxiliares
    int u; int tam; int v;

    // roda enquanto houver caminho aumentante
    while(bfs(grafo_residual, mae)) {
        // incrementa o fluxo máximo
        fluxo_maximo ++;
        
        v = t;
        u = mae[v];
        // atualiza as capacidades das arestas
        while(u!=-1) {
            tam = grafo_residual[u].size();

            // percorre vizinhos de u até achar v
            for(int j=0; j<tam; j++) {
                if(grafo_residual[u][j].first == v) {
                    grafo_residual[u][j].second -= capacidade_residual; // diminui capacidade residual

                    // percorre os vizinhos de v até achar u
                    for(int a=0; a<int(grafo_residual[v].size()); a++){
                        if(grafo_residual[v][a].first == u) {
                            grafo_residual[v][a].second += capacidade_residual; // aumenta capacidade residual
                        }
                    }
                }
            }
            // atualiza v
            v = u;
            u = mae[v];
        }  
    }
    printf("Exato: %d\n", fluxo_maximo);
}

#endif