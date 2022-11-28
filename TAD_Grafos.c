#include "TAD_Grafos.h"

//Função para inicializar a matriz do grafo de voos.
void iniciaVoos(int **voos, int numVertices){
    voos = (int**)malloc(sizeof(int*) * numVertices);

    for(int i = 0; i < numVertices; i++){
        voos[i] = (int*)malloc(sizeof(int) * numVertices);
    }
}
//Função para inicializar a lista de adjacência do grafo de rotas.
void iniciaRotas(VERTICE *rotas, int numVertices){
    for(int i = 0; i < numVertices; i++) rotas->inicio = NULL;
}
//Função que inicializa e retorna um grafo.
GRAFO* iniciaGrafo(int numVertices){
    GRAFO *grafo = (GRAFO*)malloc(sizeof(GRAFO));

    //Iniciando variáveis:
    grafo->numVertices = numVertices;
    grafo->numArestas_Rotas = 0;
    grafo->numArestas_Voos = 0;
    iniciaVoos(grafo->voos, numVertices);
    iniciaRotas(grafo->rotas, numVertices);

    return grafo;
}