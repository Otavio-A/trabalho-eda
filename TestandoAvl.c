#include<stdio.h>
#include<stdlib.h>
#include <time.h>
 
struct Node{
    int dado;
    struct Node *esquerda;
    struct Node *direita;
    int altura;
};
 
int max(int a, int b);
 
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
 
struct Node* newNode(int dado)
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    node->dado   = dado;
    node->esquerda   = NULL;
    node->direita  = NULL;
    node->altura = 1; 
    return(node);
}
 
struct Node *direitaRotate(struct Node *y)
{
    struct Node *x = y->esquerda;
    struct Node *T2 = x->direita;
 
    x->direita = y;
    y->esquerda = T2;
 
    y->altura = max(altura(y->esquerda), altura(y->direita))+1;
    x->altura = max(altura(x->esquerda), altura(x->direita))+1;
 
    return x;
}
 
struct Node *esquerdaRotate(struct Node *x)
{
    struct Node *y = x->direita;
    struct Node *T2 = y->esquerda;
 
    y->esquerda = x;
    x->direita = T2;
 
    x->altura = max(altura(x->esquerda), altura(x->direita))+1;
    y->altura = max(altura(y->esquerda), altura(y->direita))+1;
 
    return y;
}
 
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return altura(N->esquerda) - altura(N->direita);
}
 
struct Node* insert(struct Node* node, int dado)
{
    if (node == NULL)
        return(newNode(dado));
 
    if (dado < node->dado)
        node->esquerda  = insert(node->esquerda, dado);
    else if (dado > node->dado)
        node->direita = insert(node->direita, dado);
    else
        return node;

    node->altura = 1 + max(altura(node->esquerda),
                           altura(node->direita));

    int balance = getBalance(node);

    if (balance > 1 && dado < node->esquerda->dado)
        return direitaRotate(node);
    if (balance < -1 && dado > node->direita->dado)
        return esquerdaRotate(node);
 
    if (balance > 1 && dado > node->esquerda->dado)
    {
        node->esquerda =  esquerdaRotate(node->esquerda);
        return direitaRotate(node);
    }
 
    if (balance < -1 && dado < node->direita->dado)
    {
        node->direita = direitaRotate(node->direita);
        return esquerdaRotate(node);
    }
 
    return node;
}

struct Node * minValueNode(struct Node* node)
{
    struct Node* atual = node;

    while (atual->esquerda != NULL)
        atual = atual->esquerda;
 
    return atual;
}
struct Node* deleteNode(struct Node* root, int dado){
    if (root == NULL)
        return root;
        
        
        
    if ( dado < root->dado )
        root->esquerda = deleteNode(root->esquerda, dado);
 
    else if( dado > root->dado )
        root->direita = deleteNode(root->direita, dado);
 
    else{
        if( (root->esquerda == NULL) || (root->direita == NULL) ){
            struct Node *temp = root->esquerda ? root->esquerda :
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
            struct Node* temp = minValueNode(root->direita);
 
            root->dado = temp->dado;
 
            root->direita = deleteNode(root->direita, temp->dado);
        }
    }
 
    if (root == NULL)
      return root;
 
    root->altura = 1 + max(altura(root->esquerda),
                           altura(root->direita));
 
    int balance = getBalance(root);
 
    if (balance > 1 && getBalance(root->esquerda) >= 0)
        return direitaRotate(root);

    if (balance > 1 && getBalance(root->esquerda) < 0)
    {
        root->esquerda =  esquerdaRotate(root->esquerda);
        return direitaRotate(root);
    }

    if (balance < -1 && getBalance(root->direita) <= 0)
        return esquerdaRotate(root);
 
    if (balance < -1 && getBalance(root->direita) > 0)
    {
        root->direita = direitaRotate(root->direita);
        return esquerdaRotate(root);
    }
 
    return root;
}
 
void saidaArvore(struct Node *root, int espacos)
{
    if(root != NULL)
    {
    	int i = 0;
    	saidaArvore(root->direita, espacos +5);
    	for (i = 0; i < espacos; i++){
    		printf (" ");
		}
        printf("%d\n", root->dado);
        saidaArvore(root->esquerda, espacos +5);
    }
}
 
int main(){
  int a;
  time_t start_del, end_del, start_ins, end_ins;
  double diff_t, diff_t2;
  int i;
  int item;
  int espacos = 0;
  struct Node *root = NULL;
  time(&start_ins);
	srand( time( NULL ) );
	puts ("Os elementos sao:");
  	for ( i = 1; i <= 20; ++i ) {
        item = rand() % 100;
        printf( "%d ", item );
        root = insert(root, item );
    }
    time(&end_ins);
    diff_t2 = difftime(end_ins, start_ins);
    printf("\nTempo de Insercao = %.1f\n", diff_t2);
    while (1){   
      	time(&start_del);
     	puts( "\n\nA arvore e:" );
     	root = insert( root, espacos );
     	saidaArvore (root, espacos);
    	printf ("Digite o numero que deseja remover !\n");
    	scanf ("%d", &a);
    	root = deleteNode (root, a);
    	time(&end_del);
    	diff_t = difftime(end_del, start_del);
    	printf("Tempo de Delecao = %.1f\n", diff_t);
 	}
}
