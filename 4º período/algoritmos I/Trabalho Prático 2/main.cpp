#include <iostream>
#include <unordered_map>
#include <string>
#include "algoritmos.hpp"


void inicializar_grafo(vector<pair<int, vector<int>>>* &grafo_original, vector<vector<pair<int, int>>>* &grafo_residual) {
    int U, J, E;
    scanf("%d %d %d ", &U, &J, &E);

    // aloca espaço para o grafo
    grafo_original = new vector<pair<int, vector<int>>>(U+J+1);

    // grau inicial de cade vértice é zero
    for(int i=0; i<U+J+1; i++) {
        (*grafo_original)[i].first = 0;
    }

    // aloca espaço para grafo residual
    grafo_residual = new vector<vector<pair<int, int>>>(U+J+2);
        
    // vertice fonte tem arestas para todos candidatos
    for (int i=1; i<U+1; i++){
        // arestas originais
        (*grafo_residual)[0].push_back(make_pair(i, 1));
        // arestas reversas
        (*grafo_residual)[i].push_back(make_pair(0, 0));
    }

    for (int i=U+1; i<(U+J+1); i++){
        // sumidouro tem arestas para todos empregos
        (*grafo_residual)[U+J+1].push_back(make_pair(i, 0));
        // todos em empregos tem arestas pro sumidouro
        (*grafo_residual)[i].push_back(make_pair(U+J+1, 1)); 
    }

    // map para guardar as strings e seus valores numéricos
    unordered_map<string, int> map(U+J);
    
    string u, j; // auxiliares
    // lê do terminal
    cin >> u >> j;
    
    // variáveis auxiliares
    int count_u = 1; int count_j = U+1;
    int ind_u; int ind_j;
    int contador = 0;
    // loop de leitura de arestas
    while(contador < E) {
        // se palavra não tiver sido mapeada, adiciona ao mapa
        if(map.find(u) == map.end()) {
            map[u] = count_u;
            ind_u = count_u;
            count_u++;
        }
        else{ //se já tiver, busca seu inidice no map
            ind_u = map.find(u)->second;
        }
        if(map.find(j) == map.end()) {
            map[j] = count_j;
            ind_j = count_j;
            count_j++;
        }
        else{
            ind_j = map.find(j)->second;
        }
        // adiciona aresta ao grafo 
        (*grafo_original)[ind_u].second.push_back(ind_j);
        // incrementa grau do vertice u
        (*grafo_original)[ind_u].first++;
        // incrementa grau do vertice j
        (*grafo_original)[ind_j].first++;
        // adiciona aresta ao grafo 
        (*grafo_original)[ind_j].second.push_back(ind_u);
        
        // adiciona arestas ao grafo residual
        (*grafo_residual)[ind_u].push_back(make_pair(ind_j, 1)); // aresta de fluxo
        (*grafo_residual)[ind_j].push_back(make_pair(ind_u, 0)); // aresta reversa

        // atualiza o contador
        contador ++;
        // lê nova linha
        cin >> u >> j;
    }   
}

int main(int argc, char const *argv[]) {
    // criando variaveis para os grafos
    vector<pair<int, vector<int>>> *grafo_original;
    vector<vector<pair<int, int>>> *grafo_residual;
    
    // inicializa os grafos
    inicializar_grafo(grafo_original, grafo_residual);
    
    // chama algoritmo guloso
    guloso(grafo_original);

    // chama algoritmo exato
    edmonds_karp(*grafo_residual);

    // desalocando memória dos grafos
    delete grafo_original;
    delete grafo_residual;

    return 0;
}
