#include<fcntl.h>
#include<linux/cdrom.h>
#include<sys/ioctl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

int main(int argc,char* argv[]){
    //open a file descriptor to the device specified on a cmd line
    int fd=open(argv[1],O_RDONLY);
    //eject the cd rom
    ioctl(fd,CDROMEJECT);
    //close the file descriptor
    close(fd);

    return 0;
}

