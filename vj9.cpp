#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node;
typedef struct Node* P_Node;
typedef struct Node {

	int el;
	struct Node* Levo;
	struct Node* Desno;

};

P_Node NewBlankElement();
int BrisiElement();
P_Node UnesiElement(int, P_Node);
int NadiElement();
int IspisiStablo(P_Node);

int main() {
	P_Node Root;
	Root = (P_Node)malloc(sizeof(P_Node));
	Root = NULL;

	Root = UnesiElement(4, Root);
	UnesiElement(23, Root);
	UnesiElement(5, Root);
	UnesiElement(234,Root);
	UnesiElement(12, Root);

	IspisiStablo(Root);
	getchar();
	return 0;
	
}

P_Node NewBlankElement() {	//kad vrati vidi jel NULL, ako je nije uspia

	P_Node q;
	q = NULL;
	q = (P_Node)malloc(sizeof(struct Node));
	return q;
}

P_Node UnesiElement(int x, P_Node root) {

	//P_Node q = NewBlankElement();
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
	/*q->el = x;
	q->Desno = NULL;
	q->Levo = NULL;

	if  (root == NULL) {
		root = q;
		return 0;
	}

	while (root->Desno != NULL && root->Levo != NULL)
	{
		if (root->el < x) {
			root = root->Levo;
		}
		if (root->el > x) {
			root = root->Desno;
		}
	}

	if (root->el < x)
		root->Levo = q;
	if (root->el > x)
		root->Desno = q;

	return 0;
*/


int IspisiStablo(P_Node root)
{
	if (root == NULL)
		return 0;
	
	IspisiStablo(root->Levo);

	IspisiStablo(root->Desno);

	printf("%d ", root->el);
	return 0;
}

Pos tmp;
if (P == NULL)
{
	PrintError("Element not found.");
}
else if (n < P->El)
	P->Left = Delete(P->Left, n);
else if (n > P->El)
P->Right = Delete(P->Right, n);
else
{
	if (P->Left != NULL && P->Right != NULL)
	{
		// Min from Right subtree
		tmp = FindMin(P->Right);
		P->El = tmp->El;
		P->Right = Delete(P->Right, tmp->El);
		/* or Max from Left subtree
		tmp = FindMax(P->Left);
		P->El = tmp->El;
		P->Left = Delete(P->Left, tmp->El);
		*/
	}
	else
	{
		tmp = P;
		if (P->Left == NULL)
			P = P->Right;
		else
			P = P->Left;
		free(tmp);
	}
}

return P;