//referência: http://www.geeksforgeeks.org/fseek-in-c-with-example/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabalho_avl.h"

void importaRegistroParaArvore(ARVORE** root, char arquivo[]) {

    FILE* f;
    char linha[300];

    int qtd;
    int auxiliar = 47;

    f = fopen(arquivo, "r");

    if(f == NULL){
        printf("Desculpa, banco de dados indisponível\n");
        exit(0);
    }

    fscanf(f, "%d", &qtd);

    // diz quantas linhas deve saltar.
    if(qtd < 10) 
      auxiliar += 3;
    else if(qtd >= 10 && qtd < 100)
      auxiliar += 4;
    else if(qtd >= 100 && qtd < 1000)
      auxiliar += 5;
    else if(qtd >= 1000 && qtd < 10000)
      auxiliar += 6;
    else if(qtd >= 10000)
      auxiliar += 7;


    printf("A quantidade de registros eh:%d\n", qtd);
        
     // O fseek faz com que a barra se seleção pule para local indicado;
     //Nesses caso, a barra irá pular 49 bytes a partir da linha inicial(SEEK_SET);    
    fseek(f, auxiliar, SEEK_SET);
    
    for(int i = 0; i < qtd; i++) {

        ARVORE* newNode = malloc(sizeof(ARVORE));

        if(newNode == NULL){
            printf("Memoria indisponível.\n");
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


void buscaMatricula(ARVORE* root, int key){
    
    if (root == NULL){
    	puts ("Essa matricula não existe nos registros.");
        return;
	}
    else if ( key < root->pessoa.matricula ){
        buscaMatricula(root->esquerda, key);
	}
        
    else if( key > root->pessoa.matricula ){
        buscaMatricula(root->direita, key);
	}
    else if (key == root->pessoa.matricula){
    	printf("O resgitro correspondente a matricula %d eh:\n", key);
    	exibeRegistroArvore(root);
        return;
	}
}

void buscaNome(ARVORE* root, char key[]){

    if (root == NULL){
    	puts ("Esse nome nao existe nos registros.");
    	return;
	}

    else if ( strcmp(root->pessoa.nome, key) > 0 ){
        buscaNome(root->esquerda, key);
	}
        
    else if( strcmp(root->pessoa.nome, key) < 0){
        buscaNome(root->direita, key);
	}
    else if (strcmp(root->pessoa.nome, key) == 0){
    	printf("Os dados de %s sao:\n", key);
        exibeRegistroArvore(root);
        return;
	}
}




/*

void deletaMatriculaNaArvore(ARVORE** headRef) {

  ARVORE* node = (*headRef);

  int key;
  printf("Digite a matricula que deseja deletar: ");
  scanf("%d", &key);

  while(node != NULL) {

    if(node->pessoa.matricula == key){
      deleteNode(headRef, node);
      printf("Foi deletado.\n");
      return;
    }

    node = node->proximo;


  }

  printf("%d nao existe nos registros.\n", key);
  return;

}


ARVORE* criaNovoNoNaArvore() {


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
*/