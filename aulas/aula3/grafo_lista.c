#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo(int n) {
    GrafoLista *g = (GrafoLista *)malloc(sizeof(GrafoLista)); // arruma espaço na memoria para a matriz (os vetores de ponteiros)
    g->num_vertices = n;
    g->lista = (No *)malloc(sizeof(No)*n); // arruma espaço na memoria para os pontos do grafo, linhas da matriz que apontam para as relaçoes entre as arestas (contruidas como ponteiros)
    for(int i = 0; i < n; i++) { // arruma espaço na memória para cada int da matriz, pontos que avisam o estado da relaçao entre os pontos
        g->lista[i] = (No *)malloc(sizeof(No));
        g->lista[i] ->vertice = NULL;
        g->lista[i] ->proximo = NULL;
        // subistituto do calloc
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {
    // inserir v para u
    No *proximo = g->lista[u];
    No *no = (No *)malloc(sizeof(No));
    no->vertice = v;
    no->proximo = proximo;
    g->lista[u] = no; 

    // inserir u para v
    No *proximo = g->lista[v];
    No *no = (No *)malloc(sizeof(No));
    no->vertice = u;
    no->proximo = proximo;
    g->lista[v] = no;
}