#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

static void imprimir_resultado(const char *titulo, int *ordem, int tamanho) {
    printf("%s: ", titulo);
    if (ordem == NULL) {
        printf("IMPOSSIVEL (grafo possui ciclo)\n");
        return;
    }
    for (int i = 0; i < tamanho; i++) {
        printf("%d", ordem[i]);
        if (i < tamanho - 1) printf(" -> ");
    }
    printf("\n");
}

int main(void) {
    printf("=== Caso 1: DAG (6 vertices) ===\n");
    GrafoLista *g1 = criar_grafo(6);
    adicionar_aresta(g1, 5, 2);
    adicionar_aresta(g1, 5, 0);
    adicionar_aresta(g1, 4, 0);
    adicionar_aresta(g1, 4, 1);
    adicionar_aresta(g1, 2, 3);
    adicionar_aresta(g1, 3, 1);

    printf("E DAG? %s\n", eh_dag(g1) ? "Sim" : "Nao");

    int tam_kahn1 = 0, tam_dfs1 = 0;
    int *kahn1 = ordenacao_topologica_kahn(g1, &tam_kahn1);
    int *dfs1  = ordenacao_topologica_dfs(g1, &tam_dfs1);

    imprimir_resultado("Kahn (BFS)", kahn1, tam_kahn1);
    imprimir_resultado("DFS       ", dfs1, tam_dfs1);

    free(kahn1);
    free(dfs1);
    liberar_grafo(g1);

    printf("\n");
    printf("=== Caso 2: Grafo com ciclo (3 vertices) ===\n");
    GrafoLista *g2 = criar_grafo(3);
    adicionar_aresta(g2, 0, 1);
    adicionar_aresta(g2, 1, 2);
    adicionar_aresta(g2, 2, 0);

    printf("E DAG? %s\n", eh_dag(g2) ? "Sim" : "Nao");

    int tam_kahn2 = 0, tam_dfs2 = 0;
    int *kahn2 = ordenacao_topologica_kahn(g2, &tam_kahn2);
    int *dfs2  = ordenacao_topologica_dfs(g2, &tam_dfs2);

    imprimir_resultado("Kahn (BFS)", kahn2, tam_kahn2);
    imprimir_resultado("DFS       ", dfs2, tam_dfs2);

    free(kahn2);
    free(dfs2);
    liberar_grafo(g2);

    return 0;
}