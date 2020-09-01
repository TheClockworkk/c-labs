#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

#define END_OF_PROGRAM 0

int err_code = 0;

typedef struct String
{
	char* symbols;
	unsigned int length;
} String;

/*typedef struct StringsArray
{
	String* strings;
	size_t		 size;
} StringsArray;*/

String* createString(char* string)
{
	String* ptr_str = (String*)malloc(sizeof(String));
	int length; 
	length = strlen(string) + 1;
	char* str = (char*)malloc(sizeof(char) * length);

	strcpy(str, string);
	ptr_str->symbols = str;
	ptr_str->length = length;
	return ptr_str;
}

int deleteString(String* ptr_str)
{
	free(ptr_str->symbols);
	free(ptr_str);
	return 0;
}

int compareString(char* string1, char* string2)
{
	int length;

	String* ptr_str1 = (String*)malloc(sizeof(String));
	length = strlen(string1) + 1;
	char* str1 = (char*)malloc(sizeof(char) * length);

	strcpy(str1, string1);
	ptr_str1->symbols = str1;
	ptr_str1->length = length;
	
	String* ptr_str2 = (String*)malloc(sizeof(String));
	length = strlen(string2) + 1;
	char* str2 = (char*)malloc(sizeof(char) * length);

	strcpy(str2, string2);
	ptr_str2->symbols = str2;
	ptr_str2->length = length;

	int compare;
	compare = strcmp(ptr_str1->symbols, ptr_str2->symbols);

	if (compare == 0)
		printf("Identical strings");
	if (compare > 0)
		printf("1st string bigger");
	if (compare < 0)
		printf("2nd string bigger");
	return 0;
}

String* duplicateString(char* string)
{
	int length;

	String* ptr_str = (String*)malloc(sizeof(String));
	length = strlen(string) + 1;
	char* str = (char*)malloc(sizeof(char) * length);

	strcpy(str, string);
	ptr_str->symbols = str;
	ptr_str->length = length;

	String* ptr_str_copy = (String*)malloc(sizeof(String));

	ptr_str_copy->symbols = ptr_str->symbols;
	ptr_str_copy->length = ptr_str->length;
	
	printf("Copy: %s", ptr_str_copy->symbols);
	return ptr_str_copy;
}

String* concantenateString(char* string1, char* string2)
{
	int length;

	String* ptr_str1 = (String*)malloc(sizeof(String));
	length = strlen(string1) + 1;
	char* str1 = (char*)malloc(sizeof(char) * length);

	strcpy(str1, string1);
	ptr_str1->symbols = str1;
	ptr_str1->length = length;

	String* ptr_str2 = (String*)malloc(sizeof(String));
	length = strlen(string2) + 1;
	char* str2 = (char*)malloc(sizeof(char) * length);

	strcpy(str2, string2);
	ptr_str2->symbols = str2;
	ptr_str2->length = length;

	String* ptr_str_concat = (String*)malloc(sizeof(String));
	int lengthConcat;
	lengthConcat = ptr_str1->length + ptr_str2->length - 1;
	char* strConcat = (char*)malloc(sizeof(char) * lengthConcat);
	strcpy(strConcat, ptr_str1->symbols);
	strcat(strConcat, ptr_str2->symbols);

	ptr_str_concat->symbols = strConcat;
	ptr_str_concat->length = lengthConcat;

	printf("%s", ptr_str_concat->symbols);
	return ptr_str_concat; 
}


int main()
{
	//StringsArray array = { NULL, 0 };

	printf("\nIf u want to add string press 1;\nIf u wand to delete string press 2;\nIf u want to compare strings press 3.\nIf u want to duplicate string press 4.\nIf u want to concantenate strings press 5.\nIf u want to stop press 6\n\n");

	int stop = 0;
	String* ptr_str = NULL;
	int procedureNum = 0;
	char str1[] = "asdasdadda";
	char str2[] = "asdasdadd";
	while (stop < 6)
	{
		printf("\nProcedure number: ");
		scanf("%d", &procedureNum);

		switch (procedureNum)
		{
		case 1:
			ptr_str = createString(str1);
			printf("%s %d", ptr_str->symbols, ptr_str->length);
			break;

		case 2:
			deleteString(ptr_str);
			break;

		case 3:
			compareString(str1, str2);
			break;

		case 4:
			duplicateString(str1);
			break;

		case 5:
			
			concantenateString(str1, str2);
			break;

		case 6:
			stop = procedureNum;
			break;

		default:
			printf("Uncorrect procedure number input(\n\n");
			break;
		}
	}
	return 0;
}