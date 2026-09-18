#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo_lista(int n) {
    GrafoLista *g = (GrafoLista *)malloc(sizeof(GrafoLista)); // arruma espaço na memoria para a matriz (os vetores de ponteiros)
    g->n = n;
    g->adj = (No **)malloc(sizeof(No)*n); // arruma espaço na memoria para os pontos do grafo, linhas da matriz que apontam para as relaçoes entre as arestas (contruidas como ponteiros)
    for(int i = 0; i < n; i++) { // arruma espaço na memória para cada int da matriz, pontos que avisam o estado da relaçao entre os pontos
        g->adj[i] = NULL;
        // subistituto do calloc
    }
    return g;
}

void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    // inserir v para u
    No *proximo_u = g->adj[u];
    No *no_u = (No *)malloc(sizeof(No));
    no_u->destino = v;
    no_u->proximo = proximo_u;
    g->adj[u] = no_u; 

    // inserir u para v
    No *proximo_v = g->adj[v];
    No *no_v = (No *)malloc(sizeof(No));
    no_v->destino = u;
    no_v->proximo = proximo_v;
    g->adj[v] = no_v;
}

void remover_aresta_lista(GrafoLista *g, int u, int v) {
    if (u < 0 || u >= g->n || v < 0 || v >= g->n) return; // valores inválidos
 
    // remove v da lista de u
    No *atual = g->adj[u];
    No *anterior = NULL;
    while (atual != NULL) {
        if (atual->destino == v) {
            if (anterior == NULL) {
                g->adj[u] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }
 
    // remove u da lista de v
    atual = g->adj[v];
    anterior = NULL;
    while (atual != NULL) {
        if (atual->destino == u) {
            if (anterior == NULL) {
                g->adj[v] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

int grau_lista(GrafoLista *g, int u) { //quantas conecoes esse vertice faz?
    if (u < 0 || u >= g->n) return -1;
    int grau = 0;
    No *atual = g->adj[u];
    while(atual) {
        grau++;
        atual = atual->proximo;
    }
    return grau;
}

int sao_adjacentes_lista(GrafoLista *g, int u, int v) {
    if (u < 0 || u >= g->n || v < 0 || v >= g->n) return -1;
    No *atual = g->adj[u];
    while (atual) {
        if (atual->destino == v) return 1;
        atual = atual->proximo;
    }
    return 0;
}

void liberar_grafo_lista(GrafoLista *g) {
    if (!g) return;
    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];
        while (atual) {
            No *tmp = atual;
            atual = atual->proximo;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}