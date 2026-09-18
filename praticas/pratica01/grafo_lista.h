#ifndef GRAFO_LISTA_h
#define GRAFO_LISTA_h

// Lista de Adjacência
typedef struct No {
    int destino; // vertice
    struct No *proximo;
} No;

typedef struct {
    int n; // numero do vertice
    No **adj; // lista
} GrafoLista;

GrafoLista *criar_grafo_lista(int n);
void inserir_aresta_lista(GrafoLista *g, int u, int v);
void remover_aresta_lista(GrafoLista *g, int u, int v);
int grau_lista(GrafoLista *g, int u);
int sao_adjacentes_lista(GrafoLista *g, int u, int v);
void liberar_grafo_lista(GrafoLista *g);

#endif