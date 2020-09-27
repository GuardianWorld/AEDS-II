#include "TADSBB.h"

void inicializar(TipoApontador *no)
{
    *no = NULL;
	return;
}

void inserir(TipoApontador *no, int data)
{
	short Fim;
	TipoInclinacao Ino;
	IInsere(data, no, &Ino, &Fim);
}

void IInsere(int x, TipoApontador *no, TipoInclinacao *IAp, short *Fim)
{
	if (*no == NULL)
	{
		*no = (TipoApontador)malloc(sizeof(TipoNo));
		*IAp = Horizontal;
		(*no)->data = x;
		(*no)->bitE = Vertical;
		(*no)->bitD = Vertical;
		(*no)->esq = NULL;
		(*no)->dir = NULL;
		*Fim = false;
		return;
	}
	if (x < (*no)->data)
	{
		IInsere(x, &(*no)->esq, &(*no)->bitE, Fim);
		if (*Fim) return;
		if ((*no)->bitE != Horizontal)
		{
			*Fim = true;
			return;
		}
		if ((*no)->esq->bitE == Horizontal)
		{
			EE(no);
			*IAp = Horizontal;
			return;
		}
		if ((*no)->esq->bitD == Horizontal) 
		{
			ED(no); 
			*IAp = Horizontal;
		}
		return;
	}
	if (x <= (*no)->data) 
	{
		printf("Erro: Chave ja esta na arvore\n");
		*Fim = true;
		return;
	}
	IInsere(x, &(*no)->dir, &(*no)->bitD, Fim);
	if (*Fim) return;
	if ((*no)->bitD != Horizontal)
	{
		*Fim = true; return;
	}
	if ((*no)->dir->bitD == Horizontal) 
	{
		DD(no);
		*IAp = Horizontal;
		return;
	}
	if ((*no)->dir->bitE == Horizontal) 
	{
		DE(no); 
		*IAp = Horizontal;
	}
	return;
}

void EE(TipoApontador *no)
{
	TipoApontador Aux;
	Aux = (*no)->esq;
	(*no)->esq = Aux->dir;
	Aux->dir = *no;
	Aux->bitE = Vertical;
	(*no)->bitE = Vertical;
	*no = Aux;
	return;
}
void ED(TipoApontador *no)
{
	TipoApontador aux, aux2;
	aux = (*no)->esq;
	aux2 = aux->dir;
	aux->bitD = Vertical;
	(*no)->bitE = Vertical;
	aux->dir = aux2->esq;
	aux2->esq = aux;
	(*no)->esq = aux2->dir;
	aux2->dir = *no;
	*no = aux2;
	return;
}
void DD(TipoApontador *no)
{
	TipoApontador Aux;
	Aux = (*no)->dir;
	(*no)->dir = Aux->esq;
	Aux->esq = *no;
	Aux->bitD = Vertical;
	(*no)->bitD = Vertical;
	*no = Aux;
	return;
}
void DE(TipoApontador *no) // < Problemas
{
	TipoApontador Aux, Aux2;
	Aux = (*no)->dir;
	Aux2 = Aux->esq;
	Aux->bitE = Vertical;
	(*no)->bitD = Vertical;
	Aux->esq = Aux2->dir;
	Aux2->dir = Aux;
	(*no)->dir = Aux2->esq;
	Aux2->esq = *no;
	*no = Aux2;
	return;
}


void buscarElemento(TipoApontador no, int data)
{
	TipoApontador aux = no;
	while (aux != NULL)
	{
		if (data == aux->data)
		{
			printf("Valor encontrado\n");
			return;
		}
		else if (data > aux->data)
		{
			aux = aux->dir;
			//printf("Direita\n");
		}
		else if (data < aux->data)
		{
			aux = aux->esq;
			//printf("Esquerda\n");
		}
		
	}
	printf("Valor nao encontrado\n");
	return;
}

void imprimeOrdem(TipoApontador no)
{
	//Esquerda -> Imprime -> Direita -> Retorna;
	if (no != NULL)
	{
		imprimeOrdem(no->esq); //Vai para a esquerda;
		printf("%d ", no->data);
		imprimeOrdem(no->dir);
	}
	return;
}

void imprimePreOrdem(TipoApontador no)
{
	//Esquerda -> Imprime -> Direita -> Retorna;
	if (no != NULL)
	{
		printf("No: [%d], BitD: [%d] BitE: [%d]\n", no->data, no->bitD, no->bitE);
		imprimePreOrdem(no->esq); //Vai para a esquerda;
		imprimePreOrdem(no->dir);
	}
	return;
}

void imprimePosOrdem(TipoApontador no)
{
	//Esquerda -> Imprime -> Direita -> Retorna;
	if (no != NULL)
	{
		imprimePosOrdem(no->esq); //Vai para a esquerda;
		imprimePosOrdem(no->dir);
		printf("%d ", no->data);
	}
	return;
}

void deletar(TipoApontador *no, int data)
{
	short Fim;
	Ideletar(no, data, &Fim);
}

