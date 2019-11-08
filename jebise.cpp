#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Polinom;
typedef struct Polinom* P_Polinom;

struct Polinom{
	int Koeficijent;
	int Potencija;
	P_Polinom Next;
};

int CitajIzDatoteke(char* fileName, P_Polinom);
int IspisPolinoma(P_Polinom);
int SumaPolinoma();
int ProduktPolinoma(P_Polinom, P_Polinom, P_Polinom);

int main() {
	Polinom Head1;
	Polinom Head2;
	Head1.Next = NULL;
	Head2.Next = NULL;
	
	

	CitajIzDatoteke("aaaaa.txt", &Head1);
	CitajIzDatoteke("bbbbb.txt", &Head2);
	
	IspisPolinoma(Head1.Next);
	IspisPolinoma(Head2.Next);
	//zbroji
	//mnozi
	

	return 0;
}

int CitajIzDatoteke(char* fileName, P_Polinom P) {
	P_Polinom Pol;
	Pol = NULL;
	
	char* buff = NULL;
	buff = (char*)malloc(sizeof(char) * 128);
	FILE* fp = fopen(fileName, "r");
	memset(buff, '\0', 128);

	while (!feof(fp)) {

		if (P->Next == NULL) {
			Pol = NULL;
			Pol = (P_Polinom)malloc(sizeof(struct Polinom));
			P->Next = Pol;

			if (Pol == NULL) {
				return -1;
			}
		}


			fgets(buff, 127, fp);
			sscanf(buff, "%d %d", &P->Next->Koeficijent, &P->Next->Potencija, fp);
			P->Next->Next = NULL;
			P = P->Next;
	}

	fclose(fp);

	return 1;

}

int IspisPolinoma(P_Polinom P) {
	
	while(P != NULL) {
		printf("%d %d\n", P->Koeficijent, P->Potencija);
		P = P -> Next; 
	}
	return 0;
}

int ProduktPolinoma(P_Polinom P1, P_Polinom P2, P_Polinom R) {
	P_Polinom Poc = P2;
	
	while (P1 != NULL) {
		while(P )
	}
}