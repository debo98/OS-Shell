#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <pwd.h> 
#include <grp.h>
#define Delimiters " \t\r\n\a"
#define sz 1005
void ls(char *args);
