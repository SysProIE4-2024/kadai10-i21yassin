/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

// system関数のクローン
int mysystem(char *command) {
  int status = 0;
  int pid=fork();

  if (pid < 0)
   return -1;

  if (command == NULL)
   return 1;

  if (pid != 0){
    while(wait(&status)!=pid);
  }
  else {
    execl("/bin/sh","sh","-c",command,NULL);
    perror("/bin/sh");
    exit (127);
  }

  return status;
}

/* 実行例

ここに実行例を書く

*/
