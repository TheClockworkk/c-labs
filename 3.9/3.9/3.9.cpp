#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

#define TRASSER_FILE_ERR -101
#define INPUT_FILE_ERR -102
#define OUTPUT_FILE_ERR -103
#define NO_ARGS_ERR -104
#define SIMILAR_MAILS_ID_NUM -105
#define END_OF_PROGRAM 0

int err_code = 0;

typedef struct ConsumerAdress
{
	char* city;
	char* street;
	char* home;
	unsigned int room;
	unsigned int index;
} ConsumerAdress;

typedef struct PostAdress
{
	char* city;
	unsigned int index;
} PostAdress;

typedef struct Mail
{
	ConsumerAdress adresses;
	unsigned int weight;
	unsigned int identificator;
} Mail;

typedef struct Post
{
	PostAdress addres;
	Mail mails;
} Post;

typedef struct MailsArray
{
	Mail* Mails;
	size_t size;
} MailsArray;

/*typedef struct PostsArray
{
	Post* Posts;
	size_t size;
} PostsArray;*/


int addMail(struct MailsArray* arr, int count)
{
	char bufer[BUFSIZ];

	printf("Enter index: ");
	scanf("%d", &(arr->Mails[arr->size - 1]).adresses.index);

	printf("Enter city: ");
	scanf("%s", bufer);
	arr->Mails[arr->size - 1].adresses.city = (char*)malloc(sizeof(char) * (strlen(bufer) + 1));//потому что array.size указывает на следующий после выделенной памяти элеменнт
	strcpy(arr->Mails[arr->size - 1].adresses.city, bufer);

	printf("Enter street: ");
	scanf("%s", bufer);
	arr->Mails[arr->size - 1].adresses.street = (char*)malloc(sizeof(char) * (strlen(bufer) + 1));
	strcpy(arr->Mails[arr->size - 1].adresses.street, bufer);

	printf("Enter home: ");
	scanf("%s", bufer);
	arr->Mails[arr->size - 1].adresses.home = (char*)malloc(sizeof(char) * (strlen(bufer) + 1));
	strcpy(arr->Mails[arr->size - 1].adresses.home, bufer);

	printf("Enter room: ");
	scanf("%d", &(arr->Mails[arr->size - 1]).adresses.room);

	printf("Enter weight in gramms: ");
	scanf("%d", &(arr->Mails[arr->size - 1]).weight);

	printf("Enter clients identificator: ");
	scanf("%d", &(arr->Mails[arr->size - 1]).identificator);
	
	//arr->size++;
	return 0;
}

int deleteMail(struct MailsArray* arr, int deleteNum)
{
	switch (arr->size)
	{
	case 0:
		printf("Your structure is empty, cant delete nothing");
		break;

	case 1:
		arr->size = arr->size - 1;
		break;

	default:
		for (deleteNum; deleteNum < (arr->size - 1); deleteNum++)//я ставлю элемент выше делит нума на 1 на место делит нума и тд и так до -1 эл-та от исходного кол-ва
		{
			arr->Mails[deleteNum].adresses.index = arr->Mails[deleteNum + 1].adresses.index;
			arr->Mails[deleteNum].adresses.city = arr->Mails[deleteNum + 1].adresses.city;
			arr->Mails[deleteNum].adresses.street = arr->Mails[deleteNum + 1].adresses.street;
			arr->Mails[deleteNum].adresses.home = arr->Mails[deleteNum + 1].adresses.home;
			arr->Mails[deleteNum].adresses.room = arr->Mails[deleteNum + 1].adresses.room;
			arr->Mails[deleteNum].weight = arr->Mails[deleteNum + 1].weight;
			arr->Mails[deleteNum].identificator = arr->Mails[deleteNum + 1].identificator;
		}
		arr->size = arr->size - 1;
		// arr->Passengers = (Passenger*)realloc(arr->Passengers, ++(arr->size) * sizeof(Passenger));
		//for (int i = 0; i < arr->size; i++)
		//{
			//printf("%d %s %s %s %s %s %d %d %d %d\n", arr->Passengers[i].number, arr->Passengers[i].flight, arr->Passengers[i].departureAirport, arr->Passengers[i].departureCity, arr->Passengers[i].arrivalAirport, arr->Passengers[i].arrivalCity, arr->Passengers[i].times.departureHour, arr->Passengers[i].times.departureMin, arr->Passengers[i].times.arrivalHour, arr->Passengers[i].times.arrivalMin);
		//}
		break;
	}
	return 0;
}


