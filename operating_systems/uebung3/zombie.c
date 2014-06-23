#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
  pid_t pid;

  //create child
  pid=fork();

  if(pid == 0){
    //child exists and becomes a zombie
    exit(0);
  }

  sleep(90);
  printf("Exiting....\n");
  return 0;
}

/*
show processes and filter after program name "zombie":
hkernbach@kernbook~/FH/BS/uebung3$ ps x|grep zombi
410 s000  S+     0:00.00 ./zombie
6411 s000  Z+     0:00.00 (zombie) <--- HIER Zombie-Prozess (Z+)
6420 s001  S+     0:00.00 grep --color=always zombie 
*/
