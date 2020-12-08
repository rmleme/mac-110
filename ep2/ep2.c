/******************************************************************************
 * Nome do aluno: Rodrigo Mendes Leme           Numero USP: 3151151           *
 * Curso: BCC                                   Data: 25/05/1999              *
 * Nome do Professor: Yoshiharu Kohayakawa                                    *
 * Exercicio Programa Numero 2                                                *
 * Compilador usado: GCC - Linux                                              *
 * Descricao: o programa gera um arquivo postscript que, dependendo da esco-  *
 *            lha do usuario, pode conter um grafo qualquer (gerado aleatoria-*
 *            mente) ou o componente conexo do mesmo. Para tal, ele usa roti- *
 *            nas graficas basicas, backtracking, recursao e matrizes aloca-  *
 *            das dinamicamente.                                              *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "grafo_aleat.h"

/************************* Declaracao de constantes **************************/

#define TAMANHO_TRACO 1      /* Tamanho de um traco do grafo a ser desenhado */
#define BOOLEAN short int
#define FALSE 0
#define TRUE 1

/**************************** Declaracao de tipos ****************************/

typedef struct
{
  int linha,
      coluna;
} direcoes;

typedef struct
{
  BOOLEAN cima,
          baixo,
          esquerda,
          direita,
          visitado;
} vertice;

/********************** Declaracao de variaveis globais **********************/

direcoes direcao[4];      /* Vetor de direcoes. Usado em acha_conexos()   */
vertice **matriz;         /* Matriz que contem uma representacao do grafo */

/******************************************************************************
 * Funcao: aloca_matriz                                                       *
 * Entrada: linha: numero de linhas da matriz a ser alocada.                  *
 *          coluna: numero de colunas da matriz a ser alocada.                *
 * Descricao: aloca memoria dinamicamente para uma matriz bidimensional.      *
 *****************************************************************************/

void aloca_matriz(int quantas_linhas, int quantas_colunas)
{
  int indice;
  
  matriz = (vertice **) malloc(quantas_linhas * sizeof(vertice *));
  if (matriz == NULL)
  {
    printf("Erro: falta de memoria.\n");
    exit(-3);
  }

  for (indice = 0; indice < quantas_linhas; indice++)
  {
    matriz[indice] = (vertice *) malloc(quantas_colunas * sizeof(vertice));
    if (matriz[indice] == NULL)
    {
      printf("Erro: falta de memoria.\n");
      exit(-3);
    }
  }
}

/******************************************************************************
 * Funcao: preenche_matriz                                                    *
 * Entrada: quantas_linhas: numero de linhas da matriz a ser preenchida.      *
 *          quantas_colunas: numero de colunas da matriz a ser preenchida.    *
 * Descricao: preenche a matriz que representa o grafo com as ligacoes exis-  *
 *            tentes no mesmo.                                                *
 *****************************************************************************/

void preenche_matriz(int quantas_linhas, int quantas_colunas)
{
  int linha,
      coluna;

  for (linha = 0; linha < quantas_linhas; linha++)
    for (coluna = 0; coluna < quantas_colunas; coluna++)
    {
      matriz[linha][coluna].cima     = FALSE;
      matriz[linha][coluna].baixo    = FALSE;
      matriz[linha][coluna].esquerda = FALSE;
      matriz[linha][coluna].direita  = FALSE;
      matriz[linha][coluna].visitado = FALSE;
    }

  for (linha = 0; linha < quantas_linhas - 1; linha++)
    for (coluna = 0; coluna < quantas_colunas - 1; coluna++)
    {
      if (adj_i(linha,coluna))        /* Tem ligacao para baixo */
      {
        matriz[linha][coluna].baixo    = TRUE;
        matriz[linha + 1][coluna].cima = TRUE;
      }
      if (adj_j(linha,coluna))        /* Tem ligacao para a direita */
      {
        matriz[linha][coluna].direita      = TRUE;
        matriz[linha][coluna + 1].esquerda = TRUE;
      }
    }

  for (coluna = 0; coluna < quantas_colunas - 1; coluna++)
    if (adj_j(linha,coluna))          /* Ve se ha ligacoes na ultima linha */
    {
      matriz[linha][coluna].direita      = TRUE;
      matriz[linha][coluna + 1].esquerda = TRUE;
    }

  for (linha = 0; linha < quantas_linhas - 1; linha++)
    if (adj_i(linha,coluna))          /* Ve se ha ligacoes na ultima coluna */
    {
      matriz[linha][coluna].baixo    = TRUE;
      matriz[linha + 1][coluna].cima = TRUE;
    }
}

