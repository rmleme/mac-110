/****************************************************************************
 * Autor: Rodrigo Mendes Leme         Numero USP: 3151151                   *
 * Curso: computacao                  Data: 7/05/1999                       *
 * Professor: Yoshiharu Kohayakawa                                          *
 * Exercicio Programa 1-A                                                   *
 * Compilador usado: Turbo C++ 3.0                                          *
 * Descricao: este programa simula o conhecido jogo NIM. Nesta versao, dois *
 *            seres humanos jogam entre si, comecando de uma configuracao   *
 *            inicial (definida pelo usuario) ate o momento em que nao res- *
 *            te nenhum palito em jogo.                                     *
 ***************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include "rotinas.h"

/************************ Declaracao de constantes *************************/

#define QUANTOS_MONTES 5
#define MAX_PALITOS    74            /* Numero maximo de palitos por monte */

/********************* Declaracao de variaveis globais *********************/

int quantos_palitos = 0,              /* Numero de palitos em jogo                    */
	 monte[QUANTOS_MONTES],            /* Vetor que representa os montes               */
	 deixa_no_monte[QUANTOS_MONTES],   /* Palitos a serem deixados nos montes por lance */
	 coluna_atual = 1,                 /* Coluna na tela onde se desenha os palitos    */
	 linha_atual  = 7;                 /* Linha na tela onde se desenha os palitos     */

/****************************************************************************
 * Funcao: desenha_monte                                                    *
 * Entrada: coluna: coluna da tela onde serao desenhados os palitos do monte*
 *          linha: linha da tela onde serao desenhados os palitos do monte. *
 *          quantidade: numero de palitos que serao desenhados na tela.     *
 * Descricao: desenha na tela um monte de palitos.                          *
 ***************************************************************************/

void desenha_monte(int coluna, int linha, int quantidade)
{
  int indice;

  gotoxy(coluna,linha);
  for (indice = 0; indice < quantidade; indice++)
    printf("I");
}

/****************************************************************************
 * Funcao: desenha_palitos                                                  *
 * Entrada: monte1: numero de palitos a desenhar do 1o. monte.              *
 *          monte2: numero de palitos a desenhar do 2o. monte.              *
 *          monte3: numero de palitos a desenhar do 3o. monte.              *
 *          monte4: numero de palitos a desenhar do 4o. monte.              *
 *          monte5: numero de palitos a desenhar do 5o. monte.              *
 * Descricao: desenha na tela os palitos de cada monte.                     *
 ***************************************************************************/

void desenha_palitos(int monte1, int monte2, int monte3, int monte4, int monte5)
{
  int indice,
		max_palitos = -1;   /* Numero de palitos existentes no maior monte */

  if (linha_atual > 24)     /* Acabou o espaco para desenhar os palitos, */
  {                         /* limpa a tela e volta para o comeco        */
    limpa_tela(7,24);
	 linha_atual = 7;
  }

  for (indice = 1; indice <= 5; indice++)   /* Desenha os indices dos montes */
  {
    gotoxy(coluna_atual,linha_atual + indice - 1);
	 if (monte[indice - 1] == 0)      /* O monte esta vazio, */
	   textcolor(DARKGRAY);           /* destaca-o na tela   */
	 else
	   textcolor(WHITE);
	 cprintf("%d) ",indice);
  }
  textcolor(WHITE);

  desenha_monte(coluna_atual + 3,linha_atual,monte1);
  if (monte1 > max_palitos)    /* O monte 1 tem mais palitos que os outros */
    max_palitos = monte1;
  desenha_monte(coluna_atual + 3,linha_atual + 1,monte2);
  if (monte2 > max_palitos)    /* O monte 2 tem mais palitos que os outros */
    max_palitos = monte2;
  desenha_monte(coluna_atual + 3,linha_atual + 2,monte3);
  if (monte3 > max_palitos)    /* O monte 3 tem mais palitos que os outros */
    max_palitos = monte3;
  desenha_monte(coluna_atual + 3,linha_atual + 3,monte4);
  if (monte4 > max_palitos)    /* O monte 4 tem mais palitos que os outros */
	 max_palitos = monte4;
  desenha_monte(coluna_atual + 3,linha_atual + 4,monte5);
  if (monte5 > max_palitos)    /* O monte 5 tem mais palitos que os outros */
	  max_palitos = monte5;

  if (max_palitos > 0)      /* Ainda ha palitos a serem desenhados */
    escrevexy(coluna_atual + max_palitos + 4,linha_atual + 2,"->");

  coluna_atual += 8 + max_palitos;
  if (coluna_atual + 5 + max_palitos > 80)   /* Acabou o espaco para desenhar */
  {                                          /* os palitos naquela linha,  */
    coluna_atual = 1;                        /* muda de linha              */
	 linha_atual += 6;
  }
}

