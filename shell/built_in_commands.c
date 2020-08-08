#include "built_in_commands.h"

void echo(char *args){
	int len=strlen(args);
	int fl=0, i;
	for(i=0; i<len; i++){
		if(!fl && args[i]==' ')
			fl=1;
		else if(fl==1 && args[i]!=' '){
			fl=2;
			fprintf(stdout, "%c",args[i]);
		}
		else if(fl==2)
			fprintf(stdout, "%c",args[i]);
	}
	return;
}

void cd(char *args,char *home){
	char *token = strtok(args,Delimiters);
	token = strtok(NULL,Delimiters);
	int fl;
	if(token==NULL || token[0]=='~')
		chdir(home);
	else{
		fl = chdir(token);
		if(fl<0)
			fprintf(stderr,"Directory does not exist :(\n");
	}
	return;
}

void pwd(){
	char *current_directory = malloc(sz*sizeof(char));
	getcwd(current_directory, sz);
	fprintf(stdout, "%s\n", current_directory);
	return;
}
