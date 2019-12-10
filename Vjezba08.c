#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* P_Node;
typedef struct Stack* P_Stack;
struct Node {
	char  ime[512];
	P_Node Dijete;
	P_Node Next;
};

struct Stack {
	P_Node Directory;
	P_Stack Next;
};

int Nareba(P_Node, P_Stack);
int Push(P_Stack, P_Node);
P_Node Novi(char*);
int Unesi(P_Node, P_Node);
P_Node Pop(P_Stack);
int ValjanArgument(char*);
int DirectoryPostoji(P_Node, char*);
P_Node DirectoryPrekoImena(P_Node, char*);
int md(P_Node, char*);
P_Node cd(P_Node, P_Node, char*, P_Stack);
int dir(P_Node, char*, P_Stack);
P_Node NadiNajmanjiEl(P_Node, P_Node);
int ListaDirectory(P_Node, P_Stack);

int main() {
	P_Node root = Novi("root");
	P_Stack Head;
	Head= (P_Stack)malloc(sizeof(sizeof(struct Stack)));

	Head->Next = NULL;
	Head->Directory = NULL;

	return Shell(root, Head);
}



P_Node NadiNajmanjiEl(P_Node PrviElUDir, P_Node NadiEl) {
	P_Node P = PrviElUDir;

	while (P->Next != NULL && strcmp(P->ime, NadiEl->ime) < 0)
		P = P->Next;

	return P;
}

int ListaDirectory(P_Node Roditelj, P_Stack Head) {
	P_Node TrenutniFile = Roditelj->Dijete;

	printf("%s\n ", Roditelj->ime);

	if (TrenutniFile) {
		if (Head->Next)

		return -1; 
	}

	do {
		if (!TrenutniFile->Dijete)
			printf(" %s\n ", TrenutniFile->ime);
		else
			printf(" %s*\n ", TrenutniFile->ime);
		TrenutniFile = TrenutniFile->Next;
	} while (TrenutniFile != NULL);

	return 0;
}

P_Node Novi(char* ime) {
	P_Node novi;
	novi = (P_Node)malloc(sizeof(struct Node));
	strcpy(novi->ime, ime);

	novi->Next = NULL;
	novi->Dijete = NULL;

	return novi;
}

int Unesi(P_Node Roditelj, P_Node novi) {
	P_Node LijeviEl = Roditelj->Dijete;

	if (!LijeviEl) {
		Roditelj->Dijete = novi;
	}
	else {
		P_Node NajmanjiEl = NadiNajmanjiEl(Roditelj->Dijete, novi);

		if (DirectoryPostoji(Roditelj, novi->ime))
			return -1; 
		else {
			NajmanjiEl->Next = novi;
		}
	}

	return 0;
}

int Push(P_Stack Head, P_Node Directory) {
	P_Stack novi;
	novi = (P_Stack)malloc(sizeof(struct Stack));

	if (!novi)
		return -1;

	novi->Next = Head->Next;
	Head->Next = novi;
	novi->Directory = Directory;

	return 0;
}

P_Node Pop(P_Stack Head) {
	if (!Head->Next)
		return NULL; 

	P_Stack temp;
	temp = Head->Next;
	P_Node Directory = Head->Next->Directory;
	Head->Next = Head->Next->Next;
	free(temp);

	return Directory;
}

int Naredba(P_Node root, P_Stack Head) {
	P_Node Directory = root;
	int status = 0;
	int error = 0;
	char unos[512];
	char naredba[512];
	char arg[512];

	while (!status) {
		printf("%s > ", Directory->ime);

		memset(naredba, 0, 512);
		memset(arg, 0, 512);
		error = 0;

		fgets(unos, 512, stdin);
		sscanf(unos, "%s %s", naredba, arg);

		if (!strcmp(naredba, "md")) {
			md(Directory, arg);
		}
		else if (!strcmp(naredba, "cd")) {
			Directory = cd(Directory, root, arg, Head);
		}
		else if (!strcmp(naredba, "dir")) {
			dir(Directory, arg, Head);
		}
		else if (!strcmp(naredba, "exit"))
			status = 1;
		else if (!strcmp(naredba, "clear") || !strcmp(naredba, "cls")) {
#if __linux__
			system("clear");
#elif _WIN32
			system("cls");
#endif
		}
		else
			printf("Naredba nije pronaðena!\n");
	}

	return 0;
}

int ValjanArgument(char* arg) {
	if (!strlen(arg)) {
		return 0;
	}
	return 1;
}

int DirectoryPostoji(P_Node Directory, char* ImeDirektorija) {
	P_Node P = Directory->Dijete;

	while (P != NULL && strcmp(P->ime, ImeDirektorija))
		P = P->Next;

	if (P == NULL)
		return 0;

	return 1;
}
int md(P_Node Directory, char* arg) {
	int error = 0;

	if (!ValjanArgument(arg))
		printf("Greska\n");
	else {
		error = Unesi(Directory, Novi(arg));
		if (error == -2)
			printf("Direktorij veæ postoji.\n");
	}

	return error;
}

int dir(P_Node Directory, char* arg, P_Stack Head) {
	int error = 0;

	if (ValjanArgument(arg))
		if (DirectoryPostoji(Directory, arg))
			error = ListaDirectory(DirectoryPrekoImena(Directory, arg), Head);
		else
			printf("Direktorij nije pronaðen!\n");
	else
		error = ListaDirectory(Directory, Head);

	if (error == -1)
		printf("Direktorij je prazan.\n");

	return error;
}

P_Node DirectoryPrekoImena(P_Node Directory, char* ImeDirektorija) {
	P_Node P;
	P = Directory->Dijete;

	while (P != NULL && strcmp(P->ime, ImeDirektorija))
		P = P->Next;

	return P;
}



P_Node cd(P_Node Directory, P_Node* root, char* arg, P_Stack Head) {
	int error = 0;

	if (!ValjanArgument(arg))
		printf("Greska.\n");
	else if (!strcmp(arg, "..")) {
		Directory = Pop(Head);
		if (!Directory) {
			printf("Nalazite se u root direktoriju.\n");
			Directory = root;
		}
	}
	else if (!DirectoryPostoji(Directory, arg)) {
		printf("Direktorij ne postoji!\n");
	}
	else {
		error = Push(Head, Directory);
		if (error == -1)
			printf("greška\n");
		else
			Directory = DirectoryPrekoImena(Directory, arg);
	}

	return Directory;
}

