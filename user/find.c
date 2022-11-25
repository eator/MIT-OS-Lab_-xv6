#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  p = path;
  // Find first character after last slash.
//  for(p=path+strlen(path); p >= path && *p != '/'; p--)
//    ;
//  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void find(const char* dir_path,  const char* target){
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if((fd = open(dir_path, 0)) < 0){
    fprintf(2, "find: cannot open %s\n", dir_path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "find: cannot stat %s\n", dir_path);
    close(fd);
    return;
  }

  switch(st.type){
  case T_FILE:
    printf("find: some error has happened, the current find path can't be a file!\n"); 
    break;

  case T_DIR:
    if(strlen(dir_path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("find: path too long\n");
      break;
    }
    strcpy(buf, dir_path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;

      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("find: cannot stat %s\n", buf);
        continue;
      }

      switch(st.type){
      case T_FILE:
        if(!strcmp(de.name, target)){
          //printf("%s\n", fmtname(buf));
          printf("%s\n", buf);
        }
        break;

      case T_DIR:
        if(strlen(dir_path) + 1 + DIRSIZ + 1 > sizeof buf){
          printf("find: path too long\n");
          break;
        }

        if(strcmp(de.name, ".")&&strcmp(de.name, "..")){
          find(buf, target);
        }
        break;
      }
    }
  }

  close(fd);
}

int
main(int argc, char *argv[])
{

  if(argc >= 3){
    find(argv[1], argv[2]);
    exit(0);
  }
  else if(argc == 2){
    find(".", argv[1]);
    exit(0);
  }
  else{
    printf("find require 3 args, but only provided 1\n");
    exit(0);
  }
}
