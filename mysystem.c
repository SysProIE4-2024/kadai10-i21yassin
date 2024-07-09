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
i21yassine@Virtual-PC001:~/Syspro2/kadai10-i21yassin$ make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c

i21yassine@Virtual-PC001:~/Syspro2/kadai10-i21yassin$ ls -l
合計 276
-rw-r--r-- 1 i21yassine domain^users    143  7月  4 09:45 Makefile
-rw-r--r-- 1 i21yassine domain^users   2795  7月  4 09:45 README.md
-rw-r--r-- 1 i21yassine domain^users 238232  7月  4 09:45 README.pdf
-rwxr-xr-x 1 i21yassine domain^users  17192  7月  9 20:47 mysysmain
-rw-r--r-- 1 i21yassine domain^users    925  7月  4 09:45 mysysmain.c
-rw-r--r-- 1 i21yassine domain^users    642  7月  9 20:47 mysystem.c
-rw-r--r-- 1 i21yassine domain^users     90  7月  4 09:45 mysystem.h

i21yassine@Virtual-PC001:~/Syspro2/kadai10-i21yassin$ ./mysysmain "ls -l"
mysystem:
合計 276
-rw-r--r-- 1 i21yassine domain^users    143  7月  4 09:45 Makefile
-rw-r--r-- 1 i21yassine domain^users   2795  7月  4 09:45 README.md
-rw-r--r-- 1 i21yassine domain^users 238232  7月  4 09:45 README.pdf
-rwxr-xr-x 1 i21yassine domain^users  17192  7月  9 20:47 mysysmain
-rw-r--r-- 1 i21yassine domain^users    925  7月  4 09:45 mysysmain.c
-rw-r--r-- 1 i21yassine domain^users    642  7月  9 20:47 mysystem.c
-rw-r--r-- 1 i21yassine domain^users     90  7月  4 09:45 mysystem.h
retval = 00000000
system:
合計 276
-rw-r--r-- 1 i21yassine domain^users    143  7月  4 09:45 Makefile
-rw-r--r-- 1 i21yassine domain^users   2795  7月  4 09:45 README.md
-rw-r--r-- 1 i21yassine domain^users 238232  7月  4 09:45 README.pdf
-rwxr-xr-x 1 i21yassine domain^users  17192  7月  9 20:47 mysysmain
-rw-r--r-- 1 i21yassine domain^users    925  7月  4 09:45 mysysmain.c
-rw-r--r-- 1 i21yassine domain^users    642  7月  9 20:47 mysystem.c
-rw-r--r-- 1 i21yassine domain^users     90  7月  4 09:45 mysystem.h
retval = 00000000

i21yassine@Virtual-PC001:~/Syspro2/kadai10-i21yassin$ ./mysysmain
使い方 : ./mysysmain コマンド文字列

i21yassine@Virtual-PC001:~/Syspro2/kadai10-i21yassin$ ./mysysmain ""
mysystem:
retval = 00000000
system:
retval = 00000000

i21yassine@Virtual-PC001:~/Syspro2/kadai10-i21yassin$ ./mysysmain echo Hello!
使い方 : ./mysysmain コマンド文字列 

21yassine@Virtual-PC001:~/Syspro2/kadai10-i21yassin$ ./mysysmain "echo Hello!"
mysystem:
Hello!
retval = 00000000
system:
Hello!
retval = 00000000

i21yassine@Virtual-PC001:~/Syspro2/kadai10-i21yassin$ ./mysysmain "Error"
mysystem:
sh: 1: Error: not found
retval = 00007f00
system:
sh: 1: Error: not found
retval = 00007f00

i21yassine@Virtual-PC001:~/Syspro2/kadai10-i21yassin$ ./mysysmain "echo 1 && echo 2"
mysystem:
1
2
retval = 00000000
system:
1
2
retval = 00000000

i21yassine@Virtual-PC001:~/Syspro2/kadai10-i21yassin$ ./mysysmain "mkdir Doc"
mysystem:
retval = 00000000
system:
mkdir: ディレクトリ `Doc' を作成できません: ファイルが存在します
retval = 00000100

i21yassine@Virtual-PC001:~/Syspro2/kadai10-i21yassin$ ./mysysmain "rmdir Doc"
mysystem:
retval = 00000000
system:
rmdir: 'Doc' を削除できません: そのようなファイルやディレクトリはありません
retval = 00000100
*/
