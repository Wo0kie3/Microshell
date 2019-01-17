#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
//#include <sys/wait.h>
#include <string.h>
//#include <sys/utsname.h>
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m]"
#define COLOR_RESET "\x1b[0m"
#define BUFF_SIZE 1024
void help(){
    printf(YELLOW "\nJerzy Lukaszewicz" COLOR_RESET);
    printf(YELLOW "\nGrupa 1CI " COLOR_RESET CYAN "s444429" COLOR_RESET);
    printf(MAGENTA "\nMoje funkcje to:" COLOR_RESET);
    printf(MAGENTA "\n-cd"COLOR_RESET);
    printf(MAGENTA "\n-exit"COLOR_RESET);
    return;
}

void cd(char **polecenie){
    chdir(polecenie[1]);
    return;
}

char **ArgParam (char *result){
    char *polecenie[255];
    char korektor[]=" \n";
    int n=0;
    char *word = strtok (result, korektor);
    while(word !=NULL) {
        polecenie[n]=word;
    n++;
    word=strtok(NULL,korektor);
    }
    polecenie[n]=NULL;
    return polecenie;
}
 
int main(int argc, char* argv[]){
    char cwd[BUFF_SIZE];
    char *result=NULL;
    char napis[BUFF_SIZE];
    char **polecenie=NULL;
    int i,j;

    while(1){
      getcwd(cwd,sizeof(cwd));
      printf("%s$>",cwd);
      result = fgets(napis, BUFF_SIZE, stdin);
      polecenie=ArgParam(result);
      if(strlen(result)==1){
        continue;
  	}
    if(strcmp(polecenie[0],"help")==0){
    	  help();
	  }
    else if(strcmp(polecenie[0],"exit")==0){
        return -1;
    }
    else if(strcmp(polecenie[0],"cd")==0){
		    cd(polecenie);
	  }
  }
}
