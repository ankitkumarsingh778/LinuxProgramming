#include<pthread.h>
#include<iostream>
using namespace std;

bool should_exit_thread_immediately(){
    return false;
}

class ThreadExitException{
    public:
        ThreadExitException(void* return_value):
            thread_return_value(return_value){}

        void* DoThreadExit(){
            pthread_exit(thread_return_value);
        }

    private:
        void* thread_return_value;
};

void do_some_work(){
    int i=0;
    while(1){
        cout<<"i = "<<i<<endl;
        i++;
        if(should_exit_thread_immediately())
            throw ThreadExitException(NULL);
    }
}

void* thread_function(void *){
    try{
        do_some_work();
    } catch (ThreadExitException ex){
        cout<<"Thread exit exception caught.";  
        ex.DoThreadExit();
        
    }
    return NULL;
}

int main(){
    pthread_t thread;
    pthread_create(&thread,NULL,thread_function,NULL);
    pthread_join(thread,NULL);
    return 0;
}
