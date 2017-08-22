#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "trabalho_avl.h"

 
int altura(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}
/* 
ARVORE* newNode()
{
    ARVORE* node = (ARVORE*)malloc(sizeof(ARVORE));

   node->dado = dado;
    node->esquerda = NULL;
    node->direita = NULL;
    node->altura = 1; 
    return(node);
}
 */
ARVORE *direitaRotate(ARVORE *y)
{
    ARVORE *x = y->esquerda;
    ARVORE *T2 = x->direita;
 
    x->direita = y;
    y->esquerda = T2;
 
    y->altura = max(altura(y->esquerda), altura(y->direita))+1;
    x->altura = max(altura(x->esquerda), altura(x->direita))+1;
 
    return x;
}
 
ARVORE *esquerdaRotate(ARVORE *x)
{
    ARVORE *y = x->direita;
    ARVORE *T2 = y->esquerda;
 
    y->esquerda = x;
    x->direita = T2;
 
    x->altura = max(altura(x->esquerda), altura(x->direita))+1;
    y->altura = max(altura(y->esquerda), altura(y->direita))+1;
 
    return y;
}
 
int getBalance(ARVORE *N)
{
    if (N == NULL)
        return 0;
    return altura(N->esquerda) - altura(N->direita);
}
 
ARVORE* insert(ARVORE** node, ARVORE* newNode)
{ 
    
    int novoDado = newNode->pessoa.matricula;

    if ((*node) == NULL){

       newNode->esquerda = NULL;
       newNode->direita = NULL;
       newNode->altura = 1;
       (*node) = newNode;

       return (*node);


    }
        

    if (novoDado < (*node)->pessoa.matricula)
        (*node)->esquerda  = insert(&((*node)->esquerda), newNode);
    else if (novoDado > (*node)->pessoa.matricula)
        (*node)->direita = insert(&((*node)->direita), newNode);
    //else
      //  return (*node);

    (*node)->altura = 1 + max(altura((*node)->esquerda),
                           altura((*node)->direita));

    int balance = getBalance((*node));

    if (balance > 1 && novoDado < (*node)->esquerda->pessoa.matricula)
        return direitaRotate((*node));
    if (balance < -1 && novoDado > (*node)->direita->pessoa.matricula)
        return esquerdaRotate((*node));
 
    if (balance > 1 && novoDado > (*node)->esquerda->pessoa.matricula)
    {
        (*node)->esquerda =  esquerdaRotate((*node)->esquerda);
        return direitaRotate((*node));
    }
 
    if (balance < -1 && novoDado < (*node)->direita->pessoa.matricula)
    {
        (*node)->direita = direitaRotate((*node)->direita);
        return esquerdaRotate((*node));
    }
 
    return (*node);
}

ARVORE * minValueNode(ARVORE* node)
{
    ARVORE* atual = node;

    while (atual->esquerda != NULL)
        atual = atual->esquerda;
 
    return atual;
}
  
ARVORE* deleteTreeNode(ARVORE* root, int matricula){
    
    if (root == NULL)
        return root;
        
        
        
    if ( matricula < root->pessoa.matricula )
        root->esquerda = deleteTreeNode(root->esquerda, matricula);
 
    else if( matricula > root->pessoa.matricula )
        root->direita = deleteTreeNode(root->direita, matricula);
 
    else{
        if( (root->esquerda == NULL) || (root->direita == NULL) ){
            ARVORE *temp = root->esquerda ? root->esquerda :
                                             root->direita;
 
            if (temp == NULL){
                temp = root;
                root = NULL;
            }
            else 
             *root = *temp;         
            free(temp);
        }
        else
        {
            ARVORE* temp = minValueNode(root->direita);
 
            root->pessoa.matricula = temp->pessoa.matricula;
 
            root->direita = deleteTreeNode(root->direita, temp->pessoa.matricula);
        }
    }
 
    if (root == NULL)
      return root;
 
    root->altura = 1 + max(altura(root->esquerda),
                           altura(root->direita));
 
    int balance = getBalance(root);
 
    if (balance > 1 && getBalance(root->esquerda) >= 0)
        return direitaRotate(root);

    if (balance > 1 && getBalance(root->esquerda) < 0){
        root->esquerda =  esquerdaRotate(root->esquerda);
        return direitaRotate(root);
    }

    if (balance < -1 && getBalance(root->direita) <= 0)
        return esquerdaRotate(root);
 
    if (balance < -1 && getBalance(root->direita) > 0){
        root->direita = direitaRotate(root->direita);
        return esquerdaRotate(root);
    }
 
    return root;
}
 



void imprimeArvore(ARVORE *root){
    if(root != NULL){
    	imprimeArvore(root->esquerda);
        
        exibeRegistroArvore(root);

        imprimeArvore(root->direita);
    }
}
 
int main(){

    ARVORE* root = NULL;
    char arquivo[20];

    printf("Digite o nome do arquivo: ");
    scanf("%s", arquivo);

    importaRegistroParaArvore(&root, arquivo);
    imprimeArvore(root);

    //printf("\nDigite o nome que esta buscando: ");
    //char nome[20];
    //scanf("%s", nome);

    //buscaNome(root, nome);

    //printf("\nDigite a matricula que esta procurando: ");
    //int matricula;
    //scanf("%d", &matricula);

   //buscaMatricula(root, matricula);

    printf("\nDigite os dados do novo registro que deseja inserir\n");
    insereOrdenadoNaArvore(&root);

    imprimeArvore(root);

    //imprimeArvore(root);



}
