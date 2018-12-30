#include <iostream>

#include <sys/types.h>

#include <unistd.h>

using namespace std;

 

pid_t createProcess()

{

         pid_t id;

         if((id= fork()) == -1)

         {

                   cout<<"forkcreate process fail!"<<endl;

         }

         else

         {

                   return id;

         }

}

 

int main()

{

         pid_t p_id;

         int count;

         count= 4;

         if((p_id= createProcess()) > 0)

         {

                   cout<<"Currentparent process info:"<<endl;

                   count= count + 10;

                   cout<<"Parentprocess id:"<<getpid()<<" Child process id:"

                            <<p_id<<endl;

                   cout<<"Parentprocess count:"<<count<<endl;

         }

         else if(p_id == 0)

         {

                   cout<<"Currentchild process info:"<<endl;

                   count= count + 1;

                   cout<<"Childprocess id:"<<getpid()<<endl;

                   cout<<"Currentchild process count:"<<count<<endl;

         }

         cout<<"processend and count:"<<count<<endl;

         return 0;

}
