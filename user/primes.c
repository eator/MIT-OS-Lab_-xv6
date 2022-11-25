#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

void sieve_prime(int pipe_left[2])
{
  int prime;
  if(read(pipe_left[0], &prime, 4)==0){
    return;
  }
  
  // the first read must be a prime
  printf("prime %d\n", prime);

  int pid = fork();
  if(pid == 0){
    int i;
    int pipe_right[2];
    pipe(pipe_right);

    while(read(pipe_left[0], &i, 4)>0){
      if(i%prime){
        write(pipe_right[1], &i, 4);
      }
    }

    close(pipe_left[0]);
    close(pipe_right[1]);

    sieve_prime(pipe_right);
    exit(0);
  }
  else{
    wait((int*)0);
    exit(0);
  }
}

int
main()
{
  int pipe_right[2];
  pipe(pipe_right);

  for(int i = 2; i<36; i++){
    write(pipe_right[1], &i, 4);
  }
  close(pipe_right[1]);

  sieve_prime(pipe_right);

  exit(0);
}
