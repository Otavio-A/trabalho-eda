#ifndef _INFO_H_
#define _INFO_H_

typedef struct informacoes{

    int matricula;
    char* nome;
    char* sobrenome;
    char* email;
    char* telefone;
    float salario;

}INFO;

void salvaDados(INFO** headRef, INFO** tailPtr);
void insereDados();


#endif