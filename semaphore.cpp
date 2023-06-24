#include<stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <pthread.h>
#include <string.h>
#include <semaphore.h>
#include <iostream>
using namespace std;
sem_t sem1;
void* Teacher_assistant(void*arg){	
	sem_wait(&sem1);
	cout<<"evaluated"<<endl;
	sem_post(&sem1);
	pthread_exit(NULL);
}

int main(){
cout<<"Enter number of students for evaluation"<<endl;
int no_of_stud;
cin>>no_of_stud;
pthread_t my_thread[no_of_stud];
sem_init(&sem1,0,1);
void*ret_join;
for(int i=0;i<no_of_stud;i++){
	int ret=pthread_create(&my_thread[i],NULL,&Teacher_assistant,NULL);
}

for(int i=0;i<no_of_stud;i++){
	int ret=pthread_join(my_thread[i],&ret_join);
	if(ret!=0){
		perror("Pthread_join failed\n");
		exit(EXIT_FAILURE);
	}
}
sem_destroy(&sem1);
}
