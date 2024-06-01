#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int spawn(char* program,char** arg_list){
  pid_t child_pid;

  child_pid=fork();

  if(child_pid!=0)
    return child_pid;
  else{
    execvp(program,arg_list);
    fprintf(stderr,"an error occured in execvp\n");
    abort();
  }
}


int main(){
	int child_status; 
char* arg_list[]={
    "ls",
    "-l",
    "/",
    NULL
  };
  spawn("ls",arg_list);

  //wait for the child process to complete (this code updated from here)
  wait(&child_status);
if(WIFEXITED(child_status))
	printf("The child process exited normally, with exit code %d\n",WEXITSTATUS(child_status));
else
	printf("The child process exited normally\n");

  printf("done with the main program\n");
  return 0;
}
