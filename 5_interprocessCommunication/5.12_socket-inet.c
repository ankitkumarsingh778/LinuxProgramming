#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/socket.h>
#include<string.h>

//Print the content of the homepage for the server's socket
//Return the message of success.

void get_home_page(int socket_fd){
    char buffer[10000];
    ssize_t number_characters_read;

    //send the HTTP GET command for the homepage
    sprintf(buffer,"GET /\n");
    write(socket_fd,buffer,strlen(buffer));

    //read from the socket. The call to read may not return all the data at one time,
    //so keep trying untill run out.
    while(1){
        number_characters_read=read(socket_fd,buffer,10000);
        if(number_characters_read==0)
            return;
        //write the data to standard output
        fwrite(buffer,sizeof(char),number_characters_read,stdout);
    }

}

int main(int argc,char* const argv[]){
    int socket_fd;
    struct sockaddr_in name;
    struct hostent* hostinfo;

    //create the socket
    socket_fd=socket(PF_INET,SOCK_STREAM,0);
    printf("%d\n",socket_fd);
    //store the server's name in the socket address
    name.sin_family=AF_INET;

    //convert from strings to numbers
    hostinfo=gethostbyname(argv[1]);
    if(hostinfo==NULL)
        return 1;
    else 
        name.sin_addr=*((struct in_addr*) hostinfo->h_addr);

    //web servers use port 80
    name.sin_port=htons(80);

    //connect to the web server
    if(connect(socket_fd,(struct sockaddr*)&name,sizeof(struct sockaddr_in))==1){
        perror("Connect");
        return 1;
    }

    //retrieve the server's homepage
    get_home_page(socket_fd);

    return 0;
}
