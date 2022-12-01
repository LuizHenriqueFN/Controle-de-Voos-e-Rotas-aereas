//########################## Bibliotecas ###########################//peso
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Arquivos_auxiliares\Aeroportos.h"

//########################## Constantes ############################//
typedef int bool;
typedef char* String;
#define TAM 23
#define LIM 255
#define true 1
#define false 0

//########################## Structs ###############################//
//Struct que representa uma posição na lista encadeada de ligações do vértice
typedef struct TipoCelula{
    int numeroVoo;
    int numeroParadas;
    float duracao;
    int vertice;//Armazena qual é o vértice atual
    int distancia;//distancia da aresta
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
    int *fusos;
}GRAFO;

//########################## Funções ###############################//
//Função que inicializa e retorna um grafo.
GRAFO* iniciaGrafo(int numVertices);
//Função para criar aresta no grafo de rotas(direcionado)
bool criaArestaRotas(GRAFO *grafo, int Vertice_ini, int Vertice_fin, int distancia);
//Função para remover aresta no grafo de rotas(direcionado)
bool removeArestaRotas(GRAFO *grafo, int Vertice_ini, int Vertice_fin);
//Função para criar aresta no grafo de voos(não direcionado)
bool criaArestaVoos(GRAFO *grafo, int Vertice_ini, int Vertice_fin, int distancia);
//Função para remover aresta no grafo de voos(não direcionado)
bool removeArestaVoos(GRAFO *grafo, int Vertice_ini, int Vertice_fin);
void imprimir(GRAFO *grafo);
void voosDiretos(GRAFO *grafo, int aeroporto);
int leArquivoVoos(GRAFO *grafo);
int converteStringAeroporto(String aeroporto);
String converteAeroportoString(int aeroporto);
void caminho(GRAFO *grafo, int origem, int destino);
void menorCaminho_Grafo(GRAFO *grafo, int origem, int *anterior, int *distancia, int destino);