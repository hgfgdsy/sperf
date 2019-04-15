#include <stdio.h>
#include <unistd.h>
#include <string.h>

int fildes[2];
extern char **environ;

int main(int argc, char *argv[]) {
  pipe(fildes);
  char *my_arg[50]={"strace","-T"};
  int i;
  for(i=1;i<argc;i++) my_arg[i+1]=argv[i];
  pid_t pid = fork();
//  for(int j=0;j<=argc;j++) printf("mt_arg[%d] = %s\n",j,my_arg[j]);
  if(pid == 0){
	  printf("I'm son\n");
	  dup2(fildes[1],2);
	  execve("/usr/bin/strace",my_arg,environ);
	  printf("I'm son too\n");
  }
  else{
	  char PB[65536];
	  while(1){
		  int sum = read(fildes[0],PB,65536);
//		  for(int i=0;i<sum;i++) printf("%c",PB[i]);
//		  printf("sum = %d\n",sum);
                  
	  }
	  printf("I'm father\n");
  }
  return 0;
}
