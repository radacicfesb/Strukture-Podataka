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
int NadiPrethodnog(P_OSOBA,P_OSOBA);
int UnosIza(P_OSOBA, char[], char[], int);
int UnosIspred(P_OSOBA, P_OSOBA, char[], char[], int);
int SortirajListu(P_OSOBA, char[], int);
void SpremiDatoteci(P_OSOBA);
int CitajIzDatoteke(P_OSOBA);
int BrojiElemente(P_OSOBA);



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
	
	Brisi(Nadi(&Head, 2, "Izdrzi"), &Head);

	IspisiListu(&Head);

	//UnosIza(Nadi(&Head, 2, "Stagod"), "Duje", "Glavina", 1957);
	UnosIspred(&Head, Nadi(&Head, 2, "Stagod"), "Duje", "Glavina", 1957);
	IspisiListu(&Head);

	printf("%d", BrojiElemente(&Head));

	return 0;

}

int DodajNaPoc(P_OSOBA P, char Ime[], char Prezime[], int God) {

	P_OSOBA os;
	P_OSOBA prosliPrvi;

	os = (P_OSOBA)malloc(sizeof(struct _osoba));

	if (os == NULL) {
		return -1;
	}

	strcpy(os->ime, Ime);
	strcpy(os->prezime, Prezime);
	os->god = God;
	os->Next = NULL;

	prosliPrvi = P->Next;
	P->Next = os;
	os->Next = prosliPrvi;

	return 0;

}

int DodajNaKraj(P_OSOBA P, char Ime[], char Prezime[], int God) {

	P_OSOBA os;

	os = (P_OSOBA)malloc(sizeof(struct _osoba));

	if (os == NULL) {
		return -1;
	}

	strcpy(os->ime, Ime);
	strcpy(os->prezime, Prezime);
	os->god = God;
	os->Next = NULL;

	while (P->Next != NULL)
		P = P->Next;

	P->Next = os;

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
	P_OSOBA PR = NadiPrethodnog(HEAD, P);
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
int UnosIza(P_OSOBA P, char Ime[], char Prezime[], int God) {
	P_OSOBA os;
	P_OSOBA temp;

	os = (P_OSOBA)malloc(sizeof(struct _osoba));


	if (os == NULL) {
		return -1;
	}

	strcpy(os->ime, Ime);
	strcpy(os->prezime, Prezime);
	os->god = God;
	os->Next = NULL;

	temp = P->Next;
	P->Next = os;
	os->Next = temp;

	return 0;
}

int UnosIspred(P_OSOBA HEAD, P_OSOBA P, char Ime[], char Prezime[], int God) {
	
	P_OSOBA os;
	P_OSOBA temp;

	os = (P_OSOBA)malloc(sizeof(struct _osoba));


	if (os == NULL) {
		return -1;
	}

	strcpy(os->ime, Ime);
	strcpy(os->prezime, Prezime);
	os->god = God;
	os->Next = NULL;
	
	temp = NadiPrethodnog(HEAD,P);
	temp->Next = os;
	os->Next = P;

	return 0;
}
 int SortirajListu(P_OSOBA P, char Trazeno[], int C) { //SLAT CE SE GLAVA
	//1-ime, 2-prezime, 3-god
	int n=0;//duzina liste
	int newn = 0;
	int swap = 0;
	int i;
	P_OSOBA temp, prev_j, end;
	P = P->Next;

	end = NULL;
	if (C == 1)
	{
	
	   n = BrojiElemente(P);
	   while (swap != 1) {
		   swap = 0;
		   for (i = 1; i < n; i++) {

			   if (strcmp(P->ime, P->Next->ime) > 0)

		   }
	   }
	}
	else if (C == 2)
	{
		
	}
	else if (C == 3)
	{
		int a;
		sscanf(Trazeno, "%d", &a);
		
	}
	else
		printf("nisi napisa sta trazis u pozivu funkcije");
	return NULL;
	

}

int BrojiElemente(P_OSOBA P) { //SALJES HEAD
	int a = 0;
	while (P->Next != NULL)
	{
		a++;
		P = P->Next;
	}

	return a;

}