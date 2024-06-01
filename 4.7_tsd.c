#include<stdio.h>
#include<pthread.h>
#include<malloc.h>

//log file pointer key
static pthread_key_t thread_log_key;

//write message to the log file for the current thread
void write_to_thread_log(const char* message){
	FILE* thread_log=(FILE*) pthread_getspecific(thread_log_key);
	fprintf(thread_log,"%s\n",message);
}

//close the log file pointer THREAD_LOG
void close_thread_log(void* thread_log){
	fclose((FILE*) thread_log);
}

void* thread_function(void* args){
	char thread_log_filename[20];
	FILE* thread_log;

	//generate the filename for this thread's log file
	sprintf(thread_log_filename,"thread%d.log",(int) pthread_self());
	//open the log file
	thread_log=fopen(thread_log_filename,"w");

    pthread_setspecific(thread_log_key,thread_log);

	write_to_thread_log("Thread starting. %d");
	//do work here.....
	
	return NULL;
}

int main(){
	int i;
	pthread_t threads[5];

    pthread_key_create(&thread_log_key,close_thread_log);

    //create threads to do the work
	for(i=0;i<5;++i){
		pthread_create(&threads[i],NULL,thread_function,NULL);
	}
  
    
	//wait  for all threads to finish
	for(i=0;i<5;++i){
		pthread_join(threads[i],NULL);
	}

	return 0;
}
