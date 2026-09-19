#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#define MAX_VERTICES 100

//implicito lista para busca em largura
typedef struct No
{
    int vertice;
    struct No *proximo;
} No;
 
typedef struct
{
    No **lista;
    int num_vertices;
} GrafoLista;
 
//funcoes necessarias
GrafoLista *criar_grafo(int n);
void adicionar_aresta(GrafoLista *g, int u, int v);
void adicionar_arco(GrafoLista *g, int u, int v);
void imprimir_grafo(GrafoLista *g);

// Fila (FIFO) para BFS
typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

Fila *criar_fila(int capacidade);
int fila_vazia(Fila *f);
void enfileirar(Fila *f, int valor);
int desenfileirar(Fila *f);
 
void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int eh_bipartido(GrafoLista *g);

#endif