#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <pwd.h>
#define Delimiters " \t\r\n\a"
#define sz 1005
void another_process(char **query_array,int flag);
void execute(char *args,char *home);
void fileIO(char *args[],char* inputFile,char* outputFile,int option,int suboption);
void kjob(char *args);
int ToInt(char *str);
char **bgadd(char **args);
struct PID
{
	int num;
	char str[sz];
	int val;
	char status[sz];
}pid_array[sz];
int count;
