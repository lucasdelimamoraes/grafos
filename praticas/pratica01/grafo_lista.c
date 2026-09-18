#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo_lista(int n) {
    GrafoLista *g = malloc(sizeof(GrafoLista)); // espaço na memoria para o grafo
    g->n = n; // tamanho do grafo = n (dado pelo usuário)
    g->adj = calloc(n, sizeof(No *)); // cria a lista encadeada de ponteiros com valor 0 (graças ao calloc)
    return g;
}

;

void inserir_aresta_lista(GrafoLista *g, int u, int v) {
    No *proximo = g->adj[u];
    No *no = (No *)malloc(sizeof(No));
    no->destino = v;
    no->proximo = proximo;
    g->adj[u] = no;
}

void remover_aresta_lista(GrafoLista *g, int u, int v) {
    if (u < 0 || u >= g->n || v < 0 || v >= g->n)
    return;
    remover_aresta_lista(&g->adj[u], v);
    remover_aresta_lista(&g->adj[v], u);
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