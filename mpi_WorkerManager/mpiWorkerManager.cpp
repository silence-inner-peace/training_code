#include <stdio.h>
#include "mpi.h"
#include <malloc.h>
#include <string.h>
#include <sys/stat.h>
#include <io.h>

void manager(int p);
void worker(int id);
int read_file_name();
int main(int argc , char* argv[])
{
	int id ;
	int p ;
	MPI_Init(&argc,&argv) ;
	MPI_Comm_rank(MPI_COMM_WORLD,&id);
	MPI_Comm_size(MPI_COMM_WORLD,&p);

	if (!id)
	{
		manager(p);
	}else{
		worker(id);
	}

	MPI_Finalize();
	return 0 ;
}

void manager(int p)
{
	int *power ;
	MPI_Status status ;
	char * filename ;

	char c ;
	FILE* fp ;
	int i ;
	int file_size ;
	int terminate ;
	terminate = 0 ;

	file_size = read_file_name() ;   // 读取文件个数
	filename = (char*)malloc(sizeof(char)*1024) ;
	power = (int*)malloc(sizeof(int)*2) ;
	memset(filename,0,sizeof(char)*1024) ;
	memset(power,0,sizeof(int)*2) ;

	fp = fopen("./files.txt","r");
	if (fp==NULL)
	{
		printf("Read file list error...") ;
	}

	i = 0 ;
	do 
	{
		printf("------------------------ I am manager ------------------------\n") ;
		MPI_Recv(power,2,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status) ;   // Manager 接收到Worker的请求信息
		printf("I received the request from process :%d\n",power[1]) ;

		/************ 接收到信息后开始读文件***************/
//fgetc从文件指针stream指向的文件中读取一个字符，读取一个字节后，光标位置后移一个字节
		c= fgetc(fp);
		if ((power[0]==0)&&(c!=EOF))
		{
			while((c!='\n')&&(c!=EOF)){
				filename[i] = c ;
				i++;
				c = fgetc(fp);
			}

			MPI_Send(filename,1024,MPI_CHAR,power[1],0,MPI_COMM_WORLD) ;
			i = 0 ;
			printf("I sent the file : %s to the process :%d\n",filename,power[1]) ;
		}

		/**************** 如果文件读完则发送读完的消息给worker **********************/
		if (c==EOF)
		{
			printf("Now no files need process , send terminate sign to process:%d\n",power[1]) ;
			filename[0] = '\n';
			MPI_Send(filename,1024,MPI_CHAR,power[1],0,MPI_COMM_WORLD) ;

		}

		/******************** worker处理完发送处理完的信号**********************/
		if (power[0]==1)
		{
            terminate++;
		}

		printf("------------------------------------------------\n\n\n");

	} while (terminate<(p-1));

	printf("------------------------ The all work have done ---------------------------\n") ;

	fclose(fp);

}

void worker(int id)
{
	 int *power ;
	 char *filename ;
	 MPI_Status status ;
	 power = (int*)malloc(sizeof(int)*2) ;
	 filename = (char*)malloc(sizeof(char)*1024) ;
	 memset(power,0,sizeof(int)*2) ;
	 memset(filename,0,sizeof(char)*1024) ; 

	 power[0] = 0 ;
	 power[1] = id ;

	 for (;;)
	 {
		 printf("-----------------------I am worker : %d -------------------------\n",power[1]) ;
		 MPI_Send(power,2,MPI_INT,0,id,MPI_COMM_WORLD) ;     // 给Manager发送请求信息
		 MPI_Recv(filename,1024,MPI_CHAR,0,0,MPI_COMM_WORLD,&status) ;
		 if(filename[0]!='\n')
		 {
			 printf("I received the file : %s from Manager.\n",filename) ;

		 }else{
			 printf("I have not received from Manager , shoud be terminated .\n") ;
			 power[0] = 1 ;
			 MPI_Send(power,2,MPI_INT,0,id,MPI_COMM_WORLD) ; 
			 break ;
		 }

		 printf("-----------------------------------------------------------------\n\n\n") ;
	 }

}

int read_file_name()
{
	return 10 ;
}
