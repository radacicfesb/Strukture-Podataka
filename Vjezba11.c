#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* P_Node;
struct Node {
	char Prvi[512];
	char Zadnji[512];
	int m_br;
	P_Node Next;
};

P_Node DodajNoviEl(void);
P_Node* InicijalizirajTablicu(int);
int RacunajHash(char*, int);
int DodajEl(P_Node*, char*, char*, int);
int CitajIzDatoteke(P_Node*, char*);
int IspisiTablicu(P_Node*, int);
int IspisiListu(P_Node, int);
P_Node Unesi(P_Node, char*, char*);
P_Node IdiNaPrvi(P_Node, char*);
int IspisiM_Br(P_Node);
P_Node Nadi(P_Node*, char*, char*);

int main() {
	P_Node* Tablica = InicijalizirajTablicu(11);
	char ime[512];
	char prezime[512];
	char izbor = 'n';
	
	//if (argc < 2) {
		//printf("Unesi ime datoteke!");
		//return -2;
	//}

	CitajIzDatoteke(Tablica, "sranje.txt");

	IspisiTablicu(Tablica, 11);

	do {
		printf("Unesite ime i prezime za ispis maticnog broja ");
		scanf(" %s %s", ime, prezime);
		IspisiM_Br(Nadi(Tablica, ime, prezime));
		printf("Zelite li ispisati maticni broj za drugog korisnika [d/n] ");
		scanf(" %c", &izbor);
	} while (izbor == 'd');

	return 0;
}

P_Node DodajNoviEl(void) {
	P_Node el;
	el =(P_Node)malloc(sizeof(struct Node));

	if (!el) {
		printf("Greska");
		return -1;
	}

	memset(el->Prvi, 0, 512);
	memset(el->Zadnji, 0, 512);

	el->m_br = 0;
	el->Next = NULL;

	return el;
}

P_Node* InicijalizirajTablicu(int br) {
	int i = 0;
	P_Node* Tablica;
	Tablica = malloc(br * sizeof(P_Node));

	if (!Tablica) {
		printf("Greska");
		return -1;
	}

	for (i = 0; i < br; i++) {
		Tablica[i] = DodajNoviEl();
	}

	return Tablica;
}

int RacunajHash(char* prezime, int Vel)
{
	int sum = 0;
	int i = 0;

	for (i = 0; i < 5; i++) {
		sum += (int)prezime[i];
	}

	return sum % Vel;
}

int DodajEl(P_Node* Tablica, char* Prvi, char* Zadnji, int m_br)
{
	int Pozicija = RacunajHash(Zadnji, 11);
	P_Node el = NULL;
	P_Node temp = NULL;

	el = Unesi(Tablica[Pozicija], Prvi, Zadnji);

	strcpy(el->Prvi, Zadnji);
	strcpy(el->Zadnji, Zadnji);
	el->m_br = m_br;

	return 0;
}

int CitajIzDatoteke(P_Node* Tablica, char* filename)
{
	char buff[512];
	FILE* fp = fopen(filename, "r");

	if (!fp)
		return -1;

	while (!feof(fp)) {
		char Prvi[512];
		char Zadnji[512];
		int m_br;
		fgets(buff, 512, fp);
		sscanf(buff, "%s %s %d", Prvi, Zadnji, &m_br);
		DodajEl(Tablica, Zadnji, Prvi, m_br);
	}

	fclose(fp);

	return 0;
}

int IspisiTablicu(P_Node* Tablica, int Vel)
{
	int i = 0;

	for (i = 0; i < Vel; i++)
		if (Tablica[i]->Next)
			IspisiListu(Tablica[i]->Next, i);
		else
			printf("%d) --- \n", i);

	return 0;
}

int IspisiListu(P_Node El, int ind)
{
	P_Node element = El;

	printf("%d)", ind);

	do {
		printf(" %s %s\t", element->Prvi, element->Zadnji);
		element = element->Next;
	} while (element);

	printf("\n");

	return 0;
}

P_Node Unesi(P_Node red, char* Prvi, char* Zadnji)
{
	P_Node el = red;
	P_Node temp = NULL;

	while (el->Next && strcmp(Zadnji, el->Next->Zadnji) > 0)
		el = el->Next;

	if (el->Next && !strcmp(Zadnji, el->Next->Zadnji)) {
		el = IdiNaPrvi(red, Zadnji);
		while (el->Next && !strcmp(Zadnji, el->Next->Zadnji) && strcmp(Prvi, el->Next->Prvi) > 0)
			el = el->Next;
	}

	temp = el->Next;
	el->Next = DodajNoviEl();
	el = el->Next;
	el->Next = temp;

	return el;
}

P_Node IdiNaPrvi(P_Node El, char* Zadnji)
{
	P_Node element = El;

	while (strcmp(element->Next->Zadnji, Zadnji))
		element = element->Next;

	return element;
}

P_Node Nadi(P_Node* Tablica, char* ime, char* prezime)
{
	int Pozicija = RacunajHash(prezime, 11);

	P_Node el = Tablica[Pozicija]->Next;

	while (el)
		if (!strcmp(el->Zadnji, prezime) && !strcmp(el->Prvi, ime))
			return el;
		else
			el = el->Next;

	return el;
}

int IspisiM_Br(P_Node el)
{
	if (!el)
		return -1;

	printf("%d\n", el->m_br);

	return 0;
}