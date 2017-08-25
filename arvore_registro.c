#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geral.h"

void importaRegistroParaArvore(ARVORE** root, char arquivo[]) {

    FILE* f;
    char linha[300];

    int qtd;
    int auxiliar = 49;

    f = fopen(arquivo, "r");

    if(f == NULL){
        printf("Desculpa, banco de dados indisponivel\n");
        exit(0);
    }

    fscanf(f, "%d", &qtd);
    fseek(f, 0, SEEK_SET);

    // diz quantas linhas deve saltar.
    char c;
    for(c = fgetc(f); c != '\n'; c = fgetc(f)) {
      auxiliar++;
    }
    fseek(f, 0, SEEK_SET);
        
     // O fseek faz com que a barra se seleção pule para local indicado;
     //Nesses caso, a barra irá pular 49 bytes a partir da linha inicial(SEEK_SET);    
    fseek(f, auxiliar, SEEK_SET);
    
    for(int i = 0; i < qtd; i++) {

        ARVORE* newNode = malloc(sizeof(ARVORE));

        if(newNode == NULL){
            printf("Memoria indisponivel.\n");
            exit(0);
        }
         
         //newNode->esquerda = NULL;
         //newNode->direita = NULL;   

         fgets(linha, 120, f);

        char* tok;
        tok = strtok(linha, ",");

        while(tok != NULL) {
          
           sscanf(tok, "%d", &(newNode->pessoa.matricula));
           tok = strtok(NULL, ",");

           newNode->pessoa.nome = malloc(sizeof(tok)*10);
           strcpy(newNode->pessoa.nome, tok);
           tok = strtok(NULL, ",");

           newNode->pessoa.sobrenome = malloc(sizeof(tok)*10);
           strcpy(newNode->pessoa.sobrenome, tok);
           tok = strtok(NULL, ",");

           newNode->pessoa.email = malloc(sizeof(tok)*10);
           strcpy(newNode->pessoa.email, tok);
           tok = strtok(NULL, ",");

           newNode->pessoa.telefone = malloc(sizeof(tok)*10);
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

void buscaNomeNaArvore(ARVORE* root, char key[]){

    if (root == NULL){
    	puts ("Esse nome nao existe nos registros.");
    	return;
	}

    else if ( strcmp(root->pessoa.nome, key) > 0 ){
        buscaNomeNaArvore(root->esquerda, key);
	}
        
    else if( strcmp(root->pessoa.nome, key) < 0){
        buscaNomeNaArvore(root->direita, key);
	}
    else if (strcmp(root->pessoa.nome, key) == 0){
    	printf("Os dados de %s sao:\n", key);
        exibeRegistroArvore(root);
        return;
	}
}



ARVORE* criaNovoRegistro() {


  ARVORE* newNode = malloc(sizeof(ARVORE));

  if(newNode == NULL){
    printf("Memoria indisponível.\n");
    exit(0);
  }

    int matricula;
    printf("Matricula: ");
    scanf("%d", &(newNode->pessoa.matricula));
    getchar();

    char nome[20];
    printf("Nome: ");
    fgets(nome, 20, stdin);
    nome[strcspn(nome, "\n")] = 0;
    newNode->pessoa.nome = malloc(sizeof(nome)*10);
    strcpy(newNode->pessoa.nome,nome);

    char sobrenome[20];
    printf("Sobrenome: ");
    fgets(sobrenome, 20, stdin);
    sobrenome[strcspn(sobrenome, "\n")] = 0;
    newNode->pessoa.sobrenome = malloc(sizeof(sobrenome)*10);
    strcpy(newNode->pessoa.sobrenome,sobrenome);


    char email[30];
    printf("Email: ");
    fgets(email, 30, stdin);
    email[strcspn(email, "\n")] = 0;
    newNode->pessoa.email = malloc(sizeof(email)*10);
    strcpy(newNode->pessoa.email,email);

    char telefone[18];
    printf("Telefone: ");
    fgets(telefone, 18, stdin);
    telefone[strcspn(telefone, "\n")] = 0;
    newNode->pessoa.telefone = malloc(sizeof(telefone)*10);
    strcpy(newNode->pessoa.telefone,telefone);

    float salario;
    printf("Salario: ");
    scanf("%f", &(newNode->pessoa.salario));

    return newNode;

}

void insereOrdenadoNaArvore(ARVORE** rootRef) {

	ARVORE* newNode = criaNovoRegistro();
	ARVORE* curPtr = (*rootRef);

	while(curPtr != NULL) {

		if(curPtr->pessoa.matricula == newNode->pessoa.matricula) {
			printf("Esse registro ja existe na arvore.\n");
			return;
		}
		else if(newNode->pessoa.matricula < curPtr->pessoa.matricula){
			//printf("Indo para a direita\n");
			curPtr = curPtr->esquerda;
		}	
		else{
			//printf("Indo para a esquerda\n");
			curPtr = curPtr->direita;
		}

	}


	(*rootRef) = insert(rootRef, newNode);
	return;

}
