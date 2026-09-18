#include "grafo_lista.h"

int pilha[10];
int visitado[10];
int topo = 0;

void dfs(int u, int *p) {
    visitado[u] = 1;
    p[topo++] = u;
    printf("Empilha %i, visita %i\n", u+1, u+1);
    No *no = g->listas[u];
    while (no != NULL){ // percorre checando se já visitou
        int v = no->proximo;
        if (!visitado[v]) dfs(v, p);
        no = no->proximo;
    } 
    topo--;
    printf("Desempilha %i\n", u+1);
}