#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "busca_largura.h" // reaproveita a definicao de GrafoLista/No

// Pilha (LIFO) para DFS iterativa
typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

Pilha *criar_pilha(int capacidade);
int pilha_vazia(Pilha *p);
void empilhar(Pilha *p, int valor);
int desempilhar(Pilha *p);
 
void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *tempo, int *descoberta, int *termino);
void dfs_iterativa(GrafoLista *g, int origem, int *visitado);
int contar_componentes(GrafoLista *g);
int tem_ciclo(GrafoLista *g);

#endif