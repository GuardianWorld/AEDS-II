#ifndef TADSBB_H_INCLUDED
#define TADSBB_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct TipoNo* TipoApontador;

typedef enum {
	Vertical, Horizontal
}TipoInclinacao;

typedef struct TipoNo{
    int data;
    TipoApontador esq, dir;
	TipoInclinacao bitE, bitD;
} TipoNo;

void inicializar(TipoApontador *no);
void inserir(TipoApontador *no,int data);
void IInsere(int x, TipoApontador *no,TipoInclinacao *IAp, short *Fim);
void deletar(TipoApontador *no,int data);
void Ideletar(TipoApontador *no, int data, short *Fim);
void EsqCurto(TipoApontador *no, short *Fim);
void DirCurto(TipoApontador *no, short *Fim);
void acharAntecessor(TipoApontador *no, TipoApontador aux, short *Fim);
void deletarTudo(TipoApontador *no);
void imprimeOrdem(TipoApontador no);
void imprimePosOrdem(TipoApontador no);
void imprimePreOrdem(TipoApontador no);
void buscarElemento(TipoApontador no, int data);
int alturaSBB(TipoApontador no);
int alturaSBBH(TipoApontador no, int vert);

void EE(TipoApontador *no);
void ED(TipoApontador *no);
void DE(TipoApontador *no);
void DD(TipoApontador *no);
#endif // TADBST_H_INCLUDED
