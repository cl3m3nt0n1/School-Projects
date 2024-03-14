#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

#define ERROR -1
#define CHILD 0

static int msgPereRecu = 0;
static int msgFils1recu = 0;
static int msgFils2Recu = 0;

void handler_child1(int sig){
    if(sig == SIGUSR2){
    	msgFils1recu = 1;
        printf("Riccetto : Scribo patri meo.\n");
    }
}

void handler_child2(int sig){
    if(sig == SIGUSR1){
    	msgFils2Recu = 1;
        printf("Edipo : Scribo patri meo.\n");
    }
}

//A tribute to Pasolini

int main (int argc, char* argv[]){
	
    signal(SIGUSR2, handler_child1);
    pid_t pid, pid2;
    
    switch(pid = fork()){

        case ERROR:
            printf("La tragedie ne peut pas avoir lieu\n");
            exit(-1);
        break;

        case CHILD: 
            while(!msgFils1recu);
            printf("Riccetto : Mon papa a bien reçu ma lettre. Accepi ergo morior\n");
            msgPereRecu = 1;
        break;

        default:
            signal(SIGUSR1, handler_child2);
            switch(pid2 = fork()){  //Child 2

                case ERROR:
                    printf("La tragedie ne peut toujours pas avoir lieu\n");
                    exit(-1);
                break;

                case CHILD: 
                    while(!msgFils2Recu);
                    printf("Edipo : Mon papa a bien reçu ma lettre. Accepi ergo morior\n");
                    kill(pid, SIGUSR2);
                break;

                default:
                    kill(pid2, SIGUSR1);
                    wait(NULL);
                    printf("I miei figli sono morti \n");
                    printf("Non posso sopportare un tale dolore...\n ");
            }
    }
    return 0;
}


