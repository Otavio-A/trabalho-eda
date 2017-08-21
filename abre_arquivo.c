//referência: http://www.geeksforgeeks.org/fseek-in-c-with-example/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void importaRegistro(LISTA** headRef, char arquivo[]) {

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

        LISTA* newNode = malloc(sizeof(LISTA));

        if(newNode == NULL){
            printf("Memoria indisponível.\n");
            exit(0);
        }
         
         newNode->proximo = NULL;   

         fgets(linha, 120, f);


        char* tok;
        tok = strtok(linha, ",");

        while(tok != NULL) {
          
           sscanf(tok, "%d", &((newNode->pessoa).matricula));
           tok = strtok(NULL, ",");

           (newNode->pessoa).nome = malloc(sizeof(tok)*10);
           strcpy((newNode->pessoa).nome, tok);
           tok = strtok(NULL, ",");

           (newNode->pessoa).sobrenome = malloc(sizeof(tok)*10);
           strcpy((newNode->pessoa).sobrenome, tok);
           tok = strtok(NULL, ",");

           (newNode->pessoa).email = malloc(sizeof(tok)*10);
           strcpy((newNode->pessoa).email, tok);
           tok = strtok(NULL, ",");

           (newNode->pessoa).telefone = malloc(sizeof(tok)*10);
           strcpy((newNode->pessoa).telefone, tok);
           tok = strtok(NULL, ",");

           sscanf(tok, "%f", &((newNode->pessoa).salario));
           tok = strtok(NULL, ",");

        }

        append(headRef, newNode);
     

    }
  
}

void exibeRegistro(LISTA* curPtr) {


    printf("--------------------------------------\n");

    printf("Matricula: %d\n", curPtr->pessoa.matricula);
    printf("Nome: %s\n", curPtr->pessoa.nome);
    printf("Sobrenome: %s\n", curPtr->pessoa.sobrenome);
    printf("Email: %s\n", curPtr->pessoa.email);
    printf("Telefone: %s\n", curPtr->pessoa.telefone);
    printf("Salario: %.2f\n", curPtr->pessoa.salario);
    

}

void buscaPeloNome(LISTA* node) {

  char key[10];

  printf("Digite o nome que esta procurando: ");
  scanf("%s", key);

  while(node != NULL){

    if(strcmp((node->pessoa).nome, key) == 0){

      printf("Os dados de %s sao:\n", node->pessoa.nome);
      exibeRegistro(node);

      return;
    
    }

      node = node->proximo; 

  }

  printf("%s nao existe nos registros.\n", key);
  return;

}


void buscaPelaMatricula(LISTA* node) {

  int key;

  printf("\nDigite a matricula que esta procurando: ");
  scanf("%d", &key);

  while(node != NULL){

    if(node->pessoa.matricula == key){
      
      printf("Os dados de %d sao:\n", node->pessoa.matricula);
      exibeRegistro(node);

      return;
    }

    node = node->proximo;

  }

  printf("%d nao existe nos registros.\n", node->pessoa.matricula);
  return;

}


int main() {

  LISTA* head = NULL;
  char arquivo[20];

  printf("Digite o nome do arquivo e sua extensao: ");
  scanf("%s", arquivo);

    importaRegistro(&head, arquivo);
    printList(head);

    buscaPeloNome(head);
    buscaPelaMatricula(head);

}

