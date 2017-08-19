// Lista duplamente encadeada // Otávio Augusto Cartaxo Araújo
// Tirado dos site:
//http://www.geeksforgeeks.org/doubly-linked-list/
//http://www.geeksforgeeks.org/delete-a-node-in-a-doubly-linked-list/
#include <stdio.h>
#include <stdlib.h>
#include "DLL.h"

// adciona no início
void push(LISTA** headRef, int newData) {

	LISTA* newNode = malloc(sizeof(LISTA));

	newNode->data = newData;

	newNode->proximo = (*headRef);
	newNode->anterior = NULL;

	
	if((*headRef) != NULL)
		(*headRef)->anterior = newNode;

	(*headRef) = newNode;

}

// apaga um nó
void deleteNode(LISTA** headRef, LISTA* del) {

	if(*headRef == NULL || del == NULL) // caso base
		return;

	if(*headRef == del) 				//se o nó para ser deletado é o primeiro.
		*headRef = del->proximo;

	if(del->proximo != NULL)			//muda o próximo somente se o nó a ser deletado não é o último nó
		del->proximo->anterior = del->anterior;

	if(del->anterior != NULL)			//mud o anterior somente se o nó a ser deletado não é o primeiro nó.
		del->anterior->proximo = del->proximo;

	free(del);
	return;


}

// insere depois de um nó especifico.
void insertAfter(LISTA* prevNode, int newData) {

	if(prevNode == NULL) 
		return;

	LISTA* newNode = malloc(sizeof(LISTA));

	newNode->data = newData;

	newNode->proximo = prevNode->proximo;

	prevNode->proximo = newNode;

	newNode->anterior = prevNode;

	if(newNode->proximo != NULL)
		newNode->proximo->anterior = newNode;

}


//void insertBefore()

//insere no final.
void append(LISTA** headRef, int newData) {

  LISTA* newNode =  malloc(sizeof(LISTA));
 
    LISTA *last = *headRef;
 
    newNode->data  = newData;
 
    newNode->proximo = NULL;
 
    if (*headRef == NULL)
    {
        newNode->anterior = NULL;
        *headRef = newNode;
        return;
    }
 
    while (last->proximo != NULL)
        last = last->proximo;
 
    last->proximo = newNode;
 
    newNode->anterior = last;
 
    return;

}

void printList(LISTA* node) {

	LISTA* last;

	printf("\nEm ordem:\n");
	while(node != NULL) {
		printf(" %d ", node->data);
		last = node;
		node = node->proximo;
	}
	printf("\nEm ordem reversa:\n");
	while(last != NULL){

		printf(" %d ", last->data);
		last = last->anterior;
	}



}
//retorna a quantidade de nós em uma lista.
int getCount(LISTA* head) {

	if(head == NULL) {
		return 0;
	}

	return 1 + getCount(head->proximo);
}




