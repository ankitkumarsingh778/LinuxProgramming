#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

//write count copies of message to stream, pausing for a while between each 
void writer(const char* message, int count,FILE* stream){
    for(;count>0;--count){
        //write the message to the stream, and send it off immediately.
        fprintf(stream,"%s\n",message);
        fflush(stream);
        //snooze a while
        sleep(1); 
    }
}

//read random strings from the stream as long as possible
void reader(FILE* stream){
    char buffer[1024];
    //read until eof
    while(!feof(stream) && !ferror(stream) && fgets(buffer,sizeof(buffer),stream) != NULL)
        fputs(buffer,stdout);
}

int main(){
    int fds[2];
    pid_t pid;

    //create a pipe. FILE descriptors for the two ends of the pipe are placed in fds
    pipe(fds);
    //fork a child process
    pid = fork();
    if(pid==(pid_t) 0){
        FILE* stream;
        //this is the child process. close our copy of the write end of the file descriptor
        close(fds[1]);
        //convert the read file descriptor to a FILE object, and read from it
        stream=fdopen(fds[0],"r");
        reader(stream);
        close(fds[1]); 
    }else{
        //this is the parent process.
        FILE* stream;
        //close our copy of the read end of the file descriptor
        close(fds[0]);
        //convert the write file descriptor to a FILE object, and write to it
        stream=fdopen(fds[1],"w");
        writer("Hello, world.",5,stream);
        close(fds[1]); 
    }

    return 0;
}
