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






int CitajIzDatoteke(P_Polinom);
int Novi(P_Polinom*);
int IspisiListu(P_Polinom);
int ZbrojPolinoma(P_Polinom, P_Polinom, P_Polinom);
int UmnozakPolinoma(P_Polinom, P_Polinom, P_Polinom);

int main() {
	struct Polinom Head1;
	struct Polinom Head2;
	 struct Polinom HeadS;
	 struct Polinom HeadM;

	Head1.Next = NULL;
	Head2.Next = NULL;
	HeadS.Next = NULL;
	HeadM.Next = NULL;

	printf("Prvi polinom\n");
	CitajIzDatoteke(&Head1);
	IspisiListu(Head1.Next);
	printf("\n");

	
	printf("Drugi polinom\n");
	CitajIzDatoteke(&Head2);
	IspisiListu(Head2.Next);
	printf("\n");

	printf("Suma polinoma");
	printf("\n");
	ZbrojPolinoma(Head1.Next, Head2.Next, &HeadS);
	IspisiListu(HeadS.Next);


	printf("Umnozak polinoma");
	printf("\n");
	UmnozakPolinoma(Head1.Next, Head2.Next, &HeadM);
	IspisiListu(HeadM.Next);

	return 0;
}

int CitajIzDatoteke(P_Polinom P)
{
	P_Polinom q = NULL;
	P_Polinom temp = NULL;
	char *fileName = NULL;
	FILE *fp = NULL;

	fileName = (char*)malloc(sizeof(char) * 128);
	memset(fileName, '\0', 127);

	//printf("Unesite ime dadoteke:\n ");
	//scanf(" %s", fileName);


	while (!feof(fp))
	{
		Novi(&q);
		fscanf(fp, " %d %d", &q->Koeficijent, &q->Potencija);

		temp = P;
		while (temp->Next != NULL && temp->Next->Potencija > q->Potencija)
			temp = temp->Next;

		if (temp->Next != NULL && temp->Next->Potencija == q->Potencija)
		{
			temp->Next->Koeficijent += q->Koeficijent;
			free(q);
			if (temp->Next->Koeficijent == 0)
			{
				q = temp->Next;
				temp->Next = q->Next;

				free(q);
			}
		}
		else
		{
			q->Next = temp->Next;
			temp->Next = q;
		}

	}
	fclose(fp);

	return 0;
}

int IspisiListu(P_Polinom P)
{
	while (P != NULL)
	{
		printf(" %dx^%d", P->Koeficijent, P->Potencija);
		P = P->Next;
	}
	return 0;
}

int ZbrojPolinoma(P_Polinom P1, P_Polinom P2, P_Polinom S)
{
	P_Polinom q = NULL;
	P_Polinom temp = NULL;

	while (P1 != NULL && P2 != NULL)
	{
		Novi(&q);
		if (P1->Potencija == P2->Potencija)
		{
			q->Potencija = P1->Potencija;
			q->Koeficijent = P1->Koeficijent + P2->Koeficijent;
			P1 = P1->Next;
			P2 = P2->Next;
		}
		else if (P1->Potencija < P2->Potencija)
		{
			q->Potencija = P2->Potencija;
			q->Koeficijent = P2->Koeficijent;
			P2 = P2->Next;
		}
		else
		{
			q->Potencija = P1->Potencija;
			q->Koeficijent = P1->Koeficijent;
			P1 = P1->Next;
		}

		q->Next = S->Next;
		S->Next = q;

		S = q;
	}
	if (P1 == NULL)
		temp = P2;
	else
		temp = P1;

	while (temp != NULL)
	{
		q->Potencija = temp->Potencija;
		q->Koeficijent = temp->Koeficijent;

		q->Next = S->Next;
		S->Next = q;

		S = q;

		temp = temp->Next;
	}

	return 0;
}

int UmnozakPolinoma(P_Polinom P1, P_Polinom P2, P_Polinom M)
{
	P_Polinom q = NULL; 
	P_Polinom temp = NULL;
	P_Polinom i = NULL;
	P_Polinom j = NULL;

	i = P1;

	while (i != NULL)
	{
		j = P2;
		while (j != NULL)
		{
			Novi(&q);
			q->Potencija = i->Potencija + j->Potencija;
			q->Koeficijent = i->Koeficijent * j->Koeficijent;

			temp = M;

			while (temp->Next != NULL && temp->Next->Potencija > q->Potencija)
				temp = temp->Next;

			if (temp->Next != NULL && temp->Next->Potencija == q->Potencija)
			{
				temp->Next->Koeficijent += q->Koeficijent;
				free(q);

				if (temp->Next->Koeficijent == 0)
				{
					q = temp->Next;
					temp->Next = q->Next;

					free(q);
				}
			}
			else
			{
				q->Next = temp->Next;
				temp->Next = q;
			}

			j = j->Next;
		}
		i = i->Next;
	}

	return 0;
}

int Novi(P_Polinom* P)
{
	P_Polinom q = NULL;

	*P = (P_Polinom)malloc(sizeof(struct Polinom));
	if (*P == NULL) return -1;

	q = *P;
	q->Next = NULL;

	return 0;
}