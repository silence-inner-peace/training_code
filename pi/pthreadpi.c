#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

pthread_mutex_t mutexsum;
#define thread_count   4
double sum;

void* start_thread(void *rank);

void* start_thread(void *rank)
{
    long my_rank = rank;
    double factor;
    long long i ;
    long long my_n = 80000000/thread_count ;
    long long my_first_i = my_n*my_rank;
    long long my_last_i = my_first_i + my_n;
    double my_sum = 0.0;

    if(my_first_i % 2 == 0)
        factor = 1.0;
    else
        factor = -1.0;

    for(i = my_first_i;i<my_last_i;i++,factor = -factor)
    {
        my_sum += factor / (2*i+1);
    }

    //pthread_mutex_lock (&mutexsum);//为什么不互斥，结果也没有出问题呢？？？
    sum  += my_sum;
    //pthread_mutex_unlock (&mutexsum);
    return NULL;
}


int main(void)
{
    long thread;
    pthread_t thread_handles[thread_count];
    //thread_handles = malloc(thread_count*sizeof(pthread_t));

    struct timeval tpstart,tpend;
    float timeuse;
    gettimeofday(&tpstart,NULL);

    pthread_mutex_init(&mutexsum, NULL);

    for(thread=0;thread<thread_count;thread++)
    {
      /* Each thread works on a different set of data.
       * The offset is specified by 'i'. The size of
       * the data for each thread is indicated by VECLEN.
       */
        pthread_create(&thread_handles[thread], NULL, start_thread, (void *)thread); 
    }

    printf("main function\n");

    /* Wait on the other threads */
    for(thread=0;thread<thread_count;thread++) 
    {
        pthread_join(thread_handles[thread], NULL);
    }
    gettimeofday(&tpend,NULL);
    timeuse=1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
    timeuse/=1000000;
    printf("sum  is:%lf,and run time is: %fs \n",4*sum,timeuse);

    pthread_mutex_destroy(&mutexsum);
    pthread_exit(NULL);

    return 0;
}
