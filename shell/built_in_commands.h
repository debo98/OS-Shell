#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#define Delimiters " \t\r\n\a"
#define sz 1005
void echo(char *args);
void cd(char *args,char *home);
void pwd();
