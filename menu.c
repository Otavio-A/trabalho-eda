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


void ImportaRegistro(ARVORE* root, LISTA* head) {


	char arquivo[20];

	printf("Digite o nome do arquivo que deseja importar: ");
	scanf("%s", arquivo);

	clock_t tTree, tList;
	double tempoTree, tempoList;

	tTree = clock();
	importaRegistroParaArvore(&root, arquivo);
	tTree = clock() - tTree;

	tempoTree = ((double)tTree)/CLOCKS_PER_SEC;

	tList = clock();
	importaRegistroParaLista(&head, arquivo);
	tList = clock() - tList;

	tempoList = ((double)tList)/CLOCKS_PER_SEC;


	printf("\n---------------------------------------------------------------------------\n");
	printf("Total de registros importados: %d\n", quantidadeDeRegistros(arquivo));
	printf("Tempo de importacao para a arvore: %f segundo(s)\n", tempoTree);
	printf("Tempo de importacao para a lista duplamente encadeada: %f segundo(s)\n", tempoList);
	printf("---------------------------------------------------------------------------\n\n");




}


int main() {


	ARVORE* root = NULL;
	LISTA* head = NULL;

	ImportaRegistro(root, head);


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


		clock_t tTree, tList;
		double tempoArvore, tempoLista;

		switch(escola) {
			char subEscolha;

			case 1:
				
				printf("Em qual estrutura voce deseja buscar?\n");
				printf("(a) - Arvore | (b) - Lista Duplamente Encadeada\nescolha: ");
				scanf("%c", &subEscolha);
				
				switch(subEscolha){
					case 'a':

						printf("Digite a matricula que deseja buscar: \n");
						scanf("%d", &mat);
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
							break

						default:
							printf("Opcao invalida!\n");
							break;
				}

				break;

			case 2:

				printf("Em qual estrutura voce deseja buscar?\n");
				printf("(a) - Arvore (b) - Lista Duplamente Encadeada\nescolha: ");
				scanf("%c", &subEscolha);

				switch(subEscolha) {
					case 'a':

						printf("Digite o nome que deseja buscar: ");
						scanf("%s", name);
						tTree = clock();
						buscaNomeNaArvore(root, name);
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

				case 3:

					tTree = clock();
					insereOrdenadoNaArvore(&root);
					tTree = clock() - tTree;

					tempoArvore = ((double)tTree)/CLOCKS_PER_SEC;

					tList = clock();
					insereOrdenadoNaLista(&head);
					tList = clock();

					tempoLista = ((double)tTree)/CLOCKS_PER_SEC;

					printf("Tempo de insercao de um novo no na arvore: %f segundo(s)\n", tempoArvore);
					printf("Tempo de insercao de um novo no na lista: %f segundo(s)\n", tempoLista);

					break;

				case 4:
					

				}









		}







	}








}