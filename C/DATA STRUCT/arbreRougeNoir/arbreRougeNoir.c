#include <stdlib.h>
#include <stdio.h>
#include "arbreRougeNoir.h"


pnoeud parent(pnoeud x)
{
    return x->parent;
}

pnoeud grandparent(pnoeud x)
{
    pnoeud y = parent(x);
    if (y == NULL)
        return y;
    else
        return parent(y);
}

pnoeud frere(pnoeud x)
{
    pnoeud p = parent(x);
    if (p == NULL)
        return NULL; // Un noeud sans parent n'a pas de frere
    if (x == p->gauche)
        return p->droit;
    else
        return p->gauche;
}

//Renvoie le frère du père
pnoeud oncle(pnoeud x)
{
    pnoeud p = parent(x);
    pnoeud g = grandparent(x);
    if (g == NULL)
        return NULL; // Pas de grand parent, donc pas d'oncle
    return frere(p);
}

/*
    Création d'un arbre

*/
pnoeud creer_noeud ( int clef, void *valeur)
{
    pnoeud chene = malloc (sizeof(struct _NOEUD)) ;
    if (chene != NULL)
    {
        chene->clef = clef;
        chene->valeur = valeur;
        chene->couleur = NOIR;
        chene->parent = NULL;
        chene->gauche = NULL;
        chene->droit = NULL;
    }
    else
    {
        printf("ERR : creer_arbre allocation impossible \n");
    }
    return chene;
}

/*
    destruction de l'arbre
*/
void detruire_arbre(arbre boulot)
{
    if(boulot == NULL)
        return ;
    detruire_arbre(boulot->gauche ) ;
    detruire_arbre(boulot->droit) ;
    free(boulot) ;
}

/*
    compter le nombre de noeuds
*/
int compter_noeuds(arbre frene)
{
    if(frene == NULL)
        return 0 ;
    return (1 + compter_noeuds (frene->gauche) + compter_noeuds(frene->droit));
}

/*
    inserer dans un arbre la valeur donnée, correspondant à la clé donnée, comme fils du noeud donné
    l'algo détermine s'il doit aller à gauche ou à droite du noeud donné
*/
arbre inserer(arbre racine, pnoeud z)
{
    pnoeud x = racine;
    pnoeud y = NULL;
    while( x != NULL ) {
        y = x;
        if ( z->clef < x->clef )
            x = x->gauche ;
        else
            x = x->droit ;
    }
    z->parent = y;
    if (y == NULL)
        racine = z;
    else  {
        if (z->clef < y->clef)
            y->gauche = z ;
        else
            y->droit = z ;
    }
    z->gauche = NULL;
    z->droit = NULL;
    z->couleur = ROUGE;
    racine = reOrganiser(racine, z);
    return racine;
}



/*
    Affichage de l'arbre tel qu'il est stocké : arbre_gauche, racine, arbre_droit

    Pour afficher la valeur il faudra programmer une fonction afficher_valeur dans le type de données manipulées.
*/
void afficher_struct(arbre aulne)
{
    if(aulne == NULL)
        printf("_");
    else
    {
        printf("{") ;
        afficher_struct(aulne->gauche);
        printf(", %d ", aulne->clef);
        if (aulne->couleur == ROUGE)
            printf(" ROUGE , ");
        else
            printf(" NOIR , ");

        afficher_struct(aulne->droit) ;
        printf("}") ;
    }
}

void afficher_infixe(arbre aulne)
{
    afficher_struct(aulne) ;
    printf("\n");
}





arbre rotation_gauche(arbre racine, pnoeud x)
{
    pnoeud y = x->droit ;
    x->droit = y->gauche ;
    if (y->gauche != NULL)
        y->gauche->parent = x;
    y->parent = x->parent ;
    if(x->parent == NULL) {
        racine = y;
    }
    else {
        if ( x == x->parent->gauche)
            x->parent->gauche = y ;
        else
            x->parent->droit = y ;
    }
    y->gauche = x ;
    x->parent = y;
    return racine;
}


arbre rotation_droite(arbre racine, pnoeud x)
{
    pnoeud y = x->gauche ;
    x->gauche = y->droit ;

    if (y->droit!=NULL)
        y->droit->parent = x;
    y->parent = x->parent ;
    if(x->parent == NULL)
        racine = y;
    else
    {
        if ( x == x->parent->droit)
            x->parent->droit = y ;
        else
            x->parent->gauche = y ;
    }
    y->droit = x ;
    x->parent = y;
    return racine;
}









arbre reOrganiser( arbre racine, pnoeud n)
{
    while(n != racine && n->parent->couleur == ROUGE )
    {
        if(n->parent == n->parent->parent->gauche)
        {
            pnoeud y = n->parent->parent->droit;
            if ((y==NULL) || (y->couleur == NOIR))
            {
                if(n == n->parent->droit)
                {
                    n = n->parent;
                    racine = rotation_gauche(racine, n);
                }
                n->parent->couleur = NOIR;
                n->parent->parent->couleur = ROUGE;
                racine = rotation_droite(racine, n->parent->parent);

            }
            else
            {
                n->parent->couleur = NOIR;
                y->couleur = NOIR;
                n->parent->parent->couleur = ROUGE;
                n = n->parent->parent;
            }
        }
        else
        {
            pnoeud y = n->parent->parent->gauche;
            if (y==NULL || y->couleur==NOIR)
            {
                if(n == n->parent->gauche)
                {
                    n = n->parent;
                    racine = rotation_droite(racine, n);
                }
                n->parent->couleur = NOIR;
                n->parent->parent->couleur = ROUGE;
                racine = rotation_gauche(racine, n->parent->parent);
            }

            else
            {
                n->parent->couleur = NOIR;
                y->couleur = NOIR;
                n->parent->parent->couleur = ROUGE;
                n = n->parent->parent;
            }

        }
    }
    racine->couleur = NOIR; // la racine est toujours noire
    return racine;
}

