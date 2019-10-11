#include<stdio.h>
#include<string.h>
typedef struct {
	char ime[1500];
	char prezime[1500];
	int bod;
}student;
int brojStudenata(char *);

int main() {
	int n;
	student *s;
	FILE *fp = fopen("dat.txt", "r");

	char *fileName = NULL;
	fileName = (char*)malloc(sizeof(char) * 20);

	printf("Upisi ime fajla: \n");
	scanf("%s", fileName);

	n = brojStudenata(fileName);

	s = (student*)malloc(n*sizeof(student));

	
}

int brojStudenata(char *fileName) {

	FILE *fp = fopen(fileName, "r");
	int n = 0;
	char *buff = NULL;

	buff = (char*)malloc(sizeof(char) * 128);
	memset(buff, '\0', 128);

	while (!feof(fp))
	{
		fgets(buff, 127, fp);
		if(strlen(buff)!=0 &&
	}
}