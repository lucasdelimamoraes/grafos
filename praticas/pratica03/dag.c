#include "dag.h"

#include <stdio.h>
#include <stdlib.h>

GrafoLista *criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista *) malloc(sizeof(GrafoLista));
    if (g == NULL) {
        fprintf(stderr, "Erro ao alocar grafo.\n");
        exit(EXIT_FAILURE);
    }
 
    g->num_vertices = num_vertices;
    g->lista = (No **) calloc(num_vertices, sizeof(No *));
    if (g->lista == NULL) {
        fprintf(stderr, "Erro ao alocar lista de adjacencia.\n");
        free(g);
        exit(EXIT_FAILURE);
    }
 
    return g;
}
 
void adicionar_aresta(GrafoLista *g, int origem, int destino) {
    if (g == NULL || origem < 0 || origem >= g->num_vertices ||
        destino < 0 || destino >= g->num_vertices) {
        fprintf(stderr, "Aresta invalida: %d -> %d\n", origem, destino);
        return;
    }
 
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "Erro ao alocar no de adjacencia.\n");
        return;
    }
 
    novo->vertice = destino;
    novo->proximo = g->lista[origem];
    g->lista[origem] = novo;
}
 
void liberar_grafo(GrafoLista *g) {
    if (g == NULL) return;
 
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->lista[i];
        while (atual != NULL) {
            No *tmp = atual;
            atual = atual->proximo;
            free(tmp);
        }
    }
 
    free(g->lista);
    free(g);
}
 
int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    if (g == NULL || tamanho == NULL) return NULL;
 
    int n = g->num_vertices;
    *tamanho = 0;
 
    int *grau_entrada = (int *) calloc(n, sizeof(int));
    int *fila = (int *) malloc(n * sizeof(int));
    int *resultado = (int *) malloc(n * sizeof(int));
 
    if (grau_entrada == NULL || fila == NULL || resultado == NULL) {
        fprintf(stderr, "Erro ao alocar memoria em Kahn.\n");
        free(grau_entrada);
        free(fila);
        free(resultado);
        return NULL;
    }
 
    /* Calcula o grau de entrada de cada vertice */
    for (int u = 0; u < n; u++) {
        for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
            grau_entrada[no->vertice]++;
        }
    }
 
    /* Inicializa a fila com todos os vertices de grau de entrada 0 */
    int inicio_fila = 0, fim_fila = 0;
    for (int v = 0; v < n; v++) {
        if (grau_entrada[v] == 0) {
            fila[fim_fila++] = v;
        }
    }
 
    int indice_resultado = 0;
 
    while (inicio_fila < fim_fila) {
        int u = fila[inicio_fila++];
        resultado[indice_resultado++] = u;
 
        for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
            int v = no->vertice;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) {
                fila[fim_fila++] = v;
            }
        }
    }
 
    free(grau_entrada);
    free(fila);
    if (indice_resultado != n) {
        free(resultado);
        *tamanho = 0;
        return NULL;
    }
 
    *tamanho = indice_resultado;
    return resultado;
}
 
#define BRANCO 0
#define CINZA  1
#define PRETO  2
 
static void dfs_visita(GrafoLista *g, int u, EstadoDFS *estado) {
    if (estado->tem_ciclo) return; // ja detectou ciclo, pode parar
 
    estado->cor[u] = CINZA;
 
    for (No *no = g->lista[u]; no != NULL; no = no->proximo) {
        int v = no->vertice;
 
        if (estado->tem_ciclo) return;
 
        if (estado->cor[v] == CINZA) {
            estado->tem_ciclo = 1;
            return;
        } else if (estado->cor[v] == BRANCO) {
            dfs_visita(g, v, estado);
        }
    }
 
    estado->cor[u] = PRETO;
    estado->pilha_saida[estado->topo++] = u;
}
 
int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    if (g == NULL || tamanho == NULL) return NULL;
 
    int n = g->num_vertices;
    *tamanho = 0;
 
    EstadoDFS estado;
    estado.cor = (int *) calloc(n, sizeof(int));
    estado.pilha_saida = (int *) malloc(n * sizeof(int));
    estado.topo = 0;
    estado.tem_ciclo = 0;
 
    if (estado.cor == NULL || estado.pilha_saida == NULL) {
        fprintf(stderr, "Erro ao alocar memoria em DFS.\n");
        free(estado.cor);
        free(estado.pilha_saida);
        return NULL;
    }
 
    for (int v = 0; v < n && !estado.tem_ciclo; v++) {
        if (estado.cor[v] == BRANCO) {
            dfs_visita(g, v, &estado);
        }
    }
 
    free(estado.cor);
 
    if (estado.tem_ciclo) {
        free(estado.pilha_saida);
        *tamanho = 0;
        return NULL;
    }
 
    int *resultado = (int *) malloc(n * sizeof(int));
    if (resultado == NULL) {
        fprintf(stderr, "Erro ao alocar resultado em DFS.\n");
        free(estado.pilha_saida);
        return NULL;
    }
 
    for (int i = 0; i < n; i++) {
        resultado[i] = estado.pilha_saida[n - 1 - i];
    }
 
    free(estado.pilha_saida);
 
    *tamanho = n;
    return resultado;
}
 
int eh_dag(GrafoLista *g) {
    if (g == NULL) return 0;
 
    int tamanho = 0;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);
 
    if (ordem == NULL) {
        return 0; /* possui ciclo */
    }
 
    free(ordem);
    return 1; /* acíclico */
}
 