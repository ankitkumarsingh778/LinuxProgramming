#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

char* read_from_file(const char* filename, size_t length){
	char* buffer;
	int fd;
	ssize_t bytes_read;

	//allocate the buffer
	buffer=(char*) malloc (length);
	if(buffer==NULL)
		return NULL;

	//opening file
	fd=open(filename,O_RDONLY);
	if(fd==-1){
		free(buffer);
		return NULL;
	}

	//read data
	bytes_read=read(fd,buffer,length);
	if(bytes_read!=length){
		free(buffer);
		close(fd);
		return NULL;
	}

	close(fd);
	return buffer;
}

int main(int argc,char* argv[]){

	if(argc!=3){
		printf("Usage: %s filename length\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	int length=atoi(argv[2]);
	if(length<=0){
		printf("Invalid length: %s\n",argv[2]);
		exit(EXIT_FAILURE);
	}

	char* content=read_from_file(argv[1],length);

	if(content==NULL){
		printf("Error reading from file: %s\n",argv[1]);
		exit(EXIT_FAILURE);
	}

	printf("Content of file %s: \n%s\n",argv[1],content);
	free(content);
	return 0;
}
