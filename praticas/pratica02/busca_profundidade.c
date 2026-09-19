#include "busca_profundidade.h"

#include <stdio.h>
#include <stdlib.h>


Pilha *criar_pilha(int capacidade)
{
    Pilha *p = malloc(sizeof(Pilha));
    p->dados = malloc(capacidade * sizeof(int));
    p->capacidade = capacidade;
    p->topo = -1;
    return p;
}
 
int pilha_vazia(Pilha *p)
{
    return p->topo == -1;
}
 
void empilhar(Pilha *p, int valor)
{
    p->topo++;
    p->dados[p->topo] = valor;
}
 
int desempilhar(Pilha *p)
{
    int valor = p->dados[p->topo];
    p->topo--;
    return valor;
}
 
// DFS recursiva com tempo de descoberta e de termino de cada vertice.
// "tempo" e um contador global passado por referencia.
void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *tempo, int *descoberta, int *termino)
{
    visitado[u] = 1;
    descoberta[u] = *tempo;
    (*tempo)++;
    printf("Visita %i (descoberta = %i)\n", u + 1, descoberta[u]);
 
    No *no = g->lista[u];
    while (no != NULL)
    {
        int v = no->vertice;
        if (!visitado[v])
            dfs_recursiva(g, v, visitado, tempo, descoberta, termino);
        no = no->proximo;
    }
 
    termino[u] = *tempo;
    (*tempo)++;
    printf("Termina %i (termino = %i)\n", u + 1, termino[u]);
}
 
// DFS iterativa usando pilha explicita (marca visitado ao empilhar,
// assim cada vertice entra na pilha no maximo uma vez).
void dfs_iterativa(GrafoLista *g, int origem, int *visitado)
{
    Pilha *p = criar_pilha(g->num_vertices);
 
    visitado[origem] = 1;
    empilhar(p, origem);
    printf("Empilha %i\n", origem + 1);
 
    while (!pilha_vazia(p))
    {
        int u = desempilhar(p);
        printf("Desempilha %i, Visita %i\n", u + 1, u + 1);
 
        No *no = g->lista[u];
        while (no != NULL)
        {
            int v = no->vertice;
            if (!visitado[v])
            {
                visitado[v] = 1;
                empilhar(p, v);
                printf("Empilha %i\n", v + 1);
            }
            no = no->proximo;
        }
    }
 
    free(p->dados);
    free(p);
}
 
// Conta quantos componentes conexos o grafo possui, disparando uma
// DFS a partir de cada vertice ainda nao visitado.
int contar_componentes(GrafoLista *g)
{
    int *visitado = malloc(g->num_vertices * sizeof(int));
    int *descoberta = malloc(g->num_vertices * sizeof(int));
    int *termino = malloc(g->num_vertices * sizeof(int));
    int tempo = 0;
    int componentes = 0;
 
    for (int i = 0; i < g->num_vertices; i++)
        visitado[i] = 0;
 
    for (int i = 0; i < g->num_vertices; i++)
    {
        if (!visitado[i])
        {
            componentes++;
            dfs_recursiva(g, i, visitado, &tempo, descoberta, termino);
        }
    }
 
    free(visitado);
    free(descoberta);
    free(termino);
    return componentes;
}
 
// Auxiliar recursiva para deteccao de ciclo em grafo nao-dirigido:
// se encontrar um vizinho ja visitado que nao seja o "pai" na DFS,
// entao existe um ciclo.
static int tem_ciclo_aux(GrafoLista *g, int u, int pai, int *visitado)
{
    visitado[u] = 1;
 
    No *no = g->lista[u];
    while (no != NULL)
    {
        int v = no->vertice;
        if (!visitado[v])
        {
            if (tem_ciclo_aux(g, v, u, visitado))
                return 1;
        }
        else if (v != pai)
        {
            return 1;
        }
        no = no->proximo;
    }
 
    return 0;
}
 
int tem_ciclo(GrafoLista *g)
{
    int *visitado = malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++)
        visitado[i] = 0;
 
    for (int i = 0; i < g->num_vertices; i++)
    {
        if (!visitado[i])
        {
            if (tem_ciclo_aux(g, i, -1, visitado))
            {
                free(visitado);
                return 1;
            }
        }
    }
 
    free(visitado);
    return 0;
}
 