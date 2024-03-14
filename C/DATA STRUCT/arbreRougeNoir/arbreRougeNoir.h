#ifndef ARBREROUGENOIR_H_INCLUDED
#define ARBREROUGENOIR_H_INCLUDED


#define ROUGE 1
#define NOIR 0

// Structure Noeud
// par facilité on rajoute un champ  clef
struct _NOEUD {
    void * valeur;
    int clef;
    int couleur;
    struct _NOEUD *parent;
    struct _NOEUD  *gauche;
    struct _NOEUD  *droit;
};

typedef struct _NOEUD noeud;
typedef struct _NOEUD *pnoeud;
typedef struct _NOEUD *arbre;

arbre creer_noeud ( int , void * );


void detruire_arbre(arbre);

int compter_noeuds(arbre);


arbre inserer(arbre , pnoeud);

void afficher_crois(arbre);
void afficher_croissant(arbre);
void afficherNoeud( pnoeud );

void afficher_struct(arbre);
void afficher_infixe(arbre);


arbre rotation_gauche(arbre, pnoeud );
arbre rotation_droite(arbre, pnoeud );
arbre insererCorrection(arbre , pnoeud );
arbre reOrganiser( arbre , pnoeud );




#endif // ARBREROUGENOIR_H_INCLUDED
