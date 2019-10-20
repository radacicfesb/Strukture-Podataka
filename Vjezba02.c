#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<string.h>

struct _osoba;
typedef struct _osoba OSOBA;
typedef struct _osoba* P_OSOBA;

struct _osoba {
	char ime[256];
	char prezime[256];
	int god;
	P_OSOBA Next;
};

int DodajNaPoc(P_OSOBA, char[], char[], int);
int IspisiListu(P_OSOBA);
int DodajNaKraj(P_OSOBA, char[], char[], int);
P_OSOBA Nadi(P_OSOBA, int, char[]);
int Brisi(P_OSOBA);
int NadiPrethodnog(P_OSOBA);

int main() {
	OSOBA Head;
	Head.Next = NULL;
	if (DodajNaPoc(&Head, "Ante", "Izdrzi", 1999) == -1)
		printf("puka je malloc");
	if (DodajNaPoc(&Head, "Ivan", "Stagod", 1986) == -1)
		printf("puka je malloc");
	if (DodajNaKraj(&Head, "Nrfan", "Stfaasat", 5332) == -1)
		printf("puka je malloc");
	if (DodajNaPoc(&Head, "Neznan", "Stapisat", 2003) == -1)
		printf("puka je malloc");
	if (DodajNaKraj(&Head, "dad", "wrwr", 2043) == -1)
		printf("puka je malloc");
	IspisiListu(&Head);
;
	Brisi(Nadi(&Head, 2, "Izdrzi"), &Head);

	IspisiListu(&Head);
	return 0;

}

int DodajNaPoc(P_OSOBA P, char Ime[], char Prezime[], int God) {

	P_OSOBA os;
	P_OSOBA prosliPrvi;

	os = (P_OSOBA)malloc(sizeof(struct _osoba));

	strcpy(os->ime, Ime);
	strcpy(os->prezime, Prezime);
	os->god = God;
	os->Next = NULL;

	prosliPrvi = P->Next;
	P->Next = os;
	os->Next = prosliPrvi;

	if (os == NULL) {
		return -1;
	}

	return 0;

}

int DodajNaKraj(P_OSOBA P, char Ime[], char Prezime[], int God) {

	P_OSOBA os;

	os = (P_OSOBA)malloc(sizeof(struct _osoba));

	strcpy(os->ime, Ime);
	strcpy(os->prezime, Prezime);
	os->god = God;
	os->Next = NULL;

	while (P->Next != NULL)
		P = P->Next;

	P->Next = os;

	if (os == NULL) {
		return -1;
	}

	return 0;



}

int IspisiListu(P_OSOBA P) {
	P = P->Next; // ne zelis ispisat head pa ides odma na iduci
	if (P == NULL)
		printf("lista nema elemenata");
	else
	{
		while (P != NULL)
		{
			printf("%s %s %d\n", P->ime, P->prezime, P->god);
			P = P->Next;
		}
		printf("\n");
	}
}

P_OSOBA Nadi(P_OSOBA P, int C, char Trazeno[]) {
	//1-ime, 2-prezime, 3-god
	P = P->Next;
	if (C == 1)
	{
		while (P->Next != NULL && strcmp(Trazeno, P->ime))
			P = P->Next;
		return P;
	}
	else if (C == 2)
	{
		while (P->Next != NULL && strcmp(Trazeno, P->prezime))
			P = P->Next;
		return P;
	}
	else if (C == 3)
	{
		int a;
		sscanf(Trazeno, "%d", &a);

		while (P->Next != NULL && P->god != a)
			P = P->Next;
		return P;
	}
	else
		printf("nisi napisa sta trazis u pozivu funkcije");
		return NULL;

}

int Brisi(P_OSOBA P, P_OSOBA HEAD) { //p - brises tog
	P_OSOBA PR = NadiPrethodnog(HEAD,P);
	PR->Next = P->Next;  //Iduci prethodnog od brisanog je onaj nakon onog kojeg brises
	free(P);
	return 0;

}

int NadiPrethodnog(P_OSOBA H, P_OSOBA S) {
		
	while (H->Next != S) {
		H = H->Next;
	}
	if (H->Next == S)
		return H;
	else
		return NULL;
}
