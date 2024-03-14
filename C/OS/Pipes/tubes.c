#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>


#define ERROR -1
#define CHILD 0


/* TODO : Distinguer les zones mémoires du père et des enfants
 *  Etablir quatre tubes, deux pour émission, deux pour réception
 *  Protéger les pipes
 *
 *
 */



int comparateurCroissant ( const void * first, const void * second ) {
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return firstInt - secondInt;
}

int comparateurDecroissant ( const void * first, const void * second ) {
    int firstInt = * (const int *) first;
    int secondInt = * (const int *) second;
    return secondInt - firstInt;
}


int main(int argc, char* argv[])
{
    FILE* file = NULL;
    srand(time (NULL));
    int N, nbValues;
    int *tab = malloc(sizeof(int));
    
    int *aTrierDecroissant = malloc(sizeof(int));
    



    int tube[2], tube2[2];
    int tunnel[2], tunnel2[2];
    
    // Protège ton pipe
    pipe(tube); //pipefd[0] : Lecture du tube, pipefd[1] : écriture du tube
    pipe(tube2);
    pipe(tunnel);
    pipe(tunnel2);

    //Parent
    if(argc == 3 && (atoi(argv[2]) < 256) || atoi(argv[2])>128)
    {
        nbValues = atoi(argv[2]);
        N = atoi(argv[1]);
        int dynamicSize = nbValues*sizeof(int);
        tab = realloc(tab, dynamicSize);
        aTrierDecroissant = realloc(aTrierDecroissant, dynamicSize);


        for(int i = 0; i < N; i++)
            tab[i] = (rand()%N);
    }
    for(int i = 0; i < N ; i++){

        printf("%d \t", tab[i]);
    }
    
    printf("\n \n");
    //Children    

    for(int i = 0 ; i < 2 ; i++){

        switch(fork())
        {
            case ERROR: 
                perror("Child creation process failed.\n");
                exit(-2);
            break;

            case CHILD: 
                close(tube[1]); //L'enfant n'écrira pas.
                // recevoir les datas transmisent par le père
                //qsort() croissant
                //Rouvrir un tube
                //Transmettre les datas au père
                
                if(i == 0){ // Tri croissant
                    int *aTrierCroissant = malloc(sizeof(int)*nbValues);
                    read(tube[0], aTrierCroissant, sizeof(int)*nbValues);
                    qsort(aTrierCroissant, nbValues, sizeof(int), comparateurCroissant);
                    
                    // DEBUG
                    printf("Tri Croissant :\n");
                    for(int j = 0; j < nbValues ; j++){
                        
                        printf("%d\t", aTrierCroissant[j]);
                    }
                    printf("\n");

                    close(tube2[0]);    //Je ne veux pas lire
                    write(tube2[1],aTrierCroissant,sizeof(int)*nbValues);
                    // close(tube2[1]);
                    free(aTrierCroissant);
                }
                    // A faire après avoir ouvert un tube pour bourrer les datas
                    // write(aTrierCroissant, &intBuffer, sizeof(int));

                if(i == 1){    //Tri décroissant
                    
                    read(tube[0], aTrierDecroissant, sizeof(int)*nbValues);
                    qsort(aTrierDecroissant, nbValues, sizeof(int), comparateurDecroissant);

                    for(int j = 0; j < nbValues ; j++);
                        // printf("%d\t", aTrierDecroissant[j]);
                }
                    //Bullshit
                    // write(aTrierDecroissant, &intBuffer, sizeof(int));


            break;

            default: // Parent code

            //Envoyer les données
            // Attendre la fin du processus fils
            // Recevoir les données triées
            // printf()
            // fprintf() dans un fichier
            close(tube[0]); // Le père ne lit pas
            
            write(tube[1], tab, sizeof(int)*nbValues);
            close(tube[1]);
            close(tube2[1]);
            

            int* newTab = malloc(sizeof(int)*nbValues);
            read(tube2[0], newTab,sizeof(int)*nbValues);

            printf("Papa recoit :\n");
            for(int j = 0 ; j < nbValues ; j++)
                printf("%d\t",newTab[j]);
            printf("\n");
            
        }
    }
    free(tab);
    free(aTrierDecroissant);
    return 0;
}