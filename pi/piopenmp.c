#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<omp.h>
int main(int argc,char** argv){
    float time1, start;
    start = clock();
    long long int num_in_cycle=0;
    long long int num_point=1000000000;
    int thread_count;
    thread_count=strtol(argv[1],NULL,10);
//    printf("please input the number of point\n");
//    scanf("%lld",&num_point);

    srand(time(NULL));
    double x,y,distance_point;
    long long int i;
    #pragma omp parallel for num_threads(thread_count) default(none) \
        reduction(+:num_in_cycle) shared(num_point) private(i,x,y,distance_point)
    for( i=0;i<num_point;i++){
        x=(double)rand()/(double)RAND_MAX;
        y=(double)rand()/(double)RAND_MAX;
        distance_point=x*x+y*y;
        if(distance_point<=1){
            num_in_cycle++;
        }
    }
    double estimate_pi=(double)num_in_cycle/num_point*4;
    printf("the estimate value of pi is %lf\n",estimate_pi);
    time1 = clock() - start;
    printf("costTime: %f\n", time1 / CLOCKS_PER_SEC);
    return 0;

}