/****************************************************************************
 * Funcao: numero_de_palitos                                                *
 * Entrada: qual_monte: monte cujo numero de palitos sera definido.         *
 * Saida: o numero de palitos que o usuario deseja para aquele monte.       *
 * Descricao: pergunta ao usuario quantos palitos ele deseja para determi-  *
 *            nado monte.                                                   *
 ***************************************************************************/

int numero_de_palitos(int qual_monte)
{
  int palitos;

  do         /* Repete a pergunta ate o numero de palitos ser valido */
  {
	 gotoxy(1,3);
	 printf("Qual o numero de palitos do %do. monte (1 a 74)? ",qual_monte);
	 scanf("%d",&palitos);
	 gotoxy(49,3);
	 clreol();
  }
  while ((palitos < 1) || (palitos > MAX_PALITOS));

  return palitos;
}

/****************************************************************************
 * Funcao: inicializa_tela                                                  *
 * Descricao: desenha a tela inicial do programa.                           *
 ***************************************************************************/

void inicializa_tela(void)
{
  int coluna;

  textcolor(WHITE);
  textbackground(BLUE);
  clrscr();
  textbackground(CYAN);
  clreol();
  escrevexy(39,1,"NIM");
  escrevexy(55,1,"Rodrigo Mendes Leme - USP");
  gotoxy(1,25);
  textbackground(LIGHTGRAY);
  clreol();
  textbackground(BLUE);
  gotoxy(1,5);
  for (coluna = 1; coluna <= 80; coluna++)    /* Desenha uma linha  */
    escrevexy(coluna,5,"Ä");                  /* horizontal na tela */
}

/****************************************************************************
 * Funcao: inicializa_montes                                                *
 * Descricao: preenche os montes de palitos com os valores obtidos do usua- *
 *            rio.                                                          *
 ***************************************************************************/

void inicializa_montes(void)
{
  int indice;

  for (indice = 1; indice <= QUANTOS_MONTES; indice++)    /* Percorre cada */
  {                                                       /* monte         */
	 monte[indice - 1] = numero_de_palitos(indice);
	 quantos_palitos += monte[indice - 1];
  }

  desenha_palitos(monte[0],monte[1],monte[2],monte[3],monte[4]);
}

/****************************************************************************
 * Funcao: escolhe_pri_jogador                                              *
 * Saida: o jogador que iniciara a partida (L ou R).                        *
 * Descricao: pergunta ao usuario qual jogador ira iniciar a partida.       *
 ***************************************************************************/

char escolhe_pri_jogador(void)
{
  char pri_jogador;

  do           /* Repete a pergunta ate o usuario digitar algo valido */
  {
    escrevexy(1,4,"Qual jogador sera o primeiro, 'L' ou 'R'? ");
	 scanf("%c",&pri_jogador);
	 gotoxy(43,4);
	 clreol();
  }
  while ((toupper(pri_jogador) != 'R') && (toupper(pri_jogador) != 'L'));

  limpa_tela(3,4);
  return toupper(pri_jogador);
}

/****************************************************************************
 * Funcao: le_lance                                                         *
 * Entrada: *qual_monte: monte do qual o usuario deseja tirar palitos.      *
 *          *palitos_a_deixar: numero de palitos que o usuario quer deixar. *
 * Descricao: pergunta ao usuario de qual monte deseja tirar palitos e      *
 *            quantos deve deixar naquele monte.                            *
 ***************************************************************************/

