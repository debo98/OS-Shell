#include "pinfo.h"

void pinfo(char *args){
	char str[sz] = "/proc/";
	char str2[sz] = "";
	char str3[2];
	int num = getpid();

	char *token=strtok(args, Delimiters);
	token = strtok(NULL, Delimiters);

	sprintf(str2, "%d", num);
	if(token != NULL)
		strcat(str, token);
	else
		strcat(str, str2);

	int pid, status;
	char statpath[sz];
	strcpy(statpath, str);
	strcat(statpath, "/stat");
	FILE *stat = fopen(statpath, "r");
	if(stat == NULL){
		fprintf(stdout, "Please enter valid process PID\n");
		return;
	}
	char name[sz];
	fscanf(stat, "%d %s %c", &pid, name, &status);
	fprintf(stdout, " pid -- %d\n Process Status -- {%c}memory\n", pid, status);
	fclose(stat);

	int memsize;
	char statmpath[sz];
	strcpy(statmpath, str);
	strcat(statmpath, "/statm");
	FILE *mem = fopen(statmpath, "r");
	fscanf(mem, "%d", &memsize);
	fprintf(stdout, "- %d {Virtual Memory}\n", memsize);
	fclose(mem);

	char execpath[sz];
	strcpy(execpath, str);
	strcat(execpath, "/exe");
	char exec[sz];
	readlink(execpath, exec, sizeof(exec));
	fprintf(stdout,"Executable Path - %s\n",exec);
}