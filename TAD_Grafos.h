//########################## Bibliotecas ###########################//
#include <stdio.h>
#include <stdlib.h>

//########################## Constantes ############################//
typedef int bool;
#define Tam 10
#define true 1
#define false 0

//########################## Structs ###############################//
//Struct que representa uma posição na lista encadeada de ligações do vértice
typedef struct TipoCelula{
    int vertice;//Armazena qual é o último vértice percorrido
    int peso;//Peso da aresta
    struct TipoCelula *prox;//Próximo da lista
}CELULA;

//Struct que possui o ponteiro inicial para a lista de ligações que o vértice possui
typedef struct TipoVertice{
    CELULA *inicio;//Apontador inicial para a lista encadeada.
}VERTICE;

//Struct que armazena o número de vértices e arestas junto com o vetor de vértices
typedef struct TipoGrafo{
    int numVertices;//Quantidade de Vértices
    int numArestas_Voos;//Quantidade de Arestas do grafo de Voos
    int numArestas_Rotas;//Quantidade de Arestas do grafo de Rotas
    int **voos;//Vetor com os vértices
    VERTICE *rotas;//Vetor com os vértices
}GRAFO;

//########################## Funções ###############################//
//Funçãao que inicializa e retorna um grafo.
GRAFO* iniciaGrafo(int numVertices);