/******************************************************************************
 * Funcao: inicializa_direcoes                                                *
 * Descricao: inicializa o vetor de direcoes que e  usado em acha_conexos().  *
 *****************************************************************************/

void inicializa_direcoes(void)
{
  direcao[0].linha = -1;        direcao[0].coluna = 0;      /* Cima     */
  direcao[1].linha = 0;         direcao[1].coluna = 1;      /* Direita  */
  direcao[2].linha = 1;         direcao[2].coluna = 0;      /* Baixo    */
  direcao[3].linha = 0;         direcao[3].coluna = -1;     /* Esquerda */
}

/******************************************************************************
 * Funcao: line                                                               *
 * Entrada: y1: coordenada vertical inicial da linha.                         *
 *          x1: coordenada horizontal inicial da linha.                       *
 *          y2: coordenada vertical final da linha.                           *
 *          x2: coordenada horizontal final da linha.                         *
 * Descricao: desenha uma linha na tela.                                      *
 *****************************************************************************/

void line(double y1, double x1, double y2, double x2)
{
  MovePen(y1,x1);
  DrawLine(y2,x2);
}

/******************************************************************************
 * Funcao: desenha_grafo                                                      *
 * Entrada: quantas_linhas: numero de linhas do grafo.                        *
 *          quantas_colunas: numero de colunas do grafo.                      *
 * Descricao: desenha na tela as linhas do grafo.                             *
 *****************************************************************************/

void desenha_grafo(int quantas_linhas, int quantas_colunas)
{
  int coluna,
      linha;
  double fator_de_correcao_x,      /* Adequa a dimensao X do grafo a tela    */
         fator_de_correcao_y,      /* Adequa a dimensao Y do grafo a tela    */
         traco_real_x,             /* Tamanho do traco corrigido pelo fator  */
         traco_real_y;             /* Tamanho do traco corrigido pelo fator  */

  fator_de_correcao_x = GetWindowHeight() / quantas_colunas;
  fator_de_correcao_y = GetWindowWidth() / quantas_linhas;
  traco_real_x        = TAMANHO_TRACO * fator_de_correcao_x;
  traco_real_y        = TAMANHO_TRACO * fator_de_correcao_y;

  for (linha = 0; linha < quantas_linhas - 1; linha++)
    for (coluna = 0; coluna < quantas_colunas - 1; coluna++)
    {
      if (adj_i(linha,coluna))         /* Desenha uma linha vertical */
        line(linha * fator_de_correcao_y,coluna * fator_de_correcao_x,
             traco_real_y,0);
      if (adj_j(linha,coluna))         /* Desenha uma linha horizontal */
        line(linha * fator_de_correcao_y,coluna * fator_de_correcao_x,
             0,traco_real_x);
    }

  for (coluna = 0; coluna < quantas_colunas - 1; coluna++)
    if (adj_j(linha,coluna))           /* Desenha a ultima linha horizontal */
      line(linha * fator_de_correcao_y,coluna * fator_de_correcao_x,
           0,traco_real_x);

  for (linha = 0; linha < quantas_linhas - 1; linha++)
    if (adj_i(linha,coluna))           /* Desenha a ultima coluna vertical */
      line(linha * fator_de_correcao_y,coluna * fator_de_correcao_x,
           traco_real_y,0);
}

/******************************************************************************
 * Funcao: ha_ligacao                                                         *
 * Entrada: linha: linha (da matriz) que sera testada.                        *
 *          coluna: coluna (da matriz) que sera testada.                      *
 *          qual_direcao: direcao (da matriz) que sera testada (em relacao a  *
 *                        posicao atual).                                     *
 * Saida: a existencia ou nao de ligacao entre duas posicoes da matriz.       *
 * Descricao: a funcao testa se a posicao [linha][coluna] da matriz esta li-  *
 *            gada a posicao anterior.                                        *
 *****************************************************************************/

