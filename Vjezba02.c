#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<string.h>

struct osoba;
typedef struct osoba OSOBA;
typedef struct osoba* P_OSOBA;

struct osoba {
	char ime[1500];
	char prezime[1500];
	int god;
	P_OSOBA Next;
};

int DodajNaPoc(P_OSOBA, char [], char [], int);
int IspisiListu(P_OSOBA);
int DodajNaKraj(P_OSOBA);
P_OSOBA Nadi(P_OSOBA, int);
int Brisi(P_OSOBA);

int main() {
	OSOBA Head;
	Head.Next = NULL;
	if (DodajNaPoc(&Head, "Ante", "Izdrzi", 1999) == -1)
		printf("puka je");

}

int DodajNaPoc(P_OSOBA Head, char Ime[], char Prezime[], int God) {
	
	P_OSOBA os;
	
	os = (P_OSOBA)malloc(sizeof(struct osoba));
	
	strcpy(os->ime, Ime);
	strcpy(os->prezime, Prezime);
	os->god = God;

	os->Next = NULL;
	Head->Next = os;
	
	if (os == NULL) {
		return -1;
	}

	return 0;

	
}