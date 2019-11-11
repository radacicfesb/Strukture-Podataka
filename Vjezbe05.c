#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node;
typedef struct Node* P_Node;
struct Node {
	int Number;
	P_Node Next;
};

int AppendToSet(P_Node, int);				// saljes head di dodajes i broj sta dodajes
P_Node NewBlankElement();					// nista ne saljes
int ReadFromFile(P_Node, char*);			// head u koji citas, string ime filea
int Union(P_Node, P_Node, P_Node);			// head di se upise, head seta 1 pa 2
int Intersection(P_Node, P_Node, P_Node);	// head di se upise, head seta 1 pa 2
int PrintSet(P_Node);						// head sta ispisujes

int main() {
	struct Node Set1;
	struct Node Set2;
	struct Node UnionSet;
	struct Node IntersectionSet;

	Set1.Next = NULL;
	Set2.Next = NULL;
	UnionSet.Next = NULL;
	IntersectionSet.Next = NULL;

	ReadFromFile(&Set1, "Set1.txt");
	printf("set 1:\n");
	PrintSet(&Set1);
	ReadFromFile(&Set2, "Set2.txt");
	printf("set 2:\n");
	PrintSet(&Set2);

	printf("presjek:\n");
	Intersection(&IntersectionSet, &Set1, &Set2);
	PrintSet(&IntersectionSet);

	printf("unija:\n");
	Union(&UnionSet, &Set1, &Set2);
	PrintSet(&UnionSet);

	return 0;
}

int ReadFromFile(P_Node P, char* Filename)	//file je broj po crti
{
	int el = 0;

	char* buff = NULL;
	buff = (char*)malloc(sizeof(char) * 128);
	memset(buff, '\0', 128);

	FILE* fp = fopen(Filename, "r");

	while (!feof(fp)) {

		fgets(buff, 127, fp);
		sscanf(buff, "%d", &el);
		AppendToSet(P, el);
	}
}

P_Node NewBlankElement() {	//kad vrati vidi jel NULL, ako je nije uspia

	P_Node q;
	q = NULL;
	q = (P_Node)malloc(sizeof(struct Node));
	return q;
}

int AppendToSet(P_Node P, int new) {
	P_Node q;
	q = NewBlankElement();
	if (q == NULL)
		return -1;
	while (P->Next != NULL)
		P = P->Next;

	q->Number = new;
	q->Next = NULL;
	P->Next = q;

	return 0;
}

int PrintSet(P_Node P) {

	P = P->Next; // ne zelis ispisat head pa ides odma na iduci
	if (P == NULL)
		printf("lista nema elemenata");
	else
	{
		while (P != NULL)
		{
			printf("%d ", P->Number);
			P = P->Next;
		}
		printf("\n");
	}
}

int Union(P_Node Union, P_Node Set1, P_Node Set2) {

	Set1 = Set1->Next;
	Set2 = Set2->Next;
	int lastEntry = NULL;

	while (Set1!=NULL && Set2!=NULL) {
		
		if (Set1->Number < Set2->Number) {
			if (lastEntry != Set1->Number) {
				AppendToSet(Union, Set1->Number);
				lastEntry = Set1->Number;
			}
			Set1 = Set1->Next;
		}

		else if (Set1->Number > Set2->Number) {
			if (lastEntry != Set2->Number) {
				AppendToSet(Union, Set2->Number);
				lastEntry = Set2->Number;
			}
			Set2 = Set2->Next;
		}

		else if (Set1->Number == Set2->Number) {
			if (lastEntry != Set2->Number) {
				AppendToSet(Union, Set2->Number);
				lastEntry = Set2->Number;
		}
			Set2 = Set2->Next;
		}

	}

	while (Set1 != NULL) {
		if (lastEntry != Set1->Number) {
			AppendToSet(Union, Set1->Number);
			lastEntry = Set1->Number;
		}
		Set1 = Set1->Next;
	}

	while (Set2 != NULL){
		if (lastEntry != Set2->Number) {
			AppendToSet(Union, Set2->Number);
			lastEntry = Set2->Number;
		}
		Set2 = Set2->Next;
	}
		
	return 0;
}


int Intersection(P_Node Inter, P_Node Set1, P_Node Set2) {

	P_Node B_2;
	Set1 = Set1->Next;
	Set2 = Set2->Next;
	B_2 = Set2;

	while (Set1 != NULL) {
		while (Set2 != NULL) {
			if (Set1->Number == Set2->Number)
				AppendToSet(Inter, Set1->Number);
			Set2 = Set2->Next;
		}
		Set2 = B_2;
		Set1 = Set1->Next;
	}
}




