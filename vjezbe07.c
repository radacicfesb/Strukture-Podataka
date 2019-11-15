#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node;
typedef struct Node *P_Node;
typedef struct Node{

    char el;
    struct Node *Next;

};

int ReadFromFile(P_Node, char*);
int Push(P_Node, char);
int Calculate(P_Node, char);
int Pop(P_Node);
P_Node NewBlankElement();
int Print(P_Node);

int main()
{
    P_Node Head;
	Head = NULL;
    Head = (P_Node)malloc(sizeof(struct Node));
	Head->Next = NULL;

	ReadFromFile(Head,"pos.txt");

	Print(Head);

    return 0;
}

int ReadFromFile(P_Node P, char* Filename)	//file je broj po crti
{
	char el = 0;
	int i;
	FILE* fp = NULL;

	char* buff = NULL;
	buff = (char*)malloc(sizeof(char) * 128);
	memset(buff, '\0', 128);

	fp = fopen(Filename, "r");


	while (!feof(fp)) {

		fgets(buff, 127, fp);
		//sscanf(buff, "%c", &el);
		for(i = 0; buff[i] != '\0'; i++)
		{
			if(buff[i] != ' ')
				Push(P, buff[i]);
		}
		//Push(P, el);
	}
	return 0;
}


int Calculate(P_Node P, char op){

    float op1 = 0;
    float op2 = 0;

    switch (op)
    {

    case ('/'):
        op1 = Pop(P);
        op2 = Pop(P);
        Push(P, op2 / op1);
        break;

	case ('*'):
        op1 = Pop(P);
        op2 = Pop(P);
        Push(P, op1 * op2);
        break;

    case ('+'):
        op1 = Pop(P);
        op2 = Pop(P);
        Push(P, op1 + op2);
        break;

    case ('-'):
        op1 = Pop(P);
        op2 = Pop(P);
        Push(P, op2 - op1);
        break;

	}

    return 0;
}

int Push(P_Node S, char x) {

	P_Node q;
	P_Node tmp;

	q = NewBlankElement();
	if (q == NULL)
		return -1;
	
	tmp = S->Next;

	q->el = x;
	q->Next = tmp;
	S->Next = q;

	return 0;
}

int Pop(P_Node S) {

	P_Node temp;
	char x;

	temp = S->Next;
	S->Next = S->Next->Next;
	x = temp->el;
	free(temp);

	printf("Popnia je %c\n", &x);
	return x;
}

P_Node NewBlankElement() {	//kad vrati vidi jel NULL, ako je nije uspia

	P_Node q;
	q = NULL;
	q = (P_Node)malloc(sizeof(struct Node));
	return q;
}

int Print(P_Node P) {

	P = P->Next; // ne zelis ispisat head pa ides odma na iduci
	if (P == NULL)
		printf("lista nema elemenata");
	else
	{
		while (P != NULL)
		{
			printf("%c ", P->el);
			P = P->Next;
		}
		printf("\n");
	}

	return 0;
}

