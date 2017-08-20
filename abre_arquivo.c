//referência: http://www.geeksforgeeks.org/fseek-in-c-with-example/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"

void salvaDados(INFO** headRef, INFO** tailRef) {

    FILE* f;
    char linha[300];

    int qtd;

    f = fopen("teste.txt", "r");

    if(f == NULL){
        printf("Desculpa, banco de dados indisponível\n");
        exit(0);
    }

    fscanf(f, "%d", &qtd);
    printf("A quantidade de registros eh:%d\n", qtd);
        
     // O fseek faz com que a barra se seleção pule para local indicado;
     //Nesses caso, a barra irá pular 49 bytes a partir da linha inicial(SEEK_SET);    
    fseek(f, 52, SEEK_SET);
    
    for(int i = 0; i < qtd; i++) {

        INFO* newNode = malloc(sizeof(INFO));

        if(newNode == NULL){
            printf("Memoria indisponível.\n");
            exit(0);
        }
         
         newNode->proximo = NULL;   

         fgets(linha, 120, f);


        char* tok;
        tok = strtok(linha, ",");

        while(tok != NULL) {
          
           sscanf(tok, "%d", &(newNode->matricula));
           tok = strtok(NULL, ",");

           newNode->nome = malloc(sizeof(tok)*10);
           strcpy(newNode->nome, tok);
           tok = strtok(NULL, ",");

           newNode->sobrenome = malloc(sizeof(tok)*10);
           strcpy(newNode->sobrenome, tok);
           tok = strtok(NULL, ",");

           newNode->email = malloc(sizeof(tok)*10);
           strcpy(newNode->email, tok);
           tok = strtok(NULL, ",");

           newNode->telefone = malloc(sizeof(tok)*10);
           strcpy(newNode->telefone, tok);
           tok = strtok(NULL, ",");

           sscanf(tok, "%f", &(newNode->salario));
           tok = strtok(NULL, ",");

        }
        
        if((*headRef )== NULL){
          (*headRef) = newNode;
           (*tailRef) = newNode;
        }

        else {
            (*tailRef)->proximo = newNode;
            (*tailRef) = newNode;
        }
     

    }
  
}

void insereDados() {


    char linha[200];

    printf("Insira matricula, nome, sobrenome, email, telefone,salario separados por virgula\n");
    scanf("%s", linha);

    FILE* f;

    f = fopen("teste.txt", "r+");

    if(f == NULL){
        printf("Desculpa, banco de dados indisponível\n");
        exit(0);
    }

    int qtd;
    fscanf(f, "%d", &qtd);
    qtd++;

    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", qtd);

    fseek(f, 0, SEEK_END);
    fprintf(f, "%s", linha);

    fclose(f);

}

void imprimeDados(INFO* curPtr) {

    printf("Dados atuais:\n");

    while(curPtr != NULL) {

        printf("--------------------------------------\n");

        printf("Matricula: %d\n", curPtr->matricula);
        printf("Nome: %s\n", curPtr->nome);
        printf("Sobrenome: %s\n", curPtr->sobrenome);
        printf("Email: %s\n", curPtr->email);
        printf("Telefone: %s\n", curPtr->telefone);
        printf("Salario: %.2f\n", curPtr->salario);

        curPtr = curPtr->proximo;

    }
    printf("\n");

}


int main() {

    INFO* ini = NULL, *fim = NULL;
    fim = ini;

    salvaDados(&ini, &fim);

    imprimeDados(ini);

}

