
#include <stdio.h>
#include <stdlib.h>

//==============================
// Définition du maillon
//==============================
typedef struct Maillon {
    int val;
    struct Maillon* suiv;
} Maillon;

//==============================
// 1. Longueur d’une LLD
//==============================
int longueur(Maillon* L) {
    int c = 0;
    while (L != NULL) {
        c++;
        L = L->suiv;
    }
    return c;
}

//==============================
// Fonction utilitaire : créer un maillon
//==============================
Maillon* nouveauMaillon(int x) {
    Maillon* n = (Maillon*) malloc(sizeof(Maillon));
    n->val = x;
    n->suiv = NULL;
    return n;
}

//==============================
// 2. Ajouter un élément à la fin
//==============================
void ajouterFin(Maillon** L, int x) {
    Maillon* n = nouveauMaillon(x);

    if (*L == NULL) {
        *L = n;
        return;
    }

    Maillon* cur = *L;
    while (cur->suiv != NULL)
        cur = cur->suiv;

    cur->suiv = n;
}

//==============================
// 3. Inserer dans une LLC ordonnée
//==============================
void insererOrdonnee(Maillon** L, int x) {
    Maillon* n = nouveauMaillon(x);

    if (*L == NULL || x < (*L)->val) {
        n->suiv = *L;
        *L = n;
        return;
    }

    Maillon* cur = *L;
    while (cur->suiv != NULL && cur->suiv->val < x)
        cur = cur->suiv;

    n->suiv = cur->suiv;
    cur->suiv = n;
}

//==============================
// 4. Élément avec max occurrences
//==============================
int elementMaxOccurrences(Maillon* L) {
    int maxOcc = 0;
    int maxVal = 0;

    Maillon *i = L, *j;

    while (i != NULL) {
        int occ = 0;
        j = L;

        while (j != NULL) {
            if (j->val == i->val)
                occ++;
            j = j->suiv;
        }

        if (occ > maxOcc) {
            maxOcc = occ;
            maxVal = i->val;
        }

        i = i->suiv;
    }

    return maxVal;
}

//==============================
// 5. Supprimer occurrences (non ordonnée)
//==============================
void supprimerOcc(Maillon** L, int x) {

    while (*L != NULL && (*L)->val == x)
        *L = (*L)->suiv;

    Maillon* cur = *L;

    while (cur != NULL && cur->suiv != NULL) {
        if (cur->suiv->val == x)
            cur->suiv = cur->suiv->suiv;
        else
            cur = cur->suiv;
    }
}

//==============================
// 6. Suppression dans LLC ordonnée
//==============================
void supprimerOccOrdonnee(Maillon** L, int x) {

    while (*L != NULL && (*L)->val == x)
        *L = (*L)->suiv;

    if (*L == NULL) return;

    Maillon* cur = *L;
    while (cur->suiv != NULL && cur->suiv->val <= x) {
        if (cur->suiv->val == x)
            cur->suiv = cur->suiv->suiv;
        else
            cur = cur->suiv;
    }
}

//==============================
// 7. Fusion listes non ordonnées
//==============================
Maillon* fusionNonOrdonnees(Maillon* L1, Maillon* L2) {
    Maillon* L3 = NULL;

    Maillon* cur = L1;
    while (cur != NULL) {
        ajouterFin(&L3, cur->val);
        cur = cur->suiv;
    }

    cur = L2;
    while (cur != NULL) {
        ajouterFin(&L3, cur->val);
        cur = cur->suiv;
    }

    return L3;
}

//==============================
// 8. Fusion listes ordonnées
//==============================
Maillon* fusionOrdonnees(Maillon* L1, Maillon* L2) {
    Maillon* L3 = NULL;

    while (L1 != NULL && L2 != NULL) {
        if (L1->val <= L2->val) {
            ajouterFin(&L3, L1->val);
            L1 = L1->suiv;
        }
        else {
            ajouterFin(&L3, L2->val);
            L2 = L2->suiv;
        }
    }

    while (L1 != NULL) {
        ajouterFin(&L3, L1->val);
        L1 = L1->suiv;
    }
    while (L2 != NULL) {
        ajouterFin(&L3, L2->val);
        L2 = L2->suiv;
    }

    return L3;
}



//==============================
// Affichage de liste
//==============================
void afficher(Maillon* L) {
    while (L != NULL) {
        printf("%d -> ", L->val);
        L = L->suiv;
    }
    printf("NULL\n");
}

    //==============================
   // MAIN
  //==============================
    int main() {

    Maillon* L1 = NULL;
    Maillon* L2 = NULL;

    printf("=== Tests des fonctions ===\n\n");

    // Test ajout fin
    ajouterFin(&L1, 10);
    ajouterFin(&L1, 20);
    ajouterFin(&L1, 30);
    printf("L1 après ajout fin : ");
    afficher(L1);

    // Test insertion ordonnée
    insererOrdonnee(&L2, 40);
    insererOrdonnee(&L2, 50);
    insererOrdonnee(&L2, 60);
    insererOrdonnee(&L2, 40);
    printf("L2 (ordonnée) : ");
    afficher(L2);

    // Longueur
    printf("Longueur L1 : %d\n", longueur(L1));
    printf("Longueur L2 : %d\n", longueur(L2));
    // Max occurrences
    printf("Valeur la plus fréquente dans L2 : %d\n", elementMaxOccurrences(L2));

    // Suppression occurrences (non ordonnée)
    supprimerOcc(&L1, 10);
    printf("L1 après suppression de 10 : ");
    afficher(L1);

    // Suppression occurrences (ordonnée)
    supprimerOccOrdonnee(&L2, 50);
    printf("L2 après suppression de 50 : ");
    afficher(L2);

    // Fusion non ordonnée
    Maillon* L3 = fusionNonOrdonnees(L1, L2);
    printf("Fusion non ordonnée L1 + L2 : ");
    afficher(L3);

   // Fusion ordonnée
    Maillon* L4 = fusionOrdonnees(L2, L3);
    printf("Fusion ordonnée L2 + L3 : ");
    afficher(L4);


    return 0;
}
