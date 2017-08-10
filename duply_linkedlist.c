#include <stdio.h>
#include <stdlib.h>

typedef struct duplyLinkedList {
	int valor;

	struct duplyLinkedList* proximo;
	struct duplyLinkedList* anterior;

}LISTA;



int ehvazia(LISTA* p) {
	return p == NULL;
}

void verifica(LISTA* p) {
	if(ehvazia(p)) {
		printf("MEMORIA INDISPONIVEL.\n");
		exit(0);
	}
}


void ordena(LISTA* i) {


	if(i == NULL || i->proximo == NULL)
		return;

	LISTA* i2 = i, *p;
	int aux;

	while( i2 != NULL) {
		p = i2->proximo;
		while(p != NULL) {
			if(i2->valor > p->valor) {
			
				aux = i2->valor;
				i2->valor = p->valor;
				p->valor = aux;	


			}
			p = p->proximo;
		}
		i2 = i2->proximo;
	}

}


void insere(LISTA** i, LISTA** f, int dado) {

	
	LISTA* newNode;
	newNode = malloc(sizeof(LISTA));

	verifica(newNode);

	newNode->valor = dado;

	if(ehvazia((*i))) {
		(*i) = newNode;
		(*f) = newNode;
		newNode->anterior = NULL;
	} else {

		(*f)->proximo = newNode;
		newNode->anterior = (*f);
		(*f) = newNode;


	}

	(*f)->proximo = NULL;
	//ordena(*i);

}



LISTA* busca(LISTA* p, int v) {

//15 20 30 40 90 100

	while(p != NULL) {

		if(v == p->valor) {
			return p;
		}
		else 
			p = p->proximo;
	}



}


void removeNo(int valor, LISTA* ini, LISTA* fim) {


	LISTA* tempPtr1;
	LISTA* tempPtr2;
	LISTA* tempPtr3;


	tempPtr1 = busca(ini,  valor);

	if(tempPtr1 != NULL) {

		// se quero remover o nó inicial.
		if(tempPtr1 == ini) {
			ini = ini->proximo;
		}
		// se quero remover o último nó.
		else if(tempPtr1 == fim){
			fim = tempPtr1->anterior;

		}
		// se for um nó no meio da lista.
		else {

			tempPtr2 = tempPtr1->anterior; //ptr2 auxiliar aponta para o nó anterior do que queremos remover.
			tempPtr3 = tempPtr1->proximo; // ptr3 auxiliar aponta para o proximo do nó que queremos remover.

			// faz a substituição.
			tempPtr2->proximo = tempPtr3;
			tempPtr3->anterior = tempPtr2;

		}

		printf("%d foi removido da lista\n", tempPtr1->valor);
		free(tempPtr1);	

	}

	else
		printf("O valor nao esta na lista\n");


}


void mostraInverso(LISTA* f) {

	LISTA* k;
	k = f;
	printf("Em ordem decrescente:\nNULL -> ");
	while(k != NULL) {
		printf("%d -> ", k->valor);
		k = k->anterior;
	}
	printf("NULL\n");
}

void mostraOrdenado(LISTA* i) {

	LISTA* k;
	k = i;
	printf("Em ordem crescente:\n");
	while(k != NULL) {
		printf("%d -> ", k->valor);
		k = k->proximo;
	}
	printf("NULL\n");

}

void mostraOrdemInserida(LISTA* i) {

	LISTA* k = i;

	printf("Ordem de insercao:\n");
	while(k != NULL) {
		printf("%d -> ", k->valor);
		k = k->proximo;
	}
	printf("NULL\n");


}

int main() {


	LISTA* ini = NULL;
	LISTA* fim = NULL;

	insere(&ini,&fim, 8);
	insere(&ini,&fim, 2);
	insere(&ini,&fim, 6);
	insere(&ini,&fim, 200);
	insere(&ini,&fim, 125);

	mostraOrdemInserida(ini);

	ordena(ini);

	mostraOrdenado(ini);
	mostraInverso(fim);

	removeNo(6, ini, fim);

	printf("\n");
	mostraOrdenado(ini);
	mostraInverso(fim);


}