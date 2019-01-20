#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/utsname.h>
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m]"
#define COLOR_RESET "\x1b[0m"
#define BUFF_SIZE 1024
void help(){
	printf(RED);
	printf("*********************\n");
	printf("**Jerzy Łukaszewicz**\n");
	printf("**Grupa 1CI s444429**\n");
	printf("*********************\n");
	printf("Moje funkcje to: \n");
	printf("-cd\n");
  printf("-exit\n");
	printf("-help\n");
	printf(COLOR_RESET);
	return;
}

void cp(char **polecenie){
		if(polecenie[2]==NULL || polecenie[1]==NULL){
				if(polecenie[2] != NULL && polecenie[1]==NULL){
						perror("Arguments error");
						return;
				}
		}
		else{
				int plik=open(polecenie[1], O_RDONLY);
				if(plik == -1){
						perror("source file error");
						return;
				}
				if(open(polecenie[2],O_RDONLY) != -1){
						printf("%s already exists!\n",polecenie[2]);
						return;
				}
				int nowy = creat(polecenie[2],0666);
				if(nowy==-1){
						perror("creat error");
						return;
				}
				char buff[BUFF_SIZE];
				int x;
				while((x=read(plik,buff,sizeof(buff)))>0){
						write(nowy,buff,x);
				}
				close(nowy);
				close(plik);
		}
}

void touch(char **polecenie){
		if(open(polecenie[1],O_RDONLY) != -1){
				printf("%s already exists!\n",polecenie[1]);
				return;
		}
		else{
			creat(polecenie[1],0666);
		}
}

void ls(char **polecenie){
		if(fork()==0){
				execlp("ls","ls",polecenie[1],NULL);
				perror("execlp");
				exit(EXIT_FAILURE);
		}
		else{
			  wait(NULL);
		}
		return;
}

void cd(char **polecenie,char *path){
			printf("%s\n",path);
			if(strcmp(polecenie[1],"-")==0){
					chdir(path);
			}
			else{
					chdir(polecenie[1]);
			}
			return;
}

void ArgParam (char *result,char **polecenie){
    	char korektor[]=" \n";
    	int n=0;
    	char *word = strtok (result, korektor);
    	while(word !=NULL) {
    		polecenie[n]=word;
    		n++;
    		word=strtok(NULL,korektor);
    	}
    	polecenie[n]=NULL;
	return;
}

int main(int argc, char *argv[]){
    	char cwd[BUFF_SIZE];
    	char *result;
    	char napis[BUFF_SIZE];
    	char *polecenie[255];
			char *prevCD;
	int i=0;

    	while(1){
					char *login=getlogin();
        	getcwd(cwd,sizeof(cwd));
        	printf(GREEN "%s@" RED "%s$>" COLOR_RESET,login,cwd);
      		result = fgets(napis, BUFF_SIZE, stdin);
					prevCD=cwd;
		i=strlen(napis);
		napis[i-1]='\0';
     		ArgParam(result,polecenie);
		if(strlen(napis)==0){
			continue;
		}
  	  	if(strcmp(polecenie[0],"help")==0){
  	  		help();
		}
		else if(strcmp(polecenie[0],"exit")==0){
	        	exit(0);
	    	}
		else if(strcmp(polecenie[0],"cd")==0){
			cd(polecenie,prevCD);
		}
		else if(strcmp(polecenie[0],"ls")==0){
			ls(polecenie);
		}
		else if(strcmp(polecenie[0],"cp")==0){
			cp(polecenie);
		}
		else if(strcmp(polecenie[0],"touch")==0){
			touch(polecenie);
		}
		else{
			printf("Wrong command!\n");
		}
	}
}
