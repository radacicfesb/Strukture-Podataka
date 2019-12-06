#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node;
typedef struct Node* P_Node;
typedef struct Node {

	int el;
	struct Node* Levo;
	struct Node* Desno;

};

P_Node BrisiElement(P_Node, int);
P_Node UnesiElement(int, P_Node);
int IspisiStablo(P_Node);
P_Node NadiMin(P_Node);
P_Node NadiMax(P_Node);
P_Node NadiElement(P_Node, int);

int main() {
	P_Node Root;
	P_Node Trazeno;
	Root = (P_Node)malloc(sizeof(P_Node));
	Root = NULL;

	 Root = UnesiElement(4, Root);
	 UnesiElement(23, Root);
	 UnesiElement(5, Root);
	 UnesiElement(234, Root);
	 UnesiElement(12, Root);
	 Root = BrisiElement(234, Root);
	 Trazeno = NadiElement(Root, 4);

	IspisiStablo(Root);
	
	return 0;

}

P_Node UnesiElement(int x, P_Node root) {

	if (root == NULL) {
		root = (P_Node)malloc(sizeof(struct Node));



		root->el = x;
		root->Levo = NULL;
		root->Desno = NULL;
	}
	else if (root->el < x)
		root->Desno = UnesiElement(x, root->Desno);
	else if (root->el > x)
		root->Levo = UnesiElement(x, root->Levo);
	return root;
}

int IspisiStablo(P_Node root)
{
	if (root == NULL)
		return 0;

	IspisiStablo(root->Levo);

	IspisiStablo(root->Desno);

	printf("%d ", root->el);
	return 0;
}

P_Node BrisiElement(P_Node P, int x) {
	P_Node temp;

	 if (x < P->el)
		P->Levo = BrisiElement(P->Levo, x);
	else if (x > P->el)
		P->Desno = BrisiElement(P->Desno, x);
	else  {
		if (P->Levo != NULL && P->Desno != NULL) {
		
		temp = NadiMin(P->Desno);
		P->el = temp->el;
		P->Desno = BrisiElement(P->Desno, temp->el);
		
	}
	else
	{
		temp = P;
		if (P->Levo == NULL)
			P = P->Desno;
		else
			P = P->Levo;
		free(temp);
	}
}

return P;
}

P_Node NadiMin(P_Node P) {
	if (P != NULL && P->Levo != NULL)
	{
		return NadiMin(P->Levo);
	}

	return P;
}

P_Node NadiMax(P_Node P) {
	if (P == NULL) 
		return P;

	while (P->Desno != NULL)
		P = P->Desno;
	return P;
}

P_Node NadiElement(P_Node P, int x)
{
	if (P == NULL)
		return P;

	if (P->el < x)
		return NadiElement(P->Desno, x);
	else if (P->el > x)
		return NadiElement(P->Levo, x);
	else
		return P;
}