#include<fcntl.h>
#include<stdio.h>
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>

char* read_file(const char* filename,size_t* length){
	int  fd;
	struct stat file_info;
	char* buffer;

	fd=open(filename,O_RDONLY);

	fstat(fd,&file_info);
	*length=file_info.st_size;

	if(!S_ISREG(file_info.st_mode)){
		close(fd);
		return NULL;
	}

	buffer=(char*) malloc(*length);
	read(fd,buffer,*length);

	close(fd);
	return buffer;
}

int main() {
  size_t length;
  char* buffer = read_file(argv[1], &length);
  if (buffer == NULL) {
    printf("Error reading file.\n");
    return 1;
  }
  printf("File size: %zu bytes\n", length);
  printf("File contents: %s\n", buffer);
  free(buffer);
  return 0;
}


/*int main(int argc,char* argv[]){
  char* filename=argv[1];
  size_t length=(size_t) atoi (argv[2]);
	read_file(filename,&length);
	return 0;
	}*/
