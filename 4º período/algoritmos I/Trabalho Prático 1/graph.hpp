#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <vector>
#include "stdio.h"
using namespace std;
#define INF 0x3f3f3f3f


// estrutura auxiliar a fila de prioridades do djikstra
struct Vertice {
    int vertice = 0;
    int distancia = 0;
};

// comparador para heap minimo
struct ComparadorDistancia {
    bool operator()(const Vertice& v1, const Vertice& v2) const {
        return v1.distancia > v2.distancia;
    }
};

// classe usada na lista de adjacencias
class VerticeAdjacente {
    private:
        int vertice = 0;
        int peso_aresta = 0;
    public: 
        VerticeAdjacente(int a, int b){
            vertice = a;
            peso_aresta = b;
        }
        VerticeAdjacente() = default; // definindo o construtor padrão
    friend class Grafo;
};

// classe grafo
class Grafo {
    private:
        vector<vector<VerticeAdjacente>> grafo; // lista de adjacencias
        int n = 0; // numero de vertices
        int N = 0; // vertices originais
    public:
        Grafo(int a) {
            grafo.resize(a * 6 + 3);
            n = a * 6 + 3;
            N = a;
        }
        int par(int x);
        int impar(int x);
        void add_vertice(int v1, int v2, int w);
        int peso_aresta(int u, int v);
        void djikstra();
};


#endif // GRAPH_HPP