//referência: http://www.geeksforgeeks.org/fseek-in-c-with-example/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geral.h"

void importaRegistroParaLista(LISTA** headRef, char arquivo[]) {

    FILE* f;

    int qtd;
    int auxiliar = 0;
    char teste[200];

    f = fopen(arquivo, "r");

    if(f == NULL){
        printf("Desculpa, banco de dados indisponível\n");
        exit(0);
    }

    fscanf(f, "%d", &qtd);
    fseek(f, 0, SEEK_SET);

    // diz quantas linhas deve saltar.
  
  
   int newline = 0;
    for(char c = fgetc(f); newline < 2; c = fgetc(f)){
      if(c == '\n'){
        newline++;
      }
      else{
        auxiliar++;
      }
    }


    fseek(f, 0, SEEK_SET);
    //printf("auxiliar(LISTA) = %d\n", auxiliar);

     // O fseek faz com que a barra se seleção pule para local indicado;
     //Nesses caso, a barra irá pular 49 bytes a partir da linha inicial(SEEK_SET);

    fseek(f, auxiliar, SEEK_SET);
    fgets(teste, 200, f);
    
    for(int i = 0; i < qtd; i++) {

        LISTA* newNode = malloc(sizeof(LISTA));

        if(newNode == NULL){
            printf("Memoria indisponível.\n");
            exit(0);
        }
         
         newNode->proximo = NULL;   

          char linha[200];
         fgets(linha, 200, f);


        char* tok;
        tok = strtok(linha, ",");

        while(tok != NULL) {
          
           sscanf(tok, "%d", &((newNode->pessoa).matricula));
           tok = strtok(NULL, ",");

           //(newNode->pessoa).nome = malloc(sizeof(tok)*10);
           strcpy((newNode->pessoa).nome, tok);
           tok = strtok(NULL, ",");

           //(newNode->pessoa).sobrenome = malloc(sizeof(tok)*10);
           strcpy((newNode->pessoa).sobrenome, tok);
           tok = strtok(NULL, ",");

           //(newNode->pessoa).email = malloc(sizeof(tok)*10);
           strcpy((newNode->pessoa).email, tok);
           tok = strtok(NULL, ",");

           //(newNode->pessoa).telefone = malloc(sizeof(tok)*10);
           strcpy((newNode->pessoa).telefone, tok);
           tok = strtok(NULL, ",");

           sscanf(tok, "%f", &((newNode->pessoa).salario));
           tok = strtok(NULL, ",");

        }

        append(headRef, newNode);
     

    }

   fclose(f);
  
}

void exibeRegistroNaLista(LISTA* curPtr) {


    printf("--------------------------------------\n");
    printf("Matricula: %d\n", curPtr->pessoa.matricula);
    printf("Nome: %s\n", curPtr->pessoa.nome);
    printf("Sobrenome: %s\n", curPtr->pessoa.sobrenome);
    printf("Email: %s\n", curPtr->pessoa.email);
    printf("Telefone: %s\n", curPtr->pessoa.telefone);
    printf("Salario: %.2f\n", curPtr->pessoa.salario);
    

}

void buscaNomeNaLista(LISTA* node) {

  char key[10];

  printf("Digite o nome que esta procurando: ");
  scanf("%s", key);

  printf("Registro(s) correspondente(s) ao nome %s: \n", key);
  while(node != NULL){

    if(strcmp((node->pessoa).nome, key) == 0){

      exibeRegistroNaLista(node);
    
    }

      node = node->proximo; 

  }

  printf("%s nao existe nos registros.\n", key);
  return;

}


void buscaMatriculaNaLista(LISTA* node) {

  int key;

  printf("\nDigite a matricula que esta procurando: ");
  scanf("%d", &key);

  while(node != NULL){

    if(node->pessoa.matricula == key){
      
      printf("O registro corresponde a matricula %d eh:\n", node->pessoa.matricula);
      exibeRegistroNaLista(node);

      return;
    }

    node = node->proximo;

  }

  printf("%d nao existe nos registros.\n", key);
  return;

}

void deletaMatriculaNaLista(LISTA** headRef) {

  LISTA* node = (*headRef);

  int key;
  printf("Digite a matricula corresponde ao registro que deseja deletar: ");
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

void insereOrdenadoNaLista(LISTA** headRef, INFO* novoRegistro) {

  LISTA* newNode = malloc(sizeof(LISTA));
  LISTA* curPtr = (*headRef);

   while(curPtr != NULL) {

    if(novoRegistro->matricula == curPtr->pessoa.matricula){
      printf("Ja existe um registro com essa matricula na lista.\n");
      return;
    }

    curPtr = curPtr->proximo;

  }

  newNode->proximo = NULL;

  newNode->pessoa.matricula = novoRegistro->matricula;
  strcpy(newNode->pessoa.nome, novoRegistro->nome);
  strcpy(newNode->pessoa.sobrenome, novoRegistro->sobrenome);
  strcpy(newNode->pessoa.email, novoRegistro->email);
  strcpy(newNode->pessoa.telefone, novoRegistro->telefone);
  newNode->pessoa.salario = novoRegistro->salario;

  curPtr = (*headRef);

  // insere na lista
  while(curPtr != NULL) {

    if(curPtr->pessoa.matricula > newNode->pessoa.matricula) {
      insertAfter(curPtr->anterior, newNode);
      return;
    }

    curPtr = curPtr->proximo;

  }


  append(headRef, newNode);
  return;



}
