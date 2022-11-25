#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

const int LINE_LEN = 32;
const void* NULL = 0;

char* getline(char* buf, int max_len){
//  char ch;

  int i = 0;
  while(1){
//read(0, &ch, 1); 
    //buf[i] = ch;
    i++;
    //if(i>=max_len-2 || ch == '\n')
    if(i>=max_len-2 )
      break;
  }
 // buf[i] = '\0';

  if(i > 0){
    return buf;
  }
  else{
    return (char*)NULL;
  }
}

int
main(int argc, char* argv[])
{
  char buf[MAXARG][LINE_LEN];
  int line_cnt = 0;

  while(1){
    int i = 0;
    int eof = 0;

    while(1){
      char ch;
      if(read(0, &ch, 1)<1){
        eof = 1;
        break;
      }
      else{
        buf[line_cnt][i++] = ch;
        if(ch == '\n' || i >= LINE_LEN-1 )
          break;
      }
    }
    buf[line_cnt][i] = '\0';
    if(i>0 && buf[line_cnt][i-1] == '\n')
      buf[line_cnt][i-1] = '\0';


    if(i!=0)
      line_cnt++;

    if(eof)
      break;
    if(line_cnt>=MAXARG)
      break;
  }

  int pid = fork();
  
  if(pid == 0){
    char* new_args[line_cnt+argc];
    for(int k=1;k<argc;k++){
      new_args[k-1] = argv[k];
    }
    for(int k=0;k<line_cnt;k++){
      new_args[argc-1+k] = buf[k];
    }
    new_args[line_cnt+argc-1] = (char*)NULL;

  //  printf("ext args no: %d\n", line_cnt);
  //  printf("argvs no: %d\n", argc-1);
  //  for(int i =0;i<line_cnt+argc-1;i++){
  //    printf("%s\n", new_args[i]);
  //  }

    exec(argv[1], (char**)new_args);

    printf("xargs: some error occur on exec\n");
    exit(1);
  }
  else if(pid > 0){
    wait((int*)0);
    exit(0);
  }
  else{
    printf("xargs: fork error!\n"); 
    exit(1);
  }

//  exit(0);
}
