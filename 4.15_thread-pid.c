#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void* thread_function(void* arg){
    fprintf(stderr,"child thread pid is %d\n",(int)getpid());
    fprintf(stderr,"child thread id is %d\n",(int)pthread_self());
    // spin forever
    while(1);
    return NULL;
}

int main(){
    pthread_t thread;
    fprintf(stderr,"main thread pid is %d\n",(int)getpid());
    fprintf(stderr,"main thread is is %d\n",(int)pthread_self());
    pthread_create(&thread,NULL,&thread_function,NULL);
    //spin forever
    while(1);
    return 0;
}
