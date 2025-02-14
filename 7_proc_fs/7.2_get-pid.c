#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>

//returns the process id of the calling process, as from /proc/self

pid_t get_pid_from_proc_self(){
    char target[32];
    int pid;
    //read the target of the symbolic link
    readlink("/proc/self",target,sizeof(target));
    //the target is a directory named for the process ID.
    sscanf(target,"%d",&pid);
    return (pid_t)pid;
}

int main(){
    printf("/proc/self report process id %d\n",(int)get_pid_from_proc_self());
    printf("getpid() report process id %d \n",(int)getpid());
    
    int key;
        printf("Press any key to exit\n");
}
