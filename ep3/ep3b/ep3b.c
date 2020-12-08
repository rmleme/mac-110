/******************************************************************************
 * Nome do aluno: Rodrigo Mendes Leme           Numero USP: 3151151           *
 * Curso: BCC                                   Data: 11/06/1999              *
 * Nome do Professor: Yoshiharu Kohayakawa                                    *
 * Exercicio Programa Numero 3-B                                              *
 * Compilador usado: GCC - Linux                                              *
 * Descricao: este programa recebe dois padroes de H's e T's e simula o jogo  *
 *            de Penney-Ante com estes padroes diversas vezes, devolvendo, no *
 *            final, o numero de vitorias de cada padrao e a probabilidade do *
 *            primeiro padrao ser "melhor" que o segundo padrao.              *
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strlib.h"
#include "gb_flip.h"

/************************* Declaracao de constantes **************************/

#define MAX_TAMANHO 31        /* Tamanho maximo dos padroes de H's e T's */

/******************************************************************************
 * Funcao: lanca_moeda                                                        *
 * Saida: "H" ou "T"; "H" se foi sorteado cara ou "T" se foi sorteado coroa.  *
 * Descricao: a funcao chama o gerador de numeros aleatorios para sortear ca- *
 *            ra (0) ou coroa (1), "convertendo" o resultado para "H" ou "T". *
 *****************************************************************************/

char *lanca_moeda(void)
{
  if (gb_unif_rand(2) == 0)      /* Sorteou cara  */
    return "H";
  else                           /* Sorteou coroa */
    return "T";
}

/******************************************************************************
 * Funcao: penney_ante                                                        *
 * Entrada: *padrao1: um dos padroes de H's e T's que participara do jogo.    *
 *          *padrao2: o outro padrao de H's e T's que participara do jogo.    *
 * Saida: -1 se o padrao 1 venceu; 1 se o padrao 2 venceu; 0 se houve empate. *
 * Descricao: esta funcao simula o jogo de moedas de Penney-Ante com os dois  *
 *            padroes dados, realizando sucessivos "lancamentos" de moedas    *
 *            ate que um dos padroes dados (ou ambos) ocorra.                 *
 *****************************************************************************/

int penney_ante(char padrao1[MAX_TAMANHO], char padrao2[MAX_TAMANHO])
{
  char sequencia1[MAX_TAMANHO] = "",    /* Guardam os resultados dos lances; */
       sequencia2[MAX_TAMANHO] = "";    /* funcionamento similar a um buffer */
  int vencedor;
  char lancamento[2];        /* Guarda o resultado de um lancamento de moeda */

  while (strcmp(sequencia1,padrao1) && strcmp(sequencia2,padrao2))
  {
    strcpy(lancamento,lanca_moeda());

    if (strlen(sequencia1) == 0)        /* Primeiro lancamento */
      strcpy(sequencia1,lancamento);
    else                           /* Apaga o primeira caracter da sequencia */
    {
      if (strlen(sequencia1) >= strlen(padrao1))
        strcpy(sequencia1,SubString(sequencia1,1,strlen(sequencia1)));
      strcat(sequencia1,lancamento);     /* Inclui um novo caracter no */
    }                                    /* final da sequencia         */

    if (strlen(sequencia2) == 0)        /* Primeiro lancamento */
      strcpy(sequencia2,lancamento);
    else                           /* Apaga o primeira caracter da sequencia */
    {
      if (strlen(sequencia2) >= strlen(padrao2))
        strcpy(sequencia2,SubString(sequencia2,1,strlen(sequencia2)));
      strcat(sequencia2,lancamento);     /* Inclui um novo caracter no */
    }                                    /* final da sequencia         */
  }

  if (!strcmp(sequencia1,padrao1))       /* Obteve o padrao 1 */
    vencedor = -1;
  if (!strcmp(sequencia2,padrao2))       /* Obteve o padrao 2 */
    vencedor = 1;
  if (!strcmp(sequencia1,padrao1) && !strcmp(sequencia2,padrao2))  /* Obteve */
    vencedor = 0;                                         /* os dois padroes */
  return vencedor;
}

/******************************************************************************
 * Funcao: main                                                               *
 * Saida: 0 se o programa executou normalmente; -1 se houve algum problema.   *
 * Descricao: inicializa o programa e faz as chamadas das funcoes.            *
 *****************************************************************************/

int main(int argc, char *argv[])
{
  char padrao1[MAX_TAMANHO],
       padrao2[MAX_TAMANHO];
  long semente;             /* Semente para o gerador de numeros aleatorios */
  unsigned int qtos_experiment,
               indice,
               quantas_vit_p1 = 0,      /* Numero de vitorias do padrao 1 */
               quantas_vit_p2 = 0;      /* Numero de vitorias do padrao 2 */
  int jogada;

  if (argc == 5)          /* Numero de parametros esta correto */
  {
    strcpy(padrao1,ConvertToUpperCase(argv[1]));
    strcpy(padrao2,ConvertToUpperCase(argv[2]));
    semente         = atol(argv[3]);
    qtos_experiment = atoi(argv[4]);
    if ((strlen(padrao1) > MAX_TAMANHO) || (strlen(padrao2) > MAX_TAMANHO))
    {
      printf("Erro: 1o. e 2o. parametros nao podem ter mais de 30 caracteres.\n");
      return -1;
    }
    if (qtos_experiment < 1)
    {
      printf("Erro: 4o. parametro deve ser maior ou igual a 1.\n");
      return -1;
    }
  }  
  else
  {
    printf("Erro: numero de argumentos invalido.\n");
    printf("1o. param.: 1o. padrao de H's e T's a ser simulado.\n");
    printf("2o. param.: 2o. padrao de H's e T's a ser simulado.\n");
    printf("3o. param.: semente a ser usada no gerador de aleatorios.\n");
    printf("4o. param.: numero de jogos a ser simulado entre os padroes.\n");
    return -1;
  }

  gb_init_rand(semente);
  for (indice = 1; indice <= qtos_experiment; indice++)
  {
    jogada = penney_ante(padrao1,padrao2);
    if (jogada < 0)         /* Padrao 1 venceu */
      quantas_vit_p1++;
    else
      if (jogada > 0)       /* Padrao 2 venceu */
        quantas_vit_p2++;
      else                  /* Empate, convenciona-se que o padrao 1 venceu */
        quantas_vit_p1++;
  }
  printf("Numero de vitorias de %s (p1): %u\n",padrao1,quantas_vit_p1);
  printf("Numero de vitorias de %s (p2): %u\n",padrao2,quantas_vit_p2);
  printf("Estimativa de p1 ser melhor que p2: %.4f\n", (double) quantas_vit_p1 / qtos_experiment);
  return 0;
}
