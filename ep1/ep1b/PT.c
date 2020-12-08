#include <stdio.h>
#include <stdlib.h>
#include "pt.h"

int lance_prof_Teoria(int n1, int n2, int n3, int n4, int n5, int f)
{
    int monte;
    int novo_valor;
    int nimsum = (n1 ^ n2 ^ n3 ^ n4 ^ n5);

    if (nimsum == 0) {
	if (n1) {
	    monte = 1;
	    novo_valor = n1 - 1;
	} else if (n2) {
	    monte = 2;
	    novo_valor = n2 - 1;
	} else if (n3) {
	    monte = 3;
	    novo_valor = n3 - 1;
	} else if (n4) {
	    monte = 4;
	    novo_valor = n4 - 1;
	} else {
	    monte = 5;
	    novo_valor = n5 - 1;
	}
    } else {
	if ((n1 ^ nimsum) < n1) {
	    monte = 1;
	    novo_valor = n1 ^ nimsum;
	} else if ((n2 ^ nimsum) < n2) {
	    monte = 2;
	    novo_valor = n2 ^ nimsum;
	} else if ((n3 ^ nimsum) < n3) {
	    monte = 3;
	    novo_valor = n3 ^ nimsum;
	} else if ((n4 ^ nimsum) < n4) {
	    monte = 4;
	    novo_valor = n4 ^ nimsum;
	} else if ((n5 ^ nimsum) < n5) {
	    monte = 5;
	    novo_valor = n5 ^ nimsum;
	} else {
	    printf("Aconteceu algo muito errado...  Conserte-me!!!\n");
	    exit(0);
	}
    }

    if (f)
	return novo_valor;
    else
	return monte;
}

/**************************************************************************

As rotinas seguintes sao copiadas do programa de Knuth.  Veja

  http://www-cs-faculty.stanford.edu/~knuth/programs.html

***************************************************************************/

/*    This program by D E Knuth is in the public domain and freely copyable
 *    AS LONG AS YOU MAKE ABSOLUTELY NO CHANGES!
 *    It is explained in Seminumerical Algorithms, 3rd edition, Section 3.6
 *    (or in the errata to the 2nd edition --- see
 *        http://www-cs-faculty.stanford.edu/~knuth/taocp.html
 *    in the changes to pages 171 and following of Volume 2).              */

/*    If you find any bugs, please report them immediately to
 *                 taocp@cs.stanford.edu
 *    (and you will be rewarded if the bug is genuine). Thanks!            */

/************ see the book for explanations and caveats! *******************/

/* the old C calling conventions are used here, for reasons of portability */

#define KK 100                     /* the long lag */
#define LL  37                     /* the short lag */
#define MM (1L<<30)                 /* the modulus */
#define mod_diff(x,y) (((x)-(y))&(MM-1)) /* subtraction mod MM */

long ran_x[KK];                    /* the generator state */

/* void ran_array(long aa[],int n) */
void ran_array(long *aa, int n)    /* put n new random numbers in aa */
{
  register int i,j;
  for (j=0;j<KK;j++) aa[j]=ran_x[j];
  for (;j<n;j++) aa[j]=mod_diff(aa[j-KK],aa[j-LL]);
  for (i=0;i<LL;i++,j++) ran_x[i]=mod_diff(aa[j-KK],aa[j-LL]);
  for (;i<KK;i++,j++) ran_x[i]=mod_diff(aa[j-KK],ran_x[i-LL]);
}

#define TT  70   /* guaranteed separation between streams */
#define is_odd(x)  ((x)&1)          /* units bit of x */
#define evenize(x) ((x)&(MM-2))   /* make x even */

/* void ran_start(long seed) */
void ran_start(long seed)    /* do this before using ran_array */
{
  register int t,j;
  long x[KK+KK-1];              /* the preparation buffer */
  register long ss=evenize(seed+2);
  for (j=0;j<KK;j++) {
    x[j]=ss;                      /* bootstrap the buffer */
    ss<<=1; if (ss>=MM) ss-=MM-2; /* cyclic shift 29 bits */
  }
  for (;j<KK+KK-1;j++) x[j]=0;
  x[1]++;              /* make x[1] (and only x[1]) odd */
  ss=seed&(MM-1);
  t=TT-1; while (t) {
    for (j=KK-1;j>0;j--) x[j+j]=x[j];  /* "square" */
    for (j=KK+KK-2;j>KK-LL;j-=2) x[KK+KK-1-j]=evenize(x[j]);
    for (j=KK+KK-2;j>=KK;j--) if(is_odd(x[j])) {
      x[j-(KK-LL)]=mod_diff(x[j-(KK-LL)],x[j]);
      x[j-KK]=mod_diff(x[j-KK],x[j]);
    }
    if (is_odd(ss)) {              /* "multiply by z" */
      for (j=KK;j>0;j--)  x[j]=x[j-1];
      x[0]=x[KK];            /* shift the buffer cyclically */
      if (is_odd(x[KK])) x[LL]=mod_diff(x[LL],x[KK]);
    }
    if (ss) ss>>=1; else t--;
  }
  for (j=0;j<LL;j++) ran_x[j+KK-LL]=x[j];
  for (;j<KK;j++) ran_x[j-LL]=x[j];
}

