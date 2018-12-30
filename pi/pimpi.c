#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<mpi.h>
void read_num(long long int *num_point,int my_rank,MPI_Comm comm);
void compute_pi(long long int num_point,long long int* num_in_cycle,long long int* local_num_point,int comm_sz,long long int *total_num_in_cycle,MPI_Comm comm,int my_rank);
int main(int argc,char** argv){
    float time, start;
    start = clock();
    long long int num_in_cycle,num_point,total_num_in_cycle,local_num_point;
    int my_rank,comm_sz;
    MPI_Comm comm;
    MPI_Init(NULL,NULL);//初始化
    comm=MPI_COMM_WORLD;
    MPI_Comm_size(comm,&comm_sz);//得到进程总数
    MPI_Comm_rank(comm,&my_rank);//得到进程编号
    read_num(&num_point,my_rank,comm);//读取输入数据
    compute_pi(num_point,&num_in_cycle,&local_num_point,comm_sz,&total_num_in_cycle,comm,my_rank);
    MPI_Finalize();
    time = clock() - start;
    printf("costTime: %f\n", time / CLOCKS_PER_SEC);

    return 0;
}
void read_num(long long int* num_point,int my_rank,MPI_Comm comm){
    if(my_rank==0){
//        printf("please input num in sqaure \n");
//        scanf("%lld",num_point);
	*num_point = 1000000000;
    }
    /*
    广播函数
    int MPI_Bcast(
        void*    data_p //in/out
        int    count  //in
        MPI_Datatype    datatype //in
        int    source_proc  //in
        MPI_Comm    comm  //in    
    )
    */
    MPI_Bcast(num_point,1,MPI_LONG_LONG,0,comm);

}
void compute_pi(long long int num_point,long long int* num_in_cycle,long long int* local_num_point,int comm_sz,long long int *total_num_in_cycle,MPI_Comm comm,int my_rank){
    *num_in_cycle=0;
    *local_num_point=num_point/comm_sz;
    double x,y,distance_squared; 
    srand(time(NULL));
    for(long long int i=0;i< *local_num_point;i++){     
        x=(double)rand()/(double)RAND_MAX;
        x=x*2-1;
        y=(double)rand()/(double)RAND_MAX;
        y=y*2-1;
        distance_squared=x*x+y*y;
        if(distance_squared<=1)
        *num_in_cycle=*num_in_cycle+1;
    }
    /*
    全局函数
    MPI_Reduce(
        void*    input_data_p    //in
        void*    output_data_p    //out
        int    count        //in
        MPI_Datatype    datatype     //in
        MPI_Op    oprtator    //in
        int    dest_process    //in
        MPI_Comm    comm    //in
    )    
    */
      MPI_Reduce(num_in_cycle,total_num_in_cycle,1,MPI_LONG_LONG,MPI_SUM,0,comm);
    if(my_rank==0){
        double pi=(double)*total_num_in_cycle/(double)num_point*4;
        printf("the estimate value of pi is %lf\n",pi);
    }
}
