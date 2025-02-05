#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>

//wait for bin sem. Block until the sem value is positive, then dec by 1
int binary_semaphore_wait(int semid){
    struct sembuf operations[1];
    //use the first and only semaphore
    operations[0].sem_num=0;
    //dec by 1
    operations[0].sem_op=-1;
    //permit undo'ing
    operations[0].sem_flg=SEM_UNDO;

    return semop(semid,operations,1);
}

//post to a binary semaphore: increment its value by 1
int binary_semaphore_post(int semid){
    struct sembuf operations[1];
    //use the first and only semaphore
    operations[0].sem_num=0;
    //increment by 1
    operations[0].sem_op=1;
    //permit undo'ing
    operations[0].sem_flg=SEM_UNDO;

    return semop(semid,operations,1);
}
