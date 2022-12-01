#include "TAD_Grafos.h"

//Função para inicializar a matriz do grafo de voos.
int** iniciaVoos(int numVertices){
    int **voos;
    voos = (int**)malloc(sizeof(int*) * numVertices);

    for(int i = 0; i < numVertices; i++){
        voos[i] = (int*)malloc(sizeof(int) * numVertices);
    }

    for(int i = 0; i < numVertices; i++){
        for(int j = 0; j < numVertices; j++){
            voos[i][j] = 0;
        }
    }
    return voos;
}
//Função para inicializar a lista de adjacência do grafo de rotas.
void iniciaRotas(VERTICE *rotas, int numVertices){
    for(int i = 0; i < numVertices; i++) rotas[i].inicio = NULL;
}
//Função para ler os fusos de cada aeroporto do arquivo.
void leFusos(GRAFO *grafo){
    if(grafo == NULL) return;

    char Linha[LIM];
    String result;
    int i = 0;

    FILE *arq = fopen("./Arquivos_auxiliares//Voos_Formatados.txt", "r");
    if(arq == NULL) return;

    while(true){
        result = fgets(Linha, LIM, arq);
        if(Linha[0] == '!')break;

        if(result){
            grafo->fusos[i++] = ((int)Linha[6]) - 48;//Convertendo char para inteiro
        }
    }
    fclose(arq);
}
//Função que inicializa e retorna um grafo.
GRAFO* iniciaGrafo(int numVertices){
    GRAFO *grafo = (GRAFO*)malloc(sizeof(GRAFO));

    //Iniciando variáveis:
    grafo->numVertices = numVertices;
    grafo->numArestas_Rotas = 0;
    grafo->numArestas_Voos = 0;
    grafo->fusos = (int*)malloc(sizeof(int) * numVertices);
    leFusos(grafo);
    grafo->rotas = (VERTICE*)malloc(sizeof(VERTICE) * numVertices);
    grafo->voos = iniciaVoos(numVertices);
    iniciaRotas(grafo->rotas, numVertices);

    return grafo;
}
//Função para iniciar uma adjacência
CELULA* iniciaCelula(int vertice, int distancia){
    CELULA *adj = (CELULA*)malloc(sizeof(CELULA));//Alocando memória para a struct

    //Iniciando dados:
    adj->vertice = vertice;
    adj->distancia = distancia;
    adj->prox = NULL;

    return adj;//Retornando a adjacência criada
} 