int identificatorSearch(struct MailsArray* arr, int id)
{
	int k = 0;
	int m = 0;

	for (int i = 0; i < arr->size; i++)
	{
		if ((arr->Mails[i].identificator) == id)
		{
			k++;
		}
	}

	if (k == 0)
	{
		printf("No mail number matches\n");
		return 0;
	}

	if (k > 1)
	{
		err_code = SIMILAR_MAILS_ID_NUM;
		perror("More than one mail with similar id, bruh\n");
		exit(err_code);
	}

	if (k == 1)
	{
		for (int i = 0; i < arr->size; i++)
		{
			if ((arr->Mails[i].identificator) == id)
			{
				m = i;
				break;
			}
		}
	}

	return m;
}

int mailsSort(struct MailsArray* arr)
{
	int isSorted = 0;//пузыриком не больно
	Mail temporary;
	while (!isSorted)
	{
		isSorted = 1;

		for (int i = 1; i < arr->size; i++)
		{
			if (arr->Mails[i].adresses.index < arr->Mails[i - 1].adresses.index)
			{
				temporary = arr->Mails[i];
				arr->Mails[i] = arr->Mails[i - 1];
				arr->Mails[i - 1] = temporary;
				isSorted = 0;
			}
		}
	}

	isSorted = 0;
	while (!isSorted)
	{
		isSorted = 1;
		for (int i = 1; i < arr->size; i++)
		{
			if (arr->Mails[i].adresses.index == arr->Mails[i - 1].adresses.index && arr->Mails[i].identificator < arr->Mails[i - 1].adresses.index)
			{
				temporary = arr->Mails[i];
				arr->Mails[i] = arr->Mails[i - 1];
				arr->Mails[i - 1] = temporary;
				isSorted = 0;
			}
		}
	}
	return 0;
}

int main()
{
	MailsArray array = { NULL, 0 };
	
	printf("\nIf u want to add mail press 1;\nIf u wand to delete mail press 2;\nIf u want to see a mails list press 3.\nIf u want to stop press 4.\n\n");


	int stop = 0;
	while (stop < 4)
	{
		printf("\nProcedure number: ");
		int procedureNum = 0;
		scanf("%d", &procedureNum);

		switch (procedureNum)
		{
		case 1:
			printf("Enter mails data please. Format: index, city, street, home, room, weight, identificator.\n");
			array.Mails = (Mail*)realloc(array.Mails, ++(array.size) * sizeof(Mail));
			addMail(&array, array.size);
			break;

		case 2:
			printf("Enter mails identificator that u want to delete: ");
			int deleteNum;
			scanf("%d", &deleteNum);
			printf("\n");
			int deleteNumPose;
			deleteNumPose = identificatorSearch(&array, deleteNum);
			deleteMail(&array, deleteNumPose);
			//array.Passengers = (Passenger*)realloc(array.Passengers, --(array.size) * sizeof(Passenger));
			break;

		case 3:

			if (array.size == 0)
				printf("Massive of mails is empty.");

			else
			{
				mailsSort(&array);
				for (int i = 0; i < array.size; i++)
				{
					printf("%d %s %s %s %d %d %d\n", array.Mails[i].adresses.index, array.Mails[i].adresses.city, array.Mails[i].adresses.street, array.Mails[i].adresses.home, array.Mails[i].adresses.room, array.Mails[i].weight, array.Mails[i].identificator);
				}
			}
			break;
		case 4:
			stop = procedureNum;
			break;

		default:
			printf("Uncorrect procedure number input(\n\n");
			break;
		}
	}

	for (int i = 0; i < array.size; i++)
	{
		//free(array.Mails[i].adresses.index);
		free(array.Mails[i].adresses.city);
		free(array.Mails[i].adresses.street);
		free(array.Mails[i].adresses.home);
		//free(array.Mails[i].adresses.room);
		//free(array.Mails[i].weight);
		//free(array.Mails[i].identificator);
	}
	free(array.Mails);
	return 0;
}

