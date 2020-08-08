#include "ls.h"

void ls(char *args){
	char *token = strtok(args, Delimiters);
	token = strtok(NULL, Delimiters);
	char str[sz][sz];
	int fl = 1, i, cnt = 0;
	if(token != NULL){
		if(!strcmp(token, "-a"))
			fl = 2;
		else if(!strcmp(token, "-l"))
			fl = 3;
		else if(!strcmp(token, "-la") || !strcmp(token, "-al"))
			fl = 4;
	}
	if(fl==1 || fl==2){
		if(fl == 2)
			token = strtok(NULL, Delimiters);
		while(token != NULL){
			strcpy(str[cnt], token);
			token = strtok(NULL, Delimiters);
			cnt++;
		}
		if(!cnt){
			strcpy(str[0], ".");
			cnt++;
		}
		for(i=0; i<cnt; i++){
			DIR *present_directory;
			struct dirent *file;
			fprintf(stdout, "For %s directory :\n\n",str[i]);
			if((present_directory=opendir(str[i])) == NULL){
				fprintf(stderr,"Cannot open %s diectory",str[i]);
				return;
			}
			for(;;){
				if((file=readdir(present_directory)) != NULL){
					char str[sz];
					strcpy(str,file->d_name);
					if(str[0] == '.'){
						if(fl==2)
							printf("%s\n",str);
					}
					else{
						printf("%s\n",str);
					}
				}
				else{
					break;
				}
			}
			closedir(present_directory);
		}
	}
	else{
		token = strtok(NULL, Delimiters);
		while(token != NULL){
			strcpy(str[cnt], token);
			token=strtok(NULL, Delimiters);
			cnt++;
		}
		if(!cnt){
			strcpy(str[0], ".");
			cnt++;
		}
		for(i=0; i<cnt; i++){
			int flag;
			struct stat stats;
			struct dirent* current_directory;
			struct group *user_group = getgrgid((long)stats.st_gid);
			DIR* directory = opendir(str[i]);
			fprintf(stdout, "Directory -> %s\n\n", str[i]);
			if(directory == NULL){ 
				fprintf(stdout, "dir_list : %s : %s \n", str[i], strerror(errno));
				return ;
			}   
			struct tm lt;
			struct passwd *pwd;
			while((current_directory=readdir(directory)) != 0){
				char strin[sz];
				strcpy(strin,current_directory->d_name);
				if(strin[0] != '.'){
					stat(current_directory->d_name,&stats);  
					if(!stat(current_directory->d_name,&stats))
						pwd=getpwuid(stats.st_uid);
					if((stats.st_mode & S_IFMT) == S_IFLNK)
					{
						fprintf(stdout, "l");
						flag=1;
					}
					else if((stats.st_mode & S_IFMT) == S_IFDIR)
						fprintf(stdout, "d");
					else 
						fprintf(stdout, "-");
					long long no_of_links=(long long)stats.st_nlink;
					mode_t val;
					val = (stats.st_mode & ~S_IFMT);
					if(val & S_IRUSR) 
						fprintf(stdout, "r"); 
					else 
						fprintf(stdout, "-");
					if (val & S_IWUSR) 
						fprintf(stdout, "w");
					else 
						fprintf(stdout, "-");    
					if(val & S_IXUSR)  
						fprintf(stdout, "x") ;
					else 
						fprintf(stdout, "-");
					if(val & S_IRGRP)  
						fprintf(stdout, "r") ;
					else 
						fprintf(stdout, "-");
					if(val & S_IWGRP)  
						fprintf(stdout, "w") ;
					else 
						fprintf(stdout, "-");
					if(val & S_IXGRP)  
						fprintf(stdout, "x") ;
					else 
						fprintf(stdout, "-");
					if(val & S_IROTH)  
						fprintf(stdout, "r") ;
					else 
						fprintf(stdout, "-");
					if(val & S_IWOTH)  
						fprintf(stdout, "w") ;
					else 
						fprintf(stdout, "-");
					if(val & S_IXOTH)  
						fprintf(stdout, "x") ;
					else 
						fprintf(stdout, "-");
					fprintf(stdout, " %lld ",no_of_links);
					fprintf(stdout, " %4s ",pwd->pw_name);
					fprintf(stdout, "%4s ",user_group->gr_name);
					char timebuf[90];
					time_t t=stats.st_mtime;
					localtime_r(&t,&lt);
					strftime(timebuf,sizeof(timebuf),"%c",&lt);
					if(pwd!=0) 
						fprintf(stdout, "%lld \t%s %s\n", (long long)stats.st_size,timebuf,current_directory->d_name);
					if(pwd==0)
						fprintf(stdout, "%d %lld \t%s %s\n", stats.st_uid,(long long)stats.st_size,timebuf,current_directory->d_name); 
				}
				else{
					if(fl == 4){
						stat(current_directory->d_name, &stats);  
						if(!stat(current_directory->d_name, &stats))
							pwd = getpwuid(stats.st_uid);
						if((stats.st_mode & S_IFMT) == S_IFLNK){
							fprintf(stdout, "l");
							flag=1;
						}
						else if((stats.st_mode & S_IFMT) == S_IFDIR)
							fprintf(stdout, "d");
						else 
							fprintf(stdout, "-");
						long long no_of_links = (long long)stats.st_nlink;
						mode_t val;
						val=(stats.st_mode & ~S_IFMT);
						if(val & S_IRUSR) 
							fprintf(stdout, "r"); 
						else 
							fprintf(stdout, "-");
						if (val & S_IWUSR) 
							fprintf(stdout, "w");
						else 
							fprintf(stdout, "-");    
						if(val & S_IXUSR)  
							fprintf(stdout, "x") ;
						else 
							fprintf(stdout, "-");
						if(val & S_IRGRP)  
							fprintf(stdout, "r") ;
						else 
							fprintf(stdout, "-");
						if(val & S_IWGRP)  
							fprintf(stdout, "w") ;
						else 
							fprintf(stdout, "-");
						if(val & S_IXGRP)  
							fprintf(stdout, "x") ;
						else 
							fprintf(stdout, "-");
						if(val & S_IROTH)  
							fprintf(stdout, "r") ;
						else 
							fprintf(stdout, "-");
						if(val & S_IWOTH)  
							fprintf(stdout, "w") ;
						else 
							fprintf(stdout, "-");
						if(val & S_IXOTH)  
							fprintf(stdout, "x") ;
						else 
							fprintf(stdout, "-");
						fprintf(stdout, " %lld ",no_of_links);
						fprintf(stdout, " %4s ",pwd->pw_name);
						fprintf(stdout, "%4s ",user_group->gr_name);
						char timebuf[90];
						time_t t = stats.st_mtime;
						localtime_r(&t,&lt);
						strftime(timebuf,sizeof(timebuf),"%c",&lt);
						if(pwd!=0) 
							fprintf(stdout, "%lld \t%s %s\n", (long long)stats.st_size,timebuf,current_directory->d_name);
						if(pwd==0)
							fprintf(stdout, "%d %lld \t%s %s\n", stats.st_uid,(long long)stats.st_size,timebuf,current_directory->d_name);
					}
				}
			}
			closedir(directory);
		}
	}
}
