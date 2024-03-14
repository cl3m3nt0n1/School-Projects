#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

#define MSG_SIZE 256


struct mymsg_st // message declaration
{
    long mtype;
    char mtext[MSG_SIZE];
}mymsg;

int main(int argc, char const *argv[])
{
    int msg_id;
    int msg_type = 2;
    char calculation[MSG_SIZE];
    struct mymsg_st mymsg;
    key_t key = 0x1337;


    
    if(msg_id = msgget(key, IPC_CREAT | 0666)==-1){
        printf("Error with message queue : %d\n", errno);
        exit(EXIT_FAILURE);
    }

    mymsg.mtype = 1; //cf. enonce
    printf("Que souhaitez-vous calculer ?\n"); //Asking user
    scanf("%s", calculation);
    strcpy(mymsg.mtext, calculation); // Copying the calculation to the msg
    


    /*--------------- SENDING CALCULATION-------------*/
    if(msgsnd(msg_id, &mymsg, MSG_SIZE, 0) == -1){
        fprintf(stderr, "Erreur d'envoi du message\n");
        exit(EXIT_FAILURE);
    }
    else printf("Le message est envoye correctement !\n");

    /*--------------- WAITING FOR RESULT-------------*/
    if(msgrcv(msg_id, (struct mymsg_st*)&mymsg, MSG_SIZE, msg_type, 0) == -1)
        printf("Message recu avec erreur : %d\n",errno);
    else printf("= %s\n", mymsg.mtext); 

    exit(EXIT_SUCCESS);

    return 0;
}
