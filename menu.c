#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "geral.h"

int quantidadeDeRegistros(char arquivo[]) {


	FILE* f;
	int quantidade;

	f = fopen(arquivo, "r");

	fscanf(f, "%d", &quantidade);

	fclose(f);

	return quantidade;


}


void ImportaRegistro(ARVORE** root, LISTA** head) {


	char arquivo[20];
	printf("Digite o nome do arquivo que deseja importar: ");
	scanf("%s", arquivo);
	getchar();

	clock_t tTree, tList;
	double tempoTree, tempoList;

	tTree = clock();
	importaRegistroParaArvore(root, arquivo);
	tTree = clock() - tTree;
	tempoTree = ((double)tTree)/CLOCKS_PER_SEC;


	tList = clock();
	importaRegistroParaLista(head, arquivo);
	tList = clock() - tList;
	tempoList = ((double)tList)/CLOCKS_PER_SEC;

	
	printf("\n---------------------------------------------------------------------------\n");
	printf("Total de registros importados: %d\n", quantidadeDeRegistros(arquivo));
	printf("Tempo de importacao para a arvore: %f segundo(s)\n", tempoTree);
	printf("Tempo de importacao para a lista duplamente encadeada: %f segundo(s)\n", tempoList);
	printf("---------------------------------------------------------------------------\n\n");

}

void insereNovoRegistro(ARVORE** rootRef, LISTA** headRef){


	clock_t tTree, tList;
	double tempoArvore,  tempoLista;

	INFO* novoRegistro = malloc(sizeof(INFO));
	
	if(novoRegistro == NULL){
		puts("Memoria indisponivel");
		exit(0);
	}

	printf("Matricula: ");
	scanf("%d",  &novoRegistro->matricula);
	getchar();

	printf("Nome: ");
	fgets(novoRegistro->nome, 20, stdin);
	novoRegistro->nome[strcspn(novoRegistro->nome, "\n")] = 0;

	printf("sobrenome: ");
	fgets(novoRegistro->sobrenome, 20, stdin);
    novoRegistro->sobrenome[strcspn(novoRegistro->sobrenome, "\n")] = 0;

    printf("Email: ");
    fgets(novoRegistro->email, 30, stdin);
    novoRegistro->email[strcspn(novoRegistro->email, "\n")] = 0;

    printf("Telefone: ");
    fgets(novoRegistro->telefone, 18, stdin);
    novoRegistro->telefone[strcspn(novoRegistro->telefone, "\n")] = 0;

    printf("salario: ");
    scanf("%f", &novoRegistro->salario);
    getchar();

    tTree = clock();
    insereOrdenadoNaArvore(rootRef, novoRegistro);
    tTree = clock() - tTree;
    tempoArvore = ((double)tTree)/CLOCKS_PER_SEC;

    tList = clock();
    insereOrdenadoNaLista(headRef, novoRegistro);
    tList = clock() - tList;
    tempoLista = ((double)tList)/CLOCKS_PER_SEC;

   	printf("Tempo de insercao de um novo no na arvore: %f segundo(s)\n", tempoArvore);
	printf("Tempo de insercao de um novo no na lista: %f segundo(s)\n", tempoLista);





}


