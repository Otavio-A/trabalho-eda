// Fig. 12.19: fig12_19.c
// Creating and traversing a binary tree
// preorder, inorder, and postorder
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// self-referential structure
struct treeNode {
    struct treeNode *leftPtr; // pointer to left subtree
    int data; // node value
    int altura;
    struct treeNode *rightPtr; // pointer to right subtree
}; // end structure treeNode789
typedef struct treeNode TreeNode; // synonym for struct treeNode
typedef TreeNode *TreeNodePtr; // synonym for TreeNode*

// prototypes
void insertNode( TreeNodePtr *treePtr, int value);
void saidaArvore( TreeNodePtr treePtr, int espacos);
int busca(TreeNodePtr *ar, int inf);
TreeNode* remover(TreeNode** atualPtr);
void RotacaoLL (TreeNodePtr* ar);
void RotacaoRR (TreeNodePtr* ar);
void RotacaoLR (TreeNodePtr* ar);
void RotacaoRL (TreeNodePtr* ar);
int fatorBalanceamento (TreeNode* ar);
int altura_NO (TreeNodePtr no);
int maior(int x, int y);

// function main begins program execution
int main( int argc, char **argv )
{
	
    unsigned int i; // counter to loop from 1-10
    int item; // variable to hold random values
    TreeNodePtr rootPtr = NULL; // tree initially empty
    int a;
    int ks;

    srand( time( NULL ) );
    puts( "Os numeros postos na arvores sao:" );

    // insert random values between 0 and 14 in the tree
    for ( i = 1; i <= 20; ++i ) {
        item = rand() % 100;
        printf( "%3d", item );
        insertNode( &rootPtr, item );
    } // end for
	int espacos = 0;
    while (1){   
    	// traverse the tree inOrder
    	puts( "\n\nA arvore e:" );
    	saidaArvore( rootPtr, espacos );
   
  		// printf("\n\n%s\n\n", argv[1]); 
   		printf ("Digite o numero que deseja remover !\n");
   		scanf ("%d", &a);
   		ks = busca (&rootPtr, a);
   		if (ks){
   			printf ("%d removido com sucesso !", a);
   		} else {
   			printf("Esse numero nao esta na arvore\n");
   		}
	}
} // end main

// insert node into tree
void insertNode( TreeNodePtr *treePtr, int value ){
	int res;
    // if tree is empty
    if ( *treePtr == NULL ) {
        *treePtr = malloc( sizeof( TreeNode ) );

        // if memory was allocated, then assign data
        if ( *treePtr != NULL ) {
            ( *treePtr )->data = value;
            ( *treePtr )->leftPtr = NULL;
            ( *treePtr )->rightPtr = NULL;
        } // end if
        else {
        printf( "%d not inserted. No memory available.\n", value );
        } // end else
    } // end if
    else { // tree is not empty
        
        if ( value < ( *treePtr )->data ) {
            insertNode( &( ( *treePtr )->leftPtr ), value );
            if (fatorBalanceamento (*treePtr)>=2){
            	if (value < (*treePtr)->leftPtr->data){
            		RotacaoLL (treePtr);
				}
				else {
					RotacaoLR (treePtr);
				}
			}
        } // end if
        if ( value > ( *treePtr )->data ) {
            insertNode( &( ( *treePtr )->rightPtr ), value );
            if (fatorBalanceamento (*treePtr)>=2){
            	if (value > (*treePtr)->rightPtr->data){
            		RotacaoRR (treePtr);
				}
				else {
					RotacaoRL (treePtr);
				}
			}
        } // end if
        
        
        else { // duplicate data value ignored
            printf( "%s", "dup" );
        } // end else
    } // end else
    (*treePtr)->altura = maior (altura_NO((*treePtr)->leftPtr), altura_NO((*treePtr)->rightPtr))+1;
} // end function insertNode

// begin inorder traversal of tree
void saidaArvore( TreeNodePtr treePtr, int espacos )
{
    // if tree is not empty, then traverse
    if ( treePtr != NULL ) {
    	int i = 0;
       
        saidaArvore( treePtr->rightPtr, espacos+5 );
         for (i = 0; i < espacos; i++){
        	printf (" ");
        }
        printf( "%d\n", treePtr->data );
        
        saidaArvore( treePtr->leftPtr, espacos + 5 );
        
    } // end if
}// end function inOrder

int busca( TreeNode** raizPtr, int valor ) {
	if(raizPtr == NULL) {
		printf("Arvore vazia. Impossivel fazer uma remocao.\n");
		return 0;
	}

	TreeNode* ant = NULL;
	TreeNode* atual = ( *raizPtr );


	while(atual != NULL) {
		if(valor == atual->data) {
			if(atual == ( *raizPtr )) {
				( *raizPtr ) = remover(&atual);
			}
			else if(ant->rightPtr >= atual) {
				ant->rightPtr = remover(&atual);
			}
			else{
				ant->leftPtr = remover(&atual);
			}

			return 1;
		}

		ant = atual;

		if(valor > atual->data) {
			atual = atual->rightPtr;
		} else{
			atual = atual->leftPtr;
		}

	}

}	

TreeNode* remover(TreeNode** atualPtr ) {

	TreeNode* no1;
	TreeNode* no2;

	if( (* atualPtr )->leftPtr == NULL ) {
		no2 = ( *atualPtr )->rightPtr;
		printf("%d foi removido.\n", ( *atualPtr )->data);
		free(*atualPtr);
		return no2;
	}

	no1 = ( *atualPtr );
	no2 = ( *atualPtr )->leftPtr;

	while(no2->rightPtr != NULL) {
		no1 = no2;
		no2 = no2->rightPtr;
	}

	if(no1 != ( *atualPtr )) {
		no1->rightPtr = no2->leftPtr;
		no2->leftPtr = ( *atualPtr)->leftPtr;
	}

	no2->rightPtr = ( *atualPtr )->rightPtr;
	//printf("%d foi removido.\n", ( *atualPtr )->data);
	free(*atualPtr);
	return no2;

}

void RotacaoLL (TreeNodePtr* ar){
	TreeNode* no;
	no = (*ar)->leftPtr;
	(*ar)->leftPtr =  no->rightPtr;
	no->rightPtr = (*ar);
	(*ar)->altura = maior (altura_NO ((*ar)->leftPtr), altura_NO((*ar)->rightPtr)) +1;
	no->altura = maior (altura_NO(no->leftPtr), (*ar)->altura) +1;
	*ar = no;
}
void RotacaoRR (TreeNodePtr* ar){ 
	TreeNode* no;
	no = (*ar)->rightPtr;
	(*ar)->rightPtr =  no->leftPtr;
	no->leftPtr = (*ar);
	(*ar)->altura = maior (altura_NO ((*ar)->leftPtr), altura_NO((*ar)->rightPtr)) +1;
	no->altura = maior (altura_NO(no->rightPtr), (*ar)->altura) +1;
	*ar = no;
}
void RotacaoLR (TreeNodePtr* ar){
	RotacaoRR (&(*ar)->leftPtr);
	RotacaoLL (ar);	
}
void RotacaoRL (TreeNodePtr* ar){
	RotacaoLL (&(*ar)->rightPtr);
	RotacaoRR (ar);	
}
int altura_NO (TreeNodePtr no){
	if (no == NULL){
		return -1;
	}
	else {
		return no->altura;
	}
}
int maior (int x, int y){
	if (x > y){
		return x;
	}
	else {
		return y;
	}
}
int fatorBalanceamento (TreeNode* ar){
	return labs (altura_NO(ar->leftPtr) - altura_NO (ar->rightPtr));
}




