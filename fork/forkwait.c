#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int main(void){
    pid_t fpid = fork(), pid;

    if(fpid < 0){
        perror("fork error");
        exit(EXIT_FAILURE);
    }else if(fpid == 0){
        sleep(5);
        exit(5);
    }else{
        int stat;

        for(;;){
            pid = waitpid(fpid, &stat, WNOHANG);
            if(pid > 0){
                break;
            }else{
                printf("wait_child_proc ... \n");
                sleep(1);
            }
        }

        if(WIFEXITED(stat)){
            printf("child_proc(%d): exit_code: %d\n", pid, WEXITSTATUS(stat));
        }
    }
    return 0;
}

