typedef struct lista {

	int data;
	struct lista* proximo;
	struct lista* anterior;


}LISTA;

void push(LISTA** headRef, int newData);
void insertAfter(LISTA* prevNode, int newData);
void deleteNode(LISTA** headRef, LISTA* del);
void append(LISTA** headRef, int newData);
void printList(LISTA* node); 