int main() {


	ARVORE* root = NULL;
	LISTA* head = NULL;

	ImportaRegistro(&root, &head);


	while(1) {

		int escolha;

		int mat;
		char name[20];

		printf("\nO que voce deseja fazer agora?\n");
		printf("(1) - buscar pela matricula\n");
		printf("(2) - buscar pelo nome\n");
		printf("(3) - inserir um novo registro\n");
		printf("(4) - apagar um registro\n");
		printf("(5) - imprimir os registros\n");
		printf("escolha: ");
		scanf("%d", &escolha);
		getchar();


		clock_t tTree, tList;
		double tempoArvore, tempoLista;

		switch(escolha) {
			char subEscolha;

			case 1:
				
				printf("Em qual estrutura voce deseja buscar?\n");
				printf("(a) - Arvore | (b) - Lista Duplamente Encadeada\nescolha: ");
				scanf("%c", &subEscolha);
				getchar();
				
				switch(subEscolha){
					case 'a':

						printf("Digite a matricula que deseja buscar: \n");
						scanf("%d", &mat);
						getchar();

						tTree = clock();
						buscaMatriculaNaArvore(root, mat);
						tTree = clock() - tTree;

						tempoArvore = ((double)tTree)/CLOCKS_PER_SEC;
						printf("Tempo da funcao busca matricula na arvore: %f segundo(s)\n", tempoArvore);
						break;


						case 'b':

							tList = clock();
							buscaMatriculaNaLista(head);
							tList = clock() - tList;

							tempoLista = ((double)tList)/CLOCKS_PER_SEC;
							printf("Tempo da funcao busca matricula na lista: %f segundo(s)\n", tempoLista);
							break;

						default:
							printf("Opcao invalida!\n");
							break;
				}

				break;

			case 2:

				printf("Em qual estrutura voce deseja buscar?\n");
				printf("(a) - Arvore (b) - Lista Duplamente Encadeada\nescolha: ");
				scanf("%c", &subEscolha);
				getchar();

				switch(subEscolha) {
					case 'a':

						tTree = clock();
						buscaNomeNaArvore(root);
						tTree = clock() - tTree;

						tempoArvore = ((double)tTree)/CLOCKS_PER_SEC;
						printf("Tempo da funcao busca nome na arvore: %f segundo(s)\n", tempoArvore);
						break;


					case 'b':
						
						tList = clock();
						buscaNomeNaLista(head);
						tList = clock() - tList;

						tempoLista = ((double)tList)/CLOCKS_PER_SEC;
						printf("Tempo da funcao busca nome na lista: %f segundo(s)\n", tempoLista);
						break;

					default:
						printf("Opcao invalida!\n");
						break;
					

				}

				break;
			
			case 3:

				insereNovoRegistro(&root, &head);

				break;

			case 4:

				printf("Em qual estrutura voce deseja deletar?\n");
				printf("(a) - Arvore (b) - Lista Duplamente Encadeada\nescolha: ");
				scanf("%c", &subEscolha);
				getchar();

				switch(subEscolha) {


					case 'a':
						
						printf("Digite a matricula que deseja deletar: ");
						scanf("%d", &mat);

						tTree = clock();
						deleteTreeNode(root, mat);
						tTree = clock() - tTree;

						tempoArvore = ((double)tTree)/CLOCKS_PER_SEC;
						printf("Tempo de delecao na arvore: %f segundo(s)\n", tempoArvore);
						break;

					case 'b':

						tList = clock();
						deletaMatriculaNaLista(&head);
						tList = clock();

						tempoLista = ((double)tList)/CLOCKS_PER_SEC;
						printf("Tempo de delecao na lista: %f segundo(s)\n", tempoLista);
						break;

					default:
						printf("Opcao Invalida!\n");
						break;

				}

				break;

			case 5:

				printf("De qual estrutura voce deseja imprimir\n");
				printf("(a) - Arvore (b) - Lista Duplamente Encadeada\nescolha: ");
				scanf("%c", &subEscolha);

				switch(subEscolha) {

					case 'a':

						tTree = clock();
						imprimeArvore(root);
						tTree = clock() - tTree;

						tempoArvore = ((double)tTree)/CLOCKS_PER_SEC;
						printf("O tempo de impressao dos registros na arvore foi: %f segundo(s)\n", tempoArvore);
						break;

					case 'b':

						tList = clock();
						imprimeLista(head);
						tList = clock();

						tempoLista = ((double)tList)/CLOCKS_PER_SEC;
						printf("O tempo de impressao dos registros na lista foi: %f segundo(s)\n", tempoLista);
						break;

					default:
						printf("Opcao Invalida!\n");
						break;

				}

				break;


		}


	}


}