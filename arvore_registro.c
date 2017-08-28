#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geral.h"

void importaRegistroParaArvore(ARVORE** root, char arquivo[]) {

    FILE* f;

    int qtd;
    int auxiliar = 0;
    char teste[100];

    f = fopen(arquivo, "r");

    if(f == NULL){
        printf("Desculpa, banco de dados indisponivel\n");
        exit(0);
    }

    fscanf(f, "%d", &qtd);
    fseek(f, 0, SEEK_SET);

    // diz quantas linhas deve saltar.
    int newline = 0;
    for(char c = fgetc(f); newline < 2; c = fgetc(f)){
    	if(c == '\n'){
    		newline++;
    	} else{
    		auxiliar++;
    	}
    }

    fseek(f, 0, SEEK_SET);  


     // O fseek faz com que a barra se seleção pule para local indicado;
     //Nesses caso, a barra irá pular 49 bytes a partir da linha inicial(SEEK_SET);    

    fseek(f, auxiliar, SEEK_SET);
    fgets(teste, 100, f);

    for(int i = 0; i < qtd; i++) {

        ARVORE* newNode = malloc(sizeof(ARVORE));

        if(newNode == NULL){
            printf("Memoria indisponivel.\n");
            exit(0);
        }

        
        char linha[200];
        fgets(linha, 200, f);

        char* tok;
        tok = strtok(linha, ",");

        while(tok != NULL) {
          
           //sscanf(tok, "%d", &(newNode->pessoa.matricula));
        	newNode->pessoa.matricula = atoi(tok);
           tok = strtok(NULL, ",");

           //newNode->pessoa.nome = malloc(sizeof(tok)*10);
           strcpy(newNode->pessoa.nome, tok);
           tok = strtok(NULL, ",");

           //newNode->pessoa.sobrenome = malloc(sizeof(tok)*10);
           strcpy(newNode->pessoa.sobrenome, tok);
           tok = strtok(NULL, ",");

           //newNode->pessoa.email = malloc(sizeof(tok)*10);
           strcpy(newNode->pessoa.email, tok);
           tok = strtok(NULL, ",");
       
           //newNode->pessoa.telefone = malloc(sizeof(tok)*10);
           strcpy(newNode->pessoa.telefone, tok);
           tok = strtok(NULL, ",");

           sscanf(tok, "%f", &(newNode->pessoa.salario));
           tok = strtok(NULL, ",");

        }

        (*root) = insert(root, newNode);
     

    }

    fclose(f);
  
}

void exibeRegistroArvore(ARVORE* node) {

   printf("--------------------------------------\n");

    printf("Matricula: %d\n", node->pessoa.matricula);
    printf("Nome: %s\n", node->pessoa.nome);
    printf("Sobrenome: %s\n", node->pessoa.sobrenome);
    printf("Email: %s\n", node->pessoa.email);
    printf("Telefone: %s\n", node->pessoa.telefone);
    printf("Salario: %.2f\n", node->pessoa.salario);

    

}


void buscaMatriculaNaArvore(ARVORE* root, int key){
    
    if (root == NULL){
    	puts ("Essa matricula nao existe nos registros.");
        return;
	}
    else if ( key < root->pessoa.matricula ){
    	
        buscaMatriculaNaArvore(root->esquerda, key);
	}
        
    else if( key > root->pessoa.matricula ){
    	
        buscaMatriculaNaArvore(root->direita, key);
	}
    else if (key == root->pessoa.matricula){
    	printf("O resgitro correspondente a matricula %d eh:\n", key);
    	exibeRegistroArvore(root);
        return;
	}
}

void buscaNomeNaArvore(ARVORE* root){

    char key[10];

    printf("Digite o nome que deseja buscar: ");
    scanf("%s", key);

    ARVORE* curPtr = root;
    
    while(curPtr != NULL){
    
       // printf("No atual: %s\n", curPtr->pessoa.nome);

        if(strcmp(key, curPtr->pessoa.nome) < 0){
         //   printf("Indo para a esquerda\n");
            curPtr = curPtr->esquerda;
        } else if(strcmp(key, curPtr->pessoa.nome) > 0) {
           // printf("Indo para a direita\n");
            curPtr = curPtr->direita;
        }

        else if(strcmp(key, curPtr->pessoa.nome) == 0){
            printf("Os dados de %s sao:\n", curPtr->pessoa.nome);
            exibeRegistroArvore(curPtr);
            break;
        }


    }

    printf("%s nao existe nos registros.\n", key);
    return;

    
}


void insereOrdenadoNaArvore(ARVORE** rootRef, INFO* novoRegistro){

	ARVORE* newNode = malloc(sizeof(ARVORE));
	ARVORE* curPtr = (*rootRef);

	while(curPtr != NULL) {

		if(curPtr->pessoa.matricula == novoRegistro->matricula) {
			printf("Esse registro ja existe na arvore.\n");
			return;
		}
		else if(newNode->pessoa.matricula < curPtr->pessoa.matricula){
			curPtr = curPtr->esquerda;
		}	
		else{
			curPtr = curPtr->direita;
		}

	}

	newNode->pessoa.matricula = novoRegistro->matricula;
	strcpy(newNode->pessoa.nome, novoRegistro->nome);
	strcpy(newNode->pessoa.sobrenome, novoRegistro->sobrenome);
	strcpy(newNode->pessoa.email, novoRegistro->email);
	strcpy(newNode->pessoa.telefone, novoRegistro->telefone);
	newNode->pessoa.salario = novoRegistro->salario;

	(*rootRef) = insert(rootRef, newNode);



}

