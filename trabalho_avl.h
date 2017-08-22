typedef struct informacoes{

    int matricula;
    char* nome;
    char* sobrenome;
    char* email;
    char* telefone;
    float salario;

}INFO;


typedef struct Node{
  
    INFO pessoa;

    struct Node *esquerda;
    struct Node *direita;
    int altura;

}ARVORE;


void importaRegistroParaArvore(ARVORE** root, char arquivo[]);
void buscaMatricula(ARVORE* root, int key);
void buscaNome(ARVORE* root, char key[]);
void exibeRegistroArvore(ARVORE* node);
void insereOrdenadoNaArvore(ARVORE** rootRef);



int max(int a, int b);
int altura(struct Node *N);
ARVORE *direitaRotate(ARVORE *y);
ARVORE *esquerdaRotate(ARVORE *x);
int getBalance(ARVORE *N);
ARVORE* insert(ARVORE** node, ARVORE* newNode);
ARVORE * minValueNode(ARVORE* node);
ARVORE* deleteTreeNode(ARVORE* root, int matricula);
void exibeRegistroTree(ARVORE* node);
void imprimeArvore(ARVORE *root);

