#include <stdio.h>
#include <string.h> //É com essa biblioteca que você vai gerenciar os dados


typedef struct pessoa
{
	char *matricula;
	char *nome;
	char *sobrenome;
	char *email;
	char *telefone;
	char *salario;


}Pessoa;

int main (){ 
	char url[]="MOCK_DATA.csv";
	char ch;
	FILE *arq;
	char *linha;
	int t =0;
	int tamanho= 0;

	
	arq = fopen(url, "r");
	if(arq == NULL)
	    printf("Erro, nao foi possivel abrir o arquivo\n");
	
	fclose(arq);
	fgets(linha, 200 , arq);
	while(linha[t]!='\0'){
		int ax = 1;
		tamanho += (linha[t] - 48)*ax;
		t++;
		ax = ax*10;
	}
	fgets(linha , 200 , arq);
	


	while(linha != NULL){
		linha = fgets(linha, 200 ,arq);
		char *matricula = strtok(linha, ",");
		char *nome = strtok(linha, ",");
		char *sobrenome = strtok(linha, ",");
		char *email= strtok(linha, ",");
		char *telefone = strtok(linha, ",");
		char *salario = strtok(linha, ",");
	}
	
	return 0;
}
    
	
	