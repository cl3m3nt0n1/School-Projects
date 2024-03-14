#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/msg.h>

#define MSG_SIZE 256

struct my_msg_st {
long int my_msg_type;
char some_text[MSG_SIZE];
};

int main(int argc, char const *argv[])
{
    int msg_id;
    struct my_msg_st mymsg;
    char calculation[MSG_SIZE];
    int firstOp, secOp, result;
    char operator;
    key_t key = 0x1337;
    int msg_type = 0;

    msg_id = msgget((key_t)key, 0666 | IPC_CREAT);

    if(msg_id == -1){
        fprintf(stderr, "msgget failed : %d", errno);
        exit(EXIT_FAILURE);
    }

    if(msgrcv(msg_id, (struct mymsg*)&mymsg, MSG_SIZE, msg_type, 0) == -1){
        fprintf(stderr, "msgget failed : %d\n", errno);
        exit(EXIT_FAILURE);            
    }
    else{
        sscanf(mymsg.some_text, "%d%c%d", &firstOp, &operator, &secOp);
        switch (operator)
        {
        case '+':
            result = firstOp + secOp;
            break;
        case '*':
            result = firstOp * secOp;
            break;
        case '-':
            result = firstOp - secOp;
            break;
        case '/':
            result = firstOp / secOp;
            break;
        
        default:
            printf("Operateur invalide...\n");
            break;
        }

        sprintf(calculation, "%d", result);
        mymsg.my_msg_type = 2;
        strcpy(mymsg.some_text, calculation);

        //Sending the result
        if(msgsnd(msg_id, (struct mymsg*)&mymsg, MSG_SIZE, 0)== -1){
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        else printf("Le message est parti ! Resultat : %s\n", mymsg.some_text);
    }

    if(msgctl(msg_id, IPC_RMID, 0 ) == -1){
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);

    return 0;
}
