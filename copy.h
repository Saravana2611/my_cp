#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

static const int RW_FLAG = O_RDWR;
static const int RWC_FLAG = O_RDWR | O_CREAT;
static const mode_t RW_MODE = S_IRUSR | S_IWUSR;
static const int BUFFER_SIZE = 500;
// static const int numberOfProcess = 2;

struct Ranges
{
	ssize_t startBytes[2];
	ssize_t endBytes[2];
};

int openFile(const char *filePath, const int flag);
void closeFile(const int fd);
struct stat getFileStats(const int fd);
void copy(const char *file1Path, const char *file2Path);