/* the following routines are from exercise 3.6--15 */
/* after calling ran_start, get new randoms by, e.g., "x=ran_arr_next()" */

#define QUALITY 1009 /* recommended quality level for high-res use */
long ran_arr_buf[QUALITY];
long ran_arr_sentinel=-1;
long *ran_arr_ptr=&ran_arr_sentinel; /* the next random number, or -1 */

#define ran_arr_next() (*ran_arr_ptr>=0? *ran_arr_ptr++: ran_arr_cycle())
long ran_arr_cycle()
{
  ran_array(ran_arr_buf,QUALITY);
  ran_arr_buf[100]=-1;
  ran_arr_ptr=ran_arr_buf+1;
  return ran_arr_buf[0];
}

/**********************************************************************

Fim das rotinas de Knuth.

**********************************************************************/

long my_strlen(char *s)
{
  long l=0;
  while (*s) l++,s++;
  return l;
}

char *mens_neg()
{

  static char *expl_negativo[]={"Ops!  ", "Nao gostei...!  ", "Que chato!  ",
                       "Hmmm... ai ai ai...  ", "Bem... hmmm...  ",
		       "Vejamos... ora ora...  "
  };

  static char *recheio_negativo[]={"Bem... o que posso fazer...  ",
	 "Sera que voce nao vai cometer algum erro para eu ter alguma chance?  ",
			  "Nao sei o que fazer...  ",
			  "Vamos ver no que da...  ",
			  "Nao vou prestar muita atencao...  ",
	 "Sera que voce descobriu como usar algebra para ganhar neste jogo?  ",
  };

  static char *fim_negativo[]={"Voce aceita empate?  ",
		      "Por favor, cometa um erro!  ",
		      "Mas que azar o meu...  mas vamos la...  " 
  };

  long i, j, k, ii;
  char *s, *ss;

  i=ran_arr_next()%6;
  j=ran_arr_next()%6;
  k=ran_arr_next()%3;

  s=ss=(char *)malloc(1+my_strlen(expl_negativo[i])
		    +my_strlen(recheio_negativo[j])
		    +my_strlen(fim_negativo[k]));
  if (!s) {
    printf("Estou cansado...  Chega por agora...!\n");
    exit(1);
  }

  for (ii=0; (*s=expl_negativo[i][ii])!=0; ii++,s++);
  for (ii=0; (*s=recheio_negativo[j][ii])!=0; ii++,s++);
  for (ii=0; (*s=fim_negativo[k][ii])!=0; ii++,s++);
  *(++s)=0;

  return ss;
}

char* mens_pos()
{
  static char *expl_positivo[]={"Uau!  ", "Joia!  ", "Bacana!  ",
                       "Legal!  ", "Gostei!  ", "Aha!  "
  };

  static char *recheio_positivo[]={"Acho que sei ganhar!  ",
			  "Pode deixar comigo!  ",
			  "Estou confiante!  ",
			  "Voce nao quer desistir?  ",
			  "Tem certeza que quer continuar...?  ",
        "Nada como saber um pouco de algebra para ganhar neste jogo!  "
  };

  static char *fim_positivo[]={"OK, vamos la!  ",
		      "Mandemos ver!  ",
		      "Nao quer desistir mesmo?  "
  };

  long i, j, k, ii;
  char *s, *ss;

  i=ran_arr_next()%6;
  j=ran_arr_next()%6;
  k=ran_arr_next()%3;

  s=ss=(char *)malloc(1+my_strlen(expl_positivo[i])
		    +my_strlen(recheio_positivo[j])
		    +my_strlen(fim_positivo[k]));
  if (!s) {
    printf("Estou cansado...  Chega por agora...!\n");
    exit(1);
  }

  for (ii=0; (*s=expl_positivo[i][ii])!=0; ii++,s++);
  for (ii=0; (*s=recheio_positivo[j][ii])!=0; ii++,s++);
  for (ii=0; (*s=fim_positivo[k][ii])!=0; ii++,s++);
  *(s++)=0;

  return ss;
}

char *mens_prof_Teoria(int n1, int n2, int n3, int n4, int n5)
{
  int nimsum=(n1^n2^n3^n4^n5);
  long seed=n1+n2+n3+n4+n5; /* Para o gerador de numeros aleatorios. */

  ran_start(seed);
  if (nimsum==0)
    return mens_neg();
  else
    return mens_pos();
}