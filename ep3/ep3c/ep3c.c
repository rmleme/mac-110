/******************************************************************************
 * Nome do aluno: Rodrigo Mendes Leme           Numero USP: 3151151           *
 * Curso: BCC                                   Data: 17/06/1999              *
 * Nome do Professor: Yoshiharu Kohayakawa                                    *
 * Exercicio Programa Numero 3-C                                              *
 * Compilador usado: GCC - Linux                                              *
 * Descricao: o programa tem por objetivo encontrar o maior numero possivel   *
 *            de triplas de padroes de H's e T's que satisfacam a propriedade *
 *            p1 > p2 > p3 > p1. Isto e feito gerando-se todos os padroes pos-*
 *            siveis para um dado comprimento dos padroes. Em seguida, obtem- *
 *            se todas as probabilidades do jogo de Peeney-Ante entre esses   *
 *            padroes, encontrando, por fim, os padroes que satisfacam a cita-*
 *            da propriedade.                                                 *
 *****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "strlib.h"
#include "gb_flip.h"

/************************* Declaracao de constantes **************************/

#define MAX_TAMANHO 31        /* Tamanho maximo dos padroes de H's e T's */

/**************************** Declaracao de tipos ****************************/

typedef struct
{
  double prob;      /* Probabilidade do padrao 1 ser melhor que o padrao 2 */
  int p1,           /* Indice para o padrao 1 no vetor de padroes          */
      p2;           /* Indice para o padrao 2 no vetor de padroes          */
} prob_padroes;

/******************************************************************************
 * Funcao: dec_para_bin                                                       *
 * Entrada: numero: numero decimal a ser convertido para binario              *
 * Descricao: converte um numero de decimal para binario.                     *
 *****************************************************************************/

int dec_para_bin(int numero)
{
  int num_bin     = 0,
      potencia_10 = 1,
      quociente,
      resto;

  while (numero != 0)
  {
    quociente = numero / 2;
    resto     = numero % 2;
    num_bin += resto * potencia_10;
    numero = quociente;
    potencia_10 *= 10;
  }
  return num_bin;
}

/******************************************************************************
 * Funcao: pega_digito                                                        *
 * Entrada: *numero: numero do qual sera retirado um digito.                  *
 * Saida: o digito retirado do numero passado no parametro.                   *
 * Descricao: a funcao realiza uma divisao por 10 no numero do parametro, re- *
 *            tornando o resto obtido na divisao. O numero do parametro e al- *
 *            terado no processo.                                             *
 *****************************************************************************/

int pega_digito(int *numero)
{
  int divisor,
      resto;

  divisor = *numero / 10;
  resto   = *numero % 10;
  *numero = divisor;
  return resto;
}

/******************************************************************************
 * Funcao: inicializa_padroes                                                 *
 * Entrada: vetor_padroes: vetor que sera preenchido com H's e T's.           *
 *          quantos_padroes: numero de padroes que serao incluidos no vetor.  *
 *          tamanho_padroes: tamanho dos padroes de H's e T's.                *
 * Descricao: preenche um vetor com padroes de H's e T's.                     *
 *****************************************************************************/

void inicializa_padroes(char vetor_padroes[][MAX_TAMANHO], int quantos_padroes, int tamanho_padroes)
{
  int numero,
      num_bin,
      ind_cadeia,
      digito;
  char cadeia[MAX_TAMANHO];

  cadeia[tamanho_padroes] = '\0';
  for (numero = 0; numero <= quantos_padroes - 1; numero++)
  {
    num_bin = dec_para_bin(numero);
    ind_cadeia = 1;
    while (num_bin != 0)        /* Obtem todos os digitos de num_bin,        */
    {                           /* quebrando-o em sucessivas divisoes por 10 */
      digito = pega_digito(&num_bin);
      if (digito == 0)
        cadeia[tamanho_padroes - ind_cadeia++] = '0';
      else
        cadeia[tamanho_padroes - ind_cadeia++] = '1';
    }
    while (ind_cadeia <= tamanho_padroes)        /* Preenche com 0's o resto */
      cadeia[tamanho_padroes - ind_cadeia++] = '0';             /* da cadeia */

    /* Preenche a cadeia com os padroes de H's e T's; 0->H e 1->T */
    for (ind_cadeia = 0; ind_cadeia <= tamanho_padroes - 1; ind_cadeia++)
      if (cadeia[ind_cadeia] == '0')
        cadeia[ind_cadeia] = 'H';
      else
        cadeia[ind_cadeia] = 'T';
      strcpy(vetor_padroes[numero],cadeia);
  }
}

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
 * Funcao: prob_vitoria                                                       *
 * Entrada: *padrao1: um dos padroes de H's e T's que participara do jogo.    *
 *          *padrao2: o outro padrao de H's e T's que participara do jogo.    *
 *          qtos_experiment: numero de vezes que sera simulado o jogo.        *
 * Saida: a probabilidade do padrao 1 ser "melhor" que o padrao 2.            *
 * Descricao: a funcao testa o jogo de Penney-Ante diversas vezes com os dois *
 *            padroes.                                                        *
 *****************************************************************************/

