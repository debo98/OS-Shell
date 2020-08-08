#include "execute.h"
#include "terminal.h"
#include "signal_handlers.h"
#include <termios.h>
#include <glob.h>
#include <pwd.h>
#include <sys/stat.h>

void SIGCHLD_handler(){
	fprintf(stdout, "Process exited!\n");
}

void SIGINT_handler(){
	signal(SIGINT,SIG_IGN);
	fprintf(stdout, "Handled\n");
}

int main(){
	int i,j,k;
	struct passwd *p = getpwuid(getuid());
	struct utsname node;
	uname(&node);

	char **commands = malloc(sz*sizeof(char*));
	char *home = malloc(sz*sizeof(char));
	getcwd(home,sz);
	char line[2*sz];

	int wait_ret;
	int status;

	struct sigaction sVal;
	sVal.sa_flags = SA_RESTART;
	sVal.sa_sigaction = &HandleSignal;
	sigfillset(&sVal.sa_mask);

	shellpid=getpid();

	if(sigaction(SIGINT, &sVal, NULL)<0)
		fprintf(stderr, "Error\n");
	if(sigaction(SIGCHLD, &sVal, NULL)<0)
		fprintf(stderr, "Error\n");
	signal(SIGTSTP, ctrlZ);
	signal(SIGINT, ctrlC);

	for(;;){
		for(i=0; i<count; i++){
			if(pid_array[i].num != -1){
					wait_ret=waitpid(pid_array[i].num,&status,WNOHANG);
					if(wait_ret>=1 || wait_ret<=-2){
						if(WIFSIGNALED(status) || WIFEXITED(status)){
							fprintf(stdout, "%s with process id %d  exited successfully\n",pid_array[i].str,pid_array[i].num);
							pid_array[i].num = -1;
						}
					}
				}
		}

		fprintf(stdout, " ");
		char *current_dir = malloc(sz*sizeof(char));
		getcwd(current_dir,sz);

		int len1 = strlen(current_dir);
		int len2 = strlen(home);
		int num_commands = 0;
		for(i=0; i<len2; i++){
			if((current_dir[i]!=home[i]) || i==(len1))
				break;
		}
		if(i != (len2))
			fprintf(stdout, "%s",current_dir);
		else{
			fprintf(stdout, "%s@UBUNTU:~", getenv("USER"));
			for(i=len2; i<=len1; i++)
				fprintf(stdout, "%c", current_dir[i]);
		}
		fprintf(stdout, ">");
		fgets(line, sz, stdin);
		if(strlen(line) == 0)
			fprintf(stderr, "Error\n");
		char *token;
		token = strtok(line, ";");
		while(token != NULL){
			commands[num_commands] = token;
			num_commands++;
			token = strtok(NULL, ";");
		}
		for(i=0; i<num_commands; i++)
			execute(commands[i], home);
	}
}