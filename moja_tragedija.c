#include<stdio.h>
#include<string.h>

typedef struct {
	char ime[1500];
	char prezime[1500];
	int bod;
}student;
int brojiStudente(char *);
void Studenti(int, char *);
int Rel_br_bod(int, char *);
void IspisStudenata(int, int, char *);

int main() {
	int n;
	student *s;
	FILE *fp = fopen("dat.txt", "r");

	char *fileName = NULL;
	fileName = (char*)malloc(sizeof(char) * 20);

	printf("Upisi ime fajla: \n");
	scanf("%s", fileName);

	n = brojiStudente(fileName);

	s = (student*)malloc(n*sizeof(student));
	
	Studenti(n, fileName);
	Rel_br_bod(n, fileName);
	IspisStudenata(n, Rel_br_bod, fileName);

	retrun 0;
	
}

int brojiStudente(char *fileName) {

	FILE *fp = fopen(fileName, "r");
	int n = 0;
	char *buff = NULL;

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
}

void Studenti(int n, char *fileName) {
	int i;
	student *s;
		for (i = 0; i < n; i++) {
			fscanf(dat,"%s\n", s[i].ime);
			fscanf(dat,"%s\n", s[i].prezime);
			fscanf(dat,"%d\n", &s[i].bod);
	}
	return;
}

int Rel_br_bod(int n, char *fileName) {
	int i, max_bod = 100;
	int Rel_br_bodova[100];

	for (i = 0; i < n; i++) {
		fscanf(dat, "%d", &s[i].bod);
	}
	for (i = 0; i < n; i++) {
		Rel_br_bodova[i] = (s[i].bod / max_bod) * 100;
	}

	return Rel_br_bodova[];
}

void IspisStudenata(int n, int Rel_br_bod, char *fileName) {
	int i;

	for (i = 0; i < n; i++) {
		printf("%s %s %d %d", s[i].ime, s[i].prezime, s[i].bod, Rel_br_bod[i]);
	}

	return;
}