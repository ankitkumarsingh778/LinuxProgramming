#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

//print argument list, one arg to a line, of the process
//given by pid

void print_process_arg_list(pid_t pid){
    int fd;
    char filename[24];
    char arg_list[1024];
    size_t length;
    char* next_arg;

    //generate the name of the cmdline file for the process.
    snprintf(filename,sizeof(filename),"/proc/%d/cmdline",(int) pid);
    //read the contents of the file
    fd=open(filename,O_RDONLY);
    length=read(fd,arg_list,sizeof(arg_list));
    close(fd);

    //read does not nul terminate the buffer. so....
    arg_list[length]='\0';

    //loop over the arguments, separated by NULs
    next_arg=arg_list;
    while(next_arg<arg_list+length){
    //each arg is nul terminated so it is like string
        printf("%s\n",next_arg);
        //advance to the next argument. 
        //since each argument is NUL terminated, so strlen counts the length of the next argument, rather than list
        next_arg+=strlen(next_arg)+1;
    }

}

int main(int argc, char* argv[]){
    pid_t pid=(pid_t) atoi (argv[1]);
    print_process_arg_list(pid);

    return 0;
}
