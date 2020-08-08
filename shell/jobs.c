#include "jobs.h"
#include "execute.h"
void jobs(){
	int i=0,val=0;
	while(i<count){
		if(pid_array[i].num!=-1){
			val++;
			if(!strcmp(pid_array[i].status,"Stopped"))
				printf("[%d]   STOPPED   %s[%d]\n",val+1,pid_array[i].str,pid_array[i].val);
			else
				printf("[%d]   RUNNING   %s[%d]\n",val+1,pid_array[i].str,pid_array[i].num);
		}
		i++;
	}
}
