#include<stdio.h>
#include<sys/shm.h>
#include<sys/stat.h>
#include<errno.h>

int main(){
    int segment_id;
    char* shared_memory;
    struct shmid_ds shmbuffer;
    int segment_size;
    const int shared_segment_size=0x6400;

    //allocate a shared mem sement
    segment_id=shmget(IPC_PRIVATE,shared_segment_size,
                      IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    //ATTACH THE SHARED MEM SEGMENT
    shared_memory=(char*) shmat (segment_id,0,0);
    printf("shared memory attached at address %p\n",shared_memory);
    //segment size
    shmctl(segment_id,IPC_STAT,&shmbuffer);
    segment_size=shmbuffer.shm_segsz;
    printf("segment size: %d\n",segment_size);
    //write a string to the shared mem seg
    sprintf(shared_memory,"Hello, World.");
    //detach the  shared memory seg
    shmdt(shared_memory);
    
    //reattach shared mem at diff address
    shared_memory=(char*)shmat(segment_id,(void*)0x5000001,SHM_RND|SHM_RDONLY);
    printf("shared memory reattached at address %p\n",shared_memory);
    printf("%s\n",shared_memory);
   // sprintf(shared_memory,"Hello again");
    printf("value of error: %d",errno);
    //detach the shared mem seg
    shmdt(shared_memory);

    //deallocate the shared mem seg
    shmctl(segment_id,IPC_RMID,0);

    return 0;
}
