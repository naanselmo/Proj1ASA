# ProjASA
Introducao breve
--------------------
O nosso algoritmo é baseado em DFS.
Usamos DFS para visitar o grafo, e dar valores visited e low a cada vertice, onde estes teem o seguinte significado:
* Visited de um vertice V, representa uma especie de indice, indica a ordem de visita de V, isto é o numero de vertices visitados ate chegar a V. (Não tem nada a ver com o identificador de V que nos é dado no problema).
* Low de um vertice V, é o indice do vertice de menor indice que é possivel chegar a partir de V usando 0 ou mais arcos de arvore e depois no maximo um arco para tras. (verificar traducao)
Depois computamos todos os vertices fundamentais a partir dos valores de visited e low.

Descricao da solucao
--------------------
O nosso algoritmo divide-se nas seguintes operações, pela seguinte ordem:

1. Para computar os valores visited de cada vertice apenas precisamos de uma pre-visita<sup>1</sup>, isto é dar o valor de visited ao vertice e só depois visitar os seus vizinhos.

2. Para computar os valores low de cada vertice apenas precisamos de uma pos-visita<sup>1</sup>, isto é dar o valor de low apenas depois de visitar todos os seus vizinhos, com as seguintes condições:
  * Low de um vertice V = menor numero entre o indice de V e o menor indice de todos os vertices de arcos para tras a partir de V.
	Ou seja se um vertice vizinho W, ja foi visitado, e V nao for o antecessor deste, isto indica que V e W estao ligados por um arco para tras.
  * Low de um vertice V = menor numero entre o indice de V e o menor low de todos os vertices ligados por arcos de arvore.
	Ou seja se um vertice vizinho W, ainda não foi visitado, isto indica que V e W estao ligados por um arco de arvore.

3. Para computar quais os pontos fundamentais apenas precisamos de outra pos-visita<sup>1</sup>, e verificar apenas um conjunto de condicoes que verificam se o vertice é ou nao fundamental,
baseado nos seus valores de visited e low, e nos valores dos seus vizinhos.
Um vertice V é fundamental, se:
	* V for a raiz da DFS e tiver mais do que um filho.
	* Existir um vizinho de V, W, tal que o low de W for maior ou igual que o visited de V, isto é W não é capaz de chegar a um vertice visitado antes de V.
A medida que calculamos quais os vertices fundamentais, inserimo-os numa lista de fundamentais se estes ainda não estiverem na mesma.

4. Para saber qual o valor do menor vertice e o valor do maior vertice, iteramos a lista, fazendo uma simples comparação com o menor e o maior, atualizando estes à medida que encontramos valores menores e maiores.
Quanto ao número de vertices fundamentais, apenas basta saber qual o tamanho da lista.

<sup>1</sup> Quando dizemos visita, estamos a falar numa DFS onde antes ou depois de fazer a visita recursiva aos vizinhos executamos operacoes. 
Pre-visita seria executar a operacao e só depois visitar os vizinhos. Pos-visita seria visitar primeiro os vizinhos, e só depois de estes serem visitados, executar a operação.

Analise teorica
--------------------
Todas as operacoes descritas em cima, teem como complexidade O(V+E), visto que se baseiam em DFS, excepto o ultimo, que no pior dos casos seria O(V-2) (caso em que o grafo é como se fosse uma lista, onde todos os vertices sao fundamentais excepto o primeiro o ultimo). No melhor caso seria O(1), onde não há vertices fundamentais para iterar.
De notar que podemos tambem juntar as 3 primeiras operacoes numa mega-operacao, necessitando assim apenas de uma DFS, em vez de 3, claro que esta alteracao nao modifica a classe de complexidade do algoritmo.
Logo a complexidade total do algoritmo pertence é O(V+E).

Analise experimental
--------------------
Fizemos um programa que gerasse um grafo a partir de um parametro N = V + E.
* Se N fosse par gerava um grafo com tantos vertices quanto arestas, fazendo parte do melhor caso.
* Se N fosse impar gerava gerava um grafo com ceil(N/2) vertices e floor(N/2) arestas, fazendo parte do pior caso.

#####Pior caso (quase todos os vertices sao vertices fundamentais):
```
Exemplo de input:
3 2
1 2
2 3
```
#####Melhor caso (Não há vertices fundamentais):
```
Exemplo de input:
3 3
1 2
2 3
3 1
```

Num grafico cujos os eixos são o tempo de execução do algoritmo em millisegundos, e N (sendo N = V + E), marcamos os pontos para cada experiencia que fizemos, e depois usando linear regression, fizemos uma reta que melhor se ajustasse a todos os pontos.
Eis os resultados:

#####Pior caso
N (V+E) | 51 | 501 | 5001 | 50001 | 100001 | 200001 | 500001 | 1000001
------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- 
Tempo (ms) | 0.046047 | 0.065849 | 0.536473 | 4.07928 | 10.573 | 16.4495 | 52.2242 | 143.475
![Pior caso](http://i.imgur.com/e5GFRHn.png)


#####Melhor caso
N (V+E) | 50 | 500 | 5000 | 50000 | 100000 | 200000 | 500000 | 1000000
------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- | ------- 
Tempo (ms) | 0.04229 | 0.056593 | 0.207059 | 2.18557 | 5.59063 | 9.42237 | 41.9931 | 90.4513
![Pior caso](http://i.imgur.com/ZKomKMD.png)

Referencias
--------------------
http://www.eecs.wsu.edu/~holder/courses/CptS223/spr08/slides/graphapps.pdf#7

~~https://fenix.tecnico.ulisboa.pt/downloadFile/1970943312272240/aula5.pdf#19~~