//Função para criar aresta no grafo de rotas(direcionado)
bool criaArestaRotas(GRAFO *grafo, int Vertice_ini, int Vertice_fin, int distancia){
    if(
        grafo == NULL                     ||
        Vertice_ini < 0                   ||
        Vertice_fin < 0                   ||
        Vertice_ini >= grafo->numVertices ||
        Vertice_fin >= grafo->numVertices ||
        distancia <= 0
    ) return false;//Verificando dados

    CELULA *adj;

    //Inserindo ligação na Lista de adjacência
    adj = iniciaCelula(Vertice_fin, distancia);
    adj->prox = grafo->rotas[Vertice_ini].inicio;
    grafo->rotas[Vertice_ini].inicio = adj;//Trocando a posição do ponteiro inicial

    grafo->numArestas_Rotas++;//Incrementando número de arestas.
    return true;
}
//Função para remover aresta no grafo de rotas(direcionado)
bool removeArestaRotas(GRAFO *grafo, int Vertice_ini, int Vertice_fin){
    if(
        grafo == NULL                     ||
        Vertice_ini < 0                   ||
        Vertice_fin < 0                   ||
        Vertice_ini >= grafo->numVertices ||
        Vertice_fin >= grafo->numVertices
    ) return false;//Verificando dados

    CELULA *q = NULL, *aux = grafo->rotas[Vertice_ini].inicio;

    while(aux->prox != NULL){
        if(aux->prox->vertice == Vertice_fin){
            q = aux->prox;
            aux->prox = q->prox;
            grafo->numArestas_Rotas--;

            free(q);
            return true;
        }
        aux = aux->prox;
    }

    return false;
}
//Função para criar aresta no grafo de voos(não direcionado)
bool criaArestaVoos(GRAFO *grafo, int Vertice_ini, int Vertice_fin, int distancia){
    if(
        grafo == NULL                     ||
        Vertice_ini < 0                   ||
        Vertice_fin < 0                   ||
        Vertice_ini >= grafo->numVertices ||
        Vertice_fin >= grafo->numVertices ||
        distancia <= 0
    ) return false;//Verificando dados

    grafo->voos[Vertice_ini][Vertice_fin] = distancia;
    grafo->voos[Vertice_fin][Vertice_ini] = distancia;
    grafo->numArestas_Voos++;
}
//Função para remover aresta no grafo de voos(não direcionado)
bool removeArestaVoos(GRAFO *grafo, int Vertice_ini, int Vertice_fin){
    if(
        grafo == NULL                     ||
        Vertice_ini < 0                   ||
        Vertice_fin < 0                   ||
        Vertice_ini >= grafo->numVertices ||
        Vertice_fin >= grafo->numVertices 
    ) return false;//Verificando dados

    grafo->voos[Vertice_ini][Vertice_fin] = 0;
    grafo->voos[Vertice_fin][Vertice_ini] = 0;
    grafo->numArestas_Voos--;
}

//Função para imprimir os grafos
void imprimir(GRAFO *grafo){
    if(grafo == NULL)return;

    printf(
        "\n======================================================================================"
        "\nNúmero de vértices: %d"
        "\nNúmero de arestas(Rotas): %d"
        "\nNúmero de arestas(Voos): %d"
        "\n======================================================================================"
        "\n                                            Voos                                      ",
        grafo->numVertices,
        grafo->numArestas_Rotas,
        grafo->numArestas_Voos
    );

    putchar('\n');
    for(int i = 0; i < grafo->numVertices; i++){
        for(int j = 0; j < grafo->numVertices; j++){
            printf("%d ", grafo->voos[i][j]);
        }
        putchar('\n');
    }

    printf(
        "\n======================================================================================"
        "\n                                            Rotas                                     "
    );

    CELULA *adj;
    for(int i = 0; i < grafo->numVertices; i++){
        printf("\n|V%d|: ", i);
        adj = grafo->rotas[i].inicio;
        while(adj != NULL){
            printf("[V%d|%d]", adj->vertice, adj->distancia);
            if(adj->prox != NULL) printf("➞ ");
            else printf("↴");
            adj = adj->prox;
        }
    }
    printf("\n======================================================================================");
}

//################################### Verificações ###################################//

/*5.2. Mostrar, a partir de um aeroporto definido, quais os voos diretos (sem escalas e/ou
conexões) que partem dele e a lista desses destinos.*/
void voosDiretos(GRAFO *grafo, int aeroporto){
    if(grafo == NULL) return;

    printf("\nAeroporto %d: ", aeroporto);
    for(int i = 0; i < grafo->numVertices; i++){
        if(grafo->voos[aeroporto][i] > 0)printf("%d(%dkm), ", i, grafo->voos[aeroporto][i]);
    }
}

