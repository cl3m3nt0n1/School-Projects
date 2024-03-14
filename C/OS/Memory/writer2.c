#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "libbmp.c"
#include "libbmp.h"
#include <string.h>
#include <time.h>

// void shm_write_string(char* destination, char* msg, int msg_size,size_t memory_size)
// {
//     for(int i = 0 ; i < msg_size ; i++)
//         strncpy(destination, msg[i], memory_size);
// }


// Trying to dop ints to memory instead of chars

int main(int argc, char  *argv[])
{
    int segment_id; 
    int* shared_memory;
    //struct shmid_ds shmbuffer;
    int segment_size;
    double shared_segment_size = 0xFFFF;
    key_t key = 0x1337;
    int N = 4;
    int valeur[65536];
    int longueur, hauteur;

    srand(time(NULL));

    /*------------------ASK USER-------------------*/
    printf("Longueur de l'image ? : ");
    scanf("%d", &longueur);
    printf("\nHauteur de l'image ? : ");
    scanf("%d", &hauteur);
    printf("\n");

    int img_size = longueur*hauteur;
    

    /*-----------SHARED MEMORY CREATION------------*/

    // Shared memory segment allocation
    segment_id = shmget (key, (size_t)shared_segment_size,
                       IPC_CREAT | 0666);
    
    if(segment_id == -1){
        perror("shmget()");
        exit(-1);
    }
    else{
        printf("id segment : %d\n", segment_id);

        // Shared memory attachement
        shared_memory = (int*) shmat (segment_id, 0, 0);
        if(shared_memory == (int *)-1){
            perror("shmat()");
            exit(-2);
        }

        printf ("mémoire partagée attachée à l'adresse %p\n", shared_memory);


        /*----------- IMAGE PARAMETERS DROP ------------*/

        for (int i = 0 ; i < img_size ; i++){
            valeur[i] = rand()%256;
            // fprintf("%d ", tab[i]);
        }    
        //Fill in the shared memory
        memcpy(shared_memory, &valeur, img_size*sizeof(&valeur));
        
        printf("\n");
        printf("\n");
        printf("\n"); 

        for(int i = 0 ; i < img_size ; i ++ )
            printf("%d\t", shared_memory[i]);
        printf("\n");

        shmdt(shared_memory);
    }
    return 0;
}
