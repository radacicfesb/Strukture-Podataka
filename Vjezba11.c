#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* P_Node;
struct Node {
	char Ime[512];
	char Prezime[512];
	int m_br;
	P_Node Next;
};


P_Node* InicijalizirajTablicu(int);
P_Node DodajNoviEl(void);
P_Node Nadi(P_Node*, char*, char*);
int CitajIzDatoteke(P_Node*, char*);
int IspisiTablicu(P_Node*, int);
int RacunajHash(char*, int);
int DodajEl(P_Node*, char*, char*, int);
int IspisiListu(P_Node, int);
int IspisiM_Br(P_Node);
P_Node Nadi(P_Node*, char*, char*);
P_Node Unesi(P_Node, char*, char*);
P_Node IdiNaPrvi(P_Node, char*);

int main() {
	P_Node* Tablica = InicijalizirajTablicu(11);
	char ime[512];
	char prezime[512];
	char izbor = 'n';
	

	CitajIzDatoteke(Tablica, "studenti.txt");

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

P_Node DodajNoviEl(void) {
	P_Node el;
	el =(P_Node)malloc(sizeof(struct Node));

	if (!el) {
		printf("Greska");
		return -1;
	}

	memset(el->Ime, 0, 512);
	memset(el->Prezime, 0, 512);

	el->m_br = 0;
	el->Next = NULL;

	return el;
}




int DodajEl(P_Node* Tablica, char* Prvi, char* Zadnji, int m_br)
{
	int Pozicija = RacunajHash(Prezime, 11);
	P_Node el = NULL;
	P_Node temp = NULL;

	el = Unesi(Tablica[Pozicija], Ime, Prezime);

	strcpy(el->Ime, Prezime);
	strcpy(el->Prezime, Prezime);
	el->m_br = m_br;

	return 0;
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

int CitajIzDatoteke(P_Node* Tablica, char* filename)
{
	char buff[512];
	FILE* fp = fopen(filename, "r");

	if (!fp)
		return -1;

	while (!feof(fp)) {
		char Ime[512];
		char Prezime[512];
		int m_br;
		fgets(buff, 512, fp);
		sscanf(buff, "%s %s %d", Ime, Prezime, &m_br);
		DodajEl(Tablica, Prezime, Ime, m_br);
	}

	fclose(fp);

	return 0;
}
int IspisiListu(P_Node El, int ind)
{
	P_Node element = El;

	printf("%d)", ind);

	do {
		printf(" %s %s\t", element->Ime, element->Prezime);
		element = element->Next;
	} while (element);

	printf("\n");

	return 0;
}


P_Node IdiNaPrvi(P_Node El, char* Prezime)
{
	P_Node element = El;

	while (strcmp(element->Next->Prezime, Prezime))
		element = element->Next;

	return element;
}

P_Node Nadi(P_Node* Tablica, char* ime, char* prezime)
{
	int Pozicija = RacunajHash(prezime, 11);

	P_Node el = Tablica[Pozicija]->Next;

	while (el)
		if (!strcmp(el->Prezime, prezime) && !strcmp(el->Ime, ime))
			return el;
		else
			el = el->Next;

	return el;
}

P_Node Unesi(P_Node red, char* Ime, char* Zadnji)
{
	P_Node el = red;
	P_Node temp = NULL;

	while (el->Next && strcmp(Prezime, el->Next->Prezime) > 0)
		el = el->Next;

	if (el->Next && !strcmp(Prezime, el->Next->Prezime)) {
		el = IdiNaPrvi(red, Prezime);
		while (el->Next && !strcmp(Prezime, el->Next->Prezime) && strcmp(Ime, el->Next->Ime) > 0)
			el = el->Next;
	}

	temp = el->Next;
	el->Next = DodajNoviEl();
	el = el->Next;
	el->Next = temp;

	return el;
}


int IspisiM_Br(P_Node el)
{
	if (!el)
		return -1;

	printf("%d\n", el->m_br);

	return 0;
}
