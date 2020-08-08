#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <pwd.h>
#include <fcntl.h>
#define Delimiters " \t\r\n\a"
#define sz 1005
void SIGINT_handler();
void SIGCHLD_handler();
int shellpid;
