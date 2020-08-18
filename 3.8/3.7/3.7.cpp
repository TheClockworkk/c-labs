#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable: 4996)

#define TRASSER_FILE_ERR -101
#define INPUT_FILE_ERR -102
#define OUTPUT_FILE_ERR -103
#define NO_ARGS_ERR -104
#define SIMILAR_PASSENGERS_NUM -105
#define END_OF_PROGRAM 0

int err_code = 0;


typedef struct Time
{
	unsigned int departureHour;
	unsigned int departureMin;
	unsigned int arrivalHour;
	unsigned int arrivalMin;
} Time;

typedef struct Passenger
{
	unsigned int number;
	char* flight;
	char* departureAirport;
	char* departureCity;
	char* arrivalAirport;
	char* arrivalCity;
	Time times;
} Passenger;

typedef struct PassengersArray
{
	Passenger* Passengers;
	size_t		 size;
} PassengersArray;

int addPassenger(struct PassengersArray* arr, int count)
{
	char bufer[BUFSIZ];
	
	printf("Enter passenger code number: ");
	scanf("%d", &(arr->Passengers[arr->size - 1]).number);

	printf("Enter passenger flight: ");
	scanf("%s", bufer);
	arr->Passengers[arr->size - 1].flight = (char*)malloc(sizeof(char) * (strlen(bufer) + 1));//потому что array.size указывает на следующий после выделенной памяти элеменнт
	strcpy(arr->Passengers[arr->size - 1].flight, bufer);

	printf("Enter passenger departure airport: ");
	scanf("%s", bufer);
	arr->Passengers[arr->size - 1].departureAirport = (char*)malloc(sizeof(char) * (strlen(bufer) + 1));
	strcpy(arr->Passengers[arr->size - 1].departureAirport, bufer);

	printf("Enter passenger departure sity: ");
	scanf("%s", bufer);
	arr->Passengers[arr->size - 1].departureCity = (char*)malloc(sizeof(char) * (strlen(bufer) + 1));
	strcpy(arr->Passengers[arr->size - 1].departureCity, bufer);

	printf("Enter passenger arrival airport: ");
	scanf("%s", bufer);
	arr->Passengers[arr->size - 1].arrivalAirport = (char*)malloc(sizeof(char) * (strlen(bufer) + 1));
	strcpy(arr->Passengers[arr->size - 1].arrivalAirport, bufer);

	printf("Enter passenger arrival city: ");
	scanf("%s", bufer);
	arr->Passengers[arr->size - 1].arrivalCity = (char*)malloc(sizeof(char) * (strlen(bufer) + 1));
	strcpy(arr->Passengers[arr->size - 1].arrivalCity, bufer);

	printf("Enter passenger departure hour: ");
	scanf("%d", &(arr->Passengers[arr->size - 1]).times.departureHour);
	printf("Enter passengers departure minutes: ");
	scanf("%d", &(arr->Passengers[arr->size - 1]).times.departureMin);
	printf("Enter passengers arrival hour: ");
	scanf("%d", &(arr->Passengers[arr->size - 1]).times.arrivalHour);
	printf("Enter passengers arrival minutes: ");
	scanf("%d", &(arr->Passengers[arr->size - 1]).times.arrivalMin);

	return 0;
}

int deletePassenger(struct PassengersArray* arr, int deleteNum)
{
	for (deleteNum; deleteNum < (arr->size-1); deleteNum++)//я ставлю элемент выше делит нума на 1 на место делит нума и тд и так до -1 эл-та от исходного кол-ва
	{
		arr->Passengers[deleteNum].number = arr->Passengers[deleteNum + 1].number;
		arr->Passengers[deleteNum].flight = arr->Passengers[deleteNum +1].flight;
		arr->Passengers[deleteNum].departureAirport = arr->Passengers[deleteNum +1].departureAirport;
		arr->Passengers[deleteNum].departureCity = arr->Passengers[deleteNum +1].departureCity;
		arr->Passengers[deleteNum].arrivalAirport = arr->Passengers[deleteNum +1].arrivalAirport;
		arr->Passengers[deleteNum].arrivalCity = arr->Passengers[deleteNum +1].arrivalCity;
		arr->Passengers[deleteNum].times.departureHour = arr->Passengers[deleteNum +1].times.departureHour;
		arr->Passengers[deleteNum].times.departureMin = arr->Passengers[deleteNum +1].times.departureMin;
		arr->Passengers[deleteNum].times.arrivalHour = arr->Passengers[deleteNum +1].times.arrivalHour;
		arr->Passengers[deleteNum].times.arrivalMin = arr->Passengers[deleteNum +1].times.arrivalMin;
	}
	arr->size = arr->size - 1;

	// arr->Passengers = (Passenger*)realloc(arr->Passengers, ++(arr->size) * sizeof(Passenger));
	//for (int i = 0; i < arr->size; i++)
	//{
		//printf("%d %s %s %s %s %s %d %d %d %d\n", arr->Passengers[i].number, arr->Passengers[i].flight, arr->Passengers[i].departureAirport, arr->Passengers[i].departureCity, arr->Passengers[i].arrivalAirport, arr->Passengers[i].arrivalCity, arr->Passengers[i].times.departureHour, arr->Passengers[i].times.departureMin, arr->Passengers[i].times.arrivalHour, arr->Passengers[i].times.arrivalMin);
	//}
	return 0;
}