//Função que retorna o valor do aeroporto recebendo o nome
int converteStringAeroporto(String aeroporto){
    if(!strcmp(aeroporto, "ABQ"))return ABQ;
    if(!strcmp(aeroporto, "ATL"))return ATL;
    if(!strcmp(aeroporto, "BNA"))return BNA;
    if(!strcmp(aeroporto, "BOS"))return BOS;
    if(!strcmp(aeroporto, "DCA"))return DCA;
    if(!strcmp(aeroporto, "DEN"))return DEN;
    if(!strcmp(aeroporto, "DFW"))return DFW;
    if(!strcmp(aeroporto, "DTW"))return DTW;
    if(!strcmp(aeroporto, "HOU"))return HOU;
    if(!strcmp(aeroporto, "JFK"))return JFK;
    if(!strcmp(aeroporto, "LAX"))return LAX;
    if(!strcmp(aeroporto, "MIA"))return MIA;
    if(!strcmp(aeroporto, "MSP"))return MSP;
    if(!strcmp(aeroporto, "MSY"))return MSY;
    if(!strcmp(aeroporto, "ORD"))return ORD;
    if(!strcmp(aeroporto, "PHL"))return PHL;
    if(!strcmp(aeroporto, "PHX"))return PHX;
    if(!strcmp(aeroporto, "PVD"))return PVD;
    if(!strcmp(aeroporto, "RDU"))return RDU;
    if(!strcmp(aeroporto, "SEA"))return SEA;
    if(!strcmp(aeroporto, "SFO"))return SFO;
    if(!strcmp(aeroporto, "STL"))return STL;
    if(!strcmp(aeroporto, "TPA"))return TPA;
    return -1;
}

String converteAeroportoString(int aeroporto){
    switch(aeroporto){
        case ABQ:return "ABQ";
        case ATL:return "ATL";
        case BNA:return "BNA";
        case BOS:return "BOS";
        case DCA:return "DCA";
        case DEN:return "DEN";
        case DFW:return "DFW";
        case DTW:return "DTW";
        case HOU:return "HOU";
        case JFK:return "JFK";
        case LAX:return "LAX";
        case MIA:return "MIA";
        case MSP:return "MSP";
        case MSY:return "MSY";
        case ORD:return "ORD";
        case PHL:return "PHL";
        case PHX:return "PHX";
        case PVD:return "PVD";
        case RDU:return "RDU";
        case SEA:return "SEA";
        case SFO:return "SFO";
        case STL:return "STL";
        case TPA:return "TPA";
    }
}

//Função para calcular a distância entre dois aeroportos do arquivo
float calculaDistancia(String origem, String destino){
    FILE *arq = fopen("./Arquivos_auxiliares//Voos_Formatados.txt", "r");
    if(arq == NULL) return -1;

    float distancia = 0.0;
    int encontrou = 0;
    char linha[LIM], *result;
    char conversor[5];
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

    while(true){
        strcpy(conversor, "");//Limpando string
        result = fgets(linha, LIM, arq);//Pegando linha do arquivo

        if(linha[0] == '!')break;//Verificando final dos dados
        //10,11,12 - 14,15,16
        if(result){
            if(strstr(linha, origem) != NULL){//Verificando se é a linha do aeroporto "origem"
                conversor[0] = linha[10];
                conversor[1] = linha[11];
                conversor[2] = linha[12];
                sscanf(conversor, "%d", &x1);

                conversor[0] = linha[14];
                conversor[1] = linha[15];
                conversor[2] = linha[16];
                sscanf(conversor, "%d", &y1);
                encontrou++;
            }
            if(strstr(linha, destino) != NULL){//Verificando se é a linha do aeroporto "destino"
                conversor[0] = linha[10];
                conversor[1] = linha[11];
                conversor[2] = linha[12];
                sscanf(conversor, "%d", &x2);

                conversor[0] = linha[14];
                conversor[1] = linha[15];
                conversor[2] = linha[16];
                sscanf(conversor, "%d", &y2);
                encontrou++;
            }
        }
        if(encontrou == 2)break;
    }
    fclose(arq);
    if(encontrou == 2){
        return(sqrt(pow((x2-x1), 2) + pow((y2-y1), 2)));
    }else return -1;
}

