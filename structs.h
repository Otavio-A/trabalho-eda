#ifndef _STCT_H_
#define _STCT_H_


typedef struct informacoes{

    int matricula;
    char* nome;
    char* sobrenome;
    char* email;
    char* telefone;
    float salario;

}INFO;


typedef struct lista {

	INFO pessoa;
	
	struct lista* proximo;
	struct lista* anterior;


}LISTA;


void importaRegistro(LISTA** headRef);
void insereDados();


void push(LISTA** headRef, LISTA* newNode);
void insertAfter(LISTA* prevNode, LISTA* newNode);
void deleteNode(LISTA** headRef, LISTA* del);
void append(LISTA** headRef, LISTA* newNode);
void printList(LISTA* node);

#endif