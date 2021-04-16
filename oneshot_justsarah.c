#include<stdio.h>
#include<signal.h>
#include<unistd.h>

int n[100];
int i = 0;

void sig_handler_parent(int signum){

    //Return type of the handler function should be void
    
    while(i >= 0){
        printf("\nParent: Killing child %d \n", n[i]);
        kill(n[i], SIGKILL);
    }

    //kill children
    signal(SIGINT, SIG_DFL);
}

void sig_handler_child(int signum){

    //Return type of the handler function should be void
    printf("\nChild: Insider handler function\n");
}

int main(){
    while(1){
        int pid = fork();
        if(pid == 0){
            signal(SIGUSR1, sig_handler_child); //Register signal handler
            printf("\nChild created...my pid is %d\n", getpid());
            pause(); //child should wait for a signal
            printf("\nChild is dying!!!!!!\n");
        }
        else{
            sleep(2);
            signal(SIGINT, sig_handler_parent);
            n[i] = pid;
            i++;
            printf("\nIn parent\n");
            //kill(pid, SIGUSR1);
            //printf("\nParent: waiting for response\n");
            //pause();

        }

    }
    
}