void Ideletar(TipoApontador *no,int data, short *Fim)
{
	TipoApontador aux;
	if (*no == NULL)
	{
		printf("Chave nao esta na arvore\n");
		*Fim = true;
		return;
	}
	if ((*no)->data > data)
	{
		Ideletar(&(*no)->esq, data, Fim);
		if (!*Fim)
		{
			EsqCurto(no, Fim);
			return;
		}
	}
	if ((*no)->data < data)
	{
		Ideletar(&(*no)->dir, data, Fim);
		if (!*Fim)
		{
			DirCurto(no, Fim);
			return;
		}
	}
	*Fim = false; aux = *no;
	if (aux->dir == NULL)
	{
		*no = aux->esq;
		free(aux);
		if (*no != NULL)
		{
			*Fim = true;
			return;
		}
	}
	if (aux->esq == NULL)
	{
		*no = aux->dir;
		free(aux);
		if (*no != NULL)
		{
			*Fim = true;
			return;
		}
	}
	acharAntecessor(&aux->esq, aux, Fim);
	if (!*Fim)
	{
		EsqCurto(no, Fim);
	}
}

void acharAntecessor(TipoApontador *no, TipoApontador aux, short *Fim)
{
	if ((*no)->dir != NULL)
	{
		acharAntecessor(&(*no)->dir, aux, Fim);
		if (!*Fim)
		{
			DirCurto(no, Fim);
		}
	}
	aux->data = (*no)->data;
	aux = *no;
	*no = (*no)->esq;
	free(aux);
	if (*no != NULL)
	{
		*Fim = true;
	}
}

void EsqCurto(TipoApontador *no, short *Fim)
{
	TipoApontador aux;
	if ((*no)->bitE == Horizontal)
	{
		(*no)->bitE = Vertical; 
		*Fim = true;
		return;
	}
	if ((*no)->bitD == Horizontal)
	{
		aux = (*no)->dir;
		(*no)->dir = aux->esq;
		aux->esq = *no;
		*no = aux;
		if ((*no)->esq->dir->bitE == Horizontal)
		{
			DE(&(*no)->esq);
			(*no)->bitE = Horizontal;
		}
		else if ((*no)->esq->dir->bitD == Horizontal)
		{
			DD(&(*no)->esq);
			(*no)->bitE = Horizontal;
		}
		*Fim = true;
		return;
	}
	(*no)->bitD = Horizontal;
	if ((*no)->dir->bitE == Horizontal)
	{
		DE(no);
		*Fim = true;
		return;
	}
	if ((*no)->dir->bitD == Horizontal)
	{
		DD(no);
		*Fim = true;
		return;
	}
	
}
void DirCurto(TipoApontador *no, short *Fim)
{
	TipoApontador aux;
	if ((*no)->bitD == Horizontal)
	{
		(*no)->bitD = Vertical;
		*Fim = true;
		return;
	}
	if ((*no)->bitE == Horizontal)
	{
		aux = (*no)->esq;
		(*no)->esq = aux->dir;
		aux->dir = *no;
		*no = aux;
		if ((*no)->dir->esq->bitD == Horizontal)
		{
			ED(&(*no)->dir);
			(*no)->bitD = Horizontal;
		}
		else if ((*no)->dir->esq->bitE == Horizontal)
		{
			EE(&(*no)->dir);
			(*no)->bitD = Horizontal;
		}
		*Fim = true;
		return;
	}
	(*no)->bitE = Horizontal;
	if ((*no)->esq->bitD == Horizontal)
	{
		ED(no);
		*Fim = true;
		return;
	}
	if ((*no)->esq->bitE == Horizontal)
	{
		EE(no);
		*Fim = true;
		return;
	}
}
void deletarTudo(TipoApontador *no)
{
	while (*no != NULL)
	{
		deletar(&(*no), (*no)->data);
	}
	return;
}

int alturaSBBH(TipoApontador no, int vert)
{
	//Altura H = Considera apenas os verticais
	//Altura K = Codigo abaixo
	if (no != NULL)
	{
		int he = 0;
		int hd = 0;
		if (no->bitD == Vertical)
		{
			hd = alturaSBBH(no->dir, 1);
		}
		else
		{
			hd = alturaSBBH(no->dir, 0);
		}
		if (no->bitE == Vertical)
		{
			he = alturaSBBH(no->esq, 1);
		}
		else
		{
			he = alturaSBBH(no->esq, 0);
		}
		if (vert == 1)
		{
			if (he < hd)
			{
				return hd + 1;
			}
			else
			{
				return he + 1;
			}
		}
		else
		{
			if (he < hd)
			{
				return hd;
			}
			else
			{
				return he;
			}
		}
	}
	return 0;
}

int alturaSBB(TipoApontador no)
{
	//Altura H = Considera apenas os verticais
	//Altura K = Codigo abaixo
	if (no != NULL)
	{
		int ke = alturaSBB(no->esq);
		int kd = alturaSBB(no->dir);
		if (ke < kd)
		{
			return kd + 1;
		}
		else
		{
			return ke + 1;
		}
	}
	return -1;
}

