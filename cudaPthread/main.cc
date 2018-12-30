#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

pthread_t thread[4];

void *thread1(void *)
{
	//do GPU task
	float time, start;
	start = clock();
	printf("thread1:I'm thread1\n");
	int i, n = 100;
	float *a, *b, *c;
	a = (float *)malloc(n * sizeof(float));
	b = (float *)malloc(n * sizeof(float));
	c = (float *)malloc(n * sizeof(float));
	for(i = 0; i < n; i++)
	{
		a[i] = 1.0f;
		b[i] = 1.0f;
	}
	for(i = 0; i < 100; i++)
	{
		vectorAdd(a, b, c, n);
	}
	printf("thread1:c[%d] = %f\n", 0, c[0]);
	free(a);
	free(b);
	free(c);
	time = clock() - start;
	printf("thread1: task was finished!\ncostTime1 : %f\n", time / CLOCKS_PER_SEC);
	pthread_exit(NULL);
}

void *thread2(void *)
{
	//do CPU task
	float time, start;
	start = clock();
	printf("thread2:I'm thread2\n");
	int i, j, k = 1;
	for(i = 0; i < 10000; i++)
	{
		for(j = 0; j < 10000; j++)
		{
//			printf("thread2:k = %d\n", k);
			k++;
		}
	}
	time  = clock() - start;
	printf("thread2: task was finished!\ncostTime2 : %f\n", time / CLOCKS_PER_SEC);
	pthread_exit(NULL);
}

void *thread3(void *)
{
//do CPU task
	float time, start;
	start = clock();
	printf("thread3:I'm thread3\n");
	int i, j, k = 1;
	for(i = 0; i < 1000; i++)
	{
		for(j = 0; j < 1000; j++)
		{
//			printf("thread3:k = %d\n", k);
			k++;
		}
	}
	time  = clock() - start;
	printf("thread3: task was finished!\ncostTime3 : %f\n", time / CLOCKS_PER_SEC);
	pthread_exit(NULL);
}

void *thread4(void *)
{
//do CPU task
	float time, start;
	start = clock();
	printf("thread4:I'm thread4\n");
	int i, j, k = 1;
	for(i = 0; i < 1000; i++)
	{
		for(j = 0; j < 1000; j++)
		{
//			printf("thread4:k = %d\n", k);
			k++;
		}
	}
	time  = clock() - start;
	printf("thread4: task was finished!\ncostTime4 : %f\n", time / CLOCKS_PER_SEC);
	pthread_exit(NULL);
}

void thread_create()
{
	int temp;
	memset(&thread, 0, sizeof(thread));
	if((temp = pthread_create(&thread[0], NULL, thread1, NULL)) != 0)
		printf("线程1创建失败！\n");
	else
		printf("线程1被创建！\n");
	if((temp = pthread_create(&thread[1], NULL, thread2, NULL)) != 0)
		printf("线程2创建失败！\n");
	else
		printf("线程2被创建！\n");
	if((temp = pthread_create(&thread[2], NULL, thread3, NULL)) != 0)
		printf("线程3创建失败！\n");
	else
		printf("线程3被创建！\n");
	if((temp = pthread_create(&thread[3], NULL, thread4, NULL)) != 0)
		printf("线程4创建失败！\n");
	else
		printf("线程4被创建！\n");
}
void thread_wait()
{
	
	if(thread[1] != 0)
	{
		pthread_join(thread[1], NULL);
		printf("线程2已经结束\n");
	}
	if(thread[2] != 0)
	{
		pthread_join(thread[2], NULL);
		printf("线程3已经结束\n");
	}
	if(thread[3] != 0)
	{
		pthread_join(thread[3], NULL);
		printf("线程4已经结束\n");
	}
	if(thread[0] != 0)
	{
		pthread_join(thread[0], NULL);
		printf("线程1已经结束\n");
	}
}

int main()
{
	float time, start;
	printf("我是主函数，正在创建线程\n");
	start = clock();
	thread_create();
	printf("我是主函数，正在等待线程完成任务\n");
	thread_wait();
	time = clock() - start;
	printf("costTime0 : %f\n", time / CLOCKS_PER_SEC);
	return 0;
}
