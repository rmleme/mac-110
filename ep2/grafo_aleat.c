#include <stdio.h>
#include <stdlib.h>
#include "gb_flip.h"
#include "grafo_aleat.h"

#define GB_RAND_MAXX ((unsigned long)0x80000000)
#define ONE_PT 0.013888888888888888888888888888889

/*
 * typedefs
 */

typedef int **Graph;

/*
 * Prototipos das funcoes e variaveis globais deste modulo
 */

static int **malloc2d(int r, int c);
static Graph g;

/* 
 * Implementacao das funcoes
 */

/*
 * Para alocacao dinamica de matrizes 
 */

int **malloc2d(int r, int c)
  { int i;
    int **t = malloc(r * sizeof(int *));
    if (t == NULL) {
      printf("Error in malloc2d(): not enough memory!\n");
      exit(-1);
    }
    for (i = 0; i < r; i++) {
      t[i] = malloc(c * sizeof(int));
      if (t[i] == NULL) {
        printf("Error in malloc2d(): not enough memory!\n");
        exit(-2);
      }
    }
    return t;
  }

/*
 * Geracao do grafo aleatorio
 */

void gere_grafo(int M, int N, double p, long seed)
{
  register int i, j;

  gb_init_rand(seed);

  g = malloc2d(M, N);
  for (i=0; i<M-1; i++)
    for (j=0; j<N-1; j++) 
      g[i][j]=(((gb_next_rand()<p*GB_RAND_MAXX ? 1 : 0)<<1)
	       ^(gb_next_rand()<p*GB_RAND_MAXX ? 1 : 0));
  for (j=0; j<N-1; j++)
    g[M-1][j]=(gb_next_rand()<p*GB_RAND_MAXX ? 1 : 0);
  for (i=0; i<M-1; i++)
    g[i][N-1]=((gb_next_rand()<p*GB_RAND_MAXX ? 1 : 0)<<1);
}

/*
 * Predicados de adjacencia
 */

int adj_i(int i, int j)
{
  return g[i][j]&2;
}

int adj_j(int i, int j)
{
  return g[i][j]&1;
}

