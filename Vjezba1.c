#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<string.h>
#include<math.h>

struct student;
typedef struct student STUDENT;
typedef struct student* P_STUDENT; // pokazivac na strukturu tria mi za citat

 struct student {
	char ime[1500];
	char prezime[1500];
	int bod;
};

int brojStudenata(char*);
int citajZapise(char*, P_STUDENT);
int printSvega(P_STUDENT, int, int);


int main() {
	int n;
	int maxBod;
	P_STUDENT* list;
	
	char* fileName = NULL;
	fileName = (char*)malloc(sizeof(char) * 20);

	printf_s("Upisi ime fajla: \n");
	scanf("%s", fileName);

	n = brojStudenata(fileName);
	printf_s("ima ih %d\n", n); 



	list = (P_STUDENT*)malloc(n * sizeof(P_STUDENT));
	maxBod = citajZapise(fileName, list);
	printSvega(list, n, maxBod);


	return 0;
	

}

int brojStudenata(char* fileName) {

	FILE* fp = fopen(fileName, "r");
	int n = 0;
	char* buff = NULL;

	buff = (char*)malloc(sizeof(char) * 128);
	memset(buff, '\0', 128);

	while (!feof(fp))
	{
		fgets(buff, 127, fp);
		if (strlen(buff) != 0 && isalnum(buff[0]))
			n++;
	}
	fclose(fp);
	return n;
}


int citajZapise(char* fileName, P_STUDENT S) {
	char* buff = NULL;
	int maxBod=0;
	FILE* fp = fopen(fileName, "r");

	buff = (char*)malloc(sizeof(char) * 128);
	memset(buff, '\0', 128);

	while (!feof(fp))
	{
		fgets(buff, 127, fp);
		sscanf(buff, " %s %s %d", S->ime, S->prezime, &S->bod,fp);
		if (S->bod > maxBod)
			maxBod = S->bod;
		S++;
	}
	
	fclose(fp);

	return maxBod;

}

int printSvega(P_STUDENT list, int brojZapisa, int maxBod) {
	int i = 0;
	for (i; i < brojZapisa; i++) {
		printf("%s %s %d %f\n", list->ime, list->prezime, list->bod, ((float)list ->bod / maxBod) * 100);
		list++;
	}
	return 0;
}

