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
int NadiPrethodnog(P_OSOBA, P_OSOBA);
int UnosIza(P_OSOBA, char[], char[], int);
int UnosIspred(P_OSOBA, P_OSOBA, char[], char[], int);
int SortirajListu(P_OSOBA, int);
int SpremiDatoteci(P_OSOBA, char*);
int CitajIzDatoteke(P_OSOBA, char*);
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
	

	UnosIza(Nadi(&Head, 2, "Stagod"), "Duje", "Glavina", 1957);
	UnosIspred(&Head, Nadi(&Head, 2, "Stagod"), "Duje", "Glavina", 1957);
	IspisiListu(&Head);

	printf("%d", BrojiElemente(&Head));

	printf("prije sortiranja:\n");
	IspisiListu(&Head);
	if (SortirajListu(&Head, 2) != 1)
		printf("puklo sortiranje");
	printf("posli sortiranja:\n");
	IspisiListu(&Head);

	if (CitajIzDatoteke(&Head, "in.txt") == -1)
		printf("puka malok");
	IspisiListu(&Head);

	SpremiDatoteci(&Head, "out.txt");




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

	temp = NadiPrethodnog(HEAD, P);
	temp->Next = os;
	os->Next = P;

	return 0;
}
int SortirajListu(P_OSOBA P, int C) { //SLAT CE SE GLAVA
   //1-ime, 2-prezime, 3-god
	P_OSOBA i = P;
	P_OSOBA j = NULL;
	P_OSOBA prev_j = NULL;
	P_OSOBA end = NULL;

	
	if (C == 1)
	{

		while (i->Next != end)
		{
			prev_j = i;
			j = prev_j->Next;

			while (j->Next != end)
			{
				if (strcmp(j->ime, j->Next->ime) > 0)
				{
					prev_j->Next = j->Next;
					j->Next = j->Next->Next;
					prev_j->Next->Next = j;
					j = prev_j->Next;
				}
				prev_j = j;
				j = j->Next;
			}
			end = j;
		}

		return 1;
		
	}
	else if (C == 2)
	{
		while (i->Next != end)
		{
			prev_j = i;
			j = prev_j->Next;

			while (j->Next != end)
			{
				if (strcmp(j->prezime, j->Next->prezime) > 0)
				{
					prev_j->Next = j->Next;
					j->Next = j->Next->Next;
					prev_j->Next->Next = j;
					j = prev_j->Next;
				}
				prev_j = j;
				j = j->Next;
			}
			end = j;
		}

		return 1;
	}
	else if (C == 3)
	{
		
		while (i->Next != end)
		{
			prev_j = i;
			j = prev_j->Next;

			while (j->Next != end)
			{
				if (j->god > j->Next->god)
				{
					prev_j->Next = j->Next;
					j->Next = j->Next->Next;
					prev_j->Next->Next = j;
					j = prev_j->Next;
				}
				prev_j = j;
				j = j->Next;
			}
			end = j;
		}

		return 1;

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

int CitajIzDatoteke(P_OSOBA P, char* Filename) {

	P_OSOBA os;
	os = NULL;
	char* buff = NULL;
	FILE* fp = fopen(Filename, "r");

	buff = (char*)malloc(sizeof(char) * 128);
	memset(buff, '\0', 128);

	while (!feof(fp)) {

		if (P->Next == NULL) {
			os = NULL;
			os = (P_OSOBA)malloc(sizeof(struct _osoba));
			P->Next = os;

			if (os == NULL) {
				return -1;
			}
		}


			fgets(buff, 127, fp);
			sscanf(buff, "%s %s %d", P->Next->ime, P->Next->prezime, &P->Next->god, fp);
			P->Next->Next = NULL;
			P = P->Next;
	}

	fclose(fp);

	return 1;

}

int SpremiDatoteci(P_OSOBA P, char* Filename) {

	FILE* fp = fopen(Filename, "w");
	P = P -> Next; //necu head ispisan ka
	while (P != NULL)
	{
		fprintf(fp, "%s %s %d", P->ime, P->prezime, P->god);
		fprintf(fp, "\n");
		P = P->Next;

	}
	fclose(fp);
	return 1;
}
