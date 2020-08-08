#include "fg_bg.h"
#include "execute.h"

int ToInt(char *str){
	int len, mult = 1, ret=0, i;
	len = strlen(str);
	for(i=len-1; i>=0; i--){
		ret += ((int)str[i]-48)*mult;
		mult *= 10;
	}
	return ret;
}

void fg(char *args){
	char *token = strtok(args,Delimiters);
	token = strtok(NULL, Delimiters);
	if(token == NULL){
		printf("Wrong Usage\n");
		return;
	}
	int status = 0, flag = 0, i, a;
	int num2 = ToInt(token) - 1;
	if(pid_array[num2].num>=1 || pid_array[num2].num<=-2){
		flag = 1;
		a = pid_array[num2].num;
		kill(pid_array[num2].num, SIGCONT);
		i++;
		pid_array[num2].num = -1;
		waitpid(pid_array[num2].num, &status, WUNTRACED);
		if(WSTOPSIG(status)){
			pid_array[num2].num = a;
			status = -1;
			strcpy(pid_array[num2].status, "Stopped");
		}
	}
	if(!flag)
		printf("Process number %d not found\n",num2);
}

void bg(char *args){
	char *token = strtok(args,Delimiters);
	token = strtok(NULL,Delimiters);
	if(token == NULL){
		printf("Wrong Usage\n");
		return;
	}
	int status = 0, flag = 0;
	int num2=ToInt(token) - 1;
	if(pid_array[num2].num>=1 || pid_array[num2].num<=-2){
		flag = 1;
		kill(pid_array[num2].num,SIGCONT);
		strcpy(pid_array[num2].status,"Running");

	}
	if(!flag)
		printf("Process number %d not found\n",num2);
}