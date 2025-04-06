#include<limits.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

//finds the path containing the currently running program exe.
//the path is placed into the BUFFER, which is of length LEN.
//returns number of char in the path or -1.
size_t get_executable_path(char* buffer,size_t len){
    char* path_end;
    printf("buffer: ",*buffer);     //deb
    //read the target of /proc/self/exe
    if(readlink("/proc/self/exe",buffer,len)<=0)
        return -1;
    //find the last occurence of a forward slash, the path sep
    path_end=strchr(buffer,'/');
    printf("path_end: ",path_end);      //deb
    if(path_end==NULL)
        return -1;
    //advances to the char past the last slash
    ++path_end;
    //obtain the dir containing the prog by trunc the path after the last slash
    printf("path_end: ",path_end);      //deb
    *path_end='\0';
    //the length of the path is the number of char up through the last slash
    printf("path_end: ",path_end);      //deb
    return (size_t) (path_end-buffer);

}

int main(){
    char path[PATH_MAX];
    get_executable_path(path, sizeof(path));
    printf("this program is in the directory %s\n",path);
    return 0;
}
