// Lista duplamente encadeada // Otávio Augusto Cartaxo Araújo
// Tirado dos site:
//http://www.geeksforgeeks.org/doubly-linked-list/
//http://www.geeksforgeeks.org/delete-a-node-in-a-doubly-linked-list/
#include <stdio.h>
#include <stdlib.h>
#include "DLL.h"

// adciona no início
void push(LISTA** headRef, LISTA* newNode) {

	//LISTA* newNode = malloc(sizeof(LISTA));

	//newNode->data = newData;

	newNode->proximo = (*headRef);
	newNode->anterior = NULL;

	
	if((*headRef) != NULL)
		(*headRef)->anterior = newNode;

	(*headRef) = newNode;

}

// apaga um nó
void deleteNode(LISTA** headRef, LISTA* del) {

	if(*headRef == NULL || del == NULL) // caso base
		return ;

	if(*headRef == del) 				//se o nó para ser deletado é o primeiro.
		*headRef = del->proximo;

	if(del->proximo != NULL)			//muda o próximo somente se o nó a ser deletado não é o último nó
		del->proximo->anterior = del->anterior;

	if(del->anterior != NULL)			//muda o anterior somente se o nó a ser deletado não é o primeiro nó.
		del->anterior->proximo = del->proximo;

	exibeRegistro(del);

	free(del);
	return;


}

// insere depois de um nó especifico.
void insertAfter(LISTA* prevNode, LISTA* newNode) {

	if(prevNode == NULL) 
		return;

	newNode->proximo = prevNode->proximo;

	prevNode->proximo = newNode;

	newNode->anterior = prevNode;

	if(newNode->proximo != NULL)
		newNode->proximo->anterior = newNode;

}


//void insertBefore()

//insere no final.
void append(LISTA** headRef, LISTA* newNode) {

  //LISTA* newNode =  malloc(sizeof(LISTA)); 
    //newNode->data  = newData;
    //newNode->proximo = NULL;

    LISTA *last = *headRef;

 
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

void imprimeLista(LISTA* node) {

	//LISTA* last;

	printf("\nOs dados em ordem sao:\n");
	while(node != NULL) {
		//printf(" %d ", node->data);
		//last = node;
		exibeRegistro(node);
		node = node->proximo;
	}

	//printf("\nEm ordem reversa:\n");
	//while(last !=NULL) {
		//printf(" %d ", las->data);
		//last = last->anterior;
	//}
	printf("\n");

}