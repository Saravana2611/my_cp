#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"copy.h"

void main(int argc, char* argv[])
{
	printf("Hello World\n");
	printf("Recevied %d arguments\n", argc);

	if (argc != 3)
	{
		printf("Unsupported number of Arguments");
		exit(1);
	}
	for (int i = 0; i < argc; i++)
	{
		printf("Argument %d: %s\n", argc, argv[i]);
	}
	
	char firstFilePath[50], secondFilePath[50];
	strcpy(firstFilePath, argv[1]);
	strcpy(secondFilePath, argv[2]);
	copy(firstFilePath, secondFilePath);
}
