#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<signal.h>
void sig_handler_parent(int signum){
  printf("Parent : Received a response signal from child \n");
}

void sig_handler_child(int signum){
  while(incrementer < num){
  printf("I am waiting for my brothers...\n");
  raise(signum);
  }
}

int main(){
  pid_t pid;
  if((pid=fork())<0){
    printf("Fork Failed\n");
    exit(1);
  }
  /* Parent Process */
  else if(pid > 0){
    signal(SIGUSR1,sig_handler_parent); // Register signal handler
    sleep(1);
    //https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx
    int lower = 5;
    int upper = 20;
    int num = (rand() % (upper - lower + 1) + lower);
    int incrementer = 0;
    printf("Parent: my number of hit points are: %d\n", num);
    kill(pid,SIGUSR1);
    while(incrementer < num){
        fork();
        incrementer++;
        sleep(1);
        kill(pid,SIGUSR1);
        //printf("Child: I am waiting for my brothers...\n");
        
        //printf("incrementer: %d", incrementer);
        
    }
    
    
    pause();

      //
  }
  /* Child Process */
  else{
    signal(SIGUSR1,sig_handler_child); // Register signal handler
    sleep(1);
    pause();
  }
  return 0;
}
