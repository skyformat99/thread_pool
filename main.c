#include "thread_pool.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define ERR_EXIT(m)\
        do\
	{\
	    perror(m);\
            exit(EXIT_FAILURE);\
        }while(0)
void* mytask(void *arg)
{
	printf("thread 0x%0x is working on task %d\n", (int)pthread_self(), *(int *)arg);
	sleep(1);
	free(arg);
	return NULL;
}

int main(void)
{
	threadpool_t pool;
	threadpool_init(&pool, 3);

	int i;
	for(i=0; i<10; ++i)
	{
		int *arg=(int *)malloc(sizeof(int));
		if(arg==NULL)
			ERR_EXIT("malloc");
		*arg=i;
		threadpool_add_task(&pool, mytask, arg);
	}
	
	//sleep(15);
	threadpool_destroy(&pool);
	return 0;
}
