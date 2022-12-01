#include "TAD_Grafos.h"
/*
Anotações:
1 - Verificar se é pra ler o arquivo
2 - Verificar se o grafo de Rotas precisa de pesos.
3 - Verificar se possui voos quando inserir rotas.
4 - Significado de 257p
5 - Relatório 5.1
6 - Relatório 5.4


Orientações:
1. Elaborar uma estrutura de dados que suporte dois grafos, o das rotas e o dos voos, os quais
partilham os mesmos vértices, ou seja, os aeroportos.
2. O grafo dos voos terá apenas uma aresta para cada par (origem, destino) e pesos associados
as arestas: quantidade de voos e distância.
3. Já no grafo de voos poderá existir várias arestas direcionadas para cada par (origem, destino)
e pesos associados às arestas tais como: número do voo, distância, número de paradas e
duração.
4. A interface deve incluir:
• associar dados a partir de um arquivo sobre voos do território Americano, com aeroportos,
rotas e voos (considere as coordenadas indicadas em dezenas de Km);
• representar (demonstrar) graficamente as rotas (ligações entre aeroportos), os voos, ou
ambos.
5. Relatórios a serem gerados:
5.1. Para dois aeroportos pesquisados mostrar o caminho, como uma sequência de aeroportos,
com base no grafo das rotas;
5.2. Mostrar, a partir de um aeroporto definido, quais os voos diretos (sem escalas e/ou
conexões) que partem dele e a lista desses destinos.
5.3. Dados uma origem e um destino, desenvolver um algoritmo para determinar a viagem com
menor custo em termos de: distância total a percorrer e tempo de voo.
5.4. Desenvolver um algoritmo para determinar se é possível, a partir de um aeroporto qualquer
atingir qualquer outro (ou se será necessário em alguns casos fazer troca de aeroporto). Se for
possível, quais os aeroportos que, se ficassem fora de serviço (apenas um de cada vez),
impediriam essa situação.
5.5. Partindo de um aeroporto selecionado definir uma rota que consiga passar por todos os
aeroportos e retornar até ele. Essa rota pode ser classificada como um circuito Hamiltoniano?
*/

void Aeroportos(GRAFO *grafo){
    if(grafo == NULL) return;

    char Linha[LIM];
    String result;
    int i = 0;

    FILE *arq = fopen("./Arquivos_auxiliares//Voos_Formatados.txt", "r");
    if(arq == NULL) return;

    printf("\n\tAeroportos:");
    while(true){
        result = fgets(Linha, LIM, arq);
        if(Linha[0] == '!')break;

        if(result){
            printf("\n%c%c%c", Linha[0], Linha[1], Linha[2]);
        }
    }
    fclose(arq);
}

int main(){
    system("clear");
    int opcao;
    char escolha[4] = {};
    int origem, destino, anterior[TAM], distancia[TAM];;
    GRAFO *grafos = iniciaGrafo(TAM);
    leArquivoVoos(grafos);

    do{
        printf(
            "\n1 - Imprimir"
            "\n2 - Caminho"
            "\n3 - Voos Diretos"
            "\n4 - Viagem com menor custo"
            "\n5 - A partir de um aeroporto qualquer atingir qualquer outro"
            "\n6 - Rota para passar por todos os aeroportos"
            "\n0 - Sair"
            "\n> "
        );
        scanf("%d%*c", &opcao);

        switch(opcao){
            case 0:
                return 0;
            case 1: 
                imprimir(grafos);
                break;
            case 2: 
                Aeroportos(grafos);
                // printf("\nOrigem: ");
                // scanf("%c%c%c%*c", &escolha[0], &escolha[1], &escolha[2]);
                // origem = converteStringAeroporto(escolha);
                // printf("\nDestino: ");
                // scanf("%c%c%c%*c", &escolha[0], &escolha[1], &escolha[2]);
                // destino = converteStringAeroporto(escolha);
                // caminho(grafos, origem, destino);
                caminho(grafos, 0, 6);
                break;
            case 3:
                Aeroportos(grafos);
                printf("\nEscolha: ");
                scanf("%c%c%c%*c", &escolha[0], &escolha[1], &escolha[2]);
                voosDiretos(grafos, converteStringAeroporto(escolha));
                break;
            case 4:
                Aeroportos(grafos);
                printf("\nOrigem: ");
                scanf("%c%c%c%*c", &escolha[0], &escolha[1], &escolha[2]);
                origem = converteStringAeroporto(escolha);
                printf("\nDestino: ");
                scanf("%c%c%c%*c", &escolha[0], &escolha[1], &escolha[2]);
                destino = converteStringAeroporto(escolha);
                caminho(grafos, origem, destino);
                menorCaminho_Grafo(grafos, origem, anterior, distancia, destino);
                break;
            case 5:
                break;
            case 6:
                break;
            case 10:
                system("clear");
                break;
            default:
                printf("\nERRO!Opção inválida. Tente novamente:");
                break;
        }
    }while(true);
}