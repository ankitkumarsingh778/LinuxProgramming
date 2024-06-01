#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

sig_atomic_t sig_usr1_count=0;

void handler(int signal_number){
	sig_usr1_count++;
}

int main(){
	struct sigaction sa;
	memset (&sa,0,sizeof(sa));
	sa.sa_handler=&handler;
	sigaction(SIGUSR1,&sa,NULL);

	// Lengthy stuff: loop for a long time and print the current count
int i;
for (i = 0; i < 1000000000; i++) {
    printf("Current count: %d\n", i);
}
// End of lengthy stuff

	printf("SIGUSR1 was raised %d times\n",sig_usr1_count);

	return 0;
}
