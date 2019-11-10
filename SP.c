#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Polinom;
typedef struct Polinom* P_Polinom;

struct Polinom {
	int Koeficijent;
	int Potencija;
	P_Polinom Next;
};

int CitajIzDatoteke(char* fileName, P_Polinom);
int IspisPrvogPolinoma(P_Polinom);
int IspisDrugogPolinoma(P_Polinom);
int IspisSumePolinoma(P_Polinom);
int IspisUmnoskaPolinoma(P_Polinom);
int SumaPolinoma(P_Polinom, P_Polinom, P_Polinom);
int ProduktPolinoma(P_Polinom, P_Polinom, P_Polinom);
int UnosPolinoma(P_Polinom, int, int);
int SumaSumePolinoma(P_Polinom, P_Polinom, P_Polinom);

int main() {
	struct Polinom P1,P2,S,U;
	P1.Next = NULL;
	P2.Next = NULL;
	S.Next = NULL;
	U.Next = NULL;
	int koeficijent, potencija;
	
	UnosPolinoma(&P1, 3, 3);
	UnosPolinoma(&P1, 4, 3);
	UnosPolinoma(&P1, 5, 3);
	UnosPolinoma(&P1, 1, 3);
	UnosPolinoma(&P2, 2, 3);
	UnosPolinoma(&P2, 3, 3);
	UnosPolinoma(&P2, 8, 3);
	UnosPolinoma(&P2, 7, 3);
	
	//CitajIzDatoteke("aaaaa.txt", &P1);
	//CitajIzDatoteke("bbbbb.txt", &P2);

	
	ProduktPolinoma(P1.Next, P2.Next, &U);
	SumaPolinoma(P1.Next, P2.Next, &S);
	IspisPrvogPolinoma(P1.Next);
	IspisDrugogPolinoma(P2.Next);
	IspisSumePolinoma(S.Next);
	IspisUmnoskaPolinoma(U.Next);
	

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

int IspisPrvogPolinoma(P_Polinom P) {
	printf("Prvi polinom:\n");
	while (P != NULL) {
		printf("%dx^%d ", P->Koeficijent, P->Potencija);
		P = P->Next;
	}
	printf("\n");
	return 0;
}

int IspisDrugogPolinoma(P_Polinom P) {
	printf("Drugi polinom:\n");
	while (P != NULL) {
		printf("%dx^%d ", P->Koeficijent, P->Potencija);
		P = P->Next;
	}
	printf("\n");
	return 0;
}
int IspisUmnoskaPolinoma(P_Polinom P) {
	printf("Umnozak polinoma:\n");
	while (P != NULL) {
		printf("%dx^%d ", P->Koeficijent, P->Potencija);
		P = P->Next;
	}
	printf("\n");
	return 0;
}
int IspisSumePolinoma(P_Polinom P) {
	printf("Suma polinoma:\n");
	while (P != NULL) {
		printf("%dx^%d ", P->Koeficijent, P->Potencija);
		P = P->Next;
	}
	printf("\n");
	return 0;
}


int ProduktPolinoma(P_Polinom P1, P_Polinom P2, P_Polinom U) {
	P_Polinom temp = P2;

	while (P1 != NULL) {
		while (P2 != NULL) {
			UnosPolinoma(U, P1->Koeficijent * P2->Koeficijent, P1->Potencija + P2->Potencija);
			P2 = P2->Next;
		}
		P2 = temp;

		P1 = P1->Next;
	}
	return 0;
}

int UnosPolinoma(P_Polinom P1, int koeficijent, int potencija) {
	P_Polinom q;
	
	while (P1->Next != NULL && P1->Next->Potencija > potencija)
		P1 = P1->Next;
	q = (P_Polinom)malloc(sizeof(struct Polinom));
	q->Koeficijent = koeficijent;
	q->Potencija = potencija;
	q->Next = P1->Next;
	P1->Next = q;


	return 0;
}

int SumaPolinoma(P_Polinom P1, P_Polinom P2, P_Polinom S) {
	P_Polinom temp;
	while (P1 != NULL && P2 != NULL) {
		if (P1->Potencija == P2->Potencija) {
			UnosPolinoma(S, P1->Koeficijent + P2->Koeficijent, P1->Potencija);
			P1 = P1->Next;
			P2 = P2->Next;
			
		}
		else if (P1->Potencija > P2->Potencija) {
			UnosPolinoma(S, P1->Koeficijent, P1->Potencija); 
			P1 = P1->Next;
		}
		else {
			UnosPolinoma(S, P2->Koeficijent, P2->Potencija);
			P2 = P2->Next;
		}
	}
	//SumaSumePolinoma(S, S->Koeficijent, S->Potencija);
	if (P1 != NULL) temp = P1;
	else temp = P2;
	while (temp != NULL) {
		UnosPolinoma(S, temp->Koeficijent, temp->Potencija);
		temp = temp->Next;
	}
                                            
	return 0;
}

//int SumaSumePolinoma(P_Polinom S, P_Polinom Koeficijent, P_Polinom Potencija) {
	//while (S != NULL) {
		//if (S->Potencija == S->Next->Potencija) {
			//UnosPolinoma(S, S->Koeficijent + S->Next->Koeficijent, S->Potencija);
			//S = S->Next;

//		}
		//else if (S->Potencija > S->Next->Potencija) {
		//	UnosPolinoma(S, S->Koeficijent, S->Potencija);
			//S = S->Next;
		//}
		//else {
			//UnosPolinoma(S, S->Next->Koeficijent, S->Next->Potencija);
			//S->Next = S->Next->Next;
		//}
	//}
		//return 0;	
//}