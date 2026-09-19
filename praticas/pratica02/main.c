#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
#include "busca_profundidade.h"
 
int main(void)
{
    int n = 6;
    GrafoLista *g = criar_grafo(n);
 
    // Componente 1: triangulo 1-2-3 (tem ciclo, nao e bipartido)
    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 1, 2);
    adicionar_aresta(g, 2, 0);
 
    // Componente 2: aresta simples 4-5 (sem ciclo, bipartido)
    adicionar_aresta(g, 3, 4);
 
    // Componente 3: vertice isolado 6
 
    printf("=== Grafo ===\n");
    imprimir_grafo(g);
 
    printf("\n=== BFS a partir do vertice 1 ===\n");
    int dist[MAX_VERTICES];
    int pred[MAX_VERTICES];
    bfs(g, 0, dist, pred);
 
    printf("\nDistancias e predecessores a partir do vertice 1:\n");
    for (int i = 0; i < n; i++)
        printf("Vertice %i: dist = %i, predecessor = %i\n",
               i + 1, dist[i], pred[i] == -1 ? -1 : pred[i] + 1);
 
    printf("\n=== DFS recursiva a partir do vertice 1 ===\n");
    int visitado_rec[MAX_VERTICES] = {0};
    int descoberta[MAX_VERTICES];
    int termino[MAX_VERTICES];
    int tempo = 0;
    dfs_recursiva(g, 0, visitado_rec, &tempo, descoberta, termino);
 
    printf("\n=== DFS iterativa (com pilha) a partir do vertice 4 ===\n");
    int visitado_iter[MAX_VERTICES] = {0};
    dfs_iterativa(g, 3, visitado_iter);
 
    printf("\n=== Componentes conexos ===\n");
    printf("Numero de componentes: %i\n", contar_componentes(g));
 
    printf("\n=== Deteccao de ciclo ===\n");
    printf("O grafo possui ciclo? %s\n", tem_ciclo(g) ? "Sim" : "Nao");
 
    printf("\n=== Teste de biparticao ===\n");
    printf("O grafo e bipartido? %s\n", eh_bipartido(g) ? "Sim" : "Nao");
 
    free(g->lista);
    free(g);
 
    return 0;
}
 