void le_lance(int *qual_monte, int *palitos_a_deixar)
{
  do        /* Repete ate o usuario digitar algo valido */
  {
    escrevexy(1,3,"De qual monte deseja tirar palito(s)? ");
	 scanf("%d",qual_monte);
	 if ((*qual_monte < 1) || (*qual_monte > QUANTOS_MONTES) ||
	     (monte[*qual_monte - 1] == 0))    /* Dado invalido, corrige-o */
	 {
	   gotoxy(39,3);
		clreol();
	 }
  }
  while ((*qual_monte < 1) || (*qual_monte > QUANTOS_MONTES) ||
			(monte[*qual_monte - 1] == 0));

  do        /* Repete ate o usuario digitar algo valido */
  {
    escrevexy(1,4,"Quantos palitos deseja deixar nesse monte (0 ate ");
	 printf("%d)? ",monte[*qual_monte - 1] - 1);
	 scanf("%d",palitos_a_deixar);
	 gotoxy(51,4);
	 clreol();
  }
  while ((*palitos_a_deixar < 0) || (*palitos_a_deixar >= monte[*qual_monte - 1]));

  limpa_tela(3,4);
}

/****************************************************************************
 * Funcao: configura_monte_aux                                              *
 * Entrada: qual_monte: monte do qual o usuario deseja tirar palitos.       *
 *          palitos_a_deixar: numero de palitos que o usuario quer deixar.  *
 * Descricao: preenche um vetor auxiliar de montes indicando, para cada     *
 *            monte, quantos palitos devem ser deixados em cada um.         *
 ***************************************************************************/

void configura_monte_aux(int qual_monte, int palitos_a_deixar)
{
  int indice;

  for (indice = 0; indice <= QUANTOS_MONTES - 1; indice++)
    deixa_no_monte[indice] = monte[indice];
  deixa_no_monte[qual_monte - 1] = palitos_a_deixar;   /* Monte a alterar */
}

/****************************************************************************
 * Funcao: altera_palitos                                                   *
 * Entrada: monte1: numero de palitos a deixar no 1o. monte.                *
 *          monte2: numero de palitos a deixar no 2o. monte.                *
 *          monte3: numero de palitos a deixar no 3o. monte.                *
 *          monte4: numero de palitos a deixar no 4o. monte.                *
 *          monte5: numero de palitos a deixar no 5o. monte.                *
 * Descricao: deixa em cada monte o numero de palitos passado nos parame-   *
 *            tros.                                                         *
 ***************************************************************************/

void altera_palitos(int monte1, int monte2, int monte3, int monte4, int monte5)
{
  monte[0] = monte1;
  monte[1] = monte2;
  monte[2] = monte3;
  monte[3] = monte4;
  monte[4] = monte5;
  desenha_palitos(monte[0],monte[1],monte[2],monte[3],monte[4]);
}

/****************************************************************************
 * Funcao: main                                                             *
 * Descricao: chama as funcoes do programa e executa o jogo ate se chegar a *
 *            um vencedor.                                                  *
 ***************************************************************************/

void main(void)
{
  int qual_monte,           /* Monte do qual serao tirados palitos         */
		palitos_a_deixar,     /* Numero de palitos a ser deixado em um monte */
		jogador_atual,
		vencedor;

  inicializa_tela();
  inicializa_montes();
  jogador_atual = escolhe_pri_jogador();
  while (quantos_palitos > 0)      /* Enquanto houver palitos em jogo */
  {
    rodape(jogador_atual,", faca sua jogada.");
	 le_lance(&qual_monte,&palitos_a_deixar);
	 configura_monte_aux(qual_monte,palitos_a_deixar);
	 altera_palitos(deixa_no_monte[0],deixa_no_monte[1],deixa_no_monte[2],deixa_no_monte[3],deixa_no_monte[4]);
    quantos_palitos = monte[0] + monte[1] + monte[2] + monte[3] + monte[4];
    if (quantos_palitos == 0)      /* O jogo acabou */
	   vencedor = jogador_atual;
	 if (jogador_atual == 'L')      /* Passa a vez para o proximo jogador */
	   jogador_atual = 'R';
	 else
		jogador_atual = 'L';
  }
  rodape(vencedor," e o vencedor, parabens!");
  getch();
  textcolor(LIGHTGRAY);
  textbackground(BLACK);
  clrscr();
}