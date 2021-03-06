﻿#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

#define TRASSER_FILE_ERR -101
#define INPUT_FILE_ERR -102
#define END_OF_PROGRAM 0

int err_code = 0;

typedef struct Student
{
	unsigned int group;
	char* name;
	char* surname;
	char* lastname;
	unsigned int firstR;
	unsigned int secondR;
	unsigned int thirdR;
	unsigned int fourthR;
	unsigned int fifthR;
} Student;

typedef struct StudentsArray
{
	Student* Students;
	size_t		 size;
} StudentsArray;



int studentsCount(const char* filename)
{
	int lineCount = 0;
	FILE* a;
	if (!(a = fopen(filename, "r")))
	{
		err_code = INPUT_FILE_ERR;
		perror("Problem with input file");
		exit(err_code);
	}

	while (!feof(a))
	{
		if (fgetc(a) == '\n')
			lineCount++;
	}
	lineCount++;
	fclose (a);
	return lineCount;
}

int middleAri(struct StudentsArray* arr, int stCount, double** res)
{
	double k = 0;
	int f = 0;
	double* middleA = (double*)malloc(sizeof(double) * stCount);

	for (int i = 0; i < arr->size; i++)
	{
		k = ((double)(arr->Students[i].firstR) + (arr->Students[i].secondR) + (arr->Students[i].thirdR) + (arr->Students[i].fourthR) + (arr->Students[i].fifthR))/5;
		middleA[f] = k;
		f++;
	}
	*res = middleA;
	return k;
}




int main()
{
	const char* inputFileName = "inputFile.txt";
	const char* outputFileName = "trasserFile.txt";

	FILE* FO;
	FILE* SO;

	if (!(FO = fopen(inputFileName, "r")))
	{
		err_code = INPUT_FILE_ERR;
		perror("Problem with input file");
		exit(err_code);
	}


	StudentsArray array = { NULL, 0 };
	char buf[BUFSIZ];

	while (!feof(FO)) //заполняем структурку йоу
	{
		
		array.Students = (Student*)realloc(array.Students, ++array.size * sizeof(Student));


		fscanf(FO, "%s", buf);
		array.Students[array.size - 1].name = (char*)malloc(sizeof(char) * strlen(buf) + 1);
		strcpy(array.Students[array.size - 1].name, buf);

		fscanf(FO, "%s", buf);
		array.Students[array.size - 1].surname = (char*)malloc(sizeof(char) * strlen(buf) + 1);
		strcpy(array.Students[array.size - 1].surname, buf);

		fscanf(FO, "%s", buf);
		array.Students[array.size - 1].lastname = (char*)malloc(sizeof(char) * strlen(buf) + 1);
		strcpy(array.Students[array.size - 1].lastname, buf);

		fscanf(FO, "%d", &array.Students[array.size - 1].group);
		fscanf(FO, "%d", &array.Students[array.size - 1].firstR);
		fscanf(FO, "%d", &array.Students[array.size - 1].secondR);
		fscanf(FO, "%d", &array.Students[array.size - 1].thirdR);
		fscanf(FO, "%d", &array.Students[array.size - 1].fourthR);
		fscanf(FO, "%d", &array.Students[array.size - 1].fifthR);

		fgetc(FO);
	}
	fclose(FO);

	printf("Our dynamic massive of structures:\n");
	for (int i = 0; i < array.size; i++)
		printf("%s %s %s %d %d %d %d %d %d\n", array.Students[i].name, array.Students[i].surname, array.Students[i].lastname, array.Students[i].group, array.Students[i].firstR, array.Students[i].secondR, array.Students[i].thirdR, array.Students[i].fourthR, array.Students[i].fifthR);


	int stCount = studentsCount("inputFile.txt");

	double* resMiddle;
	//int* studentsArr = (int*)malloc(sizeof(int));
	
	int x = middleAri(&array, stCount, &resMiddle);//получаем массив средних оценок


	printf("\nmiddle personal points: ");
	double allExam = 0;
	for (int i = 0; i < stCount; i++)//получаем среднюю оценку средних оценок лол
	{
		printf("%lf ", resMiddle[i]);
		allExam += resMiddle[i];
	}
	allExam = allExam / (double)stCount;//вот тута оно получается
	printf("\n\naverage for all exams: %lf\n\n", allExam);

	int* goodBoysArr = (int*)malloc(sizeof(int));
	int goodBoysCount = 0;
	int k = 0;
	printf("good boys nums (massive): ");
	for (int i = 0; i < stCount; i++)//пихаем в массив номера good boy'ев со средней оценкой выше средней средних
	{
		if (resMiddle[i] > allExam)
		{
			goodBoysCount++;
			goodBoysArr = (int*)realloc(goodBoysArr,sizeof(int) * goodBoysCount);
			goodBoysArr[k] = i;
			k++;
			printf("%d ", goodBoysArr[k]);
		}
	}


	if (!(SO = fopen(outputFileName, "r+"))) //кидаем всё в выходной файлик, а далее выводим хороших ребяток
	{
		err_code = TRASSER_FILE_ERR;
		perror("Problem with trasser file");
		exit(err_code);
	}


	for (int i = 0; i < stCount; i++)
		fprintf(SO, "%s %s %s %lf\n", array.Students[i].name, array.Students[i].surname, array.Students[i].lastname, resMiddle[i]);

	printf("\n\ngood boys is:\n");
	for (int i = 0; i < goodBoysCount; i++)
		printf("%s %s %s\n", array.Students[goodBoysArr[i]].name, array.Students[goodBoysArr[i]].surname, array.Students[goodBoysArr[i]].lastname);

	for (int i = 0; i < stCount; i++)
	{
		free(array.Students[i].name);
		free(array.Students[i].surname);
		free(array.Students[i].lastname);
	}
	free(array.Students);
	free(resMiddle);
	free(goodBoysArr);

	fclose(SO);
}