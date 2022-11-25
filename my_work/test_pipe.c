#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
  int pipefd[2];
  pipe(pipefd);

  int pid = fork();
  if(pid ==0){
    char  ch;
    close(pipefd[1]);
    while(read(pipefd[0], &ch, 1)>0){
      printf("%c",ch);
    }
    close(pipefd[0]);
    exit(0);
  }
  else{
    for(int i=0;i<20;i++){
      close(pipefd[0]);
      write(pipefd[1], "a", 1);
    }
      close(pipefd[1]);
    wait(NULL);
    exit(0);
  }
}
