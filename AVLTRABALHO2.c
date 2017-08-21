#include<stdio.h>
#include<stdlib.h>
#include <time.h>

struct Node{
    int dado;
    char* nome;
    char* sobrenome;
    char* email;
    char* telefone;
    float salario;
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
    node->dado = dado;
    node->esquerda = NULL;
    node->direita = NULL;
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
 
void busca_mat(struct Node* root, int dado){
int x;
    if (root == NULL){
    	puts ("Nao Encontrado!");
	}
    else if ( dado < root->dado ){
    busca_mat(root->esquerda, dado);
	}
        
    else if( dado > root->dado ){
    busca_mat(root->direita, dado);
	}
    else if (dado == root->dado){
    	puts ("Encontrado!");
	}
	else {
		puts ("Nao Encontrado!");
	}	
}

/*void busca_nome(struct Node* root, char* nome){
int x;
    if (root == NULL){
    	puts ("Nao Encontrado!");
    	return 0;
	}
    else if ( nome < root->nome ){
    busca_nome(root->esquerda, nome);
	}
        
    else if( nome> root->nome ){
    busca_nome(root->direita, nome);
	}
    else if (nome == root->nome){
    	puts ("Encontrado!");
	}
	else {
		puts ("Nao Encontrado!");
	}	
}*/
  
void saidaArvore(struct Node *root){
    if(root != NULL){
    	int i = 0;
    	saidaArvore(root->esquerda);
        printf("%d\n", root->dado);
        saidaArvore(root->direita);
    }
}
 
int main(){
  int a;
  time_t start_del, end_del, start_ins, end_ins;
  double diff_t, diff_t2;
  int i;
  int item, escolha;
  char* nome_busca;
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
    for ( ; ; ){
	    printf ("O que deseja fazer?\n(1) - Importar registros atraves do arquivo\n(2) - Exibir registros por ordem de matricula\n(3) - Buscar registro por nome\n(4) - Buscar registro por matricula\n(5) - Inserir novo registo\n(6) - Remover registro\n");
	    scanf ("%d", &escolha);
	    if (escolha == 1){
	    	puts ("Digite o nome do arquivo");
		}
		else if (escolha == 2){
			puts ("-----------------o------------------");
			saidaArvore (root);
			puts ("-----------------o------------------");
		}
		else if (escolha == 3){
			puts ("Digite o nome que deseja buscar:");
			//scanf ("%s", &nome_busca);
	    	//busca_nome (root, nome_busca);
		}
		else if (escolha == 4){
			puts ("Digite a matricula que deseja buscar:");
			scanf ("%d", &a);
	    	busca_mat (root, a);
		}
		else if (escolha == 5){
			puts ("Digite as informacoes para inserir:\n1 - Matricula\n2 - Nome\n3 - Sobrenome\n4 - Email\n5 - Telefone\n6 - Salario");
		}
		else if (escolha == 6){   
	      	time(&start_del);
	    	printf ("Digite a matricula que deseja remover o registro!\n");
	    	scanf ("%d", &a);
	    	root = deleteNode (root, a);
	    	time(&end_del);
	    	diff_t = difftime(end_del, start_del);
	    	printf("Tempo de Delecao = %.1f\n", diff_t);
	 	}
	}
}
