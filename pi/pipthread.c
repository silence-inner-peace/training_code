#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <sched.h> 
#include <unistd.h> 
int thread_count;
long long int num_in_circle,n;
pthread_mutex_t mutex;
void* compute_pi(void* rank);
int main(int argc,char* argv[]){
    float time, start;
    start = clock();
    long    thread;
    pthread_t* thread_handles;
    thread_count=strtol(argv[1],NULL,10);
//    printf("please input the number of point\n");
//    scanf("%lld",&n);
    n=1000000000;
    thread_handles=(pthread_t*)malloc(thread_count*sizeof(pthread_t));
    pthread_mutex_init(&mutex,NULL);
    for(thread=0;thread<thread_count;thread++){
        //创建线程
        /*
        int pthread_create(
            pthread_t*    thread_p  //out
            const    pthread_attr_t*    attr_p
            void*    (*start_routine)(void*)    //in
            void*    arg_p    //in        
        )
        第一个参数是一个指针，指向对应的pthread_t对象。注意，pthread_t对象不是pthread_create函数分配的，必须在调用pthread_create函数前就为pthread_t
        对象分配内存空间。第二个参数不用，所以只是函数调用时把NULL传递参数。第三个参数表示该线程将要运行的函数；最后一个参数也是一个指针，指向传给函数start_routine的参数
        */


        pthread_create(&thread_handles[thread],NULL,compute_pi,(void*)thread);    
    }
    //停止线程
    /*
    int pthread_join(
        pthread_t    thread    /in
        void**    ret_val_p    /out    
    ）
    第二个参数可以接收任意由pthread_t对象所关联的那个线程产生的返回值。
    */
    for(thread=0;thread<thread_count;thread++){
        pthread_join(thread_handles[thread],NULL);    
    }
    pthread_mutex_destroy(&mutex);
    double pi=4*(double)num_in_circle/(double)n;
    printf("the esitimate value of pi is %lf\n",pi);
    time = clock() - start;
    printf("costTime: %f\n", time / CLOCKS_PER_SEC);
}
void* compute_pi(void* rank){
/*
int ranktemp=*(int*)rank;
cpu_set_t mask;
CPU_ZERO(&mask);
CPU_SET(ranktemp%2,&mask);
sched_setaffinity(0, sizeof(mask), &mask); 
*/
    long long int local_n;
    local_n=n/thread_count;
    double x,y,distance_squared;
    for(long long int i=0;i<local_n;i++){
        x=(double)rand()/(double)RAND_MAX;
        y=(double)rand()/(double)RAND_MAX;
        distance_squared=x*x+y*y;
        if(distance_squared<=1){
            pthread_mutex_lock(&mutex);
            num_in_circle++;
            pthread_mutex_unlock(&mutex);    
        }
    }
    return NULL;
}
