#include <stdio.h>
#include <stdlib.h>

typedef enum{Vermelho, Preto} Cor;

typedef struct no{
	int dado;
	Cor cor;
	struct no *esq, *dir, *pai;
}No;

int contador_altura=0;

void inserir(No **r, int vlr){
	if (*r == NULL){
	
		No *novo;
		novo = (No *)malloc(sizeof(No));
		novo->dado = vlr;
		novo->esq = NULL;
		novo->dir = NULL;
		novo->pai = NULL;
		novo->cor = Vermelho;
	
		*r = novo;
	}else{
		if (vlr > (*r)->dado){
			inserir(&(*r)->dir, vlr);
			(*r)->dir->pai = *r;
		}else{
			inserir(&(*r)->esq, vlr);
			(*r)->esq->pai = *r;
		}
	}
}

void mostrar_folhas_rec(No **r){
	if (*r != NULL){
		if ((*r)->esq == NULL && (*r)->dir == NULL)
			printf("%i\n", (*r)->dado);
		mostrar_folhas_rec(&(*r)->esq);
		mostrar_folhas_rec(&(*r)->dir);
	}
}

void pre_ordem_rec(No **r){
	if (*r != NULL){
		
		if ((*r)->pai == NULL)
			printf("%i (Raiz) (Cor: ", (*r)->dado);
		else
			printf("%i (Pai: %i) (Cor: ", (*r)->dado, (*r)->pai->dado);
		if ((*r)->cor == Vermelho)
			printf("Vermelho)\n");
		else
			printf("Preto)\n");
		
		pre_ordem_rec(&(*r)->esq);
		pre_ordem_rec(&(*r)->dir);
	}
}

void pre_ordem(No **r){
	if (*r == NULL)
		printf("Árvore vazia.\n");
	else
		pre_ordem_rec(r);
}

void em_ordem_rec(No **r){
	if (*r != NULL){
		em_ordem_rec(&(*r)->esq);
		printf("%i\n", (*r)->dado);
		em_ordem_rec(&(*r)->dir);
	}
}

void em_ordem(No **r){
	if (*r == NULL)
		printf("Árvore vazia.\n");
	else
		em_ordem_rec(r);
}

void pos_ordem_rec(No **r){
	if (*r != NULL){
		pos_ordem_rec(&(*r)->esq);
		pos_ordem_rec(&(*r)->dir);
		printf("%i\n", (*r)->dado);
	}
}

void pos_ordem(No **r){
	if (*r == NULL)
		printf("Árvore vazia.\n");
	else
		pos_ordem_rec(r);
}

int menu(){
	int opc;
	system("clear");
	printf("[0] - Sair.\n");
	printf("[1] - Inserir.\n");
	printf("[2] - Pré-ordem.\n");
	printf("[3] - Em-ordem.\n");
	printf("[4] - Pós-ordem.\n");
	printf("[5] - Quantidade de elementos.\n");
	printf("[6] - Maior elemento.\n");
	printf("[7] - Menor elemento.\n");
	printf("[8] - Remover o maior elemento.\n");
	printf("[9] - Mostrar folhas.\n");
	printf("[10] - Altura.\n");
	printf("[11] - Remover no qualquer.\n");
	
	printf("\nEscolha uma opção: ");
	scanf("%i", &opc);
	return opc;
}

int qtd(No *r){
	if (r == NULL)
		return 0;
	
	return 1 + qtd(r->esq) + qtd(r->dir);
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
		if (*r != NULL)
			(*r)->pai = NULL;
	}else{
		q->dir = p->esq;
		if (q->dir != NULL)
			q->dir->pai = q;
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
		
		if (p->esq != NULL)
			p->esq->pai = p->pai;
		
		free(p);

		return 1;
	}
	return remover_maior_rec(&(*r)->dir);
}

int altura(No **r){
	contador_altura++;
	if (*r == NULL)
		return -1;
	if ((*r)->esq == NULL && (*r)->dir == NULL)
		return 0;
	int alt_esq = altura(&(*r)->esq);
	int alt_dir = altura(&(*r)->dir);
	if (alt_esq > alt_dir){
		return 1 + alt_esq;
	}else{
		return 1 + alt_dir;
	}	
}

