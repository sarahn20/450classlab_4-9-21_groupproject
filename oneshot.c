#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
void sig_handler_parent(int signum){
  printf("Parent : Received a response signal from child \n");
}
void sig_handler_child(int signum){
  printf("Child : Received a signal from parent \n");
  sleep(1);
  kill(getppid(),SIGUSR1);
}
int main()
{
    /* Intializes random number generator */
    time_t t;
    srand((unsigned) time(&t));
    /* Random number from 5 to 20 */
    int parentHealth = (rand() % 15) + 5;
    printf("Parent health: %d\n", parentHealth);
    int numChildren = 0;
    pid_t pid;
    for(int i = 0; i<parentHealth; i++)
    {
        fork();
        signal(SIGUSR1,sig_handler_child); // Register signal handler
        printf("Child: waiting for signal\n");
        //pause();
    }
    
    if((pid=fork())<0)
    {
        printf("Fork Failed\n");
        exit(1);
    }
    /* Child Process */
    else if(pid==0)
    {
        numChildren++;
        signal(SIGUSR1,sig_handler_child); // Register signal handler
        printf("Child: waiting for signal\n");
        pause();
    }
    /* Parent Process */
    else
    {
        signal(SIGUSR1,sig_handler_parent); // Register signal handler
        sleep(1);
        printf("Parent: sending signal to Child\n");
        kill(pid,SIGUSR1);
        printf("Parent: waiting for response\n");
        pause();
    }
    
    return 0;
}
