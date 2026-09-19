#ifndef DAG_H
#define DAG_H

// estrutura da lista (implicita na pergunta)
typedef struct No
{
    int vertice;
    struct No *proximo; //NoAdj
} No; 

typedef struct
{
    No **lista;
    int num_vertices;
} GrafoLista;

//
typedef struct {
    int *cor;
    int *pilha_saida;   
    int topo;
    int tem_ciclo;
} EstadoDFS;
 
// funcoes das listas (basico do basico)
GrafoLista *criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, int origem, int destino);
void liberar_grafo(GrafoLista *g);

// funcoes pedidas pelo exercicio
int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho); // — retorna array com a ordenação ou NULL se houver ciclo.
int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho); // — empilha na saída da DFS.
int eh_dag(GrafoLista *g); // — verifica se o grafo é acíclico.

#endif