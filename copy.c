#include "copy.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int openFile(const char *filePath, const int flag)
{
	printf("Called OpenFile\n");
	int fd = open(filePath, flag, RW_MODE);
	if (fd < 0)
	{
		printf("Error in opening file\n");
		exit(1);
	}
	printf("File opened\n");
	return fd;
}

void closeFile(const int fd)
{
	printf("Called CloseFile\n");
	int ret = close(fd);
	if (ret < 0)
	{
		printf("Error in closing file\n");
		exit(1);
	}
}

struct stat getFileStats(const int fd)
{
	printf("Called getFileStats\n");

	struct stat fileStats;
	int ret = fstat(fd, &fileStats);
	if (ret != 0)
	{
		printf("Error in fetching file stats\n");
		exit(1);
	}

	printf("File size: %jd bytes\n", (intmax_t)fileStats.st_size);
	printf("Blocks allocated: %jd\n", (intmax_t)fileStats.st_blocks);

	return fileStats;
}

void getCopyRange(struct stat *fileStats, struct Ranges *ranges)
{
	int totalFileSize = fileStats->st_size;
	ranges->startBytes[0] = 0;
	ranges->endBytes[0] = totalFileSize / 2;

	ranges->startBytes[1] = totalFileSize / 2;
	ranges->endBytes[1] = totalFileSize;
}

void copyFile(int fd1, int fd2, int offset, ssize_t size)
{
	printf("Copying File till %zd bytes\n", size);
	char buffer[BUFFER_SIZE];
	ssize_t bytesRead, totalBytesCopied = 0;

	// reposition to file reader
	if (lseek(fd1, offset, SEEK_SET) == -1)
	{
		printf("Error in seeking file\n");
		exit(1);
	}

	while (totalBytesCopied < size)
	{
		ssize_t toRead = BUFFER_SIZE;

		printf("toRead = %ld totalBytesCopied = %ld\n", toRead, totalBytesCopied);
		if (size - totalBytesCopied < BUFFER_SIZE)
		{
			printf("toRead = %ld\n", toRead);			
			toRead = size - totalBytesCopied;
		}
		printf("toRead = %ld\n", toRead);

		bytesRead = read(fd1, buffer, toRead);
		if (bytesRead < 0)
		{
			printf("Error in seeking file\n");
			exit(1);
		}

		ssize_t bytesWritten = write(fd2, buffer, bytesRead);
		if (bytesWritten < 0)
		{
			printf("Error in Wrtiting File\n");
			exit(1);
		}
		printf("BytesWritten = %zd\n", bytesWritten);
		totalBytesCopied += bytesRead;
	}
}

void copy(const char *file1Path, const char *file2Path)
{
	printf("Called Copy\n");

	int fd1 = openFile(file1Path, RW_FLAG);
	struct stat file1Stats = getFileStats(fd1);

	int fd2 = openFile(file2Path, RWC_FLAG);
	struct stat fil2Stats = getFileStats(fd2);

	struct Ranges ranges;
	getCopyRange(&file1Stats, &ranges);

	for (int i = 0; i < 2; i++)
	{
		printf("startBytes of %d = %zd \n", i, ranges.startBytes[i]);
		printf("EndButes of %d = %zd \n", i, ranges.endBytes[i]);
		copyFile(fd1, fd2, ranges.startBytes[i], ranges.endBytes[i] - ranges.startBytes[i]);
	}

	closeFile(fd1);
	closeFile(fd2);
	printf("File Copied\n");
}
