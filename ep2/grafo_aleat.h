#ifndef _grafo_aleat_h
#define _grafo_aleat_h

/*
 * gere_grafo()
 * ------------
 * Para que o modulo grafo_aleat gere um grafo aleatorio, 
 * o programa cliente deve executar a chamada
 *
 * gere_grafo(M, N, p, seed);
 *
 * onde M, N sao as dimensoes X e Y do grafo, p 'e a probabilidade
 * de existencia de cada aresta e seed 'e a semente para o gerador
 * de numeros aleatorios.
 */

void gere_grafo(int M, int N, double p, long seed);


/*
 * adj_i() e adj_j() 
 * -----------------
 * Estas funcoes informam se dois dados vertices
 * sao ou nao adjacentes no grafo que foi gerado pelo
 * modulo grafo_aleat.  
 *
 * A chamada adj_i(i,j) devolve 1 se o vertice 
 * (i, j) 'e adjacente ao vertice (i+1, j) e
 * devolve 0 caso contrario. 
 *
 * Analogamente, adj_j(i,j) devolvve 1 se o vertice 
 * (i, j) 'e adjacente ao vertice (i, j+1) e
 * devolve 0 caso contrario.
 *
 * Importante: estas funcoes assumem que os vertices
 * em questao pertencem ao grafo.  Por exemplo, na
 * chamada adj_i(i,j), assume-se que
 * 
 * 0 <= i < M-1 e 0 <= j < N.
 */

int adj_i(int i, int j);
int adj_j(int i, int j);
  
#endif
