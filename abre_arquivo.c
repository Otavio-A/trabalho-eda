//referência: http://www.geeksforgeeks.org/fseek-in-c-with-example/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geral.h"

void importaRegistroParaLista(LISTA** headRef, char arquivo[]) {

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

  while(node != NULL){

    if(strcmp((node->pessoa).nome, key) == 0){

      printf("Os dados de %s sao:\n", node->pessoa.nome);
      exibeRegistroNaLista(node);

      return;
    
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
      
      printf("Os dados de %d sao:\n", node->pessoa.matricula);
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


LISTA* criaNovoNoNaLista() {


  LISTA* newNode = malloc(sizeof(LISTA));

  if(newNode == NULL){
    printf("Memoria indisponível.\n");
    exit(0);
  }

    printf("Por favor, digite as informacoes solicitadas abaixo\n");

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


void insereOrdenadoNaLista(LISTA** headRef){

  LISTA* curPtr = (*headRef);
  LISTA* newNode = criaNovoNoNaLista();

  // verifica se ja existe uma matricula dessa na lista
  while(curPtr != NULL) {

    if(newNode->pessoa.matricula == curPtr->pessoa.matricula){
      printf("Ja existe um registro com essa matricula na lista.\n");
      return;
    }

    curPtr = curPtr->proximo;

  }

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