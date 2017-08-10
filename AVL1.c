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
TreeNode* remover(TreeNode* ar);
void RotacaoLL (TreeNodePtr* ar);
void RotacaoRR (TreeNodePtr* ar);
void RotacaoLR (TreeNodePtr* ar);
void RotacaoRL (TreeNodePtr* ar);
int fatorBalanceamento (TreeNode* ar);
int altura_NO (TreeNodePtr no);
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
    puts( "\n\nA arvore eh:" );
    saidaArvore( rootPtr, espacos );
   
  // printf("\n\n%s\n\n", argv[1]); 
   printf ("Digite o numero que deseja remover !\n");
   scanf ("%d", &a);
   ks = busca (&rootPtr, a);
   if (ks){
   	printf ("%d removido com sucesso !", a);
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
int busca(TreeNodePtr *ar, int inf){
	if (ar == NULL){
		return 0;
	}
	TreeNodePtr aux2 = NULL;
	TreeNodePtr aux1 = *ar;
	while (ar != NULL){
		if (inf == aux1->data){
			if (aux1 == *ar){
				*ar = remover (aux1);
			}
			else{
				if (aux2->rightPtr == aux1){
					aux2->rightPtr = remover (aux1);
				}
				else {
					aux2->leftPtr = remover (aux1);
				}
			}
			return 1;
		}
		aux2 = aux1;
		if (inf > aux1->data){
			aux1 = aux1->rightPtr;
		}
		else {
			aux1 = aux1->leftPtr;
		}
	}
}	

TreeNode* remover(TreeNode* ar){
	TreeNode* aux2;
	TreeNode* aux1;

	if ((*ar).leftPtr == NULL){
		aux2 =  (*ar).rightPtr;
		free (ar);
		return aux2;
	}
	aux1 = ar;
	aux2 = ar->leftPtr;
	while (aux2->rightPtr != NULL){
		aux1 = aux2;
		aux2 = aux2->rightPtr;
	}
	if (aux1 != (ar)){
		aux1->rightPtr =  aux2->leftPtr;
		aux2->leftPtr = ar->leftPtr;
	}
	aux2->rightPtr = ar->rightPtr;
	free (ar);
	return aux2;
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