double prob_vitoria(char padrao1[MAX_TAMANHO], char padrao2[MAX_TAMANHO], int qtos_experiment)
{
  int jogada,
      indice,
      quantas_vit_p1 = 0,      /* Numero de vitorias do padrao 1 */
      quantas_vit_p2 = 0;      /* Numero de vitorias do padrao 2 */

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
  return (double) quantas_vit_p1 / qtos_experiment;
}

/******************************************************************************
 * Funcao: main                                                               *
 * Saida: 0 se o programa executou normalmente; -1 se houve algum problema.   *
 * Descricao: inicializa o programa e faz as chamadas das funcoes.            *
 *****************************************************************************/

int main(int argc, char *argv[])
{
  char padroes[100000][MAX_TAMANHO];
  prob_padroes probs[100000];
  unsigned int quantos_jogos,
               tamanho_padroes,
               opcao,
               mais_lento,            /* Indices utilizados           */
               lento,                 /* na geracao de probabilidades */
               rapido,                /* e procura das triplas        */
               mais_rapido,           /* no vetor de probabilidades   */
               quantas_probs   = 0,
               quantas_triplas = 0;

  if (argc == 4)          /* Numero de parametros esta correto */
  {
    quantos_jogos   = atoi(argv[1]);
    tamanho_padroes = atoi(argv[2]);
    opcao           = atoi(argv[3]);
    if (quantos_jogos < 1)
    {
      printf("Erro: 1o. parametro deve ser maior que zero.\n");
      return -1;
    }
    if ((tamanho_padroes < 1) || (tamanho_padroes > 30))
    {
      printf("Erro: 2o. parametro deve ser maior que zero e menor que 30.\n");
      return -1;
    }
    if ((opcao != 0) && (opcao != 1))
    {
      printf("Erro: 3o. parametro deve valer 0 ou 1.\n");
      return -1;
    }
  }  
  else
  {
    printf("Erro: numero de argumentos invalido.\n");
    printf("1o. param.: numero de jogos a ser simulado entre dois padroes.\n");
    printf("2o. param.: comprimento dos padroes a serem testados.\n");
    printf("3o. param.: 0 -> mostra apenas o total de triplas encontradas.\n");
    printf("            1 -> mostra todas as triplas na tela.\n");
    return -1;
  }

  gb_init_rand(31415);      /* Semente definida arbitrariamente */
  inicializa_padroes(padroes,pow(2,tamanho_padroes),tamanho_padroes);

  /* Testa as probabilidades de vitoria de todos os padroes sobre os outros */
  for (lento = 0; lento < pow(2,tamanho_padroes) - 1; lento++)
    for (rapido = 0; rapido <= pow(2,tamanho_padroes) - 1; rapido++)
      if (lento != rapido)        /* Nao precisa testar o mesmo padrao */
      {
        probs[quantas_probs].prob = prob_vitoria(padroes[lento],padroes[rapido],quantos_jogos);
        probs[quantas_probs].p1 = lento;
        probs[quantas_probs].p2 = rapido;
        quantas_probs++;
      }

  /* Procura as triplas desejadas no vetor de probabilidades */
  for (mais_lento = 0; mais_lento < quantas_probs - 3; mais_lento++)
    for (lento = mais_lento + 1; lento < quantas_probs - 2; lento++)
      for (rapido = lento + 1; rapido < quantas_probs - 1; rapido++)
        for (mais_rapido = rapido + 1; mais_rapido < quantas_probs; mais_rapido++)
        if ((probs[mais_lento].p2 == probs[lento].p1) &&
            (probs[lento].p2 == probs[rapido].p1) &&
            (probs[rapido].p2 == probs[mais_rapido].p1) &&
            (probs[mais_rapido].p2 == probs[mais_lento].p1))
          if ((probs[mais_lento].prob > 0.5) && (probs[lento].prob > 0.5) &&
              (probs[rapido].prob > 0.5) && (probs[mais_rapido].prob > 0.5))
            if (opcao == 0)           /* Mostra apenas o total de triplas */
              quantas_triplas++;
            else                      /* Mostra todas as triplas na tela */
              printf("(%s, %s, %s)\n",padroes[probs[mais_lento].p1],
                     padroes[probs[lento].p1],padroes[probs[rapido].p1]);

  if (opcao == 0)           /* Mostra apenas o total de triplas */
      printf("Total de triplas: %d\n",quantas_triplas);
  return 0;
}
