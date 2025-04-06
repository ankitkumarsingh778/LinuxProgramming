#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

//prints the environment, one environment variable to a line, of the process given by pid
void print_process_environment(pid_t pid){
    int fd;
    char filename[24];
    char environment[8192];
    size_t length;
    char* next_var;

    //generate the environ file for the process.
    snprintf(filename,sizeof(filename),"/proc/%d/environ",(int)pid);
    //read the contents of the file
    fd=open(filename,O_RDONLY);
    length=read(fd,environment,sizeof(environment));
    close(fd);
    //read does not NUL-terminate the buffer, so do it here
    environment[length]='\0';
    //loop over variables. variables are separated by NULs
    next_var=environment;
    while(next_var<environment+length){
        //print the variables. each is nul terminated, so just treat it like an ordinary string.
        printf("%s\n",next_var);
        //advance to the next variable.
        //since each variable is nul terminated strlen counts the length of the next variable, not the whole list
        next_var+=strlen(next_var)+1;

    }

}

int main(int argc,char* argv[]){
    pid_t pid=(pid_t) atoi (argv[1]);
    print_process_environment(pid);
    return 0;
}


