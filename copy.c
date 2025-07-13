#include "copy.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <stdlib.h>

const int RW_FLAG = O_RDWR;
const int RWC_FLAG = O_RDWR | O_CREAT;
const mode_t RW_MODE = S_IRUSR | S_IWUSR;
const int BUFFER_SIZE = 500;

int openFile(const char* filePath, const int flag)
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

	printf("File size: %jd bytes\n", (intmax_t) fileStats.st_size);
	printf("Blocks allocated: %jd\n", (intmax_t) fileStats.st_blocks);

	return fileStats;
}

void copy(const char* file1Path, const char* file2Path)
{
	printf("Called Copy\n");
	char buffer[BUFFER_SIZE];
	
	int fd1 = openFile(file1Path, RW_FLAG);
	struct stat file1Stats = getFileStats(fd1);

	int fd2 = openFile(file2Path, RWC_FLAG);
	struct stat fil2Stats = getFileStats(fd2);

	ssize_t bytesRead;
	while ((bytesRead = read(fd1, buffer, BUFFER_SIZE)) > 0)
	{
		write(fd2, buffer, bytesRead);
	}

        fil2Stats = getFileStats(fd2);

	closeFile(fd1);
	closeFile(fd2);
	printf("File Copied\n");
}

