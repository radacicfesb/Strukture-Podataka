#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct Node* P_Node;
typedef struct Stack* P_Stack;


 struct Node {
	char el[128];
	P_Node Levo;
	P_Node Desno;
};

 struct Stack{
	char el[128];
	P_Stack Next;
};

P_Node StackUStablo(P_Stack, P_Node);
int IspisiStablo(P_Node);
int CitajIzDatoteke(P_Stack, char*);
int Operator(char);
int Push(P_Stack, char*);
char* Pop(P_Stack);
int IzrazUStack(P_Stack, char*);
P_Node NoviCvor();


int main()
{
	char filename[512];
	P_Stack Head;
	Head =(P_Stack)malloc(sizeof(struct Stack));
	Head->Next = NULL;
	P_Node root;
	root = NoviCvor();
	
	memset(Head->el, 0, 128);

	printf("Unesite ime datoteke: ");
	scanf(" %s", filename);

	CitajIzDatoteke(Head, filename);

	root = IzrazUStack(Head, root);

	IspisiStablo(root);

	return 0;
}

int CitajIzDatoteke(P_Stack P, char* filename) {
	FILE* fp = NULL;
	char* buff = NULL;
	fp = fopen(filename, "r");

	fgets(buff, 128, fp);
	IzrazUStack(P, buff);

	return 0;
}

int Operator(char el) {
	switch (el)
	{
	case '/':
	case '-':
	case '+':
	case '*':
		return 1;
	}
	return 0;
}

P_Node NoviCvor() {
	P_Node novi;
	novi =(P_Node)malloc(sizeof(struct Node));
	novi->Levo= NULL;
	novi->Desno = NULL;

	return novi;
}

int IspisiStablo(P_Node S) {

	IspisiStablo(S->Levo);
	printf("%s", S->el);
	IspisiStablo(S->Desno);
	return 0;
}

int IzrazUStack(P_Stack P, char* buff) {
	char op[512];
	int offset = 0;

	while (sscanf(buff, " %s %n", op, &offset) == 1)
	{
		IzrazUStack(P, op);
		buff += offset;
		offset = 0;
	}

	return 0;
}

P_Node StackUStablo(P_Stack Head, P_Node root) {
	char* el = Pop(Head);
	root = NoviCvor();

	strcpy(root->el, el);

	if (Operator(root->el[0])) {
		root->Desno = StackUStablo(Head, root->Desno);
		root->Levo = StackUStablo(Head, root->Levo);
	}

	return root;
}

int Push(P_Stack P, char* op) {
	P_Stack S = (P_Stack)malloc(sizeof(struct Stack));

	if (S == NULL)
		return -1;

	S->Next = P->Next;
	P->Next = S;
	strcpy(S->el, op);

	return 0;
}

char* Pop(P_Stack P) {
	char* temp = malloc(sizeof(char));

	P_Stack tempS = P->Next;
	strcpy(temp, tempS->el);
	P->Next = P->Next->Next;
	free(tempS);

	return temp;
}