BOOLEAN ha_ligacao(int linha, int coluna, int qual_direcao)
{
  switch(qual_direcao)
  {
    case 0: return matriz[linha][coluna].cima;
            break;
    case 1: return matriz[linha][coluna].direita;
            break;
    case 2: return matriz[linha][coluna].baixo;
            break;
    case 3: return matriz[linha][coluna].esquerda;
            break;
    default: return FALSE;
  }
}

/******************************************************************************
 * Funcao: acha_conexos                                                       *
 * Entrada: quantas_linhas: numero de linhas da matriz do grafo.              *
 *          quantas_colunas: numero de colunas da matriz do grafo.            *
 *          linha_inic: posicao inicial vertical na matriz do grafo.          *
 *          coluna_inic: posicao inicial horizontal na matriz do grafo.       *
 *          direcao_inic: direcao inicial a ser testada na matriz do grafo.   *
 * Saida: o numero de vertices conectados ao vertice central.                 *
 * Descricao: atraves do algoritmo recursivo de backtracking, a funcao acha   *
 *            todos os vertices alcancaveis do ponto central pelas arestas.   *
 *****************************************************************************/

long acha_conexos(int quantas_linhas, int quantas_colunas, int linha_inic,
                  int coluna_inic, int direcao_inic)
{
  int linha_nova        = linha_inic,
      coluna_nova       = coluna_inic,
      qual_direcao      = direcao_inic;
  long quantos_vertices = 0;

  if (qual_direcao > 3)          /* Ja testou todas as direcoes possiveis */
  {
    matriz[linha_inic][coluna_inic].visitado = TRUE;
    return quantos_vertices;
  } 
  else                 /* Ainda ha direcoes a serem testadas */
  {
    linha_nova  += direcao[qual_direcao].linha;
    coluna_nova += direcao[qual_direcao].coluna;
    if (((linha_nova >= 0) && (linha_nova <= (quantas_linhas - 1))) &&
        ((coluna_nova >= 0) && (coluna_nova <= (quantas_colunas - 1))) &&
        ha_ligacao(linha_inic,coluna_inic,qual_direcao) &&
        !matriz[linha_nova][coluna_nova].visitado)
    {
      matriz[linha_inic][coluna_inic].visitado = TRUE;
      quantos_vertices++;
      quantos_vertices += acha_conexos(quantas_linhas,quantas_colunas,
                                       linha_nova,coluna_nova,0);
      quantos_vertices += acha_conexos(quantas_linhas,quantas_colunas,
                                       linha_nova,coluna_nova,1);
      quantos_vertices += acha_conexos(quantas_linhas,quantas_colunas,
                                       linha_nova,coluna_nova,2);
      quantos_vertices += acha_conexos(quantas_linhas,quantas_colunas,
                                       linha_nova,coluna_nova,3);
    }
    else           /* Nao achou uma ligacao, testa proxima direcao */
    {
      qual_direcao++;
      quantos_vertices += acha_conexos(quantas_linhas,quantas_colunas,
                                       linha_inic,coluna_inic,qual_direcao);
    }
    return quantos_vertices;
  }
}

/******************************************************************************
 * Funcao: desenha_conexo                                                     *
 * Entrada: quantas_linhas: numero de linhas do componente conexo.            *
 *          quantas_colunas: numero de colunas do componente conexo.          *
 * Descricao: desenha na tela as linhas do componente conexo.                 *
 *****************************************************************************/

