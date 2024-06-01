#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NUM_THREADS 3

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;

int shared_data=0;

void* thread_function(void* thread_id){
    long tid=(long)thread_id;

    printf("Thread %ld is performing some work...\n",tid);

    pthread_mutex_lock(&mutex);
    shared_data++;

    while(shared_data < 5){
        printf("Thread %ld is waiting....\n",tid);
        pthread_cond_wait(&condition,&mutex); 
    }

    printf("Thread %ld resumes work as condition is met. Shared data: %d\n",tid,shared_data);

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(){
    pthread_t threads[NUM_THREADS];
    long t;

    for(t=0;t<NUM_THREADS;t++){
        if(pthread_create(&threads[t],NULL,thread_function,(void*)t)!=0){
            fprintf(stderr,"Error creating thread %ld\n",t);
            exit(EXIT_FAILURE); 
        } 
    }
    sleep(1);

    pthread_mutex_lock(&mutex);
    shared_data=5;
    printf("Main thread signals condition change. Shared data: %d\n",shared_data);
    pthread_cond_broadcast(&condition);
    pthread_mutex_unlock(&mutex);

    for(t=0;t<NUM_THREADS;t++){
        pthread_join(threads[t],NULL); 
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

    return 0;
}
