#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>


int main(){
  pid_t pid = fork();
  if(pid==0){
    close(1);
    sleep(1);
    printf("child");
    exit(0);
  }
  else{
    sleep(1);
    printf("parent");
    wait(NULL);
    exit(0);
  }
  

}
