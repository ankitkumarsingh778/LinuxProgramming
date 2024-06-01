#include<stdio.h>
#include<pthread.h>

int thread_flag;
pthread_mutex_t thread_flag_mutex;

void initializer_flag(){
    pthread_mutex_init(&thread_flag_mutex,NULL);
    thread_flag=0;
}

void* thread_function(void* thread_arg){
    while(1){
        int flag_is_set;

        pthread_mutex_lock(&thread_flag_mutex);
        flag_is_set=thread_flag;

        pthread_mutex_unlock(&thread_flag_mutex);

        if(flag_is_set)
           do_work(thread_arg);
       //else don't do anything loop again, 
    }
    return NULL;
}

void do_work(int thread_arg){
   for(int i=0;i<10;i++){
    printf("Flag is set: %d, for thread Id: %d\n",thread_flag,thread_arg); 
   } 
}

void set_thread_flag(int flag_value){
    pthread_mutex_lock(&thread_flag_mutex);
    thread_flag=flag_value;
    pthread_mutex_unlock(&thread_flag_mutex);
}

int main(int argc,char* argv[]){
    const int numThreads=3;
    pthread_t threads[numThreads]; 
    int threadIds[numThreads];
     
    //creating threads
    for(int i=0;i<numThreads;++i){
        threadIds[i]=+1;
        pthread_create(&threads[i],NULL,thread_function,(void*)&threadIds[i]); 
    }

    for(int i=0;i<numThreads;++i){
        thread[i].initializer_flag(); 
    } 

    //wait for threads to finish
    for(int i=0;i<numThreads;++i){
        pthread_join(threads[i],NULL); 
    }

    return 0;
}