int numSearch(struct PassengersArray* arr, int num)
{
	int k = 0;
	int m = 0;

	for (int i = 0; i < arr->size; i++)
	{
		if ((arr->Passengers[i].number) == num)
		{
			k++;
		}
	}

	if (k == 0)
	{
		printf("No passenger number matches\n");
		return 0;
	}

	if (k > 1)
	{
		err_code = SIMILAR_PASSENGERS_NUM;
		perror("More than one passenger with similar id, bruh\n");
		exit(err_code);
	}

	if (k == 1)
	{
		for (int i = 0; i < arr->size; i++)
		{
			if ((arr->Passengers[i].number) == num)
			{
				m = i;
				break;
			}
		}
	}

	return m;

}



int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		err_code = NO_ARGS_ERR;
		perror("No arguments bruh");
		exit(err_code);
	}

	const char* inputFileName = argv[1];
	FILE* fo;

	if (!(fo = fopen(inputFileName, "r")))
	{
		err_code = INPUT_FILE_ERR;
		perror("Problem with input file");
		exit(err_code);
	}

	PassengersArray array = { NULL, 0 };
	char buf[BUFSIZ];
	while (!feof(fo))
	{
		array.Passengers = (Passenger*)realloc(array.Passengers, ++(array.size) * sizeof(Passenger));//расширяем под пассажира
		
		fscanf(fo, "%d", &(array.Passengers[array.size - 1]).number);

		fscanf(fo, "%s", buf);
		array.Passengers[array.size - 1].flight = (char*)malloc(sizeof(char) * (strlen(buf) + 1));//потому что array.size указывает на следующий после выделенной памяти элеменнт
		strcpy(array.Passengers[array.size - 1].flight, buf);

		fscanf(fo, "%s", buf);
		array.Passengers[array.size - 1].departureAirport = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
		strcpy(array.Passengers[array.size - 1].departureAirport, buf);

		fscanf(fo, "%s", buf);
		array.Passengers[array.size - 1].departureCity = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
		strcpy(array.Passengers[array.size - 1].departureCity, buf);

		fscanf(fo, "%s", buf);
		array.Passengers[array.size - 1].arrivalAirport = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
		strcpy(array.Passengers[array.size - 1].arrivalAirport, buf);

		fscanf(fo, "%s", buf);
		array.Passengers[array.size - 1].arrivalCity = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
		strcpy(array.Passengers[array.size - 1].arrivalCity, buf);

		fscanf(fo, "%d", &(array.Passengers[array.size - 1]).times.departureHour);
		fscanf(fo, "%d", &(array.Passengers[array.size - 1]).times.departureMin);
		fscanf(fo, "%d", &(array.Passengers[array.size - 1]).times.arrivalHour);
		fscanf(fo, "%d", &(array.Passengers[array.size - 1]).times.arrivalMin);

		fgetc(fo);
	}
	fclose(fo);

	printf("Your passengers list, sir:\n");
	for (int i = 0; i < array.size; i++)
	{
		printf("%d %s %s %s %s %s %d %d %d %d\n", array.Passengers[i].number, array.Passengers[i].flight, array.Passengers[i].departureAirport, array.Passengers[i].departureCity, array.Passengers[i].arrivalAirport, array.Passengers[i].arrivalCity, array.Passengers[i].times.departureHour, array.Passengers[i].times.departureMin, array.Passengers[i].times.arrivalHour, array.Passengers[i].times.arrivalMin);
	}
	
	int passengersCount;
	passengersCount = array.size;

	printf("\nIf u want to add passenger press 1;\nIf u wand to delete passenger press 2;\nIf u want to see a passengers list press 3.\n\n");

	int procedureNum = 0;
	printf("Procedure number: ");
	scanf("%d", &procedureNum);
	
	switch (procedureNum)
	{
		case 1:
			printf("Enter passenger data please.\n");
			array.Passengers = (Passenger*)realloc(array.Passengers, ++(array.size) * sizeof(Passenger));
			addPassenger(&array, array.size);
			break;

		case 2:
			printf("Enter passengers num that u want to delete: ");
			int deleteNum;
			scanf("%d", &deleteNum);
			printf("\n\n");
			int deleteNumPose;
			deleteNumPose = numSearch(&array, deleteNum);
			deletePassenger(&array, deleteNumPose);
			//array.Passengers = (Passenger*)realloc(array.Passengers, --(array.size) * sizeof(Passenger));

			break;

		case 3:
			for (int i = 0; i < array.size; i++)
			{
				printf("%d %s %s %s %s %s %d %d %d %d\n", array.Passengers[i].number, array.Passengers[i].flight, array.Passengers[i].departureAirport, array.Passengers[i].departureCity, array.Passengers[i].arrivalAirport, array.Passengers[i].arrivalCity, array.Passengers[i].times.departureHour, array.Passengers[i].times.departureMin, array.Passengers[i].times.arrivalHour, array.Passengers[i].times.arrivalMin);
			}
			break;
		default:
			printf("Uncorrect input(\n\n");
	}


	for (int i = 0; i < array.size; i++)
	{
		printf("%d %s %s %s %s %s %d %d %d %d\n", array.Passengers[i].number, array.Passengers[i].flight, array.Passengers[i].departureAirport, array.Passengers[i].departureCity, array.Passengers[i].arrivalAirport, array.Passengers[i].arrivalCity, array.Passengers[i].times.departureHour, array.Passengers[i].times.departureMin, array.Passengers[i].times.arrivalHour, array.Passengers[i].times.arrivalMin);
	}
		
	for (int i = 0; i < array.size; i++)
	{
		free(array.Passengers[i].flight);
		free(array.Passengers[i].departureCity);
		free(array.Passengers[i].departureAirport);
		free(array.Passengers[i].arrivalCity);
		free(array.Passengers[i].arrivalAirport);
	}
		free(array.Passengers);
	


	return 0;
}