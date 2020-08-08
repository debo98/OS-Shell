#include "signal_handlers.h"
#include "execute.h"
#include "terminal.h"

void validPID(int pid, int sigterm){
	kill(pid, sigterm);
	int i;
	for(i=0; i<count; i++){
		if(pid_array[i].num == pid){
			fprintf(stdout, "%s with process id %d  exited successfully\n",pid_array[i].str,pid_array[i].num);
			pid_array[i].num = -1;
		}
	}
}

void HandleSignal(int sig, siginfo_t *si, void *context){
	switch(sig){
		int status, pid, i, pos;
		case SIGCHLD:
			pid = waitpid(-1, NULL, WNOHANG);
			if(pid > 0)
			{
				validPID(pid, SIGTERM);
			}
			break;
		case SIGINT:
			break;
	}
}

void ctrlZ(int signo){
	if(signo == SIGTSTP){
		if(getpid() == shellpid)
			fprintf(stdout, "\n");
		else
			kill(getpid(), SIGTSTP);
	}
}

void ctrlC(int signo){
	if(signo == SIGINT){
		if(getpid() == shellpid)
			fprintf(stdout, "\n");
		else
			kill(getpid(), 9);
	}
}
