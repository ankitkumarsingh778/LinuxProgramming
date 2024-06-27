#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

typedef int temp_file_handle;

temp_file_handle write_temp_file(char* buffer,size_t length){
  char temp_filename[]="/tmp/temp_file.XXXXXX";
  int fd=mkstemp(temp_filename);

  unlink(temp_filename);

  write(fd,&length,sizeof(length));

  write(fd,buffer,length);

  return fd;
}

char* read_temp_file(temp_file_handle temp_file,size_t* length){
  char* buffer;
  int fd=temp_file;

  lseek(fd,0,SEEK_SET);

  read(fd,length,sizeof(*length));

  buffer=(char*)malloc(*length);
  read(fd,buffer,*length);

  close(fd);
  return buffer;
}

int main(){
  char* data="Hello, World!";
  size_t length=strlen(data)+1;

  temp_file_handle temp_file=write_temp_file(data,length);
  printf("Wrote %zu bytes to a temporary file.\n",length);

  char* buffer=read_temp_file(temp_file,&length);
  printf("Read %zu bytes form the temporary file: %s\n",length,buffer);

  free(buffer);

  return 0;
}