//Função para criar arestas a partir das ligações do arquivo
int leArquivoVoos(GRAFO *grafo){
    if(grafo == NULL) return false;
    String result, origem, destino;
    char linha[LIM];

    FILE *arquivo = fopen("./Arquivos_auxiliares//Voos_Formatados.txt", "r");
    if(arquivo == NULL) return false;

    while(fgetc(arquivo) != '!');//Posicionando para ler as ligações
    fgets(linha, LIM-1, arquivo);//Pulando linha
    
    //Percorrendo o arquivo:
    while(true){
        result = fgets(linha, LIM-1, arquivo);//Lendo linha
        if(linha[0] == '!')break;//Verificando fim das ligações

        if(result){
            origem = strtok(linha, ",");
            destino = strtok(NULL, "");
            destino[3] = '\0';//Removendo a quebra de linha

            criaArestaVoos(grafo, converteStringAeroporto(origem), converteStringAeroporto(destino), calculaDistancia(origem, destino));
        }
    }

    fclose(arquivo);
    return true;
}
//Função para retornar o caminho entre dois vértices.
void caminho(GRAFO *grafo, int origem, int destino){
    if(
        grafo == NULL                   ||
        origem < 0                      ||
        destino < 0                     ||
        origem >= grafo->numVertices    ||
        destino >= grafo->numVertices
    ) return;//Verificando dados

    String x = converteAeroportoString(origem);
    String y = converteAeroportoString(destino);

    if(grafo->voos[origem][destino] > 0){
        printf("\n\tCaminho de %s até %s:", x, y);
        printf("\n[%s]➞ [%s]", x, y);
        return;
        //...
    }
}

//Função para verificar qual é a menor distância
int procuraMenorDistancia(int *distancia, int *visitado, int numVertices){
    int menor = -1, primeiro = 1;
    for(int i = 0; i < numVertices; i++){
        if(distancia[i] >= 0 && visitado[i] == 0){//Verificando se o vértice já foi visitado
            if(primeiro){
                menor = i;
                primeiro = 0;
            }else{
                if(distancia[menor] > distancia[i]) menor = i;//Verificando se é o menor caminho.
            }
        }
    }
    return menor;
}

//Função para imprimir o menor caminho
void imprimeMenorCaminho(int *anterior, int origem, int destino){
    int aux = origem;
    printf("\nMenor caminho de %s até %s:\n", converteAeroportoString(origem), converteAeroportoString(destino));
    
    for(int i = 0; i < TAM; i++){
        if(anterior[i] == aux)printf("[%s]", converteAeroportoString(i));
        if(i < TAM-1)printf("➞ ");
    }
}

//Função para verificar qual é o menor caminho
void menorCaminho_Grafo(GRAFO *grafo, int origem, int *anterior, int *distancia, int destino){
    int cont, NV, ind, *visitado, aeroporto;
    cont = NV = grafo->numVertices;

    //Iniciando dados:
    visitado = (int*)malloc(sizeof(int) * NV);
    for(int i = 0; i < NV; i++){
        anterior[i] = -1;
        distancia[i] = -1;
        visitado[i] = 0;
    }
    distancia[origem] = 0;//Iniciando a primeira posição que será verificada

    while(cont > 0){
        aeroporto = procuraMenorDistancia(distancia, visitado, NV);
        if(aeroporto == -1)
            break;

        visitado[aeroporto] = 1;
        cont--;
        for(int i = 0; i < grafo->numVertices; i++){
            ind = grafo->voos[aeroporto][i];
            if(distancia[ind] < 0){
               distancia[ind] = distancia[aeroporto] + 1;//ou peso da aresta
               anterior[ind] = aeroporto;
            }else{
                if(distancia[ind] > distancia[aeroporto] + 1){
                    distancia[ind] = distancia[aeroporto] + 1;//ou peso da aresta
                    anterior[ind] = aeroporto;
                }
            }
        }
    }
    putchar('\n');
    for(int i = 0; i < TAM; i++){
        printf("%d ", anterior[i]);
    }
    free(visitado);
    // imprimeMenorCaminho(anterior, origem, destino);
}