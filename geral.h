#ifndef _GERAL_H
#define _GERAL_H

typedef struct informacoes{

    int matricula;
    char nome[20];
    char sobrenome[20];
    char email[30];
    char telefone[18];
    float salario;

}INFO;


typedef struct lista {

	INFO pessoa;
	
	struct lista* proximo;
	struct lista* anterior;


}LISTA;



void push(LISTA** headRef, LISTA* newNode);
void deleteNode(LISTA** headRef, LISTA* del);
void insertAfter(LISTA* prevNode, LISTA* newNode);
void append(LISTA** headRef, LISTA* newNode);
void imprimeLista(LISTA* node);

void importaRegistroParaLista(LISTA** headRef, char arquivo[]);
void exibeRegistroNaLista(LISTA* node);
void deletaMatriculaNaLista(LISTA** headRef);
void buscaMatriculaNaLista(LISTA* node);
void buscaNomeNaLista(LISTA* node);
void insereOrdenadoNaLista(LISTA** headRef, INFO* novoRegistro);


typedef struct Node{
  
    INFO pessoa;

    struct Node *esquerda;
    struct Node *direita;
    int altura;

}ARVORE;


int max(int a, int b);
int altura(struct Node *N);
ARVORE *direitaRotate(ARVORE *y);
ARVORE *esquerdaRotate(ARVORE *x);
int getBalance(ARVORE *N);
ARVORE* insert(ARVORE** node, ARVORE* newNode);
ARVORE * minValueNode(ARVORE* node);
ARVORE* deleteTreeNode(ARVORE* root, int matricula);
void exibeRegistroTree(ARVORE* node);
void imprimeArvore(ARVORE *root);


void importaRegistroParaArvore(ARVORE** root, char arquivo[]);
void buscaMatriculaNaArvore(ARVORE* root, int key);
void buscaNomeNaArvore(ARVORE* root, char key[]);
void exibeRegistroArvore(ARVORE* node);
void insereOrdenadoNaArvore(ARVORE** rootRef, INFO* novoRegistro);
int buscaEmOrdem(ARVORE* root, char key[]);
int buscaPreOrdem(ARVORE* root, char key[]);
int buscaPosOrdem(ARVORE* root, char key[]);


#endif