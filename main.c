#include<stdio.h>
#include"copy.h"

void main(int argc, char* argv[])
{
	printf("Hello World\n");
	printf("Recevied %d arguments\n", argc);

	for (int i = 0; i < argc; i++)
	{
		printf("Argument %d: %s\n", argc, argv[i]);
	}
	
	char firstFilePath[50] = "first.txt";
	char secondFilePath[50] = "second.txt";
	copy(firstFilePath, secondFilePath);
}
