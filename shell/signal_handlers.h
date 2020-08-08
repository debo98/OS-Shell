#include <stdio.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <math.h>
#define Delimiters " \t\r\n\a"
#define sz 1005
void HandleSignal(int sig, siginfo_t *si, void *context);
void ctrlZ(int);
void ctrlC(int signo);