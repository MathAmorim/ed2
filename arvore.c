#include <stdio.h>
#include <stdlib.h>
typedef struct no{
    int dado;
    struct no *esq, *dir;

}No;

void inserir(No **, int);
void pre_ordem(No **);
void em_ordem(No **);
void pos_ordem(No **);
void menu();
int qtd(No **r);
int remover_maior_rec(No **r);
int remover_maior(No **r);
int * maior_rec(No **r);
int * maior(No **r);
void mostra_folha(No **r);
int altura(No **r);

int main(){
    menu();
}

void menu(){
    int opc, valor;
    No *r = NULL;
    int *aux;

    inserir(&r, 10);
    inserir(&r, 3);
    inserir(&r, 15);
    inserir(&r, 8);
    inserir(&r, 5);


    while (opc != 0) {
        system("clear||cls");
        printf("[00] - Sair\n");
        printf("[01] - Inserir\n");
        printf("[02] - Pre Ordem\n");
        printf("[03] - Em Ordem\n");
        printf("[04] - Pos Ordem\n");
        printf("[05] - Quantidade de Elementos\n");
        printf("[06] - Maior elemento\n");
        printf("[07] - Menor elemento\n");
        printf("[08] - Remover o maior elemento\n");
        printf("[09] - Mostrar Folha\n");
        printf("[10] - Mostrar Altura da Arvore\n");
        printf("[11] - Remover No\n");




        printf("\nEscolha uma opção: ");
        scanf("%i",&opc);
        switch (opc) {
            case 1:{
                printf("Valor: ");
                scanf("%i", &valor);
                inserir(&r, valor);
            }break;
            case 2:{
                pre_ordem(&r);
                printf("\n");
            }break;
            case 3:{
                em_ordem(&r);
                printf("\n");
            }break;
            case 4:{
                pos_ordem(&r);
                printf("\n");
            }break;
            case 5:{
                printf("Quantidade de Elementos: %i\n",qtd(&r));
            }break;
            case 6:{
                aux = maior_rec(&r);
				if (aux == NULL)
					printf("Árvore sem elementos.\n");
				else
					printf("Maior: %i\n", *aux);
				break;
            }break;
            case 7:{
                
            }break;
            case 8:{
                
            }break;
            case 9:{
                printf("Folhas: \n");
                mostra_folha(&r);
            }break;
            case 10:{
                printf("Altura: %i\n",altura(&r));
            }break;
            case 11:{
                printf("Valor: ");
                scanf("%i",&valor);
                
            }break;


        }
        getchar();
        getchar();
    }
}

void inserir(No **raiz, int vlr){
    
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
}

void pre_ordem(No **r){
    if(*r != NULL){
        printf("%i ",(*r)->dado);
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

int remover_maior_rec(No **r){
	
	if (*r == NULL)
		return 0;
	
	if ((*r)->dir == NULL){
		No *p;
		p = *r;
		*r = p->esq;
		free(p);
		return 1;
	}
	return remover_maior_rec(&(*r)->dir);
}

int altura(No **r){
    if(*r == NULL)
        return -1;
    if (((*r)->esq == NULL) && ((*r)->dir == NULL)) 
        return 0;
    int esq = altura(&(*r)->esq);
    int dir = altura(&(*r)->dir);
    if( esq > dir)
        return 1 + esq;
    else
     return 1 + dir;
}

int remover_valor(No **r,int vlr){
    if (*r ==NULL) 
        return 0;
    if((*r)->dado == vlr){
        if((*r)->esq == NULL){ //caso 1
            No *p;
            p = *r;
            *r = p->dir;
            free(p);
            return 1;
        }else {
            if((*r)->dir == NULL){ //caso 2
                No *p;
                p = *r;
                *r = p->esq;
                free(p);
                return 1;

            }else{ //caso 3
                (*r)->dado = * maior(&(*r)->esq);
                remover_maior(&(*r)->esq);
                return 1;
            }
        }
    }else{
        if (vlr > (*r)->dado) {
            return remover_valor(&(*r)->dir, vlr);
        }else{
            return remover_valor(&(*r)->esq, vlr);
        }
    }
}