int remover_por_valor(No **r, int vlr){
	if (*r == NULL)
		return 0;
	if ((*r)->dado == vlr){ // elemento a ser removido encontrado
		No *p;
		p = *r;
		if ((*r)->esq == NULL){ // caso 1
			*r = p->dir;
			if(p->dir != NULL) p->dir->pai = p->pai;
			free(p);
			return 1;
		}
		
		if ((*r)->dir == NULL){ // caso 2
			*r = p->esq;
			if(p->esq != NULL) p->esq->pai = p->pai;
			free(p);
			return 1;			
		}
		
		// caso 3
		(*r)->dado = * maior(&(*r)->esq);
		remover_maior(&(*r)->esq);
		return 1;

	}else{
		if (vlr > (*r)->dado){ // buscar pelo lado direito 
			return remover_por_valor(&(*r)->dir, vlr);
		}else{ // buscar pelo lado esquerdo
			return remover_por_valor(&(*r)->esq, vlr);
		}
	}
}


void rse(No **r){

	if (*r == NULL || (*r)->dir == NULL){
		printf("Erro ao chamar rse.\n");
		exit(0);
	}

	printf("RSE(%i)\n", (*r)->dado);

	No *p;
	
	p = (*r)->dir; //p = 20
	(*r)->dir = p->esq; //10 -> 15
	p->esq = *r; //20 -> 10
	*r = p; 

	(*r)->pai = p->esq->pai; 
	(*r)->esq->pai = *r;
	if((*r)->esq->dir != NULL) (*r)->esq->dir->pai = (*r)->esq;
}

void rsd(No **r){

	if (*r == NULL || (*r)->esq == NULL){
		printf("Erro ao chamar rsd.\n");
		exit(0);
	}

	printf("RSD(%i)\n", (*r)->dado);

	No *p;
	p = (*r)->esq;
	(*r)->esq = p->dir;
	p->dir = *r;
	*r = p;

	(*r)->pai = p->dir->pai; 
	(*r)->dir->pai = *r;
	if((*r)->dir->esq != NULL) (*r)->dir->esq->pai = (*r)->dir;
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
	if (*r == NULL)
		return 0;
	return altura(&(*r)->esq) - altura(&(*r)->dir);
}

void correcao(No **r){
	if (fat_bal(r) > 1){ // devo rotacionar para direita
		if (fat_bal(&(*r)->esq) < 0){
			rdd(r);
		}else{
			rsd(r);
		}
	}else{
		if (fat_bal(r) < -1){ // devo rotacionar para esquerda
			if (fat_bal(&(*r)->dir) > 0){
				rde(r);
			}else{
				rse(r);
			}
		}
	}
}

int main(){
	No *r=NULL;
	int opc, valor;
	int *aux;

	inserir(&r, 15);
	inserir(&r, 10);
	inserir(&r, 5);
	inserir(&r, 8);
	// inserir(&r, 20);
	// inserir(&r, 15);	
		
	pre_ordem(&r);
	
	rsd(&r->esq);
	// remover_maior_rec(&r);

	printf("rotacao.\n");
	
	pre_ordem(&r);

/*	
	while(opc = menu()){
		switch(opc){
			case 1:
				printf("valor: ");
				scanf("%i", &valor);
				inserir(&r, valor);
				printf("%i inserido.\n", valor);
				break;

			case 2:
				pre_ordem(&r);
				break;

			case 3:
				em_ordem(&r);
				break;

			case 4:
				pos_ordem(&r);
				break;

			case 5:
				printf("Quantidade de elementos: %i\n", qtd(r));
				break;

			case 6:
				aux = maior_rec(&r);
				if (aux == NULL)
					printf("Árvore sem elementos.\n");
				else
					printf("Maior: %i\n", *aux);
				break;

			case 7:
				printf("Deixada como exercício.\n");
				break;

			case 8:
				if (remover_maior_rec(&r))
					printf("Maior elemento removido.\n");
				else
					printf("Árvore vazia\n");
				break;
			case 9:
				mostrar_folhas_rec(&r);
				break;
			case 10:
				contador_altura = 0;
				printf("Altura: %i\n", altura(&r));
				printf("qtd chamadas: %i\n", contador_altura);
				break;
			case 11:
				printf("valor: ");
				scanf("%i", &valor);
				if (remover_por_valor(&r, valor))
					printf("%i removido.\n", valor);
				else
					printf("%i não encontrado.\n", valor);
				break;

				
			default:
				printf("Opção inválida.\n");
		}
		getchar();
		getchar();
	}
	*/
}










