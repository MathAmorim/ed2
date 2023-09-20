#include <stdio.h>
#include <stdlib.h>
typedef struct no{
    int dado;
    int alt;
    struct no *esq, *dir;

}No;

//void inserir(No **, int);
void inserir_avl(No **, int);
void pre_ordem(No **);
void em_ordem(No **);
void pos_ordem(No **);
void menu();
int qtd(No **);
int * maior_rec(No **);
int * maior(No **);
void mostra_folha(No **);
int altura(No **);
void rse(No **);
void rsd(No **);
void rde(No **);
void rdd(No **);
int fat_bal(No **);
void correcao(No **);
int max(No **, No **);
//--------------------------------------//
int main(){
    menu();
}

void menu(){
    system("clear||cls");
    int opc, valor;
    No *r = NULL;
    int *aux;

    inserir_avl(&r, 10);
    inserir_avl(&r, 15);
    inserir_avl(&r, 20);
    /* inserir_avl(&r, 20);
    inserir_avl(&r, 23);
    inserir_avl(&r, 70);
    inserir_avl(&r, 80);
    inserir_avl(&r, 55);
    inserir_avl(&r, 72); */
    


    pre_ordem(&r);
    printf("\n");
    
    
}
void inserir_avl(No **raiz, int vlr){
    
    if(*raiz == NULL){
        No *novo;
        novo = (No *)malloc(sizeof(No));
        novo->dado = vlr;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;

        *raiz = novo;
    }else{
        if(vlr > (*raiz)->dado){
            inserir_avl(&(*raiz)->dir,vlr);
        }else{
            inserir_avl(&(*raiz)->esq,vlr);
        }
        (*raiz)->alt = 1 + max(&(*raiz)->esq, &(*raiz)->dir);
		correcao(raiz);
    }
}
void rse(No **r){
    /*
função para a rotação à esquerda*/
    if(*r == NULL || (*r)->dir == NULL){
        return;
    }
    No *s;

    printf("RSE(%i)\n",(*r)->dado);
    s = (*r)->dir; 
    (*r)->dir = s->esq;
    (*r)->alt = 1 + max(&(*r)->esq, &(*r)->dir); //atualizando a altura
    s->esq = *r;
    *r = s;
    (*r)->alt = 1 + max(&(*r)->esq, &(*r)->dir); //atualizando a altura


}
void rsd(No **r){
    /*
função para a rotação à direita*/
    if(*r == NULL || (*r)->esq == NULL){
        return;
    }

    No *s;

    printf("RSD(%i)\n",(*r)->dado);
    s = (*r)->esq; 
    (*r)->esq = s->dir;
    (*r)->alt = 1 + max(&(*r)->esq, &(*r)->dir); //atualizando a altura
    s->dir = *r;
    *r = s;
    (*r)->alt = 1 + max(&(*r)->esq, &(*r)->dir); //atualizando a altura

}
void rde(No **r){
    rsd(&(*r)->dir);
    rse(r);
}
void rdd(No **r){
    rse(&(*r)->esq);
    rsd(r);
}
int fat_bal(No **r){
    if(*r == NULL)
        return 0;
    return altura(&(*r)->esq) - altura(&(*r)->dir);
}
void correcao(No **r){
    if (fat_bal(r) > 1) { //rotaciona pra dir
        if (fat_bal(&(*r)->esq) < 0) {
            rdd(r);
        } else 
            rsd(r);
    } else {
        if(fat_bal(r) < -1){ //rotaciona pra esq
            if (fat_bal(&(*r)->dir) > 0) {
                rde(r);
            } else
                rse(r);
        }
    }
}
/*void inserir(No **raiz, int vlr){
    
    if(*raiz == NULL){
        No *novo;
        novo = (No *)malloc(sizeof(No));
        novo->dado = vlr;
        novo->esq = NULL;
        novo->dir = NULL;

        *raiz = novo;
    }else{
        if(vlr > (*raiz)->dado){
            inserir(&(*raiz)->dir,vlr);
        }else{
            inserir(&(*raiz)->esq,vlr);
        }
    }
}*/

void pre_ordem(No **r){
    if(*r != NULL){
        printf("%i (alt:%i)",(*r)->dado, (*r)->alt);
        pre_ordem(&(*r)->esq);
        pre_ordem(&(*r)->dir);
    }
}
void em_ordem(No **r){
    if(*r != NULL){
        em_ordem(&(*r)->esq);
        printf("%i ",(*r)->dado);
        em_ordem(&(*r)->dir);
    }
}
void pos_ordem(No **r){
    if(*r != NULL){
        pos_ordem(&(*r)->esq);
        pos_ordem(&(*r)->dir);
        printf("%i ",(*r)->dado);
    }
}

int qtd(No **r){
    if (*r == NULL) {
        return 0;
    }else {
        return 1 + qtd(&(*r)->esq) + qtd(&(*r)->dir);
    }
}
void mostra_folha(No **r){
    if(*r != NULL){
        mostra_folha(&(*r)->esq);
        mostra_folha(&(*r)->dir);
        if (((*r)->esq == NULL) && ((*r)->dir == NULL)) {
            printf("%i ",(*r)->dado);
        }
    }
}

int * maior(No **r){
	if (*r == NULL)
		return NULL;
	
	No *p;
	for (p = *r; p->dir!=NULL;p=p->dir);
	return &p->dado;
}

int * maior_rec(No **r){
	if (*r == NULL)
		return NULL;

	if ((*r)->dir == NULL)
		return &(*r)->dado;	
	
	return maior_rec(&(*r)->dir);
}

int altura(No **r){
    if(*r == NULL)
        return -1;
    /*if (((*r)->esq == NULL) && ((*r)->dir == NULL)) 
        return 0;
    int esq = altura(&(*r)->esq);
    int dir = altura(&(*r)->dir);
    if( esq > dir)
        return 1 + esq;
    else
        return 1 + dir;*/
    return (*r)->alt;
}
int max(No **r1, No **r2){
	if ((*r1 == NULL) && (*r2 == NULL ))
		return -1;
	if (*r1 == NULL)
		return (*r2)->alt;
	if (*r2 == NULL)
		return (*r1)->alt;
	if ((*r1)->alt > (*r2)->alt)
		return (*r1)->alt;
	return (*r2)->alt;
}
int remover_maior(No **r){
	
	if (*r == NULL)
		return 0;
	
	No *p, *q;
	q = NULL;
	for (p=*r; p->dir!=NULL; p=p->dir){
		q = p;
	}
	if (q == NULL){ // Remoção do nó raiz
		*r = p->esq;
	}else{
		q->dir = p->esq;
	}
	free(p);
	return 1;	
}