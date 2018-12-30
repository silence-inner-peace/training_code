#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
using namespace std;
 
#define NUM_THREADS     5


struct thread_data{
   int  msgLength;
   int *message;
};
 
void *PrintHello(void *threadarg)
{
    float time, start;
    start = clock();
    struct thread_data &my_data = *((struct thread_data *) threadarg);
 
    cout << "Thread ID : " << my_data.msgLength <<endl;
   for (int i = 0; i < my_data.msgLength; ++i)
   {
        cout << my_data.message[i] << ",";
   }
   cout<<endl;
   int i = 10000;
   int k = 0;
   while(i - (my_data.msgLength) * 1000 > k)
   {
        k++;
   }
    time = clock() - start;
    printf("thread%d: task was finished!costTime%d : %f\n", my_data.msgLength, my_data.msgLength, time / CLOCKS_PER_SEC);
    pthread_exit(NULL);
}

void open()
{
   pthread_t threads[NUM_THREADS];
   struct thread_data td[NUM_THREADS];
   int rc;
   int i;
   int j;
   for( i=0; i < NUM_THREADS; i++ ){
      cout <<"main() : creating thread, " << i << endl;
      td[i].msgLength = i;
      td[i].message = new int[i];
      for(j = 0;j< i;j++)
      {
        (td[i].message)[j] = j;
      }
      rc = pthread_create(&threads[i], NULL,
                          PrintHello, (void *)&td[i]);
      if (rc){
         cout << "Error:unable to create thread," << rc << endl;
         exit(-1);
      }
   }
   pthread_exit(NULL);
}

int main ()
{
    open();
}

