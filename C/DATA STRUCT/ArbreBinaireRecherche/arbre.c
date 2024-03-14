#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct noeud_s{
    int val;
    struct noeud_s * gauche;
    struct noeud_s * droite;

}*noeud_t;

typedef noeud_t arbre_t;

arbre_t cree_arbre(int value, noeud_t left, noeud_t right){

    arbre_t tree = (arbre_t)malloc(sizeof(arbre_t));
    tree->val = value;
    tree->droite = right;
    tree->gauche = left;

    return tree;
}

void detruit_arbre(arbre_t tree){
    if(tree == NULL) return ;//Condition d'arrêt

    detruit_arbre(tree->gauche);
    detruit_arbre(tree->droite);

    free(tree);        //Condition de récursion

}

int nombre_noeuds(arbre_t tree){
    if (tree == NULL) return 0;
    return(1+nombre_noeuds(tree->gauche) + nombre_noeuds(tree->droite));
}

void affiche_arbre(arbre_t tree){   //Affiche valeurs (croissant)

    if(tree != NULL){
        affiche_arbre(tree->gauche);
        printf("%d\t", tree->val);
        affiche_arbre(tree->droite);
    }
}

void affiche_arbre2(arbre_t tree, char* buf){

    char bufferGauche[512] = "";
    char bufferDroite[512] = "";

    if(tree->gauche != NULL)
        affiche_arbre2(tree->gauche, bufferGauche);
    else
        strcpy(bufferGauche, "_\0");

    if(tree->droite != NULL)
        affiche_arbre2(tree->droite, bufferDroite);
    else
        strcpy(bufferDroite, "_\0");

    sprintf(buf, "{%s, %d, %s}", bufferGauche, tree->val, bufferDroite);

}


arbre_t inserer(arbre_t tree,int clef){
    noeud_t node = cree_arbre(clef, NULL, NULL);
    noeud_t x = tree;
    noeud_t y = NULL;

    while(tree != NULL){
        y = x;
        if(clef < x->val )
            x = x->gauche;
        else
            x = x->droite;
    }
    if(y->droite == NULL)
        y->droite = node;
    else y->gauche = node;

    return tree;
}

int main(void)
{
    return 0;
}

