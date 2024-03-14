#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>


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
    printf("Scribo patri meo.\n");
}

// Fonction récursive : Exécute n fois 
// (le nombre d'aller-retours spécifiés)
// le scénario de la tragédie Pasolinienne
void Pasolini_n_time(int nbAllerRetours, pid_t pid, pid_t ppid){
    msgFilsRecu = 0;
    msgPereRecu = 0;
    signal(SIGUSR1, handler_parent); //Reloading
    	
    switch(pid = fork()){

        case ERROR:
            printf("La tragedie ne peut pas avoir lieu\n");
            exit(-1);
        break;

        case CHILD: 
            kill(ppid, SIGUSR1);
            while(!msgFilsRecu);
            printf("Mon papa a bien reçu ma lettre. Accepi ergo morior.\n");
        break;

        default:
            signal(SIGUSR1, handler_child);
            while(!msgPereRecu);
            kill(pid, SIGUSR1);
            printf("Il mio figlio e morto per la %d volta !\n", nbAllerRetours+1);
            printf("Non posso sopportare un tale dolore...\n ");
            if(nbAllerRetours > 0){
                Pasolini_n_time(nbAllerRetours-1, pid, ppid);
            }
    }
}

//A tribute to Pasolini.

int main(int argc, char* argv[])
{
    int nbAllerRetours = atoi(argv[1]);
    pid_t pid, ppid = getpid();
    Pasolini_n_time(nbAllerRetours-1,pid,ppid);
    
    return 0;
}

