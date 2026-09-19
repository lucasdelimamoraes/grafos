#include "busca_largura.h"

#include <stdio.h>
#include <stdlib.h>


GrafoLista *criar_grafo(int n)
{
    GrafoLista *g = malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->lista = malloc(n * sizeof(No *));
 
    for (int i = 0; i < n; i++)
        g->lista[i] = NULL;
 
    return g;
}
 
void adicionar_arco(GrafoLista *g, int u, int v)
{
    No *novo = malloc(sizeof(No));
    novo->vertice = v;
    novo->proximo = g->lista[u];
    g->lista[u] = novo;
}
 
void adicionar_aresta(GrafoLista *g, int u, int v)
{
    adicionar_arco(g, u, v);
    adicionar_arco(g, v, u);
}
 
void imprimir_grafo(GrafoLista *g)
{
    for (int i = 0; i < g->num_vertices; i++)
    {
        printf("%i:", i + 1);
        No *no = g->lista[i];
        while (no != NULL)
        {
            printf(" -> %i", no->vertice + 1);
            no = no->proximo;
        }
        printf("\n");
    }
}
 
Fila *criar_fila(int capacidade)
{
    Fila *f = malloc(sizeof(Fila));
    f->dados = malloc(capacidade * sizeof(int));
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}
 
int fila_vazia(Fila *f)
{
    return f->tamanho == 0;
}
 
void enfileirar(Fila *f, int valor)
{
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}
 
int desenfileirar(Fila *f)
{
    int valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return valor;
}
 
// BFS a partir de "origem": calcula distancia (numero de arestas) e
// predecessor de cada vertice na arvore de busca.
void bfs(GrafoLista *g, int origem, int *dist, int *pred)
{
    int *visitado = malloc(g->num_vertices * sizeof(int));
    Fila *f = criar_fila(g->num_vertices);
 
    for (int i = 0; i < g->num_vertices; i++)
    {
        visitado[i] = 0;
        dist[i] = -1;
        pred[i] = -1;
    }
 
    visitado[origem] = 1;
    dist[origem] = 0;
    enfileirar(f, origem);
    printf("Enfileira %i\n", origem + 1);
 
    while (!fila_vazia(f))
    {
        int u = desenfileirar(f);
        printf("Desinfileira %i, Visita %i\n", u + 1, u + 1);
 
        No *no = g->lista[u];
        while (no != NULL)
        {
            int v = no->vertice;
            if (!visitado[v])
            {
                visitado[v] = 1;
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(f, v);
                printf("Enfileira %i\n", v + 1);
            }
            no = no->proximo;
        }
    }
 
    free(visitado);
    free(f->dados);
    free(f);
}
 
// Teste de biparticao via 2-coloracao usando BFS.
// Percorre todos os componentes, ja que o grafo pode ser desconexo.
int eh_bipartido(GrafoLista *g)
{
    int *cor = malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++)
        cor[i] = -1;
 
    for (int origem = 0; origem < g->num_vertices; origem++)
    {
        if (cor[origem] != -1)
            continue;
 
        Fila *f = criar_fila(g->num_vertices);
        cor[origem] = 0;
        enfileirar(f, origem);
 
        while (!fila_vazia(f))
        {
            int u = desenfileirar(f);
            No *no = g->lista[u];
            while (no != NULL)
            {
                int v = no->vertice;
                if (cor[v] == -1)
                {
                    cor[v] = 1 - cor[u];
                    enfileirar(f, v);
                }
                else if (cor[v] == cor[u])
                {
                    free(f->dados);
                    free(f);
                    free(cor);
                    return 0;
                }
                no = no->proximo;
            }
        }
 
        free(f->dados);
        free(f);
    }
 
    free(cor);
    return 1;
}