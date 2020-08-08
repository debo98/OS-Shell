#include "environment.h"
void set(char *args){
	char *token, *tkn1, *tkn2, *tkn3;
	token = strtok(args, Delimiters);

	tkn1 = strtok(NULL, Delimiters);
	tkn2 = strtok(NULL, Delimiters);
	if(tkn1==NULL && tkn2==NULL) {
		fprintf(stdout, "Wrong Usage\n");
		return;
	}

	tkn3=strtok(NULL, Delimiters);
	if(tkn3 != NULL) {
		fprintf(stdout, "Wrong Usage\n");
		return;
	}

	if(getenv(tkn1) != NULL)
		fprintf(stdout, "Variable Overwritten\n");
	else
		fprintf(stdout, "Variable Created\n");

	if(tkn2 == NULL)
		setenv(tkn1, "", 1);
	else
		setenv(tkn1, tkn2, 1);
}

void unset(char *args){
	char *token, *tkn1;
	token=strtok(args,Delimiters);
	tkn1=strtok(NULL,Delimiters);
	if(tkn1 == NULL) {
		fprintf(stdout, "Wrong Usage\n");
		return;
	}
	if(getenv(tkn1) == NULL) {
		fprintf(stdout, "Variable does not exists\n");
		return;
	}
	fprintf(stdout, "Variable Destroyed\n");
	unsetenv(tkn1);
}