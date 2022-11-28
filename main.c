#include "TAD_Grafos.h"

/*
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

int main(){
    system("clear");
    return 0;
}