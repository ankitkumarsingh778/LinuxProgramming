#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc, char* argv[]){
    const char* const filename=argv[1];
    int fd=open(filename,O_RDONLY);
    printf("in process %d, file descriptor %d is open to %s\n",(int)getpid(),(int)fd,filename);
    while(1);
    return 0;
}

