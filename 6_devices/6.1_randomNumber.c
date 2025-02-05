//program to generate random number using /dev/random
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>

//return a random between min and max inclusive. obtain randomness from /dev/random
int random_number(int min, int max){
    //store a file descriptor opened to /dev/random in a static variable.
    //this way we don't need to open the file everytime this function is called.
    static int dev_random_fd=-1;
    char* next_random_byte;
    int bytes_to_read;
    unsigned random_value;

    //make sure max>min
    assert(max>min);

    //if first time this function is called open a file descriptor to /dev/random
    if(dev_random_fd==-1){
        dev_random_fd=open("/dev/random",O_RDONLY);
        assert(dev_random_fd!=-1);
    }
    //read enough random bytes to fill an integer variable
    /**/printf("random_value_start: %d\n",random_value);
    next_random_byte=(char*) &random_value;
    bytes_to_read=sizeof(random_value);
    //loop until we have read enough bytes. Because /dev/random is filled from user
    //generated actions. the read may block or may return only a single random byte at a time
    do{
        int bytes_read;
        bytes_read=read(dev_random_fd,next_random_byte,bytes_to_read);
        bytes_to_read-=bytes_read;
        next_random_byte+=bytes_read;
    }while(bytes_to_read>0);

    /*deb*/printf("next_rn_b: %d\n",next_random_byte);
    printf("random_value: %d\n",random_value);
    //compute a random number in correct range.
    return min+(random_value%(max-min+1));
}

int main(int argc,char* argv[]){
    if(argc<3){
        fprintf(stderr,"Usage: %s <min> <max>\n",argv[0]);
    }
    int min=atoi(argv[1]);
    int max=atoi(argv[2]);

    for(int i=0;i<50;i++){
        int rndm=random_number(min,max);
        printf("Random number between %d and %d : %d\n",min,max,rndm);
    }


    return 0;
}
