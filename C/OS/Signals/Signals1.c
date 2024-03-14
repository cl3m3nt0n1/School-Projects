#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define ERROR -1
#define CHILD 0

static int msgPereRecu = 0;
static int msgFilsRecu = 0;

void handler_parent(int s){
    msgFilsRecu = 1;
    printf("Il mio figlio mi ha scritto\n");
}

void handler_child(int s){
    msgPereRecu = 1;
}

//A tribute to Pasolini.

int main(int argc, char* argv[])
{
  signal(SIGUSR1, handler_child);
  pid_t pid;

  if((pid=fork())==ERROR){   // Check for errors
    printf("La tragedie ne peut pas avoir lieu\n");
    exit(1);
  }

  switch(pid){
      case CHILD : //
        sleep(1);
        printf("J'envoie un message a Papa\n");
        kill(getppid(), SIGUSR1);
        while(!msgPereRecu);
        printf("Mon papa a bien reçu ma lettre. Accepi ergo morior.\n");
      break;

      default :
        signal(SIGUSR1, handler_parent); // Expecting SIGUSR1 to be received
        while(!msgFilsRecu);
        kill(pid, SIGUSR1);
        wait(NULL);
        printf("Il mio figlio e morto !\nNon posso sopportare un tale dolore...\n ");
  }
  
  return 0;
}

