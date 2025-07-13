#include "copy.h"

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>

int RW_FLAG = O_RDWR;
int RWC_FLAG = O_RDWR | O_CREAT;
mode_t RW_MODE = S_IRUSR | S_IWUSR;
int BUFFER_SIZE = 500;

int openFile(char* filePath, int flag)
{
	printf("Called OpenFile\n");
        int fd = open(filePath, flag, RW_MODE);
        if (fd < 0)
        {
                printf("Error in opening file\n");
                return -1; //Change to EXIT()
        }
        printf("File opened\n");
	return fd;
}

void closeFile(int fd)
{
	printf("Called CloseFile\n");
	int ret = close(fd);
	if (ret < 0)
	{
		printf("Error in closing file\n");
		// return -1;  Change to Exit()
	}
}

struct stat getFileStats(int fd)
{
	printf("Called getFileStats\n");

	struct stat fileStats;
	int ret = fstat(fd, &fileStats);
	if (ret != 0)
	{
		printf("Error in fetching file stats\n");
	}

	printf("File size: %jd bytes\n", (intmax_t) fileStats.st_size);
	printf("Blocks allocated: %jd\n", (intmax_t) fileStats.st_blocks);

	return fileStats;
}

void copy(char* file1Path, char* file2Path)
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

	closeFile(fd1);
	closeFile(fd2);
	printf("File Copied\n");
}

