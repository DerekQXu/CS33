#include "csapp.h"
#include <pthread.h>
#include <stdio.h>
void *thread(void *vargp);

int main(int argc, const char* argv[])
{
	/*
 	* dynamically allocated vargp to take in an array
 	* ptr[0] = N, ptr[1] = T
 	*   N is used to keep track of layers
 	*   T is used to print thread #
 	*/
	int N = atoi(argv[1]);
	if (N == 1)
	{
		printf("Thread 0 done\n");
		exit(0);
	}
	void *ptr_l = malloc(2*sizeof(int));
	void *ptr_r = malloc(2*sizeof(int));
	*((int*)ptr_l) = N-1;
	*(((int*)ptr_l)+1) = 1;
	*((int*)ptr_r) = N-1;
	*(((int*)ptr_r)+1) = 2;
	if (N > 1){
		pthread_t tid1;
		pthread_t tid2;
		pthread_create(&tid1, NULL, thread, ptr_l);
		pthread_create(&tid2, NULL, thread, ptr_r);
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
	}
	free (ptr_l);
	free (ptr_r);
	printf("Thread 0 done\n");
	exit(0);
}

void *thread(void *vargp)
{
	void *ptr_l = malloc(2*sizeof(int));
	void *ptr_r = malloc(2*sizeof(int));
	*((int*)ptr_l) = *((int*)vargp) - 1;
	*(((int*)ptr_l)+1) = 2 * (*(((int*)vargp)+1)) + 1;
	*((int*)ptr_r) = *((int*)vargp) - 1;
	*(((int*)ptr_r)+1) = 2 * (*(((int*)vargp)+1)) + 2;

	if (*((int*)ptr_l)>0){
		pthread_t tid1;
		pthread_t tid2;
		pthread_create(&tid1, NULL, thread, ptr_l);
		pthread_create(&tid2, NULL, thread, ptr_r);
		pthread_join(tid1, NULL);
		pthread_join(tid2, NULL);
	}
	free (ptr_l);
	free (ptr_r);
	printf("Thread %d done\n", *(((int*)vargp)+1));
	return NULL;
}
