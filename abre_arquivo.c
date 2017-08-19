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
    char* a;
    char* b;
    char* c;
    char linha[100];

    int n1, n2, n3; 

    f = fopen("teste.txt", "r");
    printf("----------------------------\n");


    while((fscanf(f,"%s", linha)) != EOF) {
        INFO pessoa;

        char* tok;
        tok = strtok(linha, ",");

        while(tok != NULL) {
            //printf("%s\n", tok);
            //tok = strtok(NULL, ",");
            //a = tok;
            //tok = strtok(NULL, ",");
            //b = tok;
            //tok = strtok(NULL, ",");
            //c = tok;
            //tok = strtok(NULL, ",");

            //sscanf(tok, "%d", &n1);
            //tok = strtok(NULL, ",");
            //sscanf(tok, "%d", &n2);
            //tok = strtok(NULL, ",");
            //sscanf(tok, "%d", &n3);
            //tok = strtok(NULL, ",");


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


