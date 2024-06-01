#include<stdio.h>
#include<pthread.h>

void* thread_function(void* thread_arg){
  int i=300;
  while(i>0){
    fputc('x',stderr);
    i--;
  }
  return NULL;
}

int main(){
  pthread_attr_t attr;
  pthread_t thread;

  pthread_attr_init (&attr);
  pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
  pthread_create(&thread,&attr,&thread_function,NULL);

  int i=300;
  //    pthread_join(thread,NULL);
  while(i>0){
      fputc('o',stderr);
      i--;
  }
  return 0;
}
