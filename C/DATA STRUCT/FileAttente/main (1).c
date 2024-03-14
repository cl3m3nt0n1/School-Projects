#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void testEntiers( QUEUE *q)
{

    int i;
    int *a = NULL;

    srand(time(NULL));
    for(i=0; i<50; i++)
    {
        a =(int*)malloc(sizeof(int));
        *a = rand();
        queue_enqueue(q, a);
    }

}

void testChaine( QUEUE *q)
{
    int i;
    char *s;

    for(i=0; i<10; i++)
    {
        s = (char*)malloc(sizeof(char)*100);
        printf("entrer la couleur de la perle a enfiler \n");
        fflush(stdin);
        scanf("%s",s);
        queue_enqueue(q, s);
    }
}

void queue_print_deuxListes(QUEUE *q1, QUEUE *q2) {
    CELL *cour1= q1->first;
    CELL *cour2= q2->first;
    int i;
    for (i=1; i<=queue_size(q1); i++)
    {
        int x1 = (*((int *)(cour1->value)));
         int x2 = (*((int *)(cour2->value)));
        printf(" %3d : %5d \t| %5d\n", i, x1,  x2);
        cour1 = cour1->next ;
        cour2 = cour2->next ;
    }


}

int main()
{
    printf(" ************ Exploration des files d\'attentes en C *************\n");

    QUEUE *q;
    q = queue_create();
    int choix = 4;

    while (choix != 0)
    {
        printf("\n\n Sur quel type de données souhaitez vous travailler ? \n");
        printf("\t\t Init + Aff liste d\'entiers : tapez 1\n");
        printf("\t\t Init + Aff liste de Strings : tapez 2\n");
        printf("\t\t Inverser une liste d'entiers : tapez 3\n");
        printf("\t\t Clone recursif sur liste d'entiers : tapez 4\n");
        printf("\t\t Pour quitter : tapez 0\n\n");

        scanf("%d", &choix);

        switch (choix)
        {
        case 0 :
            printf("Au revoir ...\n");
            break;
        case 1 :
            testEntiers(q);
            queue_print_int(q);
            break;
        case 2 :

            testChaine(q);
            queue_print_string(q);
            break;
        case 3 :

            testEntiers(q);
            queue_print_int(q);
            queue_shift(q);
            printf("Après inversion \n");
            queue_print_int(q);
            break;
        case 4 :
            testEntiers(q);
            QUEUE *q2 ;
            q2 = queue_create();
            queue_clone(q,q2);
            queue_print_deuxListes(q,q2);
            queue_destroy(q2);
            break;


        default :
            printf("Saisie non valide. Recommencez !");
            break;

        }

        queue_destroy(q);
    }
    return 0;
}
