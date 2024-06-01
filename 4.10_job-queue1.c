#include<malloc.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

struct Job{
    int id;
    struct Job* next;
};

struct Job* job_queue;
pthread_mutex_t queue_mutex=PTHREAD_MUTEX_INITIALIZER;

void enqueueJob(int jobId){
    struct Job* newJob=(struct Job*)malloc(sizeof(struct Job));
    newJob->id=jobId;
    newJob->next=NULL;

   pthread_mutex_lock(&queue_mutex);

   if(job_queue==NULL){
        job_queue=newJob; 
    } else{
        struct Job* temp=job_queue;
        while(temp->next!=NULL){
            temp=temp->next; 
        }
        temp->next=newJob; 
    }

    pthread_mutex_unlock(&queue_mutex);
}

struct Job* dequeueJob(){
    pthread_mutex_lock(&queue_mutex);

    if(job_queue==NULL){
        pthread_mutex_unlock(&queue_mutex);
        return NULL; 
    }

    struct Job* currentJob=job_queue;
    job_queue=job_queue->next;

    pthread_mutex_unlock(&queue_mutex);

    return currentJob;
}

void* processJobs(void* arg){
    int threadId=*(int*)arg;

    printf("Thread working: %d",threadId);

    while(1){
        struct Job* currentJob=dequeueJob();

        if(currentJob == NULL){
            printf("Thread %d: No job available. Exiting.\n",threadId);
            pthread_exit(NULL); 
        }

        //process the job
        printf("Thread %d: Processing Job %d\n",threadId,currentJob->id);
        //add job processing logic
        //
        //free the allocated memory
        free(currentJob); 
    }
}

//process queue jobs until the queue is empty
/*void* thread_function(void* arg){
    while(job_queue!=NULL){
        struct Job* next_job=job_queue;

        job_queue=job_queue->next;

        process_job(next_job);

        free(next_job); 
    }
    return NULL;
}*/

int main(int argc,char* argv[]){
    const int numThreads=3; 
    pthread_t threads[numThreads];
    int threadIds[numThreads];

    //create threads
    for (int i=0;i<numThreads;++i){
        threadIds[i]=i+1;
        pthread_create(&threads[i],NULL,processJobs,(void*)&threadIds[i]);
    }
       //add some jobs to the queue
       for(int i=1;i<=10;++i){
            enqueueJob(i); 
       }
        
       //wait for threads to finish
       for(int i=0;i<numThreads;++i){
            pthread_join(threads[i],NULL); 
       } 

       printf("All threds have finished processing.\n");    
    return 0;
}

/* int status=pthread_create(&thread,NULL,thread_function,NULL);
    if(status!=0){
        fprintf(stderr,"Error creating thread: %d\n",status); 
        return 1; 
    }

    status=pthread_join(thread,NULL);
    if(status!=0){
        fprintf(stderr,"Error joining thread: %d\n",status);
        return 2; 
    }
*/
