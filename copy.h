#include<stdio.h>

int openFile(const char* filePath, const int flag);
void closeFile(const int fd);
struct stat getFileStats(const int fd);
void copy(const char* file1Path, const char* file2Path);
