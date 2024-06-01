#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//array of balance, indexed by account no.
float *account_balances;

struct thread_args{
  int from_acct;
  int to_acct;
  double amount;
};

//process for transaction
int process_transaction(int from_acct,int to_acct,float dollars){
	int old_cancel_state;

	//check the balance in From_Acct
	if(account_balances[from_acct]<dollars)
		return 1;
	
	//begin critical section
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,&old_cancel_state);

	//move the money
	account_balances[to_acct]+=dollars;
	account_balances[from_acct]-=dollars;

	//end critical section
	pthread_setcancelstate(old_cancel_state,NULL);

	return 0;
}

int main(){
  struct thread_args args1={1,2,100.0};
  struct thread_args args2={3,4,200.0};
  struct thread_args args3={5,6,300.0};
  
  //init acct balance
   account_balances=malloc(sizeof(float)*10);

  for(int i=0;i<10;i++){
    account_balances[i]=1000.0; //init balance
  }

  //some threads to perform transactions
  pthread_t t1,t2,t3;
  //thread1 to transfer 100 from acc1 to acct2
  pthread_create(&t1,NULL,(void*)process_transaction,&args1);
  pthread_create(&t2,NULL,(void*)process_transaction,&args2);
  pthread_create(&t3,NULL,(void*)process_transaction,&args3);

  //waiting for threads to finish
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);

  //print the final acct. balances
  for(int i=0;i<10;i++){
    printf("Account %d: %.2f\n",i,account_balances[i]);
  }

  //free memory
  free(account_balances);
  return 0;
}
