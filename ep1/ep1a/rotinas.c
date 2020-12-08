/****************************************************************************
 * Modulo: rotinas auxiliares                                               *
 * Autor: Rodrigo Mendes Leme - 3151151                                     *
 * Descricao: modulo que contem rotinas auxiliares genericas para a tela.   *
 ***************************************************************************/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "rotinas.h"

/****************************************************************************
 * Funcao: escrevexy                                                        *
 * Entrada: coluna: coluna onde sera escrita a cadeia.                      *
 *          linha: linha onde sera escrita a cadeia.                        *
 *          cadeia: texto que sera escrito na tela.                         *
 * Descricao: a funcao escreve um texto na tela, de acordo com as coordena- *
 *            das recebidas nos parametros.                                 *
 ***************************************************************************/

void escrevexy(int coluna, int linha, char *cadeia)
{
  gotoxy(coluna,linha);
  printf("%s",cadeia);
}

/****************************************************************************
 * Funcao: rodape                                                           *
 * Entrada: caracter: uma letra que sera impressa na tela.                  *
 *          cadeia: uma cadeia de caracteres que sera impressa na tela.     *
 * Descricao: escreve na ultima linha da tela uma mensagem ao usuario.      *
 ***************************************************************************/

void rodape(char caracter, char *cadeia)
{
  int coluna;

  if (strlen(cadeia + 1) > 80)   /* A cadeia nao cabe no rodape, trunca-a */
    strncpy(cadeia,cadeia,80);
  coluna = (80 - strlen(cadeia + 1)) / 2;

  gotoxy(coluna,25);
  textcolor(BLACK);
  textbackground(LIGHTGRAY);
  cprintf("%c%s",caracter,cadeia);
  textcolor(WHITE);
  textbackground(BLUE);
}

/****************************************************************************
 * Funcao: limpa_rodape                                                     *
 * Descricao: limpa a ultima linha da tela.                                 *
 ***************************************************************************/

void limpa_rodape(void)
{
  textbackground(LIGHTGRAY);
  gotoxy(1,25);
  clreol();
  textbackground(BLUE);
}

/****************************************************************************
 * Funcao: mensagem                                                         *
 * Entrada: cadeia: uma cadeia de caracteres que sera impressa na tela.     *
 * Descricao: escreve na ultima linha da tela uma mensagem ao usuario, e es-*
 *            pera ate que o mesmo pressione uma tecla.                     *
 ***************************************************************************/

void mensagem(char *cadeia)
{
  int coluna;

  if (strlen(cadeia) > 80)   /* A cadeia nao cabe no rodape, trunca-a */
    strncat(cadeia,cadeia,80);
  coluna = (80 - strlen(cadeia)) / 2;

  gotoxy(coluna,25);
  textcolor(BLACK);
  textbackground(LIGHTGRAY);
  cprintf("%s",cadeia);
  getch();
  limpa_rodape();
  textcolor(WHITE);
  textbackground(BLUE);
}

/****************************************************************************
 * Funcao: limpa_tela                                                       *
 * Entrada: y1: canto superior.                                             *
 *          y2: canto inferior.                                             *
 * Descricao: limpa a regiao da tela definida nos parametros.               *
 ***************************************************************************/

void limpa_tela(int y1, int y2)
{
  int linha;

  for (linha = y1; linha <= y2; linha++)
  {
    gotoxy(1,linha);
	 clreol();
  }
}

/****************************************************************************
 * Funcao: dec_para_bin                                                     *
 * Entrada: numero: numero decimal a ser convertido para binario            *
 * Descricao: converte um numero de decimal para binario.                   *
 ***************************************************************************/

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