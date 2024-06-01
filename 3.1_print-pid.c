#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(int argc,char** argv[]){
	pid_t pid=getpid();
	pid_t ppid=getppid();
	printf("The process id is: %d\n",pid);
	printf("The parent process id is:  %d\n",ppid);

	return 0;
}
