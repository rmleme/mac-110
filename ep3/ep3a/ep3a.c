/******************************************************************************
 * Nome do aluno: Rodrigo Mendes Leme           Numero USP: 3151151           *
 * Curso: BCC                                   Data: 9/06/1999               *
 * Nome do Professor: Yoshiharu Kohayakawa                                    *
 * Exercicio Programa Numero 3-A                                              *
 * Compilador usado: GCC - Linux                                              *
 * Descricao: este programa realiza duas "tarefas" diferentes: ou ele simula  *
 *            uma sequencia de lances de uma moeda ate que um dado padrao     *
 *            ocorra, indicando o numero de lancamentos da mesma, ou ele rea- *
 *            liza varias dessas simulacoes, indicando a media dos resultados *
 *            dos lancamentos.                                                *
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
 * Funcao: simula_lances                                                      *
 * Entrada: *padrao: padrao de H's e T's que sera "procurado" pela funcao.    *
 * Saida: numero de lancamentos da moeda ate o padrao dado ocorrer.           *
 * Descricao: a funcao simula uma sequencia de lances de moeda ate que o pa-  *
 *            drao dado ocorra.                                               *
 *****************************************************************************/

int simula_lances(char padrao[MAX_TAMANHO])
{
  char sequencia[MAX_TAMANHO];         /* Guarda resultados dos lances; */
                             /* funcionamento similar ao de um buffer   */
  int quantos_lances;    /* Numero de lancamentos da moeda              */

  /* Enquanto a sequencia nao tiver o mesmo tamanho do padrao a procurar, */
  /* nao adianta testa-la; portanto, ela e preenchida com o resultado de  */
  /* varios lances, ate que a sequencia tenha o mesmo tamanho do padrao   */
  strcpy(sequencia,lanca_moeda());
  for (quantos_lances = 1; quantos_lances <= strlen(padrao) - 1; quantos_lances++)
    strcat(sequencia,lanca_moeda());

  while (strcmp(sequencia,padrao))     /* Simula lances ate achar o padrao */
  {
    strcpy(sequencia,SubString(sequencia,1,strlen(sequencia)));   /* Suprime */
                                            /* o primeiro caracter da cadeia */
    strcat(sequencia,lanca_moeda());    /* Inclui um novo caracter no */
                                        /* final da sequencia         */
    quantos_lances++;
  }
  return quantos_lances;
}

/******************************************************************************
 * Funcao: simula_experimentos                                                *
 * Entrada: *padrao: padrao de H's e T's que sera usado nos experimentos.     *
 *          quantos_experimentos: numero de experimentos a ser realizado.     *
 * Saida: a media dos resultados dos experimentos.                            *
 * Descricao: realiza varios experimentos de simulacoes de lances de moedas,  *
 *            acumulando os resultados e devolvendo a media dos mesmos.       *
 *****************************************************************************/

double simula_experimentos(char padrao[MAX_TAMANHO], int quantos_experimentos)
{
  int indice,
      soma = 0;    /* Guarda os resultados dos simulacoes de lances de moeda */

  for (indice = 1; indice <= quantos_experimentos; indice++)
    soma += simula_lances(padrao);
  return (double) soma / quantos_experimentos;
}

/******************************************************************************
 * Funcao: main                                                               *
 * Saida: 0 se o programa executou normalmente; -1 se houve algum problema.   *
 * Descricao: inicializa o programa e faz as chamadas das funcoes.            *
 *****************************************************************************/

int main(int argc, char *argv[])
{
  char padrao[MAX_TAMANHO];        /* Padrao de H's e T's a ser testado     */
  long semente;             /* Semente para o gerador de numeros aleatorios */
  unsigned int qtos_experiment;

  if (argc == 4)          /* Numero de parametros esta correto */
  {
    strcpy(padrao,ConvertToUpperCase(argv[1]));
    semente         = atol(argv[2]);
    qtos_experiment = atoi(argv[3]);
    if (strlen(padrao) > (MAX_TAMANHO - 1))
    {
      printf("Erro: 1o. parametro nao pode ter mais de 30 caracteres.\n");
      return -1;
    }
    if (qtos_experiment < 1)
    {
      printf("Erro: 3o. parametro deve ser maior ou igual a 1.\n");
      return -1;
    }
  }  
  else
  {
    printf("Erro: numero de argumentos invalido.\n");
    printf("1o. param.: padrao de H's e T's a ser simulado.\n");
    printf("2o. param.: semente a ser usada no gerador de aleatorios.\n");
    printf("3o. param.: se igual a 1, simula lances ate obter o padrao.\n");
    printf("            se maior que 1, executa varias sequencias de simulacoes, devolvendo a media dos resultados.\n");
    return -1;
  }

  gb_init_rand(semente);
  if (qtos_experiment == 1)
    printf("Numero de lancamentos = %d\n",simula_lances(padrao));
  else
    printf("Media dos lancamentos = %.4f\n",simula_experimentos(padrao,qtos_experiment));
  return 0;
}



