#include "overkill.h"
#include "execute.h"

void overkill(){
	int i=0;
	while(i<count){
		if(pid_array[i].num != -1){
			pid_array[i].num = -1;
			kill(pid_array[i].num,SIGKILL);
		}
		i++;
	}
}
