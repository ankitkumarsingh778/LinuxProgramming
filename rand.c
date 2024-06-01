#include<stdio.h>
#include<time.h>

int main(){
    srand(time(NULL));
    int x=rand()%100;
    printf("%d",x);
}
