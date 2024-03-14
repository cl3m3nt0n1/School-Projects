#include <stdio.h>
#include <stdlib.h>
#include "arbreRougeNoir.h"



void testArbreRougeNoir()
{
    int N = 6;
    //int t[] = { 2, 5, 9,  12, 13, 15};
    int t[] = {12, 7, 5, 13, 18, 9};

    arbre acacia = NULL;
    pnoeud n;

    for (int j=0; j< N; j++)
    {
        n = creer_noeud(t[j], NULL);
        acacia = inserer(acacia, n);
        afficher_infixe(acacia) ;
    }

    detruire_arbre(acacia);
}

int main()
{
    testArbreRougeNoir();
    return 0;
}
