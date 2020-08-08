#include "built_in_commands.h"
#include "ls.h"
#include "pinfo.h"
#include "execute.h"
#include "jobs.h"
#include "overkill.h"
#include "fg_bg.h"
#include "signal_handlers.h"
#include "environment.h"

char buffer[4096];

void kjob(char *args){
	char *token = strtok(args, Delimiters);
	token = strtok(NULL, Delimiters);
	if(token == NULL){
		printf("Wrong Usage\n");
		return;
	}
	int a = ToInt(token) - 1;
	token = strtok(NULL,Delimiters);
	if(token == NULL){
		printf("Wrong Usage\n");
		return;
	}
	if((pid_array[a].num<=-2 || pid_array[a].num>=1) && strcmp(pid_array[a].status,"Stopped"))
		kill(pid_array[a].num, ToInt(token));
	else
		printf("Process number not found\n");
}

void another_process(char **query_array,int flag){
	int pid = fork();
	int status = 0;
	if(!pid){
		query_array = bgadd(query_array);
		signal(SIGTSTP, &ctrlZ); 
		signal(SIGINT, &ctrlC); 
		if(!flag)
			setpgid(0,0);
		if(execvp(query_array[0], query_array))
			fprintf(stderr, "ERROR: \"%s\" command unrecognised\n", query_array[0]);
	}
	else{
		if(!flag){
			waitpid(pid, &status,WUNTRACED);
			if(WSTOPSIG(status)){
				pid_array[count].val = pid;
				pid_array[count].num = pid;
				count++;
				strcpy(pid_array[count].status, "Stopped");
				strcpy(pid_array[count].str, query_array[0]);
				status = -1;
			}
		}
		else{
			printf("%s with process id : %d started \n",query_array[0],pid);
			pid_array[count].val = pid;
			pid_array[count].num = pid;
			count++;
			strcpy(pid_array[count].status,"Running");
			strcpy(pid_array[count].str,query_array[0]);
			usleep(80);
		}
	}
}

char **bgadd(char **args){
	char in[sz], out[sz], outdir[sz];
	char *query_array = args[0];
	int fd1, fd2, fd3, c=0;
	int flag1=0, flag2=0, flag3=0;
	while(query_array != NULL){
		if(!strncmp(query_array, "<", 1)){
			flag1=1;
			args[c]=NULL;
			strcpy(in,args[c+1]);
		}
		if(!strncmp(query_array, ">", 1)){
			flag2=1;
			args[c]=NULL;
			strcpy(out,args[c+1]);
		}
		if(!strncmp(query_array, ">>", 2)){
			flag3=1;
			args[c]=NULL;
			strcpy(outdir, args[c+1]);
		}
		c++;
		query_array = args[c];
	}
	if(!flag1 && !flag2 && !flag3)
		return args;
	if(flag1){
		fd1 = open(in, O_RDONLY, 0);
		if(fd1 < 0){
			fprintf(stderr, "Error in opening file");
			exit(0);
		}
		dup2(fd1, 0);
		close(fd1);
	}
	if(flag2){
		fd2 = open(out,O_WRONLY|O_CREAT,0666);
		if(fd2 < 0){
			fprintf(stderr, "Error in opening the output file");
			exit(0);
		}
		dup2(fd2, 1);
		close(fd2);
	}
	if(flag3){
		fd3 = open(outdir,O_WRONLY|O_CREAT|O_APPEND,0666);
		if(fd3 < 0){
			fprintf(stderr, "Error in opening the output file");
			exit(0);
		}
		dup2(fd3, 1);
		close(fd3);
	}
	return args;
}

void execute(char *args, char *home){
	int numTokens=1, j=0, is_redir_piping=0, flag=0, i=0;
	char temp3[sz];
	strcpy(temp3,args);
	char *tokens[sz];
	char temp[sz], built_in[sz];
	char **query_array = (char**)malloc(100 * sizeof(char *));
	if((tokens[0]=strtok(temp3,Delimiters)) == NULL)
		return;
	while((tokens[numTokens]=strtok(NULL,Delimiters)) != NULL)
		numTokens++;
	strcpy(temp, args);
	strcpy(built_in, args);

	char *token = strtok(temp,Delimiters);
	if(token == NULL)
		return;

	while(token != NULL){
		if(!strcmp(token, "&")){
			flag = 1;
		}
		else{
			query_array[i] = (char *)malloc(strlen(token)+1);
			strcpy(query_array[i], token);
			i++;
		}
		token = strtok(NULL,Delimiters);	
	}
	query_array[i] = NULL;

	char *token2 = strtok(args,Delimiters);
	if(!strcmp(token2,"cd"))
		cd(built_in,home);
	else if(!strcmp(token2,"pwd") && is_redir_piping!=1)
		pwd();
	else if(!strcmp(token2,"echo") && is_redir_piping!=1)
		echo(built_in);
	else if(!strcmp(token2,"quit"))
		exit(0);
	else if(!strcmp(token2,"kjob"))
		kjob(built_in);
	else if(!strcmp(token2,"ls") && is_redir_piping!=1)
		ls(built_in);
	else if(!strcmp(token2,"pinfo"))
		pinfo(built_in);
	else if(!strcmp(token2,"jobs"))
		jobs();
	else if(!strcmp(token2,"overkill"))
		overkill();
	else if(!strcmp(token2,"fg"))
		fg(built_in);
	else if(!strcmp(token2,"bg"))
		bg(built_in);
	// else if(!strcmp(token2,"setenv"))
	// 	set(built_in);
	// else if(!strcmp(token2,"unsetenv"))
	// 	unset(built_in); 
	else
		another_process(query_array,flag);
	
	for(i=0;query_array[i] != NULL;i++){
		free(query_array[i]);
	}
}
