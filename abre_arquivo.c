#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct informacoes{

    int matricula;
    char* nome;
    char* sobrenome;
    char* email;
    char* telefone;
    float salario;

}INFO;



int main() {

    
    FILE* f;
    char linha[100];

    int cont;

    f = fopen("teste.txt", "r");
    
    fscanf(f, "%d", &cont);
    printf("A quantidade de registros eh: %d\n", cont);
    
    printf("----------------------------\n");
    fseek(f, 49, SEEK_SET);         // pula para a linha 3.


    while((fscanf(f,"%s", linha)) != EOF) {
        INFO pessoa;

        char* tok;
        tok = strtok(linha, ",");

        while(tok != NULL) {
          
           sscanf(tok, "%d", &(pessoa.matricula));
           tok = strtok(NULL, ",");

           pessoa.nome = tok;
           tok = strtok(NULL, ",");
           pessoa.sobrenome = tok;
           tok = strtok(NULL, ",");
           pessoa.email = tok;
           tok = strtok(NULL, ",");
           pessoa.telefone = tok;
           tok = strtok(NULL, ",");

           sscanf(tok, "%f", &(pessoa.salario));
           tok = strtok(NULL, ",");

        }

        printf("Matricula:%d\n", pessoa.matricula);
        printf("Nome:%s\n", pessoa.nome);
        printf("Sobrenome:%s\n", pessoa.sobrenome);
        printf("Email:%s\n", pessoa.email);
        printf("Telefone:%s\n", pessoa.telefone);
        printf("Salario:%.2f\n", pessoa.salario);


        printf("-----------------------------\n");

    }

}