void desenha_conexo(int quantas_linhas, int quantas_colunas)
{
  int linha,
      coluna;
  double fator_de_correcao_x,      /* Adequa a dimensao X do grafo a tela    */
         fator_de_correcao_y,      /* Adequa a dimensao Y do grafo a tela    */
         traco_real_x,             /* Tamanho do traco corrigido pelo fator  */
         traco_real_y;             /* Tamanho do traco corrigido pelo fator  */

  fator_de_correcao_x = GetWindowHeight() / quantas_colunas;
  fator_de_correcao_y = GetWindowWidth() / quantas_linhas;
  traco_real_x        = TAMANHO_TRACO * fator_de_correcao_x;
  traco_real_y        = TAMANHO_TRACO * fator_de_correcao_y;

  for (linha = 0; linha < quantas_linhas; linha++)
    for (coluna = 0; coluna < quantas_colunas; coluna++)
      if (matriz[linha][coluna].visitado)
      {
        if (matriz[linha][coluna].baixo)
          line(linha * fator_de_correcao_y,coluna * fator_de_correcao_x,
               traco_real_y,0);
	if (matriz[linha][coluna].direita)
          line(linha * fator_de_correcao_y,coluna * fator_de_correcao_x,
               0,traco_real_x);
      }
}

/******************************************************************************
 * Funcao: main                                                               *
 * Entrada: quantas_colunas: numero de colunas do grafo.                      *
 *          quantas_linhas: numero de linhas do grafo.                        *
 *          prob: probabilidade de existencia de cada aresta.                 *
 *          semente: usado no gerador de numeros aleatorios.                  *
 *          opcao: vale 0 (desenha todo o grafo) ou 1 (desenha apenas o com-  *
 *                 nente conexo).                                             *
 * Saida: codigo de erro.                                                     *
 * Descricao: chama as funcoes pricipais do programa.                         *
 *****************************************************************************/

int main(int argc, char *argv[])
{
  int quantas_colunas,
      quantas_linhas,
      opcao,
      qual_direcao;
  double prob;
  long semente,
       quantos_vert_conec = 1,    /* Numero de vertices do componente conexo */
       max_vertices;              /* Numero maximo de vertices do grafo      */

  if (argc == 6)        /* O numero de parametros esta correto */
  {
    quantas_colunas = atoi(argv[1]);
    quantas_linhas  = atoi(argv[2]);
    prob            = atof(argv[3]);
    semente         = atol(argv[4]);
    opcao           = atoi(argv[5]);
  }
  else
  {
    printf("Erro: numero de argumentos invalido.\n");
    printf("1o. parametro: numero de colunas.\n");
    printf("2o. parametro: numero de linhas.\n");
    printf("3o. parametro: probabilidade (usado na construcao do grafo).\n");
    printf("4o. parametro: semente (para o gerador de numeros aleatorios).\n");
    printf("5o. parametro: 0 -> desenha tudo; 1 -> desenha so o conexo.\n");
    return -1;
  }

  gere_grafo(quantas_colunas,quantas_linhas,prob,semente);
  InitGraphics();

  if (opcao == 0)        /* Desenha o grafo inteiro */
    desenha_grafo(quantas_linhas,quantas_colunas);
  else
    if (opcao == 1)      /* Desenha apenas o componente conexo */
    {
      aloca_matriz(quantas_linhas,quantas_colunas);
      preenche_matriz(quantas_linhas,quantas_colunas);
      inicializa_direcoes();
      for (qual_direcao = 0; qual_direcao <= 3; qual_direcao++)
        quantos_vert_conec += acha_conexos(quantas_linhas,quantas_colunas,
                                           quantas_linhas/2,quantas_colunas/2,
                                           qual_direcao);
      desenha_conexo(quantas_linhas,quantas_colunas);
      max_vertices = quantas_linhas * quantas_colunas;

      printf("Os parametros do grafo sao\n");
      printf("   (M, N, p, seed) = (%d, %d, %g, %ld)\n",quantas_colunas,
             quantas_linhas,prob,semente);
      printf("   O componente conexo de (M/2, N/2) contem %ld vertices.\n",
             quantos_vert_conec);
      printf("   [Maximo possivel: M * N = %d * %d = %ld]\n",quantas_colunas,
             quantas_linhas,max_vertices);
      printf("   [Razao: %ld/%ld = %.5f]\n",quantos_vert_conec,max_vertices,
             (double) quantos_vert_conec / max_vertices);
    }
    else
    {
      printf("Erro: 5o. parametro deve valer 0 ou 1.\n");
      return -2;
    }
  return 0;
}
