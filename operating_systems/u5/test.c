#include <unistd.h>

char * command_and_parm_array_with_path[] = {"/bin/ls","/bin/ls","-l","/",0};

char *command_and_parm_arry[] = {"ls","ls","-l","/",0};

char * environment[] = {"HOME=/home/het","PATH=/bin:/usr/bin:/home/het",0};

int main(int argc, char **argv, char **envp)

{
 char c;


 if(!fork())
  execlp("ls","ls","-l","/",0); // die Argumente als Liste ohne Pfad

}