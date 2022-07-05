#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

pthread_t thread1, thread2, thread3; 
pthread_mutex_t mutex;
pthread_mutexattr_t mutexattr;

int policy = SCHED_RR;
int priority = 10;
struct sched_param param;

void *thread1handler() 
{
	pthread_mutex_lock(&mutex);
	printf("thread 1 created\n");
    for(int i = 0; i < 1000000000; i++) {}
	pthread_mutex_unlock(&mutex);
	printf("thread 1 finished\n");
}

void *thread2handler() 
{
	pthread_mutex_lock(&mutex);
	printf("thread 2 created\n");
    for(int i = 0; i < 1000000000; i++) {}
	pthread_mutex_unlock(&mutex);
	printf("thread 2 finished\n");
}

void *thread3handler() 
{
	pthread_mutex_lock(&mutex);
	printf("thread 3 created\n");
    for(int i = 0; i < 1000000000; i++) {}
	pthread_mutex_unlock(&mutex);
	printf("thread 3 finished\n");
}

int main()
{
	//Create mutex and initialize it.
	pthread_mutexattr_setprotocol(&mutexattr,PTHREAD_PRIO_INHERIT);
	pthread_mutex_init(&mutex,&mutexattr);
    
    // Set priority and intiialize
	int minpriority = sched_get_priority_min(policy);
	param.sched_priority = minpriority;
	pthread_create(&thread1, NULL, thread1handler, NULL);     
	pthread_setschedparam(thread1,policy,&param);                      
	
	// Set priority and intiialize
	int maxpriority = sched_get_priority_max(policy);
	param.sched_priority = maxpriority;
	pthread_create(&thread3, NULL, thread3handler, NULL);     
	pthread_setschedparam(thread3,policy,&param);                      
	
	// Set priority and intiialize
	param.sched_priority = priority;
	pthread_create(&thread2, NULL, thread2handler, NULL);     
	pthread_setschedparam(thread2,policy,&param);                      
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	
	return 0;
}
