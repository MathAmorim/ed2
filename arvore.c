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

int main(){
    menu();
}

void menu(){
    int opc, valor;
    No *r = NULL;
    
    while (opc != 0) {
        system("clear||cls");
        printf("[0] - Sair\n");
        printf("[1] - Inserir\n");
        printf("[2] - Pre Ordem\n");
        printf("[3] - Em Ordem\n");
        printf("[4] - Pos Ordem\n");
        printf("[5] - Quantidade de Elementos\n");



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