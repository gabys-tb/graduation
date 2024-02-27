#include <iostream>
#include "graph.hpp"

// lê entrada do usuario e add vertices e arestas ao grafo g
void inicializar_grafo(Grafo& g){
    int x1, x2, d, c;
    c = scanf("%d %d %d ", &x1, &x2, &d);
    while(c > 0) {
        if (d%2 == 0) {g.add_vertice(x1, x2, d);}
        c = scanf("%d %d %d ", &x1, &x2, &d);
    }
}

// função principal
int main(int argc, char const *argv[]) {
    int n, a;
    // le numero de vertices e arestas 
    scanf("%d %d", &n, &a);
    
    Grafo * g = new Grafo(n);

    inicializar_grafo(*g);
    g->djikstra();
    return 0